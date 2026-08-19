#!/bin/bash
set -e # Exit immediately if a command fails

# --- Configuration ---
NEXTCLOUD_USER=
NEXTCLOUD_PASS=

NEXTCLOUD_REMOTE="https://cloud.nextcloud.com/remote.php/dav/files" # Name of configured remote
BASE_REMOTE_PATH="3DPARTY_DEPS"
THDPARTY_DIR="."
LOCAL_BUILD_DIR="./build_output"
TRIPLETS=(
    "x64-linux-dynamic"
    #"arm64-linux"

    #"x64-windows"
    #"arm64-windows"

    #"x64-osx"
    #"arm64-osx"
)

mkdir -p "$LOCAL_BUILD_DIR"

# Dependencies array: NAME|VERSION
DEPS=(
    "cef|5414"
    "libvlc|3.0.18"
    "boost|1.72"
    "qt|5.9.9"
    "v8|8.9"
)

# --- Main Loop ---
for dep_info in "${DEPS[@]}"; do

    IFS="|" read -r NAME VERSION <<< "$dep_info"

    DEP_DIR="${THDPARTY_DIR}/${NAME}"
    BASE_DIR="tools/${VERSION}"

    if [ -e "${DEP_DIR}/${BASE_DIR}/Dockerfile" ]; then
        docker build -t build-base:latest ${DEP_DIR}/${BASE_DIR}
    fi

    for triplet in "${TRIPLETS[@]}"; do

        DOCKER_PATH="${BASE_DIR}/${triplet}"


        if [ ! -d "${DEP_DIR}/${DOCKER_PATH}" ]; then
            continue
        fi

        echo ">>> Building $NAME version $VERSION for $triplet..."

        # 1. Docker Build and Output to host
        # --output type=local,dest=... requires Docker BuildKit
        FILENAME="${NAME}-${VERSION}-${triplet}_binary.tar.bz2"

        docker build \
            --build-arg VERSION=$VERSION \
            --output type=local,dest="${LOCAL_BUILD_DIR}" \
            --target artifacts \
            -t $NAME:$VERSION ${DEP_DIR}/${DOCKER_PATH}

        mv "${LOCAL_BUILD_DIR}/${NAME}_binary.tar.bz2" "${LOCAL_BUILD_DIR}/${FILENAME}"
        
        # Calculate Hash
        NEW_HASH=$(sha512sum "${LOCAL_BUILD_DIR}/${FILENAME}" | awk '{print $1}')
        echo ">>> Hash: $NEW_HASH"

        # 3. Upload to Nextcloud
        REMOTE_FOLDER="${BASE_REMOTE_PATH}/${NAME}/${VERSION}/${triplet}"
        
        echo ">>> Uploading to ${NEXTCLOUD_REMOTE}/${NEXTCLOUD_USER}/${REMOTE_FOLDER}..."
        curl -u "${NEXTCLOUD_USER}:${NEXTCLOUD_PASS}" \
            -X MKCOL "${NEXTCLOUD_REMOTE}/${NEXTCLOUD_USER}/${BASE_REMOTE_PATH}/${NAME}"
        curl -u "${NEXTCLOUD_USER}:${NEXTCLOUD_PASS}" \
            -X MKCOL "${NEXTCLOUD_REMOTE}/${NEXTCLOUD_USER}/${BASE_REMOTE_PATH}/${NAME}/${VERSION}"
        curl -u "${NEXTCLOUD_USER}:${NEXTCLOUD_PASS}" \
            -X MKCOL "${NEXTCLOUD_REMOTE}/${NEXTCLOUD_USER}/${REMOTE_FOLDER}"
        curl -u "${NEXTCLOUD_USER}:${NEXTCLOUD_PASS}" \
            -X DELETE \
            "${NEXTCLOUD_REMOTE}/${NEXTCLOUD_USER}/${REMOTE_FOLDER}/${NAME}_binary.tar.bz2"
        curl -u "${NEXTCLOUD_USER}:${NEXTCLOUD_PASS}" \
            -T "${LOCAL_BUILD_DIR}/${FILENAME}" \
            "${NEXTCLOUD_REMOTE}/${NEXTCLOUD_USER}/${REMOTE_FOLDER}/${NAME}_binary.tar.bz2"

        # 4. Update the local Git repository's hashes.txt
        HASH_FILE="${DEP_DIR}/hashes.txt"
        echo ">>> Updating $HASH_FILE..."
        # Append or update line
        if grep -q "${VERSION}|${triplet}" "$HASH_FILE"; then
            sed -i "s/.*${VERSION}|${triplet}.*/${VERSION}|${triplet}|${NEW_HASH}/" "$HASH_FILE"
        else
            echo "${VERSION}|${triplet}|${NEW_HASH}" >> "$HASH_FILE"
        fi
        
        echo ">>> Finished $NAME."
    done
done

echo ">>> All heavy dependencies built and uploaded."
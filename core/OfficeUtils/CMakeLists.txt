cmake_minimum_required(VERSION 3.10)

function(add_officeutils TARGET OFFICE_UTILS_DIR)

    set(OFFICE_UTILS_SOURCES_DIR "${OFFICE_UTILS_DIR}/src")

    # OfficeUtils.pro
    set(OFFICE_UTILS_SOURCES
        ${OFFICE_UTILS_SOURCES_DIR}/OfficeUtils.cpp
        ${OFFICE_UTILS_SOURCES_DIR}/ZipBuffer.cpp
        ${OFFICE_UTILS_SOURCES_DIR}/ZipUtilsCP.cpp
        
        ${OFFICE_UTILS_SOURCES_DIR}/OfficeUtils.h
        ${OFFICE_UTILS_SOURCES_DIR}/OfficeUtilsCommon.h
        ${OFFICE_UTILS_SOURCES_DIR}/ZipBuffer.h
        ${OFFICE_UTILS_SOURCES_DIR}/ZipFolder.h
        ${OFFICE_UTILS_SOURCES_DIR}/ZipUtilsCP.h

        ${OFFICE_UTILS_SOURCES_DIR}/zlib_addon.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/adler32.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/compress.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/contrib/minizip/ioapi.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/contrib/minizip/ioapibuf.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/contrib/minizip/miniunz.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/contrib/minizip/minizip.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/contrib/minizip/mztools.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/contrib/minizip/unzip.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/contrib/minizip/zip.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/crc32.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/deflate.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/gzclose.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/gzlib.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/gzread.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/gzwrite.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/infback.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/inffast.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/inflate.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/inftrees.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/trees.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/uncompr.c
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/zutil.c

        ${OFFICE_UTILS_SOURCES_DIR}/zlib_addon.h
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/contrib/minizip/crypt.h
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/contrib/minizip/ioapi.h
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/contrib/minizip/ioapibuf.h
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/contrib/minizip/mztools.h
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/contrib/minizip/unzip.h
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/contrib/minizip/zip.h
    )

    target_sources( ${TARGET} PRIVATE ${OFFICE_UTILS_SOURCES} )

    if (WIN32)
        target_sources( ${TARGET} PRIVATE
            ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/contrib/minizip/iowin32.c
        )
    endif()

    target_include_directories( ${TARGET} PRIVATE
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11/contrib/minizip
        ${OFFICE_UTILS_SOURCES_DIR}/zlib-1.2.11
        ${OFFICE_UTILS_SOURCES_DIR}
    )

    if( NOT MSVC )
        target_compile_options( ${TARGET} PRIVATE "SHELL:-include unistd.h")
    endif()
endfunction()

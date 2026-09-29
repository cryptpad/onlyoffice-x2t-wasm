cmake_minimum_required(VERSION 3.10)

project(EpubFile)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../..")

include(${CORE_ROOT_DIR}/common.cmake)

set(EPUB_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

if(NOT TARGET kernel)
    add_subdirectory(${CORE_ROOT_DIR}/Common kernel)
endif()

if(NOT TARGET graphics)
    add_subdirectory(${CORE_ROOT_DIR}/DesktopEditor/graphics/cmake graphics)
endif()

if(NOT TARGET HtmlFile2)
    add_subdirectory(${CORE_ROOT_DIR}/HtmlFile2 HtmlFile2)
endif()

add_library(EpubFile SHARED
    ${EPUB_ROOT_DIR}/src/CBookContentItem.cpp
    ${EPUB_ROOT_DIR}/src/CBookInfo.cpp
    ${EPUB_ROOT_DIR}/src/CBookItem.cpp
    ${EPUB_ROOT_DIR}/src/CBookToc.cpp
    ${EPUB_ROOT_DIR}/src/CEpubFile.cpp

    ${EPUB_ROOT_DIR}/CEpubFile.h
    ${EPUB_ROOT_DIR}/src/CBookToc.h
    ${EPUB_ROOT_DIR}/src/CBookContentItem.h
    ${EPUB_ROOT_DIR}/src/CBookItem.h
    ${EPUB_ROOT_DIR}/src/CBookInfo.h
    ${EPUB_ROOT_DIR}/src/EpubFile_global.h
)

set_default_options(EpubFile)

target_compile_definitions(EpubFile PRIVATE
    EPUBFILE_USE_DYNAMIC_LIBRARY
)

target_include_directories(EpubFile PRIVATE
    ${EPUB_ROOT_DIR}
)

# dynamic libs
target_link_libraries(EpubFile PUBLIC
    kernel
    graphics
    HtmlFile2
)

copy_artifacts_to_folder("EpubFile" "${EO_CORE_OUTPUT_DIR}")

declare_victory( EpubFile )

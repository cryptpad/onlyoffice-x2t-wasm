cmake_minimum_required(VERSION 3.5)

project(EpubFile LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT TARGET HtmlFile2)
    add_subdirectory(${CORE_ROOT_DIR}/HtmlFile2 HtmlFile2)
endif()

if(NOT TARGET graphics)
    add_subdirectory(${CORE_ROOT_DIR}/DesktopEditor/graphics/cmake graphics)
endif()

if(NOT TARGET kernel)
    add_subdirectory(${CORE_ROOT_DIR}/Common kernel)
endif()

add_library(EpubFile SHARED
  src/CEpubFile.cpp
  src/CBookToc.cpp
  src/CBookContentItem.cpp
  src/CBookItem.cpp
  src/CBookInfo.cpp
)

target_compile_definitions(EpubFile PRIVATE EPUBFILE_LIBRARY)

copy_artifacts_to_folder("EpubFile" "${EO_CORE_OUTPUT_DIR}")
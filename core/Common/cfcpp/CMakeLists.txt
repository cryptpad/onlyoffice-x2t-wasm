cmake_minimum_required(VERSION 3.10)

project(CompoundFileLib)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../..")

include(${CORE_ROOT_DIR}/common.cmake)

add_library(CompoundFileLib STATIC
    RBTree/rbtree.cpp
    Stream/fstream_utils.cpp
    Stream/stream_utils.cpp
    cfitem.cpp
    cfstorage.cpp
    cfstream.cpp
    compoundfile.cpp
    directoryentry.cpp
    header.cpp
    sector.cpp
    sectorcollection.cpp
    streamrw.cpp
    streamview.cpp

    RBTree/action.h
    RBTree/irbnode.h
    RBTree/rbtree.h
    RBTree/rbtreeexception.h
    Stream/fstream_utils.h
    Stream/fstream_wrapper.h
    Stream/stream_utils.h
    cfexception.h
    cfitem.h
    cfstorage.h
    cfstream.h
    compoundfile.h
    compoundfile_impl.h
    directoryentry.h
    event.h
    guid.h
    header.h
    idirectoryentry.h
    sector.h
    sectorcollection.h
    slist.h
    Stream/stream.h
    streamrw.h
    streamview.h
    svector.h
)

set_default_options(CompoundFileLib)

set_property(TARGET CompoundFileLib PROPERTY POSITION_INDEPENDENT_CODE ON)

declare_victory( CompoundFileLib )

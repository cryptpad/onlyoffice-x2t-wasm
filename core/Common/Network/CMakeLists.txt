cmake_minimum_required(VERSION 3.10)

project(kernel_network)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../..")

include(${CORE_ROOT_DIR}/common.cmake)

if(NOT TARGET kernel)
    add_subdirectory(${CORE_ROOT_DIR}/Common kernel)
endif()

set(SOCKETIO_INSTALL_DIR "${EO_CORE_3RD_PARTY_INSTALL_DIR}/socketio")
get_filename_component(SOCKETIO_INSTALL_DIR_ABS "${SOCKETIO_INSTALL_DIR}" ABSOLUTE)

add_library(kernel_network SHARED
    ${SOCKETIO_INSTALL_DIR}/src_no_tls/internal/sio_client_impl.cpp
    ${SOCKETIO_INSTALL_DIR}/src_no_tls/internal/sio_client_impl.h
    ${SOCKETIO_INSTALL_DIR}/src_no_tls/internal/sio_packet.cpp
    ${SOCKETIO_INSTALL_DIR}/src_no_tls/internal/sio_packet.h
    ${SOCKETIO_INSTALL_DIR}/src_no_tls/sio_client.cpp
    ${SOCKETIO_INSTALL_DIR}/src_no_tls/sio_client.h
    ${SOCKETIO_INSTALL_DIR}/src_no_tls/sio_message.h
    ${SOCKETIO_INSTALL_DIR}/src_no_tls/sio_socket.cpp
    ${SOCKETIO_INSTALL_DIR}/src_no_tls/sio_socket.h
    ${SOCKETIO_INSTALL_DIR}/src/internal/sio_client_impl.cpp
    ${SOCKETIO_INSTALL_DIR}/src/internal/sio_client_impl.h
    ${SOCKETIO_INSTALL_DIR}/src/internal/sio_packet.cpp
    ${SOCKETIO_INSTALL_DIR}/src/internal/sio_packet.h
    ${SOCKETIO_INSTALL_DIR}/src/sio_client.cpp
    ${SOCKETIO_INSTALL_DIR}/src/sio_client.h
    ${SOCKETIO_INSTALL_DIR}/src/sio_message.h
    ${SOCKETIO_INSTALL_DIR}/src/sio_socket.cpp
    ${SOCKETIO_INSTALL_DIR}/src/sio_socket.h

    WebSocket/src/managerWebSocket.cpp
    WebSocket/src/socketio/socketio_internal.cpp

    WebSocket/include/websocket.h
	WebSocket/src/websocketbase.h
    WebSocket/src/socketio/socketio_internal.h
    WebSocket/src/socketio/socketio_internal_private.h
    WebSocket/src/socketio/socketio_internal_private_no_tls.h

    # filetransporter.pri
    ${CMAKE_CURRENT_SOURCE_DIR}/FileTransporter/src/FileTransporter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/FileTransporter/src/Session.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/FileTransporter/src/manager.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/FileTransporter/include/FileTransporter.h
	${CMAKE_CURRENT_SOURCE_DIR}/FileTransporter/include/manager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FileTransporter/src/FileTransporter_private.h
	${CMAKE_CURRENT_SOURCE_DIR}/FileTransporter/src/transport_external.h
	${CMAKE_CURRENT_SOURCE_DIR}/FileTransporter/src/Session.h
)

# filetransporter.pri
if( MSVC )
    target_sources( kernel_network PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/FileTransporter/src/FileTransporter_win.cpp
    )
else()
    target_sources( kernel_network PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/FileTransporter/src/FileTransporter_curl.cpp
    )
endif()

set_default_options(kernel_network)

if( MSVC )
    set_source_files_properties(
        ${CMAKE_CURRENT_SOURCE_DIR}/FileTransporter/src/FileTransporter_win.cpp
        PROPERTIES
            COMPILE_DEFINITIONS "UNICODE;_UNICODE"
    )
endif()

target_compile_definitions(kernel_network PRIVATE
    KERNEL_USE_DYNAMIC_LIBRARY_BUILDING
    BOOST_DATE_TIME_NO_LIB
    BOOST_REGEX_NO_LIB
    ASIO_STANDALONE
    _WEBSOCKETPP_CPP11_STL_
    _WEBSOCKETPP_CPP11_FUNCTIONAL_
    _WEBSOCKETPP_CPP11_TYPE_TRAITS_
    _WEBSOCKETPP_CPP11_CHRONO_
    SIO_TLS=1
    SIO_TLS_NO=0
    USE_IOWEBSOCKET
)

if(UNIX)
    target_compile_definitions(kernel_network PRIVATE
        USE_EXTERNAL_TRANSPORT
    )
endif()

target_include_directories(kernel_network PRIVATE
    ${OPENSSL_INSTALL_DIR_ABS}/include
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}
    ${SOCKETIO_INSTALL_DIR_ABS}/lib/websocketpp
    ${SOCKETIO_INSTALL_DIR_ABS}/lib/rapidjson/include
    ${SOCKETIO_INSTALL_DIR_ABS}/lib/asio/asio/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/FileTransporter
)

target_link_libraries(kernel_network PRIVATE
    ${OPENSSL_LIBSSL}
    ${OPENSSL_LIBCRYPTO}
)

target_link_libraries(kernel_network PUBLIC
    kernel
)

if( UNIX )
    target_link_libraries(kernel_network PUBLIC
        pthread
    )
endif()

if( MSVC )
    target_link_libraries(kernel_network PUBLIC
        Crypt32
        Advapi32
        urlmon
        Shell32
    )
endif()

copy_artifacts_to_folder("kernel_network" "${EO_CORE_OUTPUT_DIR}")

declare_victory( kernel_network )

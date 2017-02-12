cmake_minimum_required(VERSION 3.6)
project(smssender)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp gateway.cpp gateway.h smsc.cpp smsc.h)
add_executable(smssender ${SOURCE_FILES})

find_package (OpenSSL)

FIND_PACKAGE(CURL)
IF(CURL_FOUND)
    INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR})
    SET(requiredlibs ${requiredlibs} ${CURL_LIBRARIES} )
    target_link_libraries(smssender curl)
ELSE(CURL_FOUND)
    MESSAGE(FATAL_ERROR "Could not find the CURL library and development files.")
ENDIF(CURL_FOUND)

target_link_libraries (smssender ${OPENSSL_LIBRARIES})

if(APPLE)
    message(STATUS ">>> Apple")
    include_directories(/usr/local/opt/openssl/include/)
endif()

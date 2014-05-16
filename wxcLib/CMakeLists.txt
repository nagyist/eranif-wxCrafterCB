cmake_minimum_required(VERSION 2.8)

if ( WX_TOOL )
    # /usr/lib/x86_64-linux-gnu/wx/config/gtk2-unicode-release-2.8
    set( wxWidgets_CONFIG_EXECUTABLE ${WX_TOOL})
endif()

project(wxcLib)

## Add wxWidgets
find_package(wxWidgets COMPONENTS std REQUIRED)
include( "${wxWidgets_USE_FILE}" )

## Print the wx version
execute_process(COMMAND ${wxWidgets_CONFIG_EXECUTABLE} --version OUTPUT_VARIABLE WX_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
string(SUBSTRING "${WX_VERSION}" "0" "1" wxMAJOR_VERSION)
string(SUBSTRING "${WX_VERSION}" "2" "1" wxMINOR_VERSION)
string(SUBSTRING "${WX_VERSION}" "4" "1" wxRELEASE_NUMBER)

message("-- wxWidgets used is ${wxMAJOR_VERSION}.${wxMINOR_VERSION}.${wxRELEASE_NUMBER}")

## Use all source files
FILE(GLOB WXCLIB_SRCS "*.cpp")

if ( UNIX )
    add_definitions(-fPIC)
endif()

include_directories(${CMAKE_SOURCE_DIR})
add_library(wxcLib STATIC ${WXCLIB_SRCS})

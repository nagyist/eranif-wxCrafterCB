cmake_minimum_required(VERSION 2.8)
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" )
project(wxCrafterCB)
add_subdirectory(wxcLib)

## Try to locate codeblocks package is installed
if ( UNIX )
    find_library(LIB_CODEBLOCKS
                 NAMES 
                    libcodeblocks.so
                 HINTS  
                     /usr/lib 
                     /usr/local/lib)

    find_path(CODEBLOCKS_SDK_H NAMES sdk.h
              HINTS 
              /usr/include/codeblocks
              /usr/local/include/codeblocks
              )
              
    if ( LIB_CODEBLOCKS STREQUAL "LIB_CODEBLOCKS-NOTFOUND" OR CODEBLOCKS_SDK_H STREQUAL "STREQUAL-NOTFOUND" )
        message(FATAL_ERROR "**** Please install codeblocks-dev package. Could not locate codeblocks/sdk.h")
    else()
        message("-- Adding include directory ${CODEBLOCKS_SDK_H}")
        message("-- Adding include directory ${CMAKE_SOURCE_DIR}")
        include_directories(${CODEBLOCKS_SDK_H})
        include_directories(${CMAKE_SOURCE_DIR})
        add_definitions(-DBUILDING_PLUGIN)
    endif()
else()
    # Windows
    if( NOT DEFINED ENV{CB_SRC_DIR})
        message(FATAL_ERROR "**** Please define the environment variable CB_SRC_DIR to point to CodeBlocks source directory")
    else()
        message("-- Adding include directory ${CODEBLOCKS_SDK_H}")
        message("-- Adding include directory ${CMAKE_SOURCE_DIR}")
        include_directories($ENV{CB_SRC_DIR})
        include_directories(${CMAKE_SOURCE_DIR})
        add_definitions(-DBUILDING_PLUGIN)
    endif()
endif()

if ( UNIX )
    add_definitions(-Ulinux)
    add_definitions(-Uunix)
endif()

## Add wxWidgets
set( wxWidgets_CONFIG_EXECUTABLE /usr/lib/x86_64-linux-gnu/wx/config/gtk2-unicode-release-2.8)
find_package(wxWidgets COMPONENTS std REQUIRED)
include( "${wxWidgets_USE_FILE}" )

FILE(GLOB PLUGIN_SRCS "*.cpp")
add_library(wxCrafterCB SHARED ${PLUGIN_SRCS})
target_link_libraries(wxCrafterCB wxcLib)
target_link_libraries(wxCrafterCB ${wxWidgets_LIBRARIES})

## Create the resource zip file
add_custom_command(TARGET wxCrafterCB
    COMMAND zip -j ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/wxCrafterCB.zip ${CMAKE_SOURCE_DIR}/manifest.xml ${CMAKE_SOURCE_DIR}/Resources/Templates/wxFrameApp/* 
    POST_BUILD
)

if ( UNIX AND NOT APPLE )
    install(TARGETS wxCrafterCB DESTINATION /usr/lib/codeblocks/plugins)
    install(FILES ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/wxCrafterCB.zip DESTINATION /usr/share/codeblocks)
endif()

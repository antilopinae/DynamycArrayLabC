cmake_minimum_required(VERSION 3.6)
project(untitled)

set(CMAKE_C_STANDARD 11)

#Set your directories.  The dot representes the root application folder.
#Thus my the path to my domain folder:
set(APP_DOMAIN ./lib)
set(SRC_DOMAIN ./lib/src)

#Include the directories and now your cpp files will recognize your headers
include_directories(${APP_DOMAIN})
include_directories(${SRC_DOMAIN})

set(
        SOURCE_FILES
        main.c
        ${APP_DOMAIN}/dynamic_array.h
        ${SRC_DOMAIN}/dynamic_array.c

        ${APP_DOMAIN}/debug.h
        ${SRC_DOMAIN}/debug.c

        ${APP_DOMAIN}/test.h
        ${SRC_DOMAIN}/test.c

        ${APP_DOMAIN}/error.h
        ${SRC_DOMAIN}/error.c
)
add_executable(untitled ${SOURCE_FILES})
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT (sikuli)

SET(CMAKE_VERBOSE_MAKEFILE ON)

SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/")
INCLUDE(${CMAKE_MODULE_PATH}/common.cmake)

ADD_SUBDIRECTORY(sikuli-script)
ADD_SUBDIRECTORY(sikuli-ide)

INCLUDE(CTest)

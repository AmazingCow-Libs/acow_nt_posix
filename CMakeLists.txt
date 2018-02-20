##~---------------------------------------------------------------------------##
##                     _______  _______  _______  _     _                     ##
##                    |   _   ||       ||       || | _ | |                    ##
##                    |  |_|  ||       ||   _   || || || |                    ##
##                    |       ||       ||  | |  ||       |                    ##
##                    |       ||      _||  |_|  ||       |                    ##
##                    |   _   ||     |_ |       ||   _   |                    ##
##                    |__| |__||_______||_______||__| |__|                    ##
##                             www.amazingcow.com                             ##
##  File      : CMakeLists.txt                                                ##
##  Project   : acow_nt_posix                                                 ##
##  Date      : Feb 19, 2018                                                  ##
##  License   : GPLv3                                                         ##
##  Author    : n2omatt <n2omatt@amazingcow.com>                              ##
##  Copyright : AmazingCow - 2018                                             ##
##                                                                            ##
##  Description :                                                             ##
##                                                                            ##
##---------------------------------------------------------------------------~##

cmake_minimum_required(VERSION 3.5)

##------------------------------------------------------------------------------
## Project Settings.
project(acow_nt_posix)


##------------------------------------------------------------------------------
## Sources.
add_library(acow_nt_posix
    acow/src/win32/utsname.cpp
)


##------------------------------------------------------------------------------
## Include directories.
target_include_directories(acow_nt_posix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


##------------------------------------------------------------------------------
## Dependencies.
target_link_libraries(acow_nt_posix LINK_PUBLIC acow_cpp_goodies)

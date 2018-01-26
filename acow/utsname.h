//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : utsname.h                                                     //
//  Project   : acow_nt_posix                                                 //
//  Date      : Jan 25, 2018                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2018                                             //
//                                                                            //
//  Description :                                                             //
//  Code taken from...                                                        //
//  Linux 4.4.0-43-Microsoft #1-Microsoft Wed Dec 31 14:42:53 PST 2014 x86_64 //
//  /usr/include/sys/utsname.h                                                //
//---------------------------------------------------------------------------~//

#pragma once

// Amzing Cow Libs
#include "acow/cpp_goodies.h"

#if (ACOW_OS_IS_WINDOWS)

//----------------------------------------------------------------------------//
// Defines                                                                    //
//----------------------------------------------------------------------------//
/* Structure describing the system and machine.  */
#define _UTSNAME_LENGTH 255

#ifndef _UTSNAME_SYSNAME_LENGTH
    #define _UTSNAME_SYSNAME_LENGTH _UTSNAME_LENGTH
#endif

#ifndef _UTSNAME_NODENAME_LENGTH
    #define _UTSNAME_NODENAME_LENGTH _UTSNAME_LENGTH
#endif

#ifndef _UTSNAME_RELEASE_LENGTH
    #define _UTSNAME_RELEASE_LENGTH _UTSNAME_LENGTH
#endif

#ifndef _UTSNAME_VERSION_LENGTH
    #define _UTSNAME_VERSION_LENGTH _UTSNAME_LENGTH
#endif

#ifndef _UTSNAME_MACHINE_LENGTH
    #define _UTSNAME_MACHINE_LENGTH _UTSNAME_LENGTH
#endif

//----------------------------------------------------------------------------//
// Types                                                                      //
//----------------------------------------------------------------------------//
struct utsname
{
    /* Name of the implementation of the operating system.  */
    char sysname[_UTSNAME_SYSNAME_LENGTH];
    /* Name of this node on the network.  */
    char nodename[_UTSNAME_NODENAME_LENGTH];
    /* Current release level of this implementation.  */
    char release[_UTSNAME_RELEASE_LENGTH];
    /* Current version level of this release.  */
    char version[_UTSNAME_VERSION_LENGTH];
    /* Name of the hardware type the system is running on.  */
    char machine[_UTSNAME_MACHINE_LENGTH];
};

//----------------------------------------------------------------------------//
// Functions                                                                  //
//----------------------------------------------------------------------------//
int uname(struct utsname *name);

#else // #if (ACOW_OS_IS_WINDOWS)

    #include <sys/utsname.h>
#endif // #if (ACOW_OS_IS_WINDOWS)
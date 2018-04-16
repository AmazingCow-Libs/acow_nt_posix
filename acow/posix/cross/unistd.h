//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : unistd.h                                                      //
//  Project   : acow_nt_posix                                                 //
//  Date      : Jan 25, 2018                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2018                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// Amazing Cow Libs
#include "acow/cpp_goodies.h"


// OS isn't Windows - Assuming that it'll work on other unices.
#if (!ACOW_OS_IS_WINDOWS)
    //--------------------------------------------------------------------------
    // Just include the default header.
    #include <unistd.h>

// OS is Windows.
#else
    //--------------------------------------------------------------------------
    // Headers.
    #include <io.h>

    //--------------------------------------------------------------------------
    // Defines.
    #define isatty _isatty

#endif // #if (!ACOW_OS_IS_WINDOWS)
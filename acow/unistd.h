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


#if (ACOW_OS_IS_WINDOWS)
    //--------------------------------------------------------------------------
    // Headers.
    #include <io.h>

    #define isatty _isatty

#else
    //--------------------------------------------------------------------------
    // Just include the default header
    #include <unistd.h>

#endif // #if (ACOW_OS_IS_WINDOWS)
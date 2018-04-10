//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : utsname.cpp                                                   //
//  Project   : acow_nt_posix                                                 //
//  Date      : Jan 25, 2018                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2018                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// Header
#include "../../utsname.h"

#if (ACOW_OS_IS_WINDOWS)

// std
#include <string.h>
// Windows
#include <WinSock2.h> // This must come before Windows.h
#define WINDOWS_LEAN_AND_MEAN   
#define _WINSOCKAPI_
#include <Windows.h>
// Amazing Cow Libs
#include "CoreAssert/CoreAssert.h"

//------------------------------------------------------------------------------
// Auto "link" the WinSock2 lib.
#pragma comment(lib, "Ws2_32.lib")


//----------------------------------------------------------------------------//
// Win Api Functions                                                          //
//----------------------------------------------------------------------------//
// COWNOTE(n2omatt): Copied from codeproject without any shame :D
//   https://www.codeproject.com/Messages/5080848/A-much-easier-and-shorter-code.aspx
RTL_OSVERSIONINFOEXW* GetOsVersion() noexcept
{
    static bool                 s_init = false;
    static RTL_OSVERSIONINFOEXW s_info = {0};

    //--------------------------------------------------------------------------
    // A little optimization... We only need query once...
    if(s_init)
        return &s_info;

    typedef LONG (WINAPI* tRtlGetVersion)(RTL_OSVERSIONINFOEXW*);

    memset(&s_info, 0, sizeof(RTL_OSVERSIONINFOEXW));
    s_info.dwOSVersionInfoSize = sizeof(RTL_OSVERSIONINFOEXW);

    HMODULE        h_NtDll         = GetModuleHandleW(L"ntdll.dll");
    tRtlGetVersion f_RtlGetVersion = (tRtlGetVersion)GetProcAddress(
        h_NtDll,
        "RtlGetVersion"
    );
    //COWTODO(n2omatt): handle errors...

    s_init = (f_RtlGetVersion(&s_info) == 0);
    return &s_info;
}


//----------------------------------------------------------------------------//
// Helper Functions                                                           //
//----------------------------------------------------------------------------//
std::string get_processor_arch(WORD processorType) noexcept
{
    switch(processorType)
    {
        case PROCESSOR_ARCHITECTURE_INTEL          : return  "INTEL";
        case PROCESSOR_ARCHITECTURE_MIPS           : return  "MIPS";
        case PROCESSOR_ARCHITECTURE_ALPHA          : return  "ALPHA";
        case PROCESSOR_ARCHITECTURE_PPC            : return  "PPC";
        case PROCESSOR_ARCHITECTURE_SHX            : return  "SHX";
        case PROCESSOR_ARCHITECTURE_ARM            : return  "ARM";
        case PROCESSOR_ARCHITECTURE_IA64           : return  "IA64";
        case PROCESSOR_ARCHITECTURE_ALPHA64        : return  "ALPHA64";
        case PROCESSOR_ARCHITECTURE_MSIL           : return  "MSIL";
        case PROCESSOR_ARCHITECTURE_AMD64          : return  "AMD64";
        case PROCESSOR_ARCHITECTURE_IA32_ON_WIN64  : return  "IA32_ON_WIN64";
        case PROCESSOR_ARCHITECTURE_NEUTRAL        : return  "NEUTRAL";
        case PROCESSOR_ARCHITECTURE_ARM64          : return  "ARM64";
        case PROCESSOR_ARCHITECTURE_ARM32_ON_WIN64 : return  "ARM32_ON_WIN64";
        case PROCESSOR_ARCHITECTURE_IA32_ON_ARM64  : return  "IA32_ON_ARM64";
        default:
            return "";
    }
}

std::string get_processor_type(DWORD processorType) noexcept
{
    switch(processorType)
    {
        case PROCESSOR_INTEL_386     : return "386";
        case PROCESSOR_INTEL_486     : return "486";
        case PROCESSOR_INTEL_PENTIUM : return "PENTIUM";
        case PROCESSOR_INTEL_IA64    : return "IA64";
        case PROCESSOR_AMD_X8664     : return "X8664";
        case PROCESSOR_MIPS_R4000    : return "R4000";
        case PROCESSOR_ALPHA_21064   : return "21064";
        case PROCESSOR_PPC_601       : return "601";
        case PROCESSOR_PPC_603       : return "603";
        case PROCESSOR_PPC_604       : return "604";
        case PROCESSOR_PPC_620       : return "620";
        case PROCESSOR_HITACHI_SH3   : return "SH3";
        case PROCESSOR_HITACHI_SH3E  : return "SH3E";
        case PROCESSOR_HITACHI_SH4   : return "SH4";
        case PROCESSOR_MOTOROLA_821  : return "821";
        case PROCESSOR_SHx_SH3       : return "SH3";
        case PROCESSOR_SHx_SH4       : return "SH4";
        case PROCESSOR_STRONGARM     : return "STRONGARM";
        case PROCESSOR_ARM720        : return "720";
        case PROCESSOR_ARM820        : return "820";
        case PROCESSOR_ARM920        : return "920";
        case PROCESSOR_ARM_7TDMI     : return "7TDMI";
        case PROCESSOR_OPTIL         : return "OPTIL";
        default:
            return "";
    }
}


//----------------------------------------------------------------------------//
// Setter Functions                                                           //
//----------------------------------------------------------------------------//
int set_sysname(utsname *pName) noexcept
{
    strcpy(pName->sysname, "Windows");
    return 0;
}

int set_nodename(utsname *pName) noexcept
{
    if(gethostname(pName->nodename, _UTSNAME_NODENAME_LENGTH) != 0)
    {
        if(WSAGetLastError() == WSANOTINITIALISED)
        {
            WSADATA WSAData;
            WSAStartup(MAKEWORD(1, 0), &WSAData);

            gethostname(pName->nodename, _UTSNAME_NODENAME_LENGTH);
            WSACleanup();
        }
        else
        {
            return WSAGetLastError();
        }
    }

    return 0;
}

int set_release(utsname *pName) noexcept
{
    auto p_info = GetOsVersion();
    sprintf(
        pName->release,
        "%d.%d.%d",
        p_info->dwMajorVersion,
        p_info->dwMinorVersion,
        p_info->dwBuildNumber
    );

    return 0;
}

int set_version(utsname *pName) noexcept
{
    auto p_info = GetOsVersion();
    sprintf(
        pName->version,
        "%d.%d.%d.%d.%d",
        p_info->dwMajorVersion,
        p_info->dwMinorVersion,
        p_info->dwBuildNumber,
        p_info->wServicePackMajor,
        p_info->wServicePackMinor
    );

    return 0;
}

int set_machine(utsname *pName) noexcept
{
    SYSTEM_INFO system_info = {};
    GetSystemInfo(&system_info);

    sprintf(
        pName->machine,
        "%s %s",
        get_processor_arch(system_info.wProcessorArchitecture).c_str(),
        get_processor_type(system_info.dwProcessorType       ).c_str()
    );

    return 0;
}


//----------------------------------------------------------------------------//
// Implementation                                                             //
//----------------------------------------------------------------------------//
#define RETURN_IF_FAIL(_value_) do { if(_value_) return _value_; } while(0)

int uname(struct utsname *pName) noexcept
{
    COREASSERT_ASSERT(pName, "pName can't be null");

    RETURN_IF_FAIL(set_sysname (pName));
    RETURN_IF_FAIL(set_nodename(pName));
    RETURN_IF_FAIL(set_release (pName));
    RETURN_IF_FAIL(set_version (pName));
    RETURN_IF_FAIL(set_machine (pName));

    return 0;
}


#endif // #if (ACOW_OS_IS_WINDOWS)

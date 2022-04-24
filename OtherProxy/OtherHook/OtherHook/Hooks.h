#pragma once

#include <cstdio>
#include <string>
#include <iostream>

struct Packet {
    void* thisptr;
    char* buffer;
    int32_t a3;
    int32_t* a4;
};

typedef int32_t(__stdcall *_HttpRequest)(int32_t arg1, std::string arg2, float arg3, float arg4, float arg5, int32_t arg6, int32_t arg7, int32_t arg8, int32_t arg9, int32_t arg10, int32_t arg11, int32_t arg12);
_HttpRequest httpRequestOriginal;

typedef int32_t*(__stdcall *_SendRequest)(int32_t*, char*);
_SendRequest sendRequestOriginal;

typedef void(__thiscall* _SendPacket)(int* thisptr, char* a2, int a3, int* a4);
_SendPacket sendPacketOriginal;

int32_t __stdcall httpRequest(int32_t arg1, std::string arg2, float arg3, float arg4, float arg5, int32_t arg6, int32_t arg7, int32_t arg8, int32_t arg9, int32_t arg10, int32_t arg11, int32_t arg12)
{
    std::cout << arg2 << "\n";
    return httpRequestOriginal(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12);
}

int32_t* __stdcall sendRequest(int32_t* __this, char* a2)
{
    std::cout << std::hex << __this << "\n";
   return sendRequestOriginal(__this, a2);
}

void __fastcall sendPacket(int* ecx, char* a2, int a3, int* a4)
{
    std::cout << std::hex << ecx << "\n";
    return sendPacketOriginal(ecx, a2, a3, a4);
}

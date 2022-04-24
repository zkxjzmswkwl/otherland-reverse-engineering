#include "pch.h"
#include "MinHook.h"
#include "Hooks.h"

uintptr_t memoryBase      = (uintptr_t)GetModuleHandleA("Otherland-Shipping.exe");
uintptr_t sendPacketLoc   = memoryBase + 0xAF0300;
uintptr_t sendRequestLoc  = memoryBase + 0x3e70;
uintptr_t httpLoc         = memoryBase + 0x1187400;


uintptr_t WINAPI vroomVroom(HMODULE hModule)
{
    // Spawn console window
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "Base module: " << std::hex << memoryBase << "\n";
    std::cout << std::hex << sendPacketLoc << "\n";

    MH_Initialize();

    // Create and enable hooks
    auto sendPacketHook = MH_CreateHook((LPVOID)sendPacketLoc, &sendPacket, (LPVOID*)&sendPacketOriginal);
    if (sendPacketHook != 0)
        printf("sendPacketHook - failed to hook.\n");

    auto enableSendPacketHook = MH_EnableHook((void*)sendPacketHook);
    if (enableSendPacketHook != 0)
        printf("enableSendPacketHook - failed to enable.\n");

    auto sendRequestHook = MH_CreateHook((LPVOID)sendRequestLoc, &sendRequest, (LPVOID*)&sendRequestOriginal);
    if (sendRequestHook != 0)
        printf("sendRequestHook - failed to hook.\n");
    
    auto enableSendRequestHook = MH_EnableHook((void*)sendRequestHook);
    if (enableSendRequestHook != 0)
        printf("sendRequestHook - failed to hook.\n");

    auto httpHook = MH_CreateHook((LPVOID)httpLoc, &httpRequest, (LPVOID*)&httpRequestOriginal);
    if (httpHook != 0)
        printf("httpHook - failed to hook.\n");
    
    auto enableHttpHook = MH_EnableHook((void*)httpHook);
    if (enableHttpHook != 0)
        printf("httpHook - failed to enable.\n");

    for ( ;; )
    {
        // Exit
        if (GetAsyncKeyState(VK_F1))
            break;

        Sleep(20);
    }

    // Disable hooks (restore overwritten bytes)
    MH_DisableHook((void*)sendPacketHook);
    MH_DisableHook((void*)httpHook);
    MH_DisableHook((void*)sendRequestHook);

    // Clean up console window
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(
            CreateThread(nullptr,
                0,
                (LPTHREAD_START_ROUTINE)vroomVroom,
                hModule,
                0,
                nullptr
            )
        );
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


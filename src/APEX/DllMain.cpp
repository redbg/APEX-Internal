#include "hook.h"
#include <Windows.h>
#include <stdio.h>

DWORD WINAPI MyThread(LPVOID hModule)
{
    while (!GetAsyncKeyState(VK_END))
    {
        Sleep(100);
    }

    FreeLibraryAndExitThread((HMODULE)hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        // DisableThreadLibraryCalls(hModule);
#ifdef _DEBUG
        AllocConsole();
        FILE *file;
        freopen_s(&file, "CONIN$", "r", stdin);
        freopen_s(&file, "CONOUT$", "w", stdout);
        freopen_s(&file, "CONOUT$", "w", stderr);
        printf("DLL_PROCESS_ATTACH\n");
        CreateThread(0, 0, MyThread, (HMODULE)hModule, 0, 0);
#endif
        APEX::Hook();
        break;
    case DLL_PROCESS_DETACH:
        APEX::UnHook();
#ifdef _DEBUG
        printf("DLL_PROCESS_DETACH\n");
        FreeConsole();
#endif
        break;
    }

    return TRUE;
}

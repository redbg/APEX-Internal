#pragma once
#include "hack.h"
#include "src/SS/Memory/Memory.h"
#include <Windows.h>
#include <dxgi.h>

#ifndef _DEBUG
#define printf
#endif

typedef HRESULT (*Present_t)(IDXGISwapChain *swapChain, UINT SyncInterval, UINT Flags);

namespace APEX
{
    Present_t *presentPattern  = (Present_t *)(SS::Memory::FindPattern("GameOverlayRenderer64.dll", "\x48\x89\x6C\x24\x18\x48\x89\x74\x24\x20\x41\x56\x48\x83\xEC\x20\x41\x8B\xE8") + 0x2e);
    Present_t *present         = (Present_t *)((DWORD64)presentPattern + *(DWORD *)((DWORD64)presentPattern + 3) + 7);
    Present_t  originalPresent = *present;

    HRESULT MyPresent(IDXGISwapChain *swapChain, UINT SyncInterval, UINT Flags)
    {
        APEX::Glow();
        APEX::Aimbot();
        return originalPresent(swapChain, SyncInterval, Flags);
    }

    void Hook()
    {
        *present = MyPresent;
    }

    void UnHook()
    {
        *present = originalPresent;
    }
} // namespace APEX

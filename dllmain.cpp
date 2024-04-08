#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cstdint>
#include <tchar.h>

typedef struct arcdps_exports {
    uintptr_t size;
    uint32_t sig;
    uint32_t imguivers;
    const char* out_name;
    const char* out_build;
    void* wnd_nofilter;
    void* combat;
    void* imgui;
    void* options_end;
    void* combat_local;
    void* wnd_filter;
    void* options_windows;
} arcdps_exports;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

arcdps_exports arc_exports;

arcdps_exports* mod_init()
{
    memset(&arc_exports, 0, sizeof(arcdps_exports));
    arc_exports.sig = 0xFFFA;
    arc_exports.size = sizeof(arcdps_exports);
    arc_exports.out_name = "keyboardlayoutRemover";
    arc_exports.out_build = "1.0";

    return &arc_exports;
}


uintptr_t mod_release()
{
    HKL hkl = LoadKeyboardLayout(_T("00000409"), 0);
    UnloadKeyboardLayout(hkl);
    return 0;
}

extern "C" __declspec(dllexport)
void* get_init_addr(char*, void*, void*, HANDLE, void*, void*, uint32_t)
{
    return mod_init;
}

extern "C" __declspec(dllexport)
void* get_release_addr()
{
    return mod_release;
}
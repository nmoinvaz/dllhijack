#define WIN32_LEAN_AND_MEAN

#include <windows.h>

int fireLazor()
{
    WinExec("calc", 0);
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason, LPVOID lpvReserved)
{
    fireLazor();
    return 0;
}
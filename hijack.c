#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <shlobj_core.h>

HANDLE ThreadHandle;
DWORD ThreadId;

void RunCalculator() {
    WinExec("calc", 0);
}

void WriteToFile() {
    wchar_t OutputFile[MAX_PATH] = {0};
    wchar_t CurrentPath[MAX_PATH] = {0};
    HMODULE CurrentModule = NULL;
    HANDLE FileHandle = NULL;
    DWORD BytesWritten = 0;
    DWORD BytesToWrite = 0;

    SHGetSpecialFolderPathW(NULL, OutputFile, CSIDL_DESKTOP, 0);
    wcscat_s(OutputFile, sizeof(OutputFile), L"\\results.txt");

    if (GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                           (LPCWSTR)&WriteToFile, &CurrentModule) == 0)
        return;
    if (GetModuleFileNameW(CurrentModule, CurrentPath, sizeof(CurrentPath)) == 0)
        return;

    FileHandle = CreateFileW(OutputFile, GENERIC_WRITE, 0, 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    if (FileHandle != INVALID_HANDLE_VALUE)
        CloseHandle(FileHandle);

    FileHandle =
        CreateFileW(OutputFile, FILE_APPEND_DATA, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (FileHandle == INVALID_HANDLE_VALUE)
        return;

    BytesToWrite = wcslen(CurrentPath) * sizeof(wchar_t);
    WriteFile(FileHandle, (LPVOID)CurrentPath, BytesToWrite, &BytesWritten, NULL);
    CloseHandle(FileHandle);
}

DWORD WINAPI MyThread(LPVOID lpParam) {
    WriteToFile();
    return 0;
}

BOOL APIENTRY DllMain(HMODULE Module, DWORD ReasonForCall, LPVOID Reserved) {
    switch (ReasonForCall) {
    case DLL_PROCESS_ATTACH:
        ThreadHandle = CreateThread(NULL, 0, MyThread, NULL, 0, &ThreadId);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

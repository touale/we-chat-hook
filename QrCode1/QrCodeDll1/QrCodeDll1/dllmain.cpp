// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "framework.h"
#include "resource.h"
#include <Windows.h>
#include "hook.h"



INT_PTR CALLBACK Dlgproc(
    HWND unnamedParam1,
    UINT unnamedParam2,
    WPARAM unnamedParam3,
    LPARAM unnamedParam4);


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DialogBox(hModule, MAKEINTRESOURCE(MAIN), NULL, &Dlgproc);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


INT_PTR CALLBACK Dlgproc(HWND unnamedParam1, UINT unnamedParam2, WPARAM unnamedParam3, LPARAM unnamedParam4)
{
    switch (unnamedParam2)
    {
    case WM_INITDIALOG:

        break;
    case WM_COMMAND:
        if (unnamedParam3 == INSTALL) {
            startHook(0x2CF592,showPic,unnamedParam1);
            MessageBox(NULL, "1", "1", 0);
            SetDlgItemText(unnamedParam1, HOOK_STATIC, "ok");
            break;
        }

        if (unnamedParam3 == UNINSTALL) {
            unHook(0x2CF592);
            MessageBox(NULL, "2", "1", 0);
            break;
        }

    case WM_CLOSE:
        EndDialog(unnamedParam1, 0);
        break;
    default:
        break;
    }
    return FALSE;
}

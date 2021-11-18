// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "framework.h"
#include <Windows.h>
#include <stdint.h>
#include "resource.h"
#include "write_ReadDemo.h"

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
        //MessageBox(NULL, "DLL_THREAD_ATTACH", "", 0);
        break;
    case DLL_THREAD_DETACH:
        //MessageBox(NULL, "DLL_THREAD_DETACH", "", 0);
        break;
    case DLL_PROCESS_DETACH:
        //MessageBox(NULL, "DLL_PROCESS_DETACH", "", 0);
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
        if (unnamedParam3 == READ_DATA) {
            
            readWechatData(unnamedParam1);
            MessageBox(NULL, "1", "1", 0);
            return FALSE;
            break;
        }

        if (unnamedParam3 == WRITE_DATA) {
            SetDlgItemTextA(unnamedParam1, 1006, (LPCTSTR)"123");

            //SetDlgItemText(unnamedParam1, WXID, (LPCTSTR)"123");
            //MessageBox(NULL, "0", "1", 0);
            break;
        }

    case WM_CLOSE:
        EndDialog(unnamedParam1,0);
        break;
    default:
        break;
    }
    return FALSE;
}
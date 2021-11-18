// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "framework.h"
#include <Windows.h>
#include "resource.h"
#include "sendData.h"

DWORD ThreadProc(HMODULE hModule);

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
        // 启动一个线程加载界面
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, hModule, 0, NULL);
        
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

DWORD ThreadProc(HMODULE hModule) {

    DialogBox(hModule, MAKEINTRESOURCE(MAIN), NULL, &Dlgproc);
    return NULL;
}



INT_PTR CALLBACK Dlgproc(HWND unnamedParam1, UINT unnamedParam2, WPARAM unnamedParam3, LPARAM unnamedParam4)
{
    wchar_t wxid[0x100] = { 0 };
    wchar_t msg[0x300] = { 0 };
    switch (unnamedParam2)
    {
    case WM_INITDIALOG:

        break;
    case WM_COMMAND:
        if (unnamedParam3 == SEND) {
            GetDlgItemText(unnamedParam1, WXID, (LPSTR)wxid, sizeof(wxid));
            GetDlgItemText(unnamedParam1, SENDDATA, (LPSTR)msg, sizeof(msg));
            SendTextMsg(wxid, msg);
            MessageBox(NULL, "1", "1", 0);
            break;
        }


    case WM_CLOSE:
        //EndDialog(unnamedParam1, 0);
        break;
    default:
        break;
    }
    return FALSE;
}
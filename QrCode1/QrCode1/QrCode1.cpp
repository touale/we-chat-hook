// QrCode1.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "QrCode1.h"
#include <Windows.h>
#include "resource.h"

INT_PTR CALLBACK Dlgproc(
    HWND unnamedParam1,
    UINT unnamedParam2,
    WPARAM unnamedParam3,
    LPARAM unnamedParam4);





int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
   
    DialogBox(hInstance, MAKEINTRESOURCE(MAIN), NULL, &Dlgproc);
    return (int)0;
}


INT_PTR CALLBACK Dlgproc(HWND unnamedParam1, UINT unnamedParam2, WPARAM unnamedParam3, LPARAM unnamedParam4)
{
    if (unnamedParam2 == WM_INITDIALOG) {
        // MessageBox(NULL, "首次加载", "标题", 0);

    }
    if (unnamedParam2 == WM_CLOSE) {
        EndDialog(unnamedParam1, 0);
    }

    if (unnamedParam2 == WM_COMMAND) {
        if (unnamedParam3 == INJECTDLL) {
            MessageBox(NULL, "0", "标题", 0);
        }
        if (unnamedParam3 == UNDLL) {
            MessageBox(NULL, "1", "标题", 0);
        }

    }
    return FALSE;
}


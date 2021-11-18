
#include "framework.h"
#include "TechDemo3.h"
#include <Windows.h>
#include "resource.h"
#include <TlHelp32.h>
#include <stdio.h>

#define WECHAT_PROCESS_NAME "WeChat.exe"
LPVOID dllAdd;
HANDLE hProcess;
HMODULE k32;

INT_PTR CALLBACK Dlgproc(HWND unnamedParam1, UINT unnamedParam2, WPARAM unnamedParam3, LPARAM unnamedParam4);
VOID InjectDll();
VOID UnDll();
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
   
    DialogBox(hInstance,MAKEINTRESOURCE(IDD_MAIN),NULL,&Dlgproc);
    return (int) 0;
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
        if (unnamedParam3 == INJECT_DLL) {
            InjectDll();
        }
        if (unnamedParam3 == UN_DLL) {
            SetDlgItemText(unnamedParam1,TEST, (LPCTSTR)"123");
            UnDll();
        }

    }
    return FALSE;
}


// 1.拿到微信的进程句柄，有了句柄才能去操作微信的内存
// 通过微信的进程名称来找到进程的pid，通过pid打开微信获取到进程句柄
DWORD ProcessNameFindPID(LPCSTR ProcessName) {
    // 获取到整个系统的进程快照
    HANDLE ProcessAll = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,NULL);

    // 在快照里面对比名称
    PROCESSENTRY32 processInfo = { 0 };
    processInfo.dwSize = sizeof(PROCESSENTRY32);
    
    do {
        if (strcmp(ProcessName, processInfo.szExeFile) == 0) {
            return processInfo.th32ProcessID;
        }

    } while (Process32Next(ProcessAll, &processInfo));

    return 0;

}


// 2.在微信内部申请一块内存用来放dll的路径
VOID InjectDll() {

    CHAR pathStr[0x100] = { "F:\\OriginC\\源码\\WeChatHook1\\c\\TechDemo1\\WriteReadDemo1\\WriteReadDemo1\\Debug\\WriteReadDemo1.dll" };

    // 获取微信句柄
    DWORD PID = ProcessNameFindPID(WECHAT_PROCESS_NAME);
    if (PID == 0) {
        MessageBox(NULL, "未找到微信进程", "错误", 0);
        return;
    }

    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
    if (NULL == hProcess) {
        MessageBox(NULL, "进程打开失败", "错误", 0);
        return;
    }

    // 申请内存
    dllAdd = VirtualAllocEx(hProcess, NULL,sizeof(pathStr) ,MEM_COMMIT,PAGE_READWRITE);
    if (dllAdd == NULL) {
        MessageBox(NULL, "内存分配失败", "错误", 0);
        return;
    }

    // 把dll路劲写入
    if (WriteProcessMemory(hProcess, dllAdd, pathStr, strlen(pathStr), NULL)==0) {
        MessageBox(NULL, "路劲写入失败", "错误", 0);
        return;
    }

    CHAR test[0x100] = { 0 };
    sprintf_s(test, "写入的地址为：%p", dllAdd);
    OutputDebugString(test);

    k32 = GetModuleHandle("kernel32.dll");
    if (k32 == NULL) {
        MessageBox(NULL, "kernel32.dll异常", "错误", 0);
        return;
    }
   
    LPVOID localAdd =  GetProcAddress(k32, "LoadLibraryA");
    if (localAdd == NULL) {
        MessageBox(NULL, "localAdd异常", "错误", 0);
        return;
    }

    HANDLE exec = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)localAdd,dllAdd,0,NULL);

    if (exec == NULL) {
        MessageBox(NULL, "远程注入失败", "错误", 0);
    }

}
// 3. 写入dll路径，通过远程线程执行函数去loadLiaray 


VOID UnDll() {
   


    LPVOID localAdd = GetProcAddress(k32, "FreeLibrary");
    if (localAdd == NULL) {
        MessageBox(NULL, "localAdd异常", "错误", 0);
        return;
    }

    HANDLE exec = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)localAdd,dllAdd,0,NULL);

    if (exec == NULL) {
        MessageBox(NULL, "远程注入失败", "错误", 0);
    }
    MessageBox(NULL, "OK", "", 0);
}
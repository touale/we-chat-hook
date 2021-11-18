#include "framework.h"
#include <stdio.h>
#include "resource.h"

// 获取wechatwin基址
DWORD getWechatWinAdd() {
	HMODULE winAdd = LoadLibrary("WeChatWin.dll");
	return (DWORD)winAdd;
}

// 读取内存数据
void readWechatData(HWND unnamedParam1) {
	// 拿到模块基址
	DWORD wechatWin = getWechatWinAdd();
	CHAR wxid[0x100] = { 0 };
	sprintf_s(wxid, "%s", wechatWin + 0x1E23ED8);
	//SetDlgItemText(unnamedParam1, WXID, wxid);
	MessageBox(NULL, wxid, "1", 0);

	// 装数据的容器
	/*CHAR wxid[0x100] = { 0 };
	sprintf_s(wxid, "%s", wechatWin + 0x1131BEC);
	SetDlgItemText(unnamedParam1,WXID,wxid);*/

	CHAR username[0x100] = { 0 };
	sprintf_s(username, "%s", wechatWin + 0x1E23D5C);
	//SetDlgItemText(unnamedParam1, USERNAME, username);
	MessageBox(NULL, username, "1", 0);

	CHAR headPic[0x100] = { 0 };
	DWORD pic = wechatWin + 0x1E2403C;
	sprintf_s(headPic, "%s", *((DWORD*)pic));
	//SetDlgItemText(unnamedParam1, HEAD_PIC, headPic);
	MessageBox(NULL, headPic, "1", 0);
}
#include "framework.h"
#include <Windows.h>
#include <stdio.h>

struct wxStr {
	wchar_t* pStr;
	int pInt1;
	int pInt2;

};


DWORD GetWeChtWin() {
	return (DWORD)LoadLibrary("WeChatWin.dll");
}




VOID SendTextMsg(wchar_t* wxid, wchar_t* msg) {

	// ������Ϣcall 
	DWORD sendCall = GetWeChtWin() + 0x149EF4;

	// ��װ��Ҫ�����ݸ�ʽ
	wxStr pWxid = { 0 };
	pWxid.pStr = wxid;
	pWxid.pInt1 = wcslen(wxid);
	pWxid.pInt2 = wcslen(wxid);

	wxStr pMsg = { 0 };
	pMsg.pStr = msg;
	pMsg.pInt1 = wcslen(msg);
	pMsg.pInt2 = wcslen(msg);

	/*
		push 0x1                                 ; //01
		lea eax,dword ptr ds:[edi+0x34]
		push eax                                 ; //00
		push edi                                 ; //��Ϣ����
		lea edx,dword ptr ss:[ebp-0x90]          ; //wxid
		lea ecx,dword ptr ss:[ebp-0x5F8]         ; //������
		call WeChatWi.6434D200                   ; //���Ʒ���Ϣ
		add esp,0xC
	*/

	char* asmWxid = (char*)&pWxid.pStr;
	char* asmMsg = (char*)&pMsg.pStr;
	char buff[0x5F8] = { 0 };
	char auff[0x34] = { 0 };
	__asm {
		push 1;
		lea eax, auff;
		push eax;
		mov edi, asmMsg;
		push edi;
		lea edx, asmWxid;;
		lea ecx, buff;
		call sendCall;
		add esp, 0xC;
	}



}
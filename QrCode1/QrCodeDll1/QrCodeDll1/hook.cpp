#include "framework.h"
#include <Windows.h>
#include <stdio.h>
#include <atlimage.h>
#include "resource.h"

#define HOOK_LEN 5

HWND hDlg = 0;
BYTE backCode[HOOK_LEN] = { 0 };
DWORD getWechatWin();
DWORD reAdd = 0;
DWORD callAdd = 0;

DWORD pEax = 0;
DWORD pEcx = 0;
DWORD pEdx = 0;
DWORD pEbx = 0;
DWORD pEbp = 0;
DWORD pEsp = 0;
DWORD pEsi = 0;
DWORD pEdi = 0;


// ��ȡģ���ַ
DWORD getWechatWin() {
	return (DWORD)LoadLibrary("WeChatWin.dll");
}


VOID saveImg(DWORD qrcode) {

	DWORD picLen = qrcode + 0x4;
	char PicData[0xFFF] = { 0 };
	size_t cpyLen = (size_t) * ((LPVOID*)picLen);
	memcpy(PicData, *((LPVOID*)qrcode), cpyLen);

	FILE* pFile;
	fopen_s(&pFile, "qrcode.png", "wb");
	fwrite(PicData, sizeof(char), sizeof(PicData), pFile);
	fclose(pFile);

	//����ͼƬ����ע���������ֱ�Ӵ�����ջ�ռ���
	CImage img;
	CRect rect;
	HWND pic_handle = GetDlgItem(hDlg, PIC_QRcode);
	GetClientRect(pic_handle, &rect);
	img.Load("qrcode.png");
	img.Draw(GetDC(pic_handle), rect);
}

VOID __declspec(naked) showPic() {

	// ���ݼĴ���
	__asm {
		mov pEax, eax
		mov pEcx, ecx
		mov pEdx, edx
		mov pEbx, ebx
		mov pEbp, ebp
		mov pEsp, esp
		mov pEsi, esi
		mov pEdi, edi
	}

	saveImg(pEcx);
	//MessageBox(NULL, "HOOK����2", "0", 0);
	reAdd = getWechatWin() + 0x2CF597;
	__asm {
		mov eax, pEax
		mov ecx, pEcx
		mov edx, pEdx
		mov ebx, pEbx
		mov ebp, pEbp
		mov esp, pEsp
		mov esi, pEsi
		mov edi, pEdi
	    jmp reAdd
	}
}


// WeChatWin.dll+1F819A ��ά��hook��ʼ
//���ص�ַ WeChatWin.dll+1F 819F ��ά��hook����
void startHook(DWORD hookA,LPCVOID funAdd, HWND unnamedParam1) {
	DWORD WinAdd = getWechatWin();
	// hook�ĵ�ַ
	DWORD hookAdd = WinAdd + hookA;

	//Ҫ��ת������ - hook�ĵ�ַ - 5
	//��װ���� byte
	BYTE jmpCode[HOOK_LEN] = { 0 };
	jmpCode[0] = 0xE9;

	*(DWORD *)&jmpCode[1] = (DWORD)funAdd - hookAdd - HOOK_LEN;

	// ��ȡ�Լ��Ľ��̾��
	HANDLE hWHND = OpenProcess(PROCESS_ALL_ACCESS, NULL, GetCurrentProcessId());


	// ����hook��ַ������
	if (ReadProcessMemory(hWHND, (LPVOID)hookAdd, backCode, HOOK_LEN, NULL) == 0) {
		MessageBox(NULL, "��ȡ�ڴ�ʧ��", "����", 0);
		return;
	}

	// д����õ�����
	if (WriteProcessMemory(hWHND, (LPVOID)hookAdd, jmpCode, HOOK_LEN, NULL) == 0) {
		MessageBox(NULL, "д���ڴ�ʧ��", "����", 0);
		return;
	}

	hDlg = unnamedParam1;
}

// ж��hook

VOID unHook(DWORD hookA) {
	DWORD WinAdd = getWechatWin();
	// hook�ĵ�ַ
	DWORD hookAdd = WinAdd + hookA;

	// ��ȡ�Լ��Ľ��̾��
	HANDLE hWHND = OpenProcess(PROCESS_ALL_ACCESS, NULL, GetCurrentProcessId());
	if (WriteProcessMemory(hWHND, (LPVOID)hookAdd, backCode, HOOK_LEN, NULL) == 0) {
		MessageBox(NULL, "д���ڴ�ʧ��", "����", 0);
		return;
	}


}

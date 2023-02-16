#include<Windows.h>
#include<stdio.h>
#include <cstring>
#include <atlstr.h>
#include "resource.h"


VOID ShowError(const char* str) {
	printf_s(str);
}

BOOL FreeMyResource(UINT uiResouceName,const char* lpszResourceType,const char* lpszSaveFileName) {
	//��ȡָ��ģ�������Դ
	CString str = CString(lpszResourceType);
	LPCWSTR wszClassName = new WCHAR[str.GetLength() + 1];
	wcscpy((LPTSTR)wszClassName, T2W((LPTSTR)str.GetBuffer(NULL)));
	HRSRC hRsrc = ::FindResource(NULL, MAKEINTRESOURCE(uiResouceName), wszClassName);
	str.ReleaseBuffer();

	//��ȡ��Դ�Ĵ�С
	DWORD dwSize = ::SizeofResource(NULL, hRsrc);
	if (0 >= dwSize) {
		ShowError("SizeofResource");
		return FALSE;
	}

	//����Դ���ص��ڴ���
	HGLOBAL hGlobal = ::LoadResource(NULL, hRsrc);
	if (NULL == hGlobal) {
		ShowError("LoadResource");
		return FALSE;
	}

	//������Դ
	LPVOID lpVoid = ::LockResource(hGlobal);
	if (NULL == lpVoid) {
		ShowError("LockResource");
	}

	//������ԴΪ�ļ�
	FILE* fp = NULL;
	fopen_s(&fp,lpszSaveFileName,"wb+");
	if (NULL == fp) {
		ShowError("Save fail");
	}

	fwrite(lpVoid, sizeof(char), dwSize, fp);
	fclose(fp);
	return TRUE;
}

int main()
{
	FreeMyResource(IDR_MYRES2, "MYRES", "someres.txt");
	FreeMyResource(IDR_SOMERES2, "SOMERES", "res2.txt");
}
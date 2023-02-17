#include<Windows.h>
#include <stdio.h>
#include <stdlib.h>
typedef BOOL(*SetHook)();
typedef BOOL(*UnsetHook)();

int main()
{
    //����dll
    HMODULE hDll = LoadLibrary(L"setWindowsHookEx.dll");

    if (NULL == hDll)
    {
        return -1;
    }

    BOOL isHook = FALSE;

    //����SetGlobalHook������ַ
    SetHook SetGlobalHook = (SetHook)GetProcAddress(hDll, "SetGlobalHook");

    if (NULL == SetGlobalHook)
    {
        return -1;
    }

    //����UnsetGlobalHook������ַ
    UnsetHook UnsetGlobalHook = (UnsetHook)GetProcAddress(hDll, "UnsetGlobalHook");

    if (NULL == UnsetGlobalHook)
    {
        return -1;
    }

    //��������ȫ�ֹ���
    isHook = SetGlobalHook();

    if (isHook)
    {
        printf("Hook is ok!\n");
    }
    else
    {
        printf("Hook is error\n");
    }

    system("pause");

    //����ж��ȫ�ֹ���
    UnsetGlobalHook();

    FreeLibrary(hDll);

    return 0;
}
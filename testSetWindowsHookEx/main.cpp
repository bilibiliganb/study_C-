#include<Windows.h>
#include <stdio.h>
#include <stdlib.h>
typedef BOOL(*SetHook)();
typedef BOOL(*UnsetHook)();

int main()
{
    //加载dll
    HMODULE hDll = LoadLibrary(L"setWindowsHookEx.dll");

    if (NULL == hDll)
    {
        return -1;
    }

    BOOL isHook = FALSE;

    //导出SetGlobalHook函数地址
    SetHook SetGlobalHook = (SetHook)GetProcAddress(hDll, "SetGlobalHook");

    if (NULL == SetGlobalHook)
    {
        return -1;
    }

    //导出UnsetGlobalHook函数地址
    UnsetHook UnsetGlobalHook = (UnsetHook)GetProcAddress(hDll, "UnsetGlobalHook");

    if (NULL == UnsetGlobalHook)
    {
        return -1;
    }

    //调用设置全局钩子
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

    //调用卸载全局钩子
    UnsetGlobalHook();

    FreeLibrary(hDll);

    return 0;
}
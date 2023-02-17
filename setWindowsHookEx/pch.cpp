// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。
#pragma data_seg("mydata")
HHOOK g_hHook = NULL;
#pragma data_seg()
#pragma comment(linker, "/SECTION:mydata,RWS")

extern HMODULE g_hDllModule;
// 设置全局钩子
BOOL SetGlobalHook()
{
    g_hHook = SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)GetMsgProc, g_hDllModule, 0);
    if (NULL == g_hHook)
    {
        return FALSE;
    }
    return TRUE;
}

// 钩子回调函数
LRESULT GetMsgProc(int code, WPARAM wParam, LPARAM lParam)
{
    return CallNextHookEx(g_hHook, code, wParam, lParam);
}

//卸载钩子
BOOL UnsetGlobalHook()
{
    if (g_hHook)
    {
        UnhookWindowsHookEx(g_hHook);
    }
    return TRUE;
}
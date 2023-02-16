#include<stdio.h>
#include<iostream>
#include<Windows.h>
using namespace std;
bool  IsAlreadyRun()
{
	HANDLE hMutex = NULL;
	hMutex = ::CreateMutex(NULL, FALSE, L"TEST");
	if (hMutex) {
		if (ERROR_ALREADY_EXISTS == ::GetLastError())
		{
			return TRUE;
		}
	}
}

int main() {

	if (IsAlreadyRun())
		printf("run");
	else
	{
		printf("not run");
	}
	system("pause");
}
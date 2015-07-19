
#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

class Local
{
public:
	Local(const char* window_title);
	virtual ~Local();

	DWORD ModuleBase[2];
	DWORD pid;
	HANDLE handle;
	HWND window;
	DWORD LocalPlayer;

	template <typename T> T* Read(DWORD address);
	DWORD GetModuleBase(const char* module_name);

	int maxPlayers();
	bool onGround();

};


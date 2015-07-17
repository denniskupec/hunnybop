
#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

class Local
{
public:
	Local(const char* window_title);
	virtual ~Local();

	static const DWORD m_dwLocalPlayer = 0x00A77D2C;
	static const DWORD m_fFlags = 0x00000100;
	static const DWORD m_dwMaxPlayer = 0x000002F0;

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


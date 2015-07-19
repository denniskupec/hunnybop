
#include "Local.h"

using std::cout;

Local::Local(const char* window_title)
{
	cout << "Waiting for game...";

	while (this->window == nullptr)
	{
		this->window = FindWindow(nullptr, window_title);
		Sleep(1000);
	}

	GetWindowThreadProcessId(window, &this->pid);

	this->handle = OpenProcess(PROCESS_VM_READ, 0, (DWORD)this->pid);

	this->ModuleBase[0] = this->GetModuleBase("client.dll");
	this->ModuleBase[1] = this->GetModuleBase("engine.dll");
}

Local::~Local()
{
	CloseHandle(this->handle);
}

template <typename T>
T* Local::Read(DWORD address)
{
	T* value;
	ReadProcessMemory(this->handle, (LPVOID)address, &value, sizeof(T), NULL);
	return value;
}

DWORD Local::GetModuleBase(const char* module_name)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->pid);
	MODULEENTRY32 module_entry = { module_entry.dwSize = sizeof(MODULEENTRY32) };
	BYTE* module_base = 0;

	if (snapshot && Module32First(snapshot, &module_entry)) {
		while (Module32Next(snapshot, &module_entry)) {
			if (lstrcmpi(module_entry.szModule, (LPCSTR)module_name) == 0) {
				module_base = module_entry.modBaseAddr;
				break;
			}
		}
	}

	CloseHandle(snapshot);
	return (DWORD)module_base;
}

bool Local::onGround()
{
	UINT16 flags = (UINT16)this->Read<UINT16>(this->LocalPlayer + 0x100);
	return flags != 256;
}






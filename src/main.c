
#include <stdio.h>
#include <Windows.h>
#include <TlHelp32.h>
#include "Offsets.h"
#include "Structs.h"

struct Process Game;
struct RPMValues ReadMem;

int main()
{
	printf("Launch CSGO... \n");

	while (Game.window == NULL) {
		Game.window = FindWindow(NULL, "Counter-Strike: Global Offensive");
		Sleep(500);
	}

	printf("Found process... \n");


	GetWindowThreadProcessId(Game.window, &Game.pid);

	printf("ID: %d \n", Game.pid);


	Game.process = OpenProcess(PROCESS_ALL_ACCESS, 0, Game.pid);

	Game.modbase_client = get_module_base(Game.pid, "client.dll");

	printf("client.dll: %d \n", Game.modbase_client);
	printf("Ready, hold space. \n");

	// main loop
	while (TRUE) {

		ReadProcessMemory(Game.process, (LPVOID)(Game.modbase_client + OFFSET_LOCALPLAYER), &ReadMem.playerbase, sizeof(int), NULL);
		ReadProcessMemory(Game.process, (LPVOID)(ReadMem.playerbase + OFFSET_FLAGS), &ReadMem.onground, sizeof(int), NULL);
		ReadProcessMemory(Game.process, (LPVOID)(ReadMem.playerbase + OFFSET_HEALTH), &ReadMem.lifestate, sizeof(int), NULL);
		ReadProcessMemory(Game.process, (LPVOID)(ReadMem.playerbase + OFFSET_TEAMID), &ReadMem.teamid, sizeof(int), NULL);

		// if SPACE is held down + player is alive + player is on the ground + not spectating, send jumps
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && !player_in_air() && ReadMem.lifestate > 0 && ReadMem.teamid != 1) {
			for (int i=0; i<5; i++) {
				Sleep(1);
				SendMessage(Game.window, WM_KEYDOWN, VK_SPACE, 0x390000);
				SendMessage(Game.window, WM_KEYUP, VK_SPACE, 0x390000);
			}
		}

		Sleep(1);
	}

}

int player_in_air()
{
	return ReadMem.onground == 256 || ReadMem.onground == 258 || ReadMem.onground == 260 || ReadMem.onground == 262;
}

DWORD get_module_base(const DWORD pid, const char *module_name)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	MODULEENTRY32 module_entry = { module_entry.dwSize = sizeof(MODULEENTRY32) };
	DWORD module_base = 0;

	if (snapshot && Module32First(snapshot, &module_entry)) {
		while (Module32Next(snapshot, &module_entry)) {
			if (lstrcmpi(module_entry.szModule, module_name) == 0) {
				module_base = (DWORD)module_entry.modBaseAddr;
				break;
			}
		}
	}

	CloseHandle(snapshot);
	return module_base;
}

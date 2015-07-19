
#include <iostream>
#include "main.h"
#include "Local.h"

using std::cout;

Local CSGO = Local("Counter-Strike: Global Offensive");

int main(void)
{
	cout << "Process ID: " << CSGO.pid << "\n";

	while (1) {
		CSGO.LocalPlayer = (DWORD)CSGO.Read<DWORD>(CSGO.ModuleBase[0] + 0x00A77D2C);
		
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && CSGO.onGround()) {
			SendMessage(CSGO.window, WM_KEYDOWN, VK_SPACE, 0x390000);
			SendMessage(CSGO.window, WM_KEYUP, VK_SPACE, 0x390000);
			Sleep(17);
			SendMessage(CSGO.window, WM_KEYDOWN, VK_SPACE, 0x390000);
			SendMessage(CSGO.window, WM_KEYUP, VK_SPACE, 0x390000);
		}
		
		Sleep(1);
	}

	return 0;
}


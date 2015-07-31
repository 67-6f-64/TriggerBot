#include "classes.h"

TriggerBot::~TriggerBot()
{
	if (this->proc)
		CloseHandle(proc);
}

int TriggerBot::FindGame()
{
	while (true)
	{
		do
		{
			trigger.gameHwnd = FindWindow(NULL, "Counter-Strike: Global Offensive");
			Sleep(16);
		} while (trigger.gameHwnd == NULL);
		cout << "Game Found: " << trigger.gameHwnd << endl;

		GetWindowThreadProcessId(trigger.gameHwnd, &trigger.gamePID);
		cout << "Pid got: " << trigger.gamePID << endl;

		trigger.proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, trigger.gamePID);
		if (trigger.proc)
		{
			cout << "Process Opened: " << trigger.proc << endl;

			while (mem.clientDll == NULL)
			{
				mem.clientDll = mem.Module("client.dll", trigger.gamePID);
				Sleep(16);
			}
			cout << "Client.dll: " << mem.clientDll << endl;
			
			thread triggerBot(&trigger.Trigger);
			if (triggerBot.joinable())
				triggerBot.join();			

			break;
		}
		Sleep(16);
	}
	return 0;
}

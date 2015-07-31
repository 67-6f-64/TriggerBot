#include "classes.h"

int TriggerBot::Trigger()
{
	//mem.GetLocalPlayer();
	int oldTeam = 9;
	vector<DWORD> enemys;
	vector<int> enemysId;
	cout << "TriggerBot Thread Working...\n";
	while (true)
	{
		if (GetAsyncKeyState(0x46))
		{		
			if (mem.GetMyTeam() != oldTeam)
			{
				oldTeam = mem.GetMyTeam();
				enemys.clear();
				enemysId.clear();

				for (int i = 0; i < 64; ++i)
				{
					DWORD entityLoop = RPM<DWORD>(trigger.proc, ((mem.clientDll + entity.entityBase) + ((i - 1)*entity.loopDistance)), sizeof(DWORD));

					if (entityLoop == NULL) continue;

					if (mem.GetEntTeam(entityLoop) != 0 && mem.GetMyTeam() != mem.GetEntTeam(entityLoop))
					{
						enemys.push_back(entityLoop);
						enemysId.push_back(mem.GetEntIndex(entityLoop));
					}
				}
			}//get all targets


			if (mem.GetMyTeam() == oldTeam)
			{
				for (vector<DWORD>::size_type i = 0; i != enemys.size(); ++i)
				{

					if (find(enemysId.begin(), enemysId.end(), mem.GetMyCrossId()) == enemysId.end())
					{
						//this is used if we need to renew targets
						oldTeam = 9;
						break;
					}

					if (mem.GetEntIndex(enemys[i]) != mem.GetMyCrossId()) // crosshair without target
						continue;
					//can add punch/weapontype test here						
					WPM<int>(trigger.proc, (mem.clientDll + entity.forceAttack), 5);
					Sleep(25);
					WPM<int>(trigger.proc, (mem.clientDll + entity.forceAttack), 4);
					

				}//loop target internal more fast
			}//have target

		}//get key		

		Sleep(16);

	}
	cout << "TriggerBot Thread TERMINATED...\n";
	return 0;
}

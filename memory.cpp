#include "classes.h"

DWORD Memory::GetLocalPlayer()
{
	this->localPlayer = RPM<DWORD>(trigger.proc, (mem.clientDll + entity.localPlayer), sizeof(DWORD));
	return this->localPlayer;
}

int Memory::GetMyTeam()
{
	this->team = RPM<int>(trigger.proc, (GetLocalPlayer() + entity.iTeam), sizeof(int));
	return this->team;
}

int Memory::GetMyCrossId()
{
	this->crossHairId =  RPM<int>(trigger.proc, (GetLocalPlayer() + entity.iCrossHairID), sizeof(int));
	return this->crossHairId;
}

int Memory::GetEntTeam(DWORD address)
{
	return RPM<int>(trigger.proc, (address + entity.iTeam), sizeof(int));
}

int Memory::GetEntIndex(DWORD address)
{
	return RPM<int>(trigger.proc, (address + entity.index), sizeof(int));
}


DWORD Memory::Module(LPCSTR moduleName, DWORD pId) //function to get module address csgo.exe/client.dll/engine.dll/xxx.dll with pid
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pId);
	MODULEENTRY32  allinfo;
	BOOL haveProcess = Module32First(hSnapShot, &allinfo);
	while (haveProcess)
	{
		if (!strcmp(moduleName, allinfo.szModule))
		{
			return (DWORD)allinfo.modBaseAddr;
		}
		haveProcess = Module32Next(hSnapShot, &allinfo);
	}
	return 0;
}

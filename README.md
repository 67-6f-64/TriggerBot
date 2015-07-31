# TriggerBot

VS 2015

* File -> New Poject -> Visual C++ -> Win32 -> Win32 Console Application and add files.

* offsets 31/07/2015
* 
struct Entity
{
	//localPlayer
	DWORD localPlayer = 0xA7AFAC;
	DWORD iCrossHairID = 0x2410;
	DWORD forceAttack = 0x2E8F2A8;

	//entity
	DWORD entityBase = 0x4A1D384;
	DWORD loopDistance = 0x10;
	DWORD dormant = 0xE9;

	//comuns
	DWORD index = 0x64;
	DWORD ihealth = 0xFC;
	DWORD iTeam = 0xF0;
};

#pragma once

#include <iostream>
#include <thread>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

using namespace std;

class TriggerBot
{
public:
	~TriggerBot();

	HWND gameHwnd{};
	DWORD gamePID{};
	HANDLE proc{};
	static int FindGame();
	static int Trigger();
};

extern TriggerBot trigger;

class Memory
{
public:

	DWORD localPlayer;
	int team;
	int crossHairId;


	DWORD clientDll{};
	DWORD Module(LPCSTR moduleName, DWORD pId);
	//localPlayer
	DWORD GetLocalPlayer();
	int GetMyTeam();
	int GetMyCrossId();
	//enemy
	int GetEntTeam(DWORD address);
	int GetEntIndex(DWORD address);

};

extern Memory mem;

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

extern Entity entity;

//ReadProcessMemory template
template<typename TYPE>
TYPE RPM(HANDLE proc, DWORD address, SIZE_T size) {
	TYPE buffer = TYPE();
	::ReadProcessMemory(proc, (LPCVOID)address, &buffer, size, 0);
	return buffer;
}

//WriteProcessMemory template
template<typename TYPE>
BOOL WPM(HANDLE proc, DWORD address, TYPE dataToWrite) {
	TYPE buffer = dataToWrite;
	return ::WriteProcessMemory(proc, (LPVOID)address, &buffer, sizeof(buffer), 0);
}

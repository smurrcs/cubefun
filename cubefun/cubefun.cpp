#include <Windows.h>
#include <iostream>

DWORD pid;
DWORD ac_client = 0x400000;
DWORD LocalPlayer = 0x10F4F4;
DWORD HealthOffset = 0xF8;
DWORD ClipOffset = 0x128;
DWORD AmmoOffset = 0x150;
DWORD GrenadeOffset = 0x158;
DWORD ArmorOffset = 0xFC;

int value;
int lifehax = 9999;
int ammohax = 9999;
int cliphax = 9999;
int grenadehax = 9999;
int armorhax = 9999;

int main()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);

    std::cout << "Simple Assault Cube Hack" << std::endl;
    std::cout << "" << std::endl;
    
    HWND hWnd = FindWindowA(0, ("AssaultCube"));

    GetWindowThreadProcessId(hWnd, &pid);
    HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    ReadProcessMemory(pHandle,(void*)(ac_client + LocalPlayer), &value, sizeof(value), 0);
    //ReadProcessMemory(pHandle, (void*)(value + HealthOffset), &value, sizeof(value), 0);
    WriteProcessMemory(pHandle, (void*)(value + HealthOffset), &lifehax, sizeof(lifehax), 0);
    WriteProcessMemory(pHandle, (void*)(value + AmmoOffset), &ammohax, sizeof(ammohax), 0);
    WriteProcessMemory(pHandle, (void*)(value + ClipOffset), &cliphax, sizeof(cliphax), 0);
    WriteProcessMemory(pHandle, (void*)(value + GrenadeOffset), &grenadehax, sizeof(grenadehax), 0);
    WriteProcessMemory(pHandle, (void*)(value + ArmorOffset), &armorhax, sizeof(armorhax), 0);

    SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY);
    std::cout << "Its time to play like a GOD" << std::endl;
    std::cout << "" << std::endl;

    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    std::cout << "Life: " << lifehax << std::endl;
    std::cout << "Ammo: " << ammohax << std::endl;
    std::cout << "Clip: " << cliphax << std::endl;
    std::cout << "Grenades: " << grenadehax << std::endl;
    std::cout << "Armor: " << armorhax << std::endl;

    system("pause");

}
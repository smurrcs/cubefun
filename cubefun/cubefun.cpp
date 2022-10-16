#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>


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

DWORD GetPID(const char* ProcessName) {
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);


    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE)
        return 0;

    Process32First(processesSnapshot, &processInfo);
    if (!strcmp(processInfo.szExeFile, ProcessName))
    {
        CloseHandle(processesSnapshot);
    }

    while (Process32Next(processesSnapshot, &processInfo))
    {
        if (!strcmp(processInfo.szExeFile, ProcessName))
        {
            CloseHandle(processesSnapshot);
        }
    }
    CloseHandle(processesSnapshot);
    return processInfo.th32ProcessID;
}

MODULEENTRY32 GetModule(const char* moduleName, unsigned long ProcessID)
{
    MODULEENTRY32 modEntry = { 0 };

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID);

    if (hSnapshot != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 curr = { 0 };

        curr.dwSize = sizeof(MODULEENTRY32);
        if (Module32First(hSnapshot, &curr))
        {
            do
            {
                if (!strcmp(curr.szModule, moduleName))
                {
                    modEntry = curr;
                    break;
                }
            } while (Module32Next(hSnapshot, &curr));
        }
        CloseHandle(hSnapshot);
    }
    return modEntry;
}

int main()
{
    unsigned long long pid = GetPID("ac_client.exe");
    MODULEENTRY32 module = GetModule("ac_client.exe", pid);
    HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);

    std::cout << "Simple Assault Cube Hack" << std::endl;
    std::cout << "" << std::endl;
    
    ReadProcessMemory(pHandle,(void*)(module.modBaseAddr + LocalPlayer), &value, sizeof(value), 0);
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
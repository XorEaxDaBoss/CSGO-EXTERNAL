#pragma once
#include "header.h"

struct module_t
{
	uint32_t base, size;
};

namespace mem
{
	inline HANDLE	proc_handle = nullptr;
	inline uint32_t	proc_id = -1;

	//TODO: implement handle stealer
	inline HANDLE get_process(std::string process_name)
	{
		auto handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		PROCESSENTRY32 entry{};
		entry.dwSize = sizeof entry;

		do
		{
			if (!strcmp(entry.szExeFile, process_name.c_str()))
			{
				CloseHandle(handle);

				proc_id = entry.th32ProcessID;
				return OpenProcess(PROCESS_ALL_ACCESS, false, entry.th32ProcessID);
			}

		} while (Process32Next(handle, &entry));

		return nullptr;
	}

	inline module_t get_module(std::string module_name)
	{
		assert(proc_id != -1);

		auto handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, proc_id);

		MODULEENTRY32 entry{};
		entry.dwSize = sizeof entry;

		do
		{
			if (!strcmp(entry.szModule, module_name.c_str()))
			{
				CloseHandle(handle);

				return module_t{ (uint32_t)entry.hModule, entry.modBaseSize };
			}

		} while (Module32Next(handle, &entry));

		return module_t{ 0, 0 };
	}

	inline bool Read(uint32_t address, LPVOID buffer, uint32_t size)
	{
		SIZE_T out = NULL;

		return (ReadProcessMemory(proc_handle, (LPCVOID)address, buffer, size, &out) == TRUE);
	}

	template <typename T> 
	inline T read(uint32_t address, const T& tdefault = T())
	{
		T ret{};

		if (!Read(address, &ret, sizeof(T)))
		{
			return tdefault;
		}

		return ret;
	}

	inline bool Write(uint32_t address, LPCVOID buffer, uint32_t size)
	{
		SIZE_T out = NULL;

		return (WriteProcessMemory(proc_handle, (LPVOID)address, buffer, size, &out) == TRUE);
	}

	template <typename T> 
	inline bool write(uint32_t address, const T& value)
	{
		return Write(address, &value, sizeof(T));
	}
}
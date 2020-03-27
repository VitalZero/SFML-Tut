#pragma once
#pragma comment(lib, "Shlwapi")

#include <iostream>
#include <string>
#include <algorithm>

namespace Utils
{
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <Shlwapi.h>

	inline std::string GetWorkingDirectory()
	{
		HMODULE hModule = GetModuleHandle( nullptr );
		if ( hModule )
		{
			char path[256];
			
			GetModuleFileName( hModule, path, sizeof( path ) );
			PathRemoveFileSpec( path );
			strcat_s( path, "\\" );

			return std::string( path );
		}

		return "";
	}
} // end namespace
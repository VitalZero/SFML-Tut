#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Shlwapi.h>

namespace Utils
{
	std::string GetWorkingDirectory()
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

		return std::string( "" );
	}
} // end namespace
#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include "Utilities.h"

template<class Derived, class T>
class ResourceManager
{
public:
	ResourceManager( const std::string& pathsFile )
	{
		LoadPaths( pathsFile )
	}
	virtual ~ResourceManager()
	{
		PurgeResources();
	}

public:
	T* GetResources( const std::string& id )
	{
		auto res = Find( id );
		return (res ? res->first : nullptr);
	}
	std::string GetPath( const std::string& id )
	{
		auto path = paths.find( id );
		return (path != paths.end() ? path->second : "");
	}
	bool RequireResources( const std::string& id )
	{
		auto res = Find( id );
		if ( res )
		{
			++res->second;
			return true;
		}

		auto path = paths.find( id );
		if ( path == paths.end() )
		{
			return false;
		}
		T* resource = Load( path->second );
		if ( !resource )
		{
			return false;
		}
		resources.emplace( id, std::make_pair( resource, id ) );

		return true;
	}
	bool ReleaseResource( const std::string& id )
	{
		auto res = Find( id );
		if ( !res )
		{
			return false;
		}
		--res->second;
		if ( !res->second )
		{
			Unload( id );
		}

		return true;
	}
	T* Load( const std::string& id )
	{
		return static_cast<Derived*>(this)->Load( path );
	}

protected:
	void LoadPaths( const std::string& pathFile )
	{
		std::ifstream pathsF;
		pathsF.open( Utils::GetWorkingDirectory() + pathFile );

		if ( pathsF )
		{
			std::string line;
			while ( std::getline( pathsF, line ) )
			{
				std::stringstream keystream( line );
				std::string pathName;
				std::string path;

				keystream >> pathName:
				keystream >> path;

				paths.emplace( pathName, path );
			}
		}
		else
		{
			std::cerr << "No se pudo abrir archivo de rutas!." std::endl;
		}
	}
	void PurgeResources()
	{
		while ( resources.being() != resources.end() )
		{
			delete resources.begin()->second.first;
			resources.erase( resources.begin() );
		}
	}
	std::pair<T*, unsigned int>* Find( const std::string& id )
	{
		auto itr = resources.find( id );
		return (itr != resources.end() ? &itr->second : nullptr);
	}
	bool Unload( const std::string& id )
	{
		auto itr = resources.find( id );
		if ( itr == resources.end() )
		{
			return false;
		}
		delete itr->second.first;
		resources.erase( itr );

		return true;
	}
private:
	std::unordered_map<std::string, std::pair<T*, unsigned int>> resources;
	std::unordered_map<std::string, std::string> paths;
};
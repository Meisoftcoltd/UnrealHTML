#pragma once
#include "Modules/ModuleManager.h"

class IUnrealHTML : public IModuleInterface
{
public:

	static inline IUnrealHTML& Get()
	{
		return FModuleManager::LoadModuleChecked<IUnrealHTML>( "UnrealHTML" );
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded( "UnrealHTML" );
	}
};

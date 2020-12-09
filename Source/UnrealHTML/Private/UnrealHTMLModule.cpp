// Copyright 2020 Tracer Interactive, LLC. All Rights Reserved.
#include <UnrealHTMLModule.h>
#include "Modules/ModuleManager.h"

class FUnrealHTMLModule : public IUnrealHTML
{
public:
	virtual void StartupModule() override
	{
		//
	}

	virtual void ShutdownModule() override
	{
		//
	}
};

IMPLEMENT_MODULE(FUnrealHTMLModule, UnrealHTML);

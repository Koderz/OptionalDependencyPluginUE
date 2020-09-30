// Copyright Epic Games, Inc. All Rights Reserved.

#include "OptionalPlugin.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FOptionalPluginModule"


// This is the implementation of the current version found in the header
class FOptionalPlugin_V2 : public IOptionalPluginInterface_V2
{
public:
	FString GetMessage(FString Input) const override
	{
		return TEXT("You're using OptionalPlugin Version 2!");
	}

	int32 GetVersion() const override
	{
		return 2;
	}
};


// This is an old API example
class IOptionalPluginInterface_V1 : public IOptionalPluginInterface
{
public:
	static constexpr int32 Version = 1;
	virtual FString GetMessage() const = 0;
};

// This implements the old API example
class FOptionalPlugin_V1 : public IOptionalPluginInterface_V1
{
public:
	FString GetMessage() const override
	{
		return TEXT("You're using OptionalPlugin Version 1!");
	}

	int32 GetVersion() const override
	{
		return 1;
	}
};




class FOptionalPluginModule : public IOptionalPluginModule
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override
	{

	}

	virtual void ShutdownModule() override
	{

	}

	IOptionalPluginInterface* GetInterfaceByVersion(int32 VersionId) const override
	{
		static FOptionalPlugin_V2 Version2;
		static FOptionalPlugin_V1 Version1;

		switch (VersionId)
		{
		case 1:
			return &Version1;
		case 2:
			return &Version2;
		default:
			return nullptr;
		}
	}

};


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FOptionalPluginModule, OptionalPlugin)
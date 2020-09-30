// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class IOptionalPluginInterface
{
public:
	virtual ~IOptionalPluginInterface() { }
	virtual int32 GetVersion() const = 0;
};

class IOptionalPluginModule : public IModuleInterface
{
public:
	virtual IOptionalPluginInterface* GetInterfaceByVersion(int32 VersionId) const = 0;
};




class IOptionalPluginInterface_V2 : public IOptionalPluginInterface
{
public:
	static constexpr int32 Version = 2;
	virtual FString GetMessage(FString Input) const = 0;
};

using FOptionalPluginInterface = IOptionalPluginInterface_V2;


class FOptionalPlugin
{
	static FName GetModuleName() { return "OptionalPlugin"; }

public:
	static bool IsLoaded(bool bTryLoad = true)
	{
		IOptionalPluginModule* Module = bTryLoad ? FModuleManager::LoadModulePtr<IOptionalPluginModule>(GetModuleName()) : FModuleManager::GetModulePtr<IOptionalPluginModule>(GetModuleName());

		// If we can't find the module then we're definitely not supported.
		if (!Module)
		{
			return false;
		}

		// Validate that the module supports this version
		return Module->GetInterfaceByVersion(FOptionalPluginInterface::Version) != nullptr;
	}

	static FOptionalPluginInterface* Get(bool bTryLoad = true)
	{
		IOptionalPluginModule* Module = bTryLoad ? FModuleManager::LoadModulePtr<IOptionalPluginModule>(GetModuleName()) : FModuleManager::GetModulePtr<IOptionalPluginModule>(GetModuleName());
		check(Module);

		IOptionalPluginInterface* Utilities = Module->GetInterfaceByVersion(FOptionalPluginInterface::Version);

		return StaticCast<FOptionalPluginInterface*>(Utilities);
	}
};
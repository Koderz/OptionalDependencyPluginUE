#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"


//////////////////////////////////////////////////////////////////////////
// These do not change between versions as that would break the API

class IRuntimeImageUtilities
{
public:
	virtual ~IRuntimeImageUtilities() { };
	virtual int32 GetVersion() const = 0;
};

class IRuntimeImageUtilitiesModule : public IModuleInterface
{
public:
	virtual IRuntimeImageUtilities* GetUtilitiesVersion(int32 VersionId) = 0;
};
//////////////////////////////////////////////////////////////////////////



class FRuntimeImageUtilities_V1 : public IRuntimeImageUtilities
{
public:

	static constexpr int32 Version = 1;
	virtual int32 GetVersion() const override = 0;
	virtual FString GetName() const = 0;
};

class FRuntimeImageUtilities_V2 : public IRuntimeImageUtilities
{
public:

	static constexpr int32 Version = 2;
	virtual int32 GetVersion() const override = 0;
	virtual FString GetName() const = 0;
	virtual FString GetVersionName() = 0;
};

using FRuntimeImageUtilities = FRuntimeImageUtilities_V2;




//////////////////////////////////////////////////////////////////////////
// This does not change between versions as that would break the API
struct FRuntimeImageUtilitiesModuleInterface
{
	static FName GetModuleName() { return "RuntimeImageUtilities"; }

	static bool IsSupported()
	{
		IRuntimeImageUtilitiesModule* Module = FModuleManager::LoadModulePtr<IRuntimeImageUtilitiesModule>(GetModuleName());

		// If we can't find the module then we're definitely not supported.
		if (!Module)
		{
			return false;
		}

		// Validate that the module supports this version
		return Module->GetUtilitiesVersion(FRuntimeImageUtilities::Version) != nullptr;
	}

	static FRuntimeImageUtilities& GetImageUtilities()
	{
		IRuntimeImageUtilitiesModule* Module = FModuleManager::LoadModulePtr<IRuntimeImageUtilitiesModule>(GetModuleName());
		check(Module);

		IRuntimeImageUtilities* Utilities = Module->GetUtilitiesVersion(FRuntimeImageUtilities::Version);
		check(Utilities);

		return *StaticCast<FRuntimeImageUtilities*>(Utilities);
	}
};
//////////////////////////////////////////////////////////////////////////
// Copyright Epic Games, Inc. All Rights Reserved.

#include "RuntimeImageUtilities.h"

#include "RuntimeImageUtilities_V1.h"
#include "RuntimeImageUtilities_Current.h"

#define LOCTEXT_NAMESPACE "FRuntimeImageUtilitiesModule"

void FRuntimeImageUtilitiesModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void FRuntimeImageUtilitiesModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}





class FRuntimeImageUtilitiesImplementation_V1 : public FRuntimeImageUtilities_V1
{
public:

	int32 GetVersion() const override
	{
		return Version;
	}

	FString GetName() const override
	{
		return "Version 1";
	}
};

class FRuntimeImageUtilitiesImplementation_V2 : public FRuntimeImageUtilities_V2
{

public:

	int32 GetVersion() const override
	{
		return Version;
	}


	FString GetName() const override
	{
		return "Version 2";
	}


	FString GetVersionName() override
	{
		return "Bestest Version";
	}

};








IRuntimeImageUtilities* FRuntimeImageUtilitiesModule::GetUtilitiesVersion(int32 VersionId)
{
	static FRuntimeImageUtilitiesImplementation_V1 ImageUtilities_V1;
	static FRuntimeImageUtilitiesImplementation_V2 ImageUtilities_V2;
	switch (VersionId)
	{
	case 1:
		return &ImageUtilities_V1;
	case 2:
		return &ImageUtilities_V2;
	default:
		return nullptr;
	}


}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FRuntimeImageUtilitiesModule, RuntimeImageUtilities)
// Copyright Epic Games, Inc. All Rights Reserved.

#include "RuntimeMeshUtilitiesBPLibrary.h"
#include "RuntimeMeshUtilities.h"
#include "RuntimeImageUtilities.h"

URuntimeMeshUtilitiesBPLibrary::URuntimeMeshUtilitiesBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FString URuntimeMeshUtilitiesBPLibrary::GetMeshMessage()
{
	if (FRuntimeImageUtilitiesModuleInterface::IsSupported())
	{
		return FRuntimeImageUtilitiesModuleInterface::GetImageUtilities().GetName();
	}
	return TEXT("Library unsupported.");
}


// Copyright Epic Games, Inc. All Rights Reserved.

#include "RuntimeImageTestBPLibrary.h"
#include "RuntimeImageTest.h"
#include "RuntimeImageUtilities.h"

URuntimeImageTestBPLibrary::URuntimeImageTestBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FString URuntimeImageTestBPLibrary::GetTestMessage()
{
	if (FRuntimeImageUtilitiesModuleInterface::IsSupported())
	{
		return FRuntimeImageUtilitiesModuleInterface::GetImageUtilities()->GetName();
	}
	return TEXT("Library unsupported.");
}


// Copyright Epic Games, Inc. All Rights Reserved.

#include "DependentPluginOneBPLibrary.h"
#include "DependentPluginOne.h"
#include "OptionalPluginInterface.h"

UDependentPluginOneBPLibrary::UDependentPluginOneBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FString UDependentPluginOneBPLibrary::GetOptionalMessageOne()
{
	FOptionalPluginInterface* Interface = FOptionalPlugin::Get();
	if (Interface)
	{
		return Interface->GetMessage(TEXT(""));
	}
	return TEXT("Optional Plugin Not Found!");
}


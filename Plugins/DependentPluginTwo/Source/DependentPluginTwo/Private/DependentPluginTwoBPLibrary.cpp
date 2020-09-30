// Copyright Epic Games, Inc. All Rights Reserved.

#include "DependentPluginTwoBPLibrary.h"
#include "DependentPluginTwo.h"
#include "OptionalPluginInterface.h"

UDependentPluginTwoBPLibrary::UDependentPluginTwoBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FString UDependentPluginTwoBPLibrary::GetOptionalMessageTwo()
{
	FOptionalPluginInterface* Interface = FOptionalPlugin::Get();
	if (Interface)
	{
		return Interface->GetMessage();
	}
	return TEXT("Optional Plugin Not Found!");
}


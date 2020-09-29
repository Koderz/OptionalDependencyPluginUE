// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "RuntimeImageUtilities_Current.h"



class FRuntimeImageUtilitiesModule : public IRuntimeImageUtilitiesModule
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual IRuntimeImageUtilities* GetUtilitiesVersion(int32 VersionId) override;
};

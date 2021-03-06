// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "ThingsInWoodsHUD.generated.h"

UCLASS()
class AThingsInWoodsHUD : public AHUD
{
	GENERATED_BODY()

public:
	AThingsInWoodsHUD();

	/** */
	class AThingsInWoodsCharacter* PlayerPawn;

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;

private:

};


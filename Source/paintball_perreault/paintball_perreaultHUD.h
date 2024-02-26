// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "paintball_perreaultHUD.generated.h"

UCLASS()
class Apaintball_perreaultHUD : public AHUD
{
	GENERATED_BODY()

public:
	Apaintball_perreaultHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};


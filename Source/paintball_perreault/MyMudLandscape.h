// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MyMudLandscape.generated.h"

/**
 * 
 */
UCLASS()
class PAINTBALL_PERREAULT_API AMyMudLandscape : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMyMudLandscape();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:
	//Custom function that will create the render target
	void renderTargetFunc();

	//Custom function that will be called to draw the material
	UFUNCTION(BlueprintCallable, Category = "Mud")
		void GroundHit(FVector2D UVLoc, float Rot);

	//Initiak setup of components, materials and render target
	UPROPERTY()
		UStaticMeshComponent* landMesh;

	UPROPERTY()
		UMaterialInterface* MudInterface;
	
	UPROPERTY()
		UMaterialInstanceDynamic* MudDMI;

	UPROPERTY()
		UMaterialInterface* ImpactInterface;

	UPROPERTY()
		UMaterialInstanceDynamic* ImpactDMI;

	UPROPERTY()
		UTextureRenderTarget2D* LandRT;
	
	//Public variables that can be adjusted in the editor
	UPROPERTY(EditAnywhere)
		float strength = 3.0f;
	
	UPROPERTY(EditAnywhere)
		float UpMulti = 0.005f;

	UPROPERTY(EditAnywhere)
		float Scale = 0.008f;

	//Variables to calculate posision hit UV and scale
	UPROPERTY()
		FVector2D scrnPos;

	UPROPERTY()
		FVector2D scrnSize;


	
};

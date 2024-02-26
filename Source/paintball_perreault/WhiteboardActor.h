// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WhiteboardActor.generated.h"

UCLASS()
class PAINTBALL_PERREAULT_API AWhiteboardActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWhiteboardActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Creates mesh component
	UPROPERTY()
		UStaticMeshComponent* whiteboard_mesh;

	//Creates a reference to the marker material
	UPROPERTY()
		UMaterialInterface* markerMat;

	//Creates a dynamic material instance
	UPROPERTY()
		UMaterialInstanceDynamic* whiteboardMarker_MI;

	//Gets refrence to the render target
	UPROPERTY()
		UTextureRenderTarget2D* renderTarget;

	//Creates a blueprint function 
	UFUNCTION(BlueprintCallable)
		void DrawOnWhiteboard(FVector2D LocationToDraw);

	//Creates a drawsize varrible that can be manipulated
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float drawSize;

};

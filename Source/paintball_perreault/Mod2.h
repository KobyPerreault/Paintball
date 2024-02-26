// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Mod2.generated.h"

UCLASS()
class PAINTBALL_PERREAULT_API AMod2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMod2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//PostActorCreated allows us to call the CreateSquare function when the actor is done spawning in the world
	virtual void PostActorCreated() override;

	//PostLoad this is essentially a cleanup function that gets called immediately after loading an object
	virtual void PostLoad() override;

	//CreateSquare is the function we call that will actually generate the square we want to create
	virtual void CreateSquare();

private:
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* mesh;
};

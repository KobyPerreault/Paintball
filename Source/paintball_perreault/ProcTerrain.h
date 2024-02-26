// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProcTerrain.generated.h"

UCLASS()
class PAINTBALL_PERREAULT_API AProcTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcTerrain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Defines the properties of the Actor
	UPROPERTY(BlueprintreadWrite, EditAnywhere, Category = "Defaults")
		UProceduralMeshComponent* TerrainMesh;
	
	UPROPERTY(BlueprintreadWrite, EditAnywhere, Category = "Defaults")
		TArray <FVector> Vertices;
	
	UPROPERTY(BlueprintreadWrite, EditAnywhere, Category = "Defaults")
		TArray <int> Triangles;
	
	UPROPERTY(BlueprintreadWrite, EditAnywhere, Category = "Defaults")
		TArray<FVector> Normals;
	UPROPERTY(BlueprintreadWrite, EditAnywhere, Category = "Defaults")
		TArray<FVector2D> UV0;

	UPROPERTY(BlueprintreadWrite, EditAnywhere, Category = "Defaults")
		TArray <FLinearColor> VertexColors;
	
	TArray<FColor> UpVertColors;
	
	UPROPERTY(BlueprintreadWrite, EditAnywhere, Category = "Defaults")
		TArray<FProcMeshTangent> Tangents;

	void GenerateMesh();
	
	UFUNCTION(BlueprintCallable)
		void AlterTerrain(FVector impactPoint);
	
	UFUNCTION(BlueprintCallable)
		void AlterTerrainOpposite(FVector impactPoint);

	UPROPERTY(BlueprintreadWrite, EditAnywhere, Category = "Defaults")
		FVector depth;
	
	UPROPERTY(BlueprintreadWrite, EditAnywhere, Category = "Defaults")
		float radius;

};

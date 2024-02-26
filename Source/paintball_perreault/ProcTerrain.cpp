// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcTerrain.h"

// Sets default values
AProcTerrain::AProcTerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates an abstract subobject called RootComponent and a default subobject called TerrainMesh and attaches that to the RootComponent

	RootComponent = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	TerrainMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("TerrainMesh"));

	TerrainMesh->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AProcTerrain::BeginPlay()
{
	Super::BeginPlay();
	GenerateMesh();
}

// Called every frame
void AProcTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProcTerrain::GenerateMesh()
{
	TerrainMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UV0, VertexColors, Tangents, true);
}

//Function alters the terrain downward based on the impact point and depth
void AProcTerrain::AlterTerrain(FVector impactPoint)
{
	for (int i = 0; i < Vertices.Num(); i++)
	{
		//If the verticies fall within the impact point, their vertices are moved down by the depth and then the mesh is updated to reflect this
		if (FVector(Vertices[i] - impactPoint).Size() < radius)
		{
			Vertices[i] = Vertices[i] - depth;
			TerrainMesh->UpdateMeshSection(0, Vertices, Normals, UV0, UpVertColors, Tangents);
		}
	}
}

//Function alters the terrain upward based on the impact point and depth
void AProcTerrain::AlterTerrainOpposite(FVector impactPoint)
{
	for (int i = 0; i < Vertices.Num(); i++)
	{
		//If the verticies fall within the impact point, their vertices are moved up by the depth and then the mesh is updated to reflect this
		if (FVector(Vertices[i] - impactPoint).Size() < radius)
		{
			Vertices[i] = Vertices[i] + depth;
			TerrainMesh->UpdateMeshSection(0, Vertices, Normals, UV0, UpVertColors, Tangents);
		}
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Mod2.h"

// Sets default values
AMod2::AMod2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject <UProceduralMeshComponent>(TEXT("GeneratedMesh"));

	RootComponent = mesh;
}

// Called when the game starts or when spawned
void AMod2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMod2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMod2::PostActorCreated()
{
	Super::PostActorCreated();
	CreateSquare();
}

void AMod2::PostLoad()
{
	Super::PostLoad();
	CreateSquare();
}

void AMod2::CreateSquare()
{
	TArray <FVector> Vertices;
	TArray <int32> Triangles;
	TArray <FVector> Normals;
	TArray < FLinearColor > Colors;
	Vertices.Add(FVector(0.f, 0.f, 0.f));
	Vertices.Add(FVector(0.f, 100.f, 0.f));
	Vertices.Add(FVector(0.f, 0.f, 100.f));
	Vertices.Add(FVector(0.f, 100.f, 100.f));
	Triangles.Add(0);
	Triangles.Add(1);
	Triangles.Add(2);
	Triangles.Add(3);
	Triangles.Add(2);
	Triangles.Add(1);

	for (int32 i = 0; i < Vertices.Num(); i++)
	{
		Normals.Add(FVector(0.f, 0.f, 1.f));
		Colors.Add(FLinearColor::Red);
	}

	// Optonal arrays.
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> Tangents;
	mesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UV0, Colors, Tangents, true);
}
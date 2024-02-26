// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcObject.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
AProcObject::AProcObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	ObjectMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ObjectMesh"));

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));

	ObjectMesh->AttachTo(RootComponent);

	BaseMesh->SetCollisionProfileName("NoCollision");
	BaseMesh->SetHiddenInGame(true);
	BaseMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	BaseMesh->AttachTo(ObjectMesh);

}

// Called when the game starts or when spawned
void AProcObject::BeginPlay()
{
	Super::BeginPlay();

	if (BaseMesh)
	{
		UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(BaseMesh->GetStaticMesh(), 0, 0, Vertices, Triangles, Normals, UV0, Tangents);
		UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UV0, Normals, Tangents);

		GenerateMesh();
	}
	
}

// Called every frame
void AProcObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProcObject::GenerateMesh()
{
	ObjectMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UV0, VertexColors, Tangents, true);
}

void AProcObject::AlterMesh(FVector impactPoint)
{
	for (int i = 0; i < Vertices.Num(); i++)
	{
		if (FVector(Vertices[i] - impactPoint).Size() < radius)
		{
			Vertices[i] = Vertices[i] - depth;
			ObjectMesh->UpdateMeshSection(0, Vertices, Normals, UV0, UpVertexColors, Tangents);
		}
	}
}


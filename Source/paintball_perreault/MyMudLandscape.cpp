// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMudLandscape.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/Canvas.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

AMyMudLandscape::AMyMudLandscape()
{
	landMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Landscape Mesh"));

	RootComponent = landMesh;

	{
		//Find the landscape mesh and set it
		static ConstructorHelpers::FObjectFinder<UStaticMesh> asset(TEXT("StaticMesh'/Game/Maps/Paintball.Paintball'"));
		landMesh->SetStaticMesh(asset.Object);
	}

	{
		//Find mud material
		static ConstructorHelpers::FObjectFinder<UMaterial> asset(TEXT("Material'/Game/FirstPerson/Mud/mud_MAT.mud_MAT'"));
		MudInterface = asset.Object;
	}

	{
		//Find impact material
		static ConstructorHelpers::FObjectFinder<UMaterial> asset(TEXT("Material'/Game/FirstPerson/Mud/impact_MAT.impact_MAT'"));
		ImpactInterface = asset.Object;
	}
}

void AMyMudLandscape::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	//If mud material was set, then create a dynamic material instance and set it to the landscape mesh
	if (MudInterface)
	{
		MudDMI = UMaterialInstanceDynamic::Create(MudInterface, this);
		landMesh->SetMaterial(0, MudDMI);
	}

	//IF impact material was set, then set the default values inside the material
	if (ImpactInterface)
	{
		ImpactDMI = UMaterialInstanceDynamic::Create(ImpactInterface, this);
		ImpactDMI->SetScalarParameterValue("Strength", strength);
		ImpactDMI->SetScalarParameterValue("UpMulti", UpMulti);
	}
}



void AMyMudLandscape::BeginPlay()
{
	Super::BeginPlay();

	//Setup the render target
	renderTargetFunc();

}

void AMyMudLandscape::renderTargetFunc()
{
	//Creates the render target and sets it as the texture paramerter inside the mud material
	LandRT = UKismetRenderingLibrary::CreateRenderTarget2D(GetWorld(), 8192, 8192, ETextureRenderTargetFormat::RTF_RGBA8, FLinearColor::White, false);
	MudDMI->SetTextureParameterValue("Dis", LandRT);
}

void AMyMudLandscape::GroundHit(FVector2D UVLoc, float Rot)
{
	//Initial local variables
	UCanvas* Canvas;
	FVector2D size;
	FDrawToRenderTargetContext Rendercontext;

	//Begin draw to canvas
	UKismetRenderingLibrary::BeginDrawCanvasToRenderTarget(GetWorld(), LandRT, Canvas, size, Rendercontext);

	//Calculate location using hit uvs and scale
	scrnPos = (size * (UVLoc - 0.5f)) + ((size * 0.5f) * (1.0f - Scale));
	scrnSize = (size * Scale);

	//Draw the impact material
	Canvas->K2_DrawMaterial(ImpactDMI, scrnPos, scrnSize, FVector2D(0.0f, 0.0f), FVector2D(1.0f, 1.0f), Rot, FVector2D(0.5f, 0.5f));
	UKismetRenderingLibrary::EndDrawCanvasToRenderTarget(GetWorld(), Rendercontext);

	//Debug to make sure this event is being called. Comment out to hide
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("GroundHit Activated")));
}

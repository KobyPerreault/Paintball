// Fill out your copyright notice in the Description page of Project Settings.


#include "WhiteboardActor.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Engine.h"

// Sets default values
AWhiteboardActor::AWhiteboardActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	whiteboard_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WHITEBOARD MESH"));
	RootComponent = whiteboard_mesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>asset(TEXT("StaticMesh'/Game/Whiteboard/Cube.Cube'"));

	//sets the mesh of the whiteboard_mesh object to the asset from above
	whiteboard_mesh->SetStaticMesh(asset.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial>asset1(TEXT("Material'/Game/Whiteboard/M_Whiteboard.M_Whiteboard'"));

	//sets the material of the whiteboard_mesh object to the asset from above
	whiteboard_mesh->SetMaterial(0, asset1.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial>asset2(TEXT("Material'/Game/Whiteboard/M_Marker.M_Marker'"));

	markerMat = asset2.Object;

	static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D>asset3(TEXT("TextureRenderTarget2D'/Game/Whiteboard/RT.RT'"));

	renderTarget = asset3.Object;

}

// Called when the game starts or when spawned
void AWhiteboardActor::BeginPlay()
{
	Super::BeginPlay();

	//Checking to see if the markerMat is set to something and if not creates the material 
	if (markerMat) 
	{
		whiteboardMarker_MI = UMaterialInstanceDynamic::Create(markerMat, this);
	}
	
	//Resets the render target
	UKismetRenderingLibrary::ClearRenderTarget2D(this, renderTarget, FLinearColor::Black);
	//Sets the draw size variable
	whiteboardMarker_MI->SetScalarParameterValue("DrawSize", drawSize);
}

// Called every frame
void AWhiteboardActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWhiteboardActor::DrawOnWhiteboard(FVector2D LocationToDraw)
{
	whiteboardMarker_MI->SetVectorParameterValue("DrawLocation", FLinearColor(LocationToDraw.X, LocationToDraw.Y, 0));
	UKismetRenderingLibrary::DrawMaterialToRenderTarget(this, renderTarget, whiteboardMarker_MI);
}

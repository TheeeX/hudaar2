// Fill out your copyright notice in the Description page of Project Settings.

#include "hudAR2.h"
#include "MyActorA.h"


// Sets default values
AMyActorA::AMyActorA()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));

	RootComponent = Root;

	MyCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyCube"));
	MyCube->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AMyActorA::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActorA::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FRotator Crot = GetActorRotation();
	FVector NewLocation = GetActorLocation();
	UE_LOG(LogTemp, Log, TEXT("Rotation(current): %f, %f, %f"), Crot.Roll, Crot.Pitch, Crot.Yaw);

	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.X += DeltaHeight * 20.0f;
	NewLocation.Y += DeltaHeight * 20.0f;
	NewLocation.Z += DeltaHeight * 20.0f;
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
}


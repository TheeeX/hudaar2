// Fill out your copyright notice in the Description page of Project Settings.

#include "hudAR2.h"
#include "MyActorB.h"

#include "HudGyro.h"
#include <sstream>
#include <CString.h>

int hgyro = 0, gyroclk = 0;


// Sets default values
AMyActorB::AMyActorB()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootB = CreateDefaultSubobject<UBoxComponent>(TEXT("RootB"));

	RootComponent = RootB;

	MyCubeB = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyCubeB"));
	MyCubeB->AttachTo(RootComponent);


	//Initialise Gyro
	hgyro = initQtr();

	UE_LOG(LogTemp, Log, TEXT("Initialise Gyro : %d"), hgyro);

}

// Called when the game starts or when spawned
void AMyActorB::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActorB::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FRotator Crot = GetActorRotation();
	UE_LOG(LogTemp, Log, TEXT("Rotation(current): %f, %f, %f"), Crot.Roll, Crot.Pitch, Crot.Yaw);
	//FVector NewLocation = GetActorLocation();
	//NewLocation
	if (hgyro == 1 && gyroclk == 1) {

		float *hEulr = getQtr();
		UE_LOG(LogTemp, Log, TEXT("Eulers(Gyro): %f, %f, %f"), hEulr[0], hEulr[1], hEulr[2]);
		FRotator NewRot;
		NewRot.Yaw = hEulr[0];
		NewRot.Pitch = hEulr[1];
		NewRot.Roll = hEulr[2];
		
		SetActorRelativeRotation(NewRot);
		FRotator RotA = GetActorRotation();
		UE_LOG(LogTemp, Log, TEXT("Rotation(After): %f, %f, %f"), RotA.Roll, RotA.Pitch, RotA.Yaw);
		gyroclk = 0;

	}
	else
	{
		gyroclk = 1; 
	}
}


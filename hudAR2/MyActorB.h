// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MyActorB.generated.h"

UCLASS()
class HUDAR2_API AMyActorB : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActorB();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	UPROPERTY(EditAnywhere)
		UShapeComponent* RootB;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MyCubeB;

	float RunningTime;

	
};

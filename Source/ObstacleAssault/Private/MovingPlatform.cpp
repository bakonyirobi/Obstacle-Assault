// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// Set start location
	StartLocation = GetActorLocation();

	FString Name = GetName();

	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move platform forwards
		// Get current location
	FVector CurrentLocation = GetActorLocation();
	    // Add vector to that location
	CurrentLocation += PlatformVelocity * DeltaTime;
		// Set the location
	SetActorLocation(CurrentLocation);
	// Send platform back if gone too far
		// Check how far we've moved
	float DistanceMoved = FVector::Distance(StartLocation, CurrentLocation);     // Calculate distance between StartLocation and CurrentLocation
		// Reverse direction of motion if gone too far
	if (DistanceMoved >= MoveDistance)
	{
		FString Name = GetName();
		float OverShoot = DistanceMoved - MoveDistance;
		UE_LOG(LogTemp, Display, TEXT("Platform %s overshot by %f"), *Name, OverShoot);
		StartLocation += PlatformVelocity.GetSafeNormal() * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
}


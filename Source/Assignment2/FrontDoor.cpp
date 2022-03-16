// Fill out your copyright notice in the Description page of Project Settings.


#include "FrontDoor.h"

// Sets default values for this component's properties
UFrontDoor::UFrontDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFrontDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFrontDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (light->IsHidden() == true)
	{
		FRotator rotationLeft = FRotator(0, -65, 0);
		leftDoor->SetActorRelativeRotation(rotationLeft);

		FRotator rotationRight = FRotator(0, 180+65, 0);
		rightDoor->SetActorRelativeRotation(rotationRight);
	}
}


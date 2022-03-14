// Fill out your copyright notice in the Description page of Project Settings.


#include "DisableLight.h"

// Sets default values for this component's properties
UDisableLight::UDisableLight()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	collider->InitBoxExtent(FVector(25, 25, 25));
	collider->SetCollisionProfileName(TEXT("Trigger"));
	collider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	collider->SetWorldLocation(FVector(0, 0, 0));
	// ...
}


// Called when the game starts
void UDisableLight::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UDisableLight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDisableLight::DisableLight()
{
	if (lights.Num() <= 0) return;
	for (int i = 0; i < lights.Num(); i++)
	{
		lights[i]->SetActorHiddenInGame(true);
		lights[i]->SetActorEnableCollision(false);
		lights[i]->enableBlinking = false;
	}
}


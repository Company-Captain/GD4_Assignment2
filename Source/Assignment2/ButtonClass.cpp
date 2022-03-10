// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonClass.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AButtonClass::AButtonClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AButtonClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AButtonClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}




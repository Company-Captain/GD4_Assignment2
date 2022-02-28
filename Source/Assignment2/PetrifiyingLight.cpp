// Fill out your copyright notice in the Description page of Project Settings.


#include "PetrifiyingLight.h"
#include "Runtime/Engine/Public/EngineGlobals.h"

// Sets default values
APetrifiyingLight::APetrifiyingLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	spotlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	RootComponent = spotlight;

	// fTest

	lightCone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightCone"));
	lightCone->SetupAttachment(RootComponent);
	//lightCone->SetUsingAbsoluteRotation(true);

	rotationCurve = CreateDefaultSubobject<UCurveFloat>(TEXT("RotationCurve"));
	movementCurve = CreateDefaultSubobject<UCurveFloat>(TEXT("MovementCurve"));
	blinkingCurve = CreateDefaultSubobject<UCurveFloat>(TEXT("BlinkingCurve"));

}

// Called when the game starts or when spawned
void APetrifiyingLight::BeginPlay()
{
	Super::BeginPlay();
	
	lightCone->SetCollisionProfileName(TEXT("Trigger"));
	lightCone->SetCollisionResponseToAllChannels(ECR_Ignore);
	lightCone->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	RotationBegin();
	MovementBegin();
	BlinkingBegin();
}

// Called every frame
void APetrifiyingLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotationTick(DeltaTime);
	MovementTick(DeltaTime);
	BlinkingTick(DeltaTime);
}

void APetrifiyingLight::RotationBegin()
{
	if (enableRotation)
	{
		if (rotationCurve)
		{
			defaultRotation = GetActorRotation();
			FOnTimelineFloat UpdateRotationTimeline;
			UpdateRotationTimeline.BindUFunction(this, FName("UpdateRotationTimeline"));
			rotationTimeline.AddInterpFloat(rotationCurve, UpdateRotationTimeline);
			rotationTimeline.SetLooping(true);
			rotationTimeline.PlayFromStart();
		}
	}
}

void APetrifiyingLight::RotationTick(float DeltaTime)
{
	if (enableRotation)
	{
		rotationTimeline.TickTimeline(DeltaTime);
	}
		
}

void APetrifiyingLight::MovementBegin()
{
	if (enableMovement)
	{
		if (movementCurve)
		{
			defaultPosition = GetActorLocation();
			FOnTimelineFloat UpdateMovementTimeline;
			UpdateMovementTimeline.BindUFunction(this, FName("UpdateMovementTimeline"));
			movementTimeline.AddInterpFloat(movementCurve, UpdateMovementTimeline);
			movementTimeline.SetLooping(true);
			movementTimeline.PlayFromStart();
		}
	}
}

void APetrifiyingLight::MovementTick(float DeltaTime)
{
	if (enableMovement)
	{
		movementTimeline.TickTimeline(DeltaTime);
	}
}

void APetrifiyingLight::BlinkingBegin()
{
	if (enableBlinking)
	{
		if (blinkingCurve)
		{
			FOnTimelineFloat UpdateBlinkingTimeline;
			UpdateBlinkingTimeline.BindUFunction(this, FName("UpdateBlinkingTimeline"));
			blinkingTimeline.AddInterpFloat(blinkingCurve, UpdateBlinkingTimeline);
			blinkingTimeline.SetLooping(true);
			blinkingTimeline.PlayFromStart();
		}
	}
}

void APetrifiyingLight::BlinkingTick(float DeltaTime)
{
	if (enableBlinking)
	{
		blinkingTimeline.TickTimeline(DeltaTime);
	}
}



void APetrifiyingLight::UpdateBlinkingTimeline(float output)
{
	if (output < 1)
	{
		lightCone->SetVisibility(false);
		spotlight->SetVisibility(false);
	}
	else
	{
		lightCone->SetVisibility(true);
		spotlight->SetVisibility(true);
	}
}

void APetrifiyingLight::UpdateRotationTimeline(float output)
{
	FRotator newRotation;

	switch (rotationAxis)
	{
	case RotationAxis::Pitch:
		newRotation = FRotator(defaultRotation.Pitch + output, defaultRotation.Yaw, defaultRotation.Roll);
		break;
	case RotationAxis::Yaw:
		newRotation = FRotator(defaultRotation.Pitch, defaultRotation.Yaw + output, defaultRotation.Roll);
		break;
	case RotationAxis::Roll:
		newRotation = FRotator(defaultRotation.Pitch, defaultRotation.Yaw, defaultRotation.Roll + output);
		break;
	default:
		break;
	}

	SetActorRelativeRotation(newRotation);
}

void APetrifiyingLight::UpdateMovementTimeline(float output)
{
	FVector newPosition;

	switch (movementAxis)
	{
	case Axis::X:
		newPosition = FVector(defaultPosition.X + (output * 100), defaultPosition.Y, defaultPosition.Z);
		break;
	case Axis::Y:
		newPosition = FVector(defaultPosition.X, defaultPosition.Y + (output * 100), defaultPosition.Z);
		break;
	case Axis::Z:
		newPosition = FVector(defaultPosition.X, defaultPosition.Y, defaultPosition.Z + (output * 100));
		break;
	default:
		break;
	}

	SetActorRelativeLocation(newPosition);
}


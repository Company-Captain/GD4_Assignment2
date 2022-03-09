// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SpotLightComponent.h"
#include "Components/TimelineComponent.h"
#include "ProceduralConeMesh.h"
#include "PetrifiyingLight.generated.h"

UENUM()
enum class Axis
{
	X   UMETA(DisplayName = "X"),
	Y	UMETA(DisplayName = "Y"),
	Z   UMETA(DisplayName = "Z"),
};

UENUM()
enum class RotationAxis
{
	Pitch   UMETA(DisplayName = "Pitch"),
	Yaw	UMETA(DisplayName = "Yaw"),
	Roll   UMETA(DisplayName = "Roll"),
};

UCLASS()
class ASSIGNMENT2_API APetrifiyingLight : public AActor
{
	GENERATED_BODY()

		// Test
public:		
	UPROPERTY(EditAnywhere, Category = "Visuals")
		UProceduralConeMesh* proceduralMesh;

	UPROPERTY(EditAnywhere, Category = "Visuals")
		class USpotLightComponent* spotlight;


	UPROPERTY(EditAnywhere, Category = "Rotation")
		bool enableRotation;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Rotation")
		RotationAxis rotationAxis;

	FTimeline rotationTimeline;
	FRotator defaultRotation;

	UPROPERTY(EditAnywhere, Category = "Rotation")
		UCurveFloat* rotationCurve;


	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Blinking")
		bool enableBlinking;

	FTimeline blinkingTimeline;

	UPROPERTY(EditAnywhere, Category = "Blinking")
		UCurveFloat* blinkingCurve;


	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Movement")
		bool enableMovement;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Movement")
		Axis movementAxis;

		FTimeline movementTimeline;
		FVector defaultPosition;

	UPROPERTY(EditAnywhere, Category = "Movement")
		UCurveFloat* movementCurve;

	FTimerHandle timerHandle;
	
public:	
	// Sets default values for this actor's properties
	APetrifiyingLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Blinking();
	void RotationBegin();
	void RotationTick(float DeltaTime);
	void MovementBegin();
	void MovementTick(float DeltaTime);
	void BlinkingBegin();
	void BlinkingTick(float DeltaTime);

	UFUNCTION()
	void UpdateBlinkingTimeline(float output);
	UFUNCTION()
	void UpdateRotationTimeline(float output);
	UFUNCTION()
	void UpdateMovementTimeline(float output);

};

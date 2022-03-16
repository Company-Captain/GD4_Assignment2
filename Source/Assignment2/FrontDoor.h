// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/StaticMeshActor.h"
#include "PetrifiyingLight.h"
#include "FrontDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASSIGNMENT2_API UFrontDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		APetrifiyingLight* light;

	UPROPERTY(EditAnywhere)
		AStaticMeshActor* leftDoor;

	UPROPERTY(EditAnywhere)
		AStaticMeshActor* rightDoor;


public:	
	// Sets default values for this component's properties
	UFrontDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

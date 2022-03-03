// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProceduralMeshComponent.h"
#include "ProceduralConeMesh.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASSIGNMENT2_API UProceduralConeMesh : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int numberOfRays;
	UPROPERTY(EditAnywhere)
	int innerRadius;
	UPROPERTY(EditAnywhere)
	int outerRadius;
	UPROPERTY(EditAnywhere)
	int length;

	TArray<FVector> vertices;
	TArray<int> triangles;
	TArray<FVector2D> UVs;

	UProceduralMeshComponent* mesh;

public:

	UPROPERTY(EditAnywhere)
	UMaterial* material;

public:	
	// Sets default values for this component's properties
	UProceduralConeMesh();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

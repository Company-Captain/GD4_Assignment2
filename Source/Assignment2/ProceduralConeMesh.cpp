// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralConeMesh.h"
#include "Engine/World.h"
#include "Math/UnrealMathVectorConstants.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UProceduralConeMesh::UProceduralConeMesh()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//numberOfRays = 16;
	//innerRadius = 25;
	//outerRadius = 100;
	//length = 100;

	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMeshComponent"));
}


// Called when the game starts
void UProceduralConeMesh::BeginPlay()
{
	Super::BeginPlay();


	FVector parentLocation = GetOwner()->GetActorLocation();
	FVector actorForward = GetOwner()->GetActorForwardVector();
	FVector actorRight = GetOwner()->GetActorRightVector();
	FVector actorUp = GetOwner()->GetActorUpVector();

	FRotator temp = FRotator(-90, 0, 0);

	float angle = 0;
	for (int i = 0; i < numberOfRays; i++)
	{
		float x = FMath::Sin(angle);
		float y = FMath::Cos(angle);
		angle += 2 * PI / numberOfRays;

		FVector rayStart = parentLocation + (actorRight * x * innerRadius) + (actorUp * y * innerRadius);
		FVector rayEnd = parentLocation + (actorForward * length) + (actorRight * x * outerRadius) + (actorUp * y * outerRadius);

		FHitResult outHit;
		bool isHit = GetWorld()->LineTraceSingleByObjectType(outHit, rayStart, rayEnd, ECC_WorldStatic);
		//DrawDebugLine(GetWorld(), rayStart, rayEnd, FColor::Green, false, 1, 0, 1);

		vertices.Add(rayStart);
		if (isHit) vertices.Add(outHit.ImpactPoint);
		else vertices.Add(rayEnd);
	}

	for (int i = 0; i < vertices.Num(); i++)
	{
		triangles.Add(i);
		triangles.Add(i+1);
		triangles.Add(i+2);

		triangles.Add(i+2);
		triangles.Add(i+1);
		triangles.Add(i+3);

		/*UVs.Add(FVector2D(0, 0));
		UVs.Add(FVector2D(0, 1));
		UVs.Add(FVector2D(1, 0));
		UVs.Add(FVector2D(1, 1));*/
	}
	mesh->CreateMeshSection(0, vertices, triangles, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>(), true);
	mesh->SetMaterial(0, material);
}


// Called every frame
void UProceduralConeMesh::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector parentLocation = GetOwner()->GetActorLocation();
	FVector actorForward = GetOwner()->GetActorForwardVector();
	FVector actorRight = GetOwner()->GetActorRightVector();
	FVector actorUp = GetOwner()->GetActorUpVector();

	FRotator temp = FRotator(-90, 0, 0);

	float angle = 0;
	for (int i = 0; i < numberOfRays; i++)
	{
		float x = FMath::Sin(angle);
		float y = FMath::Cos(angle);
		angle += 2 * PI / numberOfRays;

		FVector rayStart = parentLocation + (actorRight * x * innerRadius) + (actorUp * y * innerRadius);
		FVector rayEnd = parentLocation + (actorForward * length) + (actorRight * x * outerRadius) + (actorUp * y * outerRadius);

		FHitResult outHit;
		bool isHit = GetWorld()->LineTraceSingleByObjectType(outHit, rayStart, rayEnd, ECC_WorldStatic);
		//DrawDebugLine(GetWorld(), rayStart, rayEnd, FColor::Green, false, 1, 0, 1);




		//mesh->CreateMeshSection()
	}
}


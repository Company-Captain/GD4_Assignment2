// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralConeMesh.h"
#include "Engine/World.h"
#include "Math/UnrealMathVectorConstants.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UProceduralConeMesh::UProceduralConeMesh()
{
	PrimaryComponentTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMeshComponent"));
	//mesh->bUseComplexAsSimpleCollision = true;
	//test
}


// Called when the game starts
void UProceduralConeMesh::BeginPlay()
{
	Super::BeginPlay();

	FVector parentLocation = GetOwner()->GetActorLocation();
	FVector actorForward = GetOwner()->GetActorForwardVector();
	FVector actorRight = GetOwner()->GetActorRightVector();
	FVector actorUp = GetOwner()->GetActorUpVector();

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

	for (int i = 0; i < vertices.Num() - 2; i++)
	{
		triangles.Add(i);
		triangles.Add(i+1);
		triangles.Add(i+2);

		triangles.Add(i+2);
		triangles.Add(i+1);
		triangles.Add(i+3);
	}
	int lastVertex = vertices.Num() - 1;

	triangles.Add(lastVertex);
	triangles.Add(lastVertex - 1);
	triangles.Add(0);

	triangles.Add(lastVertex - 1);
	triangles.Add(lastVertex);
	triangles.Add(0);

	triangles.Add(0);
	triangles.Add(lastVertex);
	triangles.Add(1);

	triangles.Add(lastVertex);
	triangles.Add(0);
	triangles.Add(1);

	triangles.Add(1);
	triangles.Add(0);
	triangles.Add(2);


	mesh->CreateMeshSection(0, vertices, triangles, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>(), true);
	mesh->SetMaterial(0, material);

	mesh->SetCollisionProfileName(TEXT("Trigger"));
	mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	mesh->bUseComplexAsSimpleCollision = true;
}


// Called every frame
void UProceduralConeMesh::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector parentLocation = GetOwner()->GetActorLocation();
	FVector actorForward = GetOwner()->GetActorForwardVector();
	FVector actorRight = GetOwner()->GetActorRightVector();
	FVector actorUp = GetOwner()->GetActorUpVector();

	float angle = 0;
	int vertexIndex = 0;
	for (int i = 0; i < numberOfRays; i++)
	{
		float x = FMath::Sin(angle);
		float y = FMath::Cos(angle);
		angle += 2 * PI / numberOfRays;

		FVector rayStart = parentLocation + (actorRight * x * innerRadius) + (actorUp * y * innerRadius);
		FVector rayEnd = parentLocation + (actorForward * length) + (actorRight * x * outerRadius) + (actorUp * y * outerRadius);

		FHitResult outHit;
		bool isHit = GetWorld()->LineTraceSingleByObjectType(outHit, rayStart, rayEnd, ECC_WorldStatic);
		//DrawDebugLine(GetWorld(), rayStart, rayEnd, FColor::Green, false, 0.001 , 0, 1);

		vertices[vertexIndex] = rayStart;
		if (isHit) vertices[vertexIndex + 1] = outHit.ImpactPoint;
		else vertices[vertexIndex + 1] = rayEnd;
		
		vertexIndex += 2;
	}
	mesh->UpdateMeshSection(0, vertices, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>());
}


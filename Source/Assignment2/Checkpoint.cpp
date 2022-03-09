// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include "Assignment2Character.h"
#include "Assignment2GameMode.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Capsule"));
	collider->InitBoxExtent(FVector(50,50,50));
	collider->SetCollisionProfileName(TEXT("Trigger"));

	collider->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAssignment2Character* player = Cast<AAssignment2Character>(OtherActor);
	if (player)
	{
		AGameModeBase* gm = GetWorld()->GetAuthGameMode();
		AAssignment2GameMode* cgm = Cast<AAssignment2GameMode>(gm);
		//cgm->respawnPoint = player->GetTransform();
	}
}


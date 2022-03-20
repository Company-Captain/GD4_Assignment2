// Copyright Epic Games, Inc. All Rights Reserved.

#include "Assignment2GameMode.h"
#include "Assignment2Character.h"
#include "UObject/ConstructorHelpers.h"

AAssignment2GameMode::AAssignment2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AAssignment2GameMode::BeginPlay()
{
    Super::BeginPlay();

    //Bind our Player died delegate to the Gamemode's PlayerDied function.
    if (!OnPlayerDied.IsBound())
    {
        OnPlayerDied.AddDynamic(this, &AAssignment2GameMode::PlayerDied);
    }
}

void AAssignment2GameMode::RestartPlayer(AController* NewPlayer)
{
	if (NewPlayer == nullptr || NewPlayer->IsPendingKillPending())
	{
		return;
	}

	AActor* StartSpot = FindPlayerStart(NewPlayer);

	// If a start spot wasn't found,
	if (StartSpot == nullptr)
	{
		// Check for a previously assigned spot
		if (NewPlayer->StartSpot != nullptr)
		{
			StartSpot = NewPlayer->StartSpot.Get();
			UE_LOG(LogGameMode, Warning, TEXT("RestartPlayer: Player start not found, using last start spot"));
		}
	}
	if (respawnPoint.GetLocation() == FVector(0,0,0)) respawnPoint = StartSpot->GetTransform();
	FVector rpLoc = respawnPoint.GetLocation();
	FVector bandaid = FVector(rpLoc.X, rpLoc.Y, rpLoc.Z + 20.0f);
	respawnPoint.SetLocation(bandaid);

    Super::RestartPlayerAtTransform(NewPlayer, respawnPoint);
}

void AAssignment2GameMode::PlayerDied(ACharacter* Character)
{
    //Get a reference to our Character's Player Controller
    AController* CharacterController = Character->GetController();
    RestartPlayer(CharacterController);
}

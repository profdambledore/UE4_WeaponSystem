// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE4_WeaponSystemGameModeBase.h"

#include "BaseHUD.h"
#include "UObject/ConstructorHelpers.h"

// Constructor function
AUE4_WeaponSystemGameModeBase::AUE4_WeaponSystemGameModeBase() : Super()
{
	// Use ContructorHelpers to find classes to set
	// Default Pawn
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnObject(TEXT("/Game/Player/BP_PlayerCharacter"));
	// Check that the class has been found
	if (DefaultPawnObject.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Check Succeeded"))
		DefaultPawnClass = DefaultPawnObject.Class;
	}

	// Default HUD
	HUDClass = ABaseHUD::StaticClass();
}
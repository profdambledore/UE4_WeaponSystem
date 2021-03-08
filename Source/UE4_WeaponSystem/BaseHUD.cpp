// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseHUD.h"

#include "BaseCharacter.h"
#include "PlayerHUDWidget.h"
#include "PlayerMenuWidget.h"

ABaseHUD::ABaseHUD()
{
	UE_LOG(LogTemp, Warning, TEXT("HUD Online"));

	// Setup Widget Components
	static ConstructorHelpers::FClassFinder<UPlayerHUDWidget>FoundPHWidget(TEXT("/Game/Player/HUD/WBP_PlayerHUD"));
	if (FoundPHWidget.Succeeded())
	{
		PlayerHUDWidgetClass = FoundPHWidget.Class;
	}

	static ConstructorHelpers::FClassFinder<UPlayerMenuWidget>FoundPMWidget(TEXT("/Game/Player/HUD/WBP_PlayerMenu"));
	if (FoundPMWidget.Succeeded())
	{
		PlayerMenuWidgetClass = FoundPMWidget.Class;
	}
}

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	// Setup the PlayerHUDWidget
	// Check that the class has successfully been found
	if (PlayerHUDWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("HUD class was found"));
		PlayerHUDWidget = CreateWidget<UPlayerHUDWidget>(GetWorld(), PlayerHUDWidgetClass);

		// Check that it was created
		if (PlayerHUDWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("Added to viewport"));
			// Add to viewport
			PlayerHUDWidget->AddToViewport();
			PlayerHUDWidget->PlayerRef = PlayerRef;
		}
	}

	// Setup the PlayerMenuWidget
	// Check that the class has successfully been found
	if (PlayerMenuWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Menu Class was found"));
		PlayerMenuWidget = CreateWidget<UPlayerMenuWidget>(GetWorld(), PlayerMenuWidgetClass);

		// Check that it was created
		if (PlayerMenuWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("Added to viewport"));
			// Add to viewport
			PlayerMenuWidget->AddToViewport();
			PlayerMenuWidget->PlayerRef = PlayerRef;

			// Toggle the visiblility
			PlayerMenuWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void ABaseHUD::GetPlayerRef(ABaseCharacter* NewRef)
{
	PlayerRef = NewRef;
}

void ABaseHUD::UpdateHUDElements()
{
	PlayerHUDWidget->SynchronizeProperties();
	if (PlayerRef->bIsInMenu == true)
	{

	}
}

void ABaseHUD::ToggleMenu()
{
	// If the player is not in the menu
	if (PlayerRef->bIsInMenu == false)
	{
		PlayerHUDWidget->SetVisibility(ESlateVisibility::Hidden);
		PlayerMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
	// If the player is in the menu
	else if (PlayerRef->bIsInMenu == true)
	{
		PlayerHUDWidget->SetVisibility(ESlateVisibility::Visible);
		PlayerMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ABaseHUD::DrawHUD()
{

}

void ABaseHUD::Tick(float DeltaSeconds)
{

}

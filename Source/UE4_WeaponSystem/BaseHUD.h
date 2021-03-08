// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "UObject/ConstructorHelpers.h"

#include "BaseHUD.generated.h"

/**
 * 
 */
UCLASS()
class UE4_WEAPONSYSTEM_API ABaseHUD : public AHUD
{
	GENERATED_BODY()

public:
	ABaseHUD();

	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
		void UpdateHUDElements();

	UFUNCTION()
		void GetPlayerRef(ABaseCharacter* NewRef);

	UFUNCTION()
		void ToggleMenu();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Widget Classes")
		TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget Classes")
		TSubclassOf<UUserWidget> PlayerMenuWidgetClass;

private:
	class UPlayerHUDWidget* PlayerHUDWidget;
	class UPlayerMenuWidget* PlayerMenuWidget;

	class ABaseCharacter* PlayerRef = nullptr;
};

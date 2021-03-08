// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "UObject/ConstructorHelpers.h"

#include "PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_WEAPONSYSTEM_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
		void SetupRef(ABaseCharacter* NewRef);

	virtual void SynchronizeProperties() override;
	virtual void NativeConstruct() override;

	FLinearColor GetAmmoColour(FString AmmoName);

public:
	// Components
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* TestImage = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWeaponSlotWidget* KineticSlot = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWeaponSlotWidget* EnergySlot = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWeaponSlotWidget* HeavySlot = nullptr;

	class ABaseCharacter* PlayerRef = nullptr;
};

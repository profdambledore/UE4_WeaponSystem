// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "WeaponStatLibrary.h"

#include "PlayerMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_WEAPONSYSTEM_API UPlayerMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
		void SetupRef(ABaseCharacter* NewRef);

	virtual void SynchronizeProperties() override;
	virtual void NativeConstruct() override;

	FLinearColor GetRarityColour(ERarityType Rarity);

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* TestImage = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWeaponInventorySlotWidget* SlotInspect = nullptr;

	class ABaseCharacter* PlayerRef = nullptr;
};

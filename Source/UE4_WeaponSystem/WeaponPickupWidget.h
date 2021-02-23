// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

#include "WeaponStatLibrary.h"

#include "WeaponPickupWidget.generated.h"

class AWeaponPickup;
/**
 * 
 */
UCLASS()
class UE4_WEAPONSYSTEM_API UWeaponPickupWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void SynchronizeProperties() override;

	UFUNCTION(BlueprintCallable)
		void SetupRef(AWeaponPickup* NewRef);

public:
	// Components
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* Background = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* Header = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* Name = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* Type = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* Rarity = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* IconColour = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* Icon = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* DamageIcon = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* Damage = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* AmmoTypeIcon = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* AmmoType = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* ArchetypeIcon = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* Archetype = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* Divider1 = nullptr;



	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* RateOfFire = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* RateOfFireBar = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* Impact = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UProgressBar* ImpactBar = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* Range = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UProgressBar* RangeBar = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* Stability = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UProgressBar* StabilityBar = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* Handling = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UProgressBar* HandlingBar = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* Reload = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UProgressBar* ReloadBar = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* Magazine = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* MagazineBar = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* Divider2 = nullptr;

	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AWeaponPickup* PickupRef = nullptr;
};

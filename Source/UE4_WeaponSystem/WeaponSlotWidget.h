// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "UObject/ConstructorHelpers.h"

#include "WeaponSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_WEAPONSYSTEM_API UWeaponSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UWeaponSlotWidget(const FObjectInitializer& ObjectInitializer);

	virtual void SynchronizeProperties() override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* Background = nullptr;

	// Replace to image
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* WeaponType = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* AmmoType = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* CurrentAmmo = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* Reserves = nullptr;
};

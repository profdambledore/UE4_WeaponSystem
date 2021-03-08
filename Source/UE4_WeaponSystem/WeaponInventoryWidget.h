// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"

#include "WeaponStatLibrary.h"

#include "WeaponInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_WEAPONSYSTEM_API UWeaponInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual void SynchronizeProperties() override;

public:

};

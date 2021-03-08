// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerMenuWidget.h"

#include "WeaponInventorySlotWidget.h"

#include "BaseCharacter.h"

void UPlayerMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerMenuWidget::SetupRef(ABaseCharacter* NewRef)
{
	PlayerRef = NewRef;
}

void UPlayerMenuWidget::SynchronizeProperties()
{

}

FLinearColor UPlayerMenuWidget::GetRarityColour(ERarityType Rarity)
{
	FLinearColor C;
	switch (Rarity) {
	case Common:
		C = FLinearColor(1, 1, 1, 1);
		break;

	case Uncommon:
		C = FLinearColor(0, 0.45, 0.02, 1);
		break;

	case Rare:
		C = FLinearColor(0, 0.3, 0.6, 1);
		break;

	case Legendary:
		C = FLinearColor(0.05, 0.0, 0.6, 1);
		break;

	case Pinnacle:
		C = FLinearColor(0.9, 0.15, 0.0, 1);
		break;

	default:
		break;

	};
	return C;
}


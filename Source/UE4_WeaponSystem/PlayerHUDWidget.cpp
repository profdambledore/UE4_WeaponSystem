// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHUDWidget.h"

#include "WeaponSlotWidget.h"
#include "BaseCharacter.h"
#include "BaseWeapon.h"

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	KineticSlot->SetVisibility(ESlateVisibility::Hidden);
	EnergySlot->SetVisibility(ESlateVisibility::Hidden);
	HeavySlot->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerHUDWidget::SetupRef(ABaseCharacter* NewRef)
{
	PlayerRef = NewRef;
}

FLinearColor UPlayerHUDWidget::GetAmmoColour(FString AmmoName)
{
	FLinearColor AC;
	if (AmmoName == "Primary")
	{
		AC = FLinearColor(1, 1, 1, 1);
	}
	else if (AmmoName == "Special")
	{
		AC = FLinearColor(0.1, 1, 0, 1);
	}
	else if (AmmoName == "Heavy")
	{
		AC = FLinearColor(0.2, 0, 0.6, 1);
	}
	return AC;
}

void UPlayerHUDWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	
	// Check if this HUD has a reference to a player
	if (PlayerRef != nullptr)
	{
		// Update Weapon Slot Widget Variables
		if (PlayerRef->KineticWeapon != nullptr)
		{
			if (KineticSlot->IsVisible() == false)
			{
				KineticSlot->SetVisibility(ESlateVisibility::Visible);
			}
			KineticSlot->CurrentAmmo->SetText(FText::FromString(FString::FromInt(PlayerRef->KineticWeapon->CurrentMag)));
			KineticSlot->Reserves->SetText(FText::FromString(FString::FromInt(PlayerRef->KineticWeapon->CurrentReserves)));
			KineticSlot->WeaponType->SetText(UEnum::GetDisplayValueAsText(PlayerRef->KineticWeapon->WeaponType));
			KineticSlot->AmmoType->SetColorAndOpacity(GetAmmoColour(UEnum::GetDisplayValueAsText(PlayerRef->KineticWeapon->AmmoType).ToString()));
		}
		else if (PlayerRef->KineticWeapon == nullptr)
		{
			KineticSlot->SetVisibility(ESlateVisibility::Hidden);
		}

		if (PlayerRef->EnergyWeapon != nullptr)
		{
			if (EnergySlot->IsVisible() == false)
			{
				EnergySlot->SetVisibility(ESlateVisibility::Visible);
			}
			EnergySlot->CurrentAmmo->SetText(FText::FromString(FString::FromInt(PlayerRef->EnergyWeapon->CurrentMag)));
			EnergySlot->Reserves->SetText(FText::FromString(FString::FromInt(PlayerRef->EnergyWeapon->CurrentReserves)));
			EnergySlot->WeaponType->SetText(UEnum::GetDisplayValueAsText(PlayerRef->EnergyWeapon->WeaponType));
			EnergySlot->AmmoType->SetColorAndOpacity(GetAmmoColour(UEnum::GetDisplayValueAsText(PlayerRef->EnergyWeapon->AmmoType).ToString()));
		}
		else if (PlayerRef->EnergyWeapon == nullptr)
		{
			EnergySlot->SetVisibility(ESlateVisibility::Hidden);
		}

		if (PlayerRef->HeavyWeapon != nullptr)
		{
			if (HeavySlot->IsVisible() == false)
			{
				HeavySlot->SetVisibility(ESlateVisibility::Visible);
			}
			HeavySlot->CurrentAmmo->SetText(FText::FromString(FString::FromInt(PlayerRef->HeavyWeapon->CurrentMag)));
			HeavySlot->Reserves->SetText(FText::FromString(FString::FromInt(PlayerRef->HeavyWeapon->CurrentReserves)));
			HeavySlot->WeaponType->SetText(UEnum::GetDisplayValueAsText(PlayerRef->HeavyWeapon->WeaponType));
			HeavySlot->AmmoType->SetColorAndOpacity(GetAmmoColour(UEnum::GetDisplayValueAsText(PlayerRef->HeavyWeapon->AmmoType).ToString()));
		}
		else if (PlayerRef->KineticWeapon == nullptr)
		{
			HeavySlot->SetVisibility(ESlateVisibility::Hidden);
		}

		// Set the Current Weapon to the top of the HUD and slightly scale it up
		switch (PlayerRef->CurrentSlot)
		{
		case SlotOne:
			// Set the Kinetic Slot to the top slot
			KineticSlot->SetRenderTransform(FWidgetTransform(FVector2D(0, 0), FVector2D(1, 1), FVector2D(0, 0), 0.0f));
			EnergySlot->SetRenderTransform(FWidgetTransform(FVector2D(40, 30), FVector2D(0.8, 0.8), FVector2D(0, 0), 0.0f));
			HeavySlot->SetRenderTransform(FWidgetTransform(FVector2D(40, 10), FVector2D(0.8, 0.8), FVector2D(0, 0), 0.0f));
			break;

		case SlotTwo:
			KineticSlot->SetRenderTransform(FWidgetTransform(FVector2D(40, 122), FVector2D(.8, .8), FVector2D(0, 0), 0.0f));
			EnergySlot->SetRenderTransform(FWidgetTransform(FVector2D(0, -92), FVector2D(1, 1), FVector2D(0, 0), 0.0f));
			HeavySlot->SetRenderTransform(FWidgetTransform(FVector2D(40, 10), FVector2D(0.8, 0.8), FVector2D(0, 0), 0.0f));
			break;

		case SlotThree:
			KineticSlot->SetRenderTransform(FWidgetTransform(FVector2D(40, 122), FVector2D(.8, .8), FVector2D(0, 0), 0.0f));
			EnergySlot->SetRenderTransform(FWidgetTransform(FVector2D(40, 140), FVector2D(0.8, 0.8), FVector2D(0, 0), 0.0f));
			HeavySlot->SetRenderTransform(FWidgetTransform(FVector2D(0, -222), FVector2D(1, 1), FVector2D(0, 0), 0.0f));
			break;

		default:
			break;
		}
	}
}
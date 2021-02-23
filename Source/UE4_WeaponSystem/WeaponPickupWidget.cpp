// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponPickupWidget.h"
#include "WeaponPickup.h"

void UWeaponPickupWidget::SetupRef(AWeaponPickup* NewRef)
{
	PickupRef = NewRef;
	SynchronizeProperties();
}

void UWeaponPickupWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	if (Background)
	{
		if (PickupRef)
		{
			// Details Section
			FLinearColor H = PickupRef->GetRarityColour(PickupRef->Weapon.Base.Rarity);
			Background->SetColorAndOpacity(FLinearColor(H.R * 0.5, H.G * 0.5, H.B * 0.5, H.A));

			Header->SetColorAndOpacity(PickupRef->GetRarityColour(PickupRef->Weapon.Base.Rarity));

			Name->SetText(FText::FromString(PickupRef->Weapon.Base.Name));

			Type->SetText(UEnum::GetDisplayValueAsText(PickupRef->Weapon.Base.Type));

			Rarity->SetText(UEnum::GetDisplayValueAsText(PickupRef->Weapon.Base.Rarity));

			IconColour->SetColorAndOpacity(PickupRef->GetRarityColour(PickupRef->Weapon.Base.Rarity));
			Icon->SetBrushFromTexture(PickupRef->Weapon.Base.Icon, false);

			Damage->SetText(UEnum::GetDisplayValueAsText(PickupRef->Weapon.Base.Damage));

			AmmoType->SetText(UEnum::GetDisplayValueAsText(PickupRef->Weapon.Base.AmmoType));

			Archetype->SetText(FText::FromString(PickupRef->Weapon.Archetype.Name));

			// Stats Section
			if (PickupRef->Weapon.Base.Type == Fusion)
			{
				RateOfFire->SetText(FText::FromString("Charge Rate"));
			};
			RateOfFireBar->SetText(FText::FromString(FString::FromInt(PickupRef->Weapon.Archetype.Impact.RateOfFire)));

			if (PickupRef->Weapon.Base.Type == Rocket)
			{
				Impact->SetText(FText::FromString("Blast Radius"));
			};
			ImpactBar->SetPercent(PickupRef->Weapon.Stats.Impact);

			if (PickupRef->Weapon.Base.Type == Rocket)
			{
				Range->SetText(FText::FromString("Velocity"));
			};
			RangeBar->SetPercent(PickupRef->Weapon.Stats.Range);

			StabilityBar->SetPercent(PickupRef->Weapon.Stats.Stability);

			HandlingBar->SetPercent(PickupRef->Weapon.Stats.Handling);

			ReloadBar->SetPercent(PickupRef->Weapon.Stats.Reload);

			MagazineBar->SetText(FText::FromString(FString::FromInt(PickupRef->Weapon.Stats.Magazine)));
		}
	}
}
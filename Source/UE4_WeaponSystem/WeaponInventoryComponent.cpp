// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponInventoryComponent.h"

// Sets default values for this component's properties
UWeaponInventoryComponent::UWeaponInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UWeaponInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UWeaponInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponInventoryComponent::AddWeaponToInventory(FWeapon WeaponToAdd)
{
	switch (WeaponToAdd.Base.Slot) {
	case SlotOne:
		KineticInventory.Add(WeaponToAdd);
		break;

	case SlotTwo:
		EnergyInventory.Add(WeaponToAdd);
		break;

	case SlotThree:
		HeavyInventory.Add(WeaponToAdd);
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("Tried to add Weapon to an unknown inventory"))
			break;
	}
}

void UWeaponInventoryComponent::RemoveWeaponFromInventory(ESlotType SlotType, int Index)
{
	switch (SlotType) {
	case SlotOne:
		KineticInventory.RemoveAt(Index);
		break;

	case SlotTwo:
		EnergyInventory.RemoveAt(Index);
		break;

	case SlotThree:
		HeavyInventory.RemoveAt(Index);
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("Tried to remove from an unknown inventory"));
		break;
	};
}

void UWeaponInventoryComponent::ChangeWeaponFromInventory(ESlotType SlotType, int Index)
{
	FWeapon OldWeapon;
	switch (SlotType) {
	case SlotOne:
		OldWeapon = KineticInventory[0];
		KineticInventory[0] = KineticInventory[Index];
		KineticInventory[Index] = OldWeapon;
		break;

	case SlotTwo:
		OldWeapon = EnergyInventory[0];
		EnergyInventory[0] = EnergyInventory[Index];
		EnergyInventory[Index] = OldWeapon;

	case SlotThree:
		OldWeapon = HeavyInventory[0];
		HeavyInventory[0] = HeavyInventory[Index];
		HeavyInventory[Index] = OldWeapon;
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("Tried to swap from an unknown inventory"));
		break;
	};
}

int UWeaponInventoryComponent::GetInventorySize(ESlotType SlotType)
{
	switch (SlotType) {
	case SlotOne:
		return KineticInventory.Num();
		break;

	case SlotTwo:
		return EnergyInventory.Num();
		break;

	case SlotThree:
		return HeavyInventory.Num();
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("Tried to check an unknown inventory"));
		return 11;
		break;
	};
}


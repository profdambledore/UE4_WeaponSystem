// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "WeaponStatLibrary.h"

#include "WeaponInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_WEAPONSYSTEM_API UWeaponInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponInventoryComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Add a weapon to a specified inventory (kinetic, energy or heavy)
	UFUNCTION()
		void AddWeaponToInventory(FWeapon WeaponToAdd);

	// Remove weapon from an inventory
	UFUNCTION()
		void RemoveWeaponFromInventory(ESlotType SlotType, int Index);

	// Change the selected weapon
	UFUNCTION()
		void ChangeWeaponFromInventory(ESlotType SlotType, int Index);

	// Called to check how filled the inventory
	UFUNCTION()
		int GetInventorySize(ESlotType SlotType);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<FWeapon> KineticInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<FWeapon> EnergyInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<FWeapon> HeavyInventory;
		
};

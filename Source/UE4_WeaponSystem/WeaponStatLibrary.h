// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Engine/Texture2D.h"
#include "Engine/DataTable.h"
#include "Math/Color.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/StaticMesh.h"

#include "WeaponStatLibrary.generated.h"

class ABaseWeapon;
/**
 * 
 */
UCLASS()
class UE4_WEAPONSYSTEM_API UWeaponStatLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};

UENUM()
enum ESlotType // The slot where a weapon recides, or the current slot eqiuped
{
	SlotOne UMETA(DisplayName = "Slot One"),
	SlotTwo UMETA(DisplayName = "Slot Two"),
	SlotThree UMETA(DisplayName = "Slot Three"),
};

UENUM()
enum EWeaponType // The weapon's type
{
	Auto UMETA(DisplayName = "Auto Rifle"),
	Pulse UMETA(DisplayName = "Pulse Rifle"),
	Scout UMETA(DisplayName = "Scout Rifle"),
	HCannon UMETA(DisplayName = "Hand Cannon"),
	Shotgun UMETA(DisplayName = "Shotgun"),
	Sniper UMETA(DisplayName = "Sniper Rifle"),
	Fusion UMETA(DisplayName = "Fusion Rifle"),
	Machine UMETA(DisplayName = "Machine Gun"),
	Rocket UMETA(DisplayName = "Rocket Launcher"),
};

UENUM()
enum EDamageType // The weapon's damage type
{
	Kinetic UMETA(DisplayName = "Kinetic"),
	Solar UMETA(DisplayName = "Solar"),
	Arc UMETA(DisplayName = "Arc"),
	Void UMETA(DisplayName = "Void"),
};

UENUM()
enum EAmmoType // The weapon's ammo type
{
	Primary UMETA(DisplayName = "Primary"),
	Special UMETA(DisplayName = "Special"),
	Heavy UMETA(DisplayName = "Heavy"),
};

UENUM()
enum ERarityType // The rarity of the weapon
{
	Common UMETA(DisplayName = "Common"),
	Uncommon UMETA(DisplayName = "Uncommon"),
};

UENUM()
enum EPerkType // The perk's type (sights, barrels, magazine)
{
	Sight UMETA(DisplayName = "Sight"),
	Barrel UMETA(DisplayName = "Barrel"),
};

// Structs
// Archetype Structs

USTRUCT(BlueprintType)
struct FImpact // Define a archetype's impact and rate of fire, or impact and charge time, as well as the max and minimum damage
{
	GENERATED_USTRUCT_BODY();

public:
	// RateOfFire == Charge time for Fusion Rifles
	UPROPERTY(EditAnywhere)
		uint16 RateOfFire;

	UPROPERTY(EditAnywhere)
		uint8 MaxDamage;

	UPROPERTY(EditAnywhere)
		uint8 MinDamage;

	UPROPERTY(EditAnywhere)
		float CritMultiplier;
};

USTRUCT(BlueprintType)
struct FRange // Define a archetype's range that it does maximum damage, and how fast it falls of after
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere)
		float MaxRange;

	UPROPERTY(EditAnywhere)
		float MinRange;

	UPROPERTY(EditAnywhere)
		float MaxDropoff;

	UPROPERTY(EditAnywhere)
		float MinDropoff;
};

USTRUCT(BlueprintType)
struct FStability // Define a archetype's stability or how much visual kick (how much the weapon moves from the reticle when fired), actual kick (how much from the original point the reticle moves) and in-burst kick
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere)
		float MinVisKick;

	UPROPERTY(EditAnywhere)
		float MaxVisKick;

	UPROPERTY(EditAnywhere)
		float MinActKick;

	UPROPERTY(EditAnywhere)
		float MaxActKick;

	UPROPERTY(EditAnywhere)
		float MinInBurst;

	UPROPERTY(EditAnywhere)
		float MaxInBurst;
};

USTRUCT(BlueprintType)
struct FHandling // Define a archetype's draw, stow and ADS speeds.
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere)
		float MinDraw;

	UPROPERTY(EditAnywhere)
		float MaxDraw;

	UPROPERTY(EditAnywhere)
		float MinStow;

	UPROPERTY(EditAnywhere)
		float MaxStow;

	UPROPERTY(EditAnywhere)
		float MinADS;

	UPROPERTY(EditAnywhere)
		float MaxADS;
};

USTRUCT(BlueprintType)
struct FReloadMag // Define a archetype's reload speed and magazine size
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere)
		float MinReload;

	UPROPERTY(EditAnywhere)
		float MaxReload;

	UPROPERTY(EditAnywhere)
		float MaxMag;

	UPROPERTY(EditAnywhere)
		float MinMag;
};

USTRUCT(BlueprintType)
struct FArchetype : public FTableRowBase // Define a single archetype
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere)
		FString Name; // Archetype name

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Icon; // Weapon Icon

	UPROPERTY(EditAnywhere)
		FName Perk;

	UPROPERTY(EditAnywhere)
		FImpact Impact;

	UPROPERTY(EditAnywhere)
		FRange Range;

	UPROPERTY(EditAnywhere)
		FStability Stability;

	UPROPERTY(EditAnywhere)
		FHandling Handling;

	UPROPERTY(EditAnywhere)
		FReloadMag Reload;
};

// Weapon Structs

USTRUCT(BlueprintType)
struct FWeaponBase // Define the base of a weapon (name, type, subtype, class, icon, description, rarity, element, ammo and mesh)
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name; // Weapon name

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EWeaponType> Type; // Weapon Type

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EDamageType> Damage; // Damage Type

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Archetype; //  Weapon archetype

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Icon; // Weapon Icon

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Description; // Weapon description

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<ERarityType> Rarity; // Weapon rarity

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EAmmoType> AmmoType; // What ammo the weapon uses

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<ESlotType> Slot; // If a weapon is a kinetic (slot one), energy (slot two) or a power (slot three)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* Mesh; // The mesh of the weapon

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* MagMesh; // The magazine mesh of the weapon

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* HipfireIcon; // Weapon Icon
};

USTRUCT(BlueprintType)
struct FIStats // Define the base stats of a weapon
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere)
		float Impact;

	UPROPERTY(EditAnywhere)
		float Range;

	UPROPERTY(EditAnywhere)
		float Stability;

	UPROPERTY(EditAnywhere)
		float Handling;

	UPROPERTY(EditAnywhere)
		float Reload;

	UPROPERTY(EditAnywhere)
		int8 Magazine;
};

USTRUCT(BlueprintType)
struct FPerk : public FTableRowBase // Define the base of a weapon (name, type, subtype, class, icon, description, rarity, element, ammo and mesh)
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Icon;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<EPerkType> Type;

	UPROPERTY(EditAnywhere)
		FString Desc;

	UPROPERTY(EditAnywhere)
		FIStats Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* Mesh;
};

USTRUCT(BlueprintType)
struct FPerkTable // Define a column of a weapon's random roll
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FName> Perks;
};

USTRUCT(BlueprintType)
struct FGenTable // Struct used for when the perk columns have been randomly chosen
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentSelected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FPerk> Column;
};

// Finalization Structs - used during the weapon generation

USTRUCT(BlueprintType)
struct FGetWeapon : public FTableRowBase // Define a single archetype
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FWeaponBase Base;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ABaseWeapon> Class; // Class to be used

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FIStats Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FPerkTable> PerkTable;
};

USTRUCT(BlueprintType)
struct FWeapon // Used when a weapon is a pickup or is in the inventory
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FWeaponBase Base;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ABaseWeapon> Class; // Class to be used

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FIStats Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FArchetype Archetype;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FGenTable> PerkTable;
};
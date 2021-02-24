// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon.h"

#include "BaseCharacter.h"
#include "WeaponInventoryComponent.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
	// Setup Scene Component
	//WeaponRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));

	// Setup Weapon Meshes
	BaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Base Mesh"));
	SetRootComponent(BaseMesh);

	SightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sight Mesh"));
	MagazineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magazine Mesh"));

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseWeapon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseWeapon::SetupWeaponBase(ESlotType SlotType, bool bHasSight)
{
	// Set the ref to the attached player
	PlayerRef = Cast<ABaseCharacter>(GetParentActor());

	// Set the reference to the correct array
	// * is a pointer, makes a copy of the FWeapon
	// & is a reference to the weapon in the inventory
	switch (SlotType)
	{
	case SlotOne:
		ThisWeapon = &(PlayerRef->WeaponInventoryComponent->KineticInventory[0]);
		break;

	case SlotTwo:
		ThisWeapon = &(PlayerRef->WeaponInventoryComponent->EnergyInventory[0]);
		break;

	case SlotThree:
		ThisWeapon = &(PlayerRef->WeaponInventoryComponent->HeavyInventory[0]);
		break;

	default:
		break;
	}

	// Set the skeletal mesh of the weapon
	BaseMesh->SetSkeletalMesh(ThisWeapon->Base.Mesh);

	if (bHasSight)
	{
		// Call SetSight
		SightMesh->AttachToComponent(BaseMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), FName("SightSocket"));
		SetSight();
	};

	MagazineMesh->AttachToComponent(BaseMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), FName("MagazineSocket"));
	MagazineMesh->SetStaticMesh(ThisWeapon->Base.MagMesh);

}

void ABaseWeapon::SetSight()
{
	for (int i = 0; i < ThisWeapon->PerkTable.Num(); i++)
	{
		// If the perk column contains sights, then...
		if (ThisWeapon->PerkTable[i].Column[0].Type == Sight)
		{
			// Set the sight to the current selected sight
			SightMesh->SetStaticMesh(ThisWeapon->PerkTable[i].Column[ThisWeapon->PerkTable[i].CurrentSelected].Mesh);
			break;
		};
	};
}


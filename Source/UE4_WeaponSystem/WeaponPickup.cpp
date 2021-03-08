// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponPickup.h"
#include "BaseCharacter.h"
#include "WeaponPickupWidget.h"

// Sets default values
AWeaponPickup::AWeaponPickup()
{
	// Add components
	// Setup Scene Component
	WeaponRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));

	// Setup Skeletal and Static Meshes
	BaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Base Mesh"));
	SightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sight Mesh"));
	MagazineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magazine Mesh"));

	// Setup Particle System and Widget Related Components
	WeaponParticleSys = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Dropped Weapon Particle System"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> FoundParticleSys(TEXT("/Game/Weapon/Pickup/PS_WeaponPickup"));
	if(FoundParticleSys.Succeeded())
	{
		WeaponParticleSys->SetTemplate(FoundParticleSys.Object);
	}

	WeaponWidgetRange = CreateDefaultSubobject<USphereComponent>(TEXT("Dropped Weapon Widget Range"));
	WeaponWidgetRange->SetSphereRadius(1000.0);
	WeaponWidgetRange->GetGenerateOverlapEvents();

	WeaponWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Dropped Weapon Widget"));
	WeaponWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
	WeaponWidgetComponent->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	static ConstructorHelpers::FClassFinder<UUserWidget> FoundWidget(TEXT("/Game/Weapon/Pickup/WBP_WeaponPickup"));
	if(FoundWidget.Succeeded())
	{
		WeaponWidgetComponent->SetWidgetClass(FoundWidget.Class);
	}
	WeaponWidgetComponent->SetVisibility(false, false);

	// Setup the pickup collision
	WeaponPickupCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Dropped Weapon Pickup Collision"));
	WeaponPickupCollision->SetRelativeLocation(FVector(20.0f, 0.0f, 10.0f));
	WeaponPickupCollision->SetRelativeScale3D(FVector(1.5f, 0.5f, 0.5f));

	// Set Data Tables
	static ConstructorHelpers::FObjectFinder<UDataTable> FGetWeaponObject(TEXT("/Game/Weapon/Data/DT_Weapon"));
	if (FGetWeaponObject.Succeeded())
	{
		FGetWeaponDataTable = FGetWeaponObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> FArchetypeObject(TEXT("/Game/Weapon/Data/DT_Archetype"));
	if (FArchetypeObject.Succeeded())
	{
		FArchetypeDataTable = FArchetypeObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> FPerkObject(TEXT("/Game/Weapon/Data/DT_Perk"));
	if (FPerkObject.Succeeded())
	{
		FPerkDataTable = FPerkObject.Object;
	}

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWeaponPickup::BeginPlay()
{
	Super::BeginPlay();

	WeaponWidgetRange->OnComponentBeginOverlap.AddDynamic(this, &AWeaponPickup::OnWidgetOverlapBegin);
	WeaponWidgetRange->OnComponentEndOverlap.AddDynamic(this, &AWeaponPickup::OnWidgetOverlapEnd);

	SetWeaponToPickup(testName); // REMOVE, currently for testing
	
}

void AWeaponPickup::OnWidgetOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//check if Actors do not equal nullptr
	if (OtherActor && (OtherActor != this))
	{
		WeaponWidgetComponent->SetVisibility(true, true);
	}
}

void AWeaponPickup::OnWidgetOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this))
	{
		WeaponWidgetComponent->SetVisibility(false, false);
	}
}

// Called every frame
void AWeaponPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Check if the widget is visible.  if it is then set widget component to face the player
	// Calculate the new rotation
	if (WeaponWidgetComponent->IsVisible())
	{
		FVector PlayerLoc = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();
		FRotator NewRot = (PlayerLoc - WeaponWidgetComponent->GetComponentLocation()).Rotation();
		WeaponWidgetComponent->SetWorldRotation(NewRot);
	}


}
void AWeaponPickup::SetWeaponToPickup(FName DroppedWeapon)
{
	if (DroppedWeapon != "")
	{
		FGetWeapon* RowWeapon = FGetWeaponDataTable->FindRow<FGetWeapon>(DroppedWeapon, FString("Couldn't Find"), true);

		// Setup the weapon's components
		WeaponParticleSys->SetColorParameter(FName("ParamColour"), GetRarityColour(RowWeapon->Base.Rarity));
		BaseMesh->SetSkeletalMesh(RowWeapon->Base.Mesh);
		MagazineMesh->AttachToComponent(BaseMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), FName("MagazineSocket"));
		MagazineMesh->SetStaticMesh(RowWeapon->Base.MagMesh);

		// Create a random roll for the weapon
		// Local variable to hold the perk columns
		TArray<FGenTable> CreatedTable;
		// For each column of perks
		for (int i = 0; i < RowWeapon->PerkTable.Num(); i++)
		{
			// Choose a amount of random perks from the perk table
			NewPerkColumn.CurrentSelected = 0;
			NewPerkColumn.Column = GenerateRandomPerkColumn(RowWeapon->PerkTable[i]);
			CreatedTable.Add(NewPerkColumn);
		};

		// Get the Archetype
		FArchetype* RowArchetype = FArchetypeDataTable->FindRow<FArchetype>(RowWeapon->Base.Archetype, FString("Couldn't Find"), true);

		// Set this weapons variable
		Weapon.Base = RowWeapon->Base;
		Weapon.Class = RowWeapon->Class;
		Weapon.Stats = RowWeapon->Stats;
		Weapon.Archetype = *RowArchetype;
		Weapon.PerkTable = CreatedTable;

		// Set stats based on perks chosen
		// For each perk column
		for (int i = 0; i < Weapon.PerkTable.Num(); i++)
		{
			// If the perk column contains sights, then...
			if (Weapon.PerkTable[i].Column[0].Type == Sight)
			{
				SightMesh->SetStaticMesh(Weapon.PerkTable[i].Column[0].Mesh);
				SightMesh->AttachToComponent(BaseMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), FName("SightSocket"));
			};
			// Add the perk stats to the weapon stats -- This could be updated at a later point.  However, doing Weapon.Stats(Weapon.Stats.Impact += Weapon...Impact) doesn't work
			Weapon.Stats.Impact += Weapon.PerkTable[i].Column[0].Stats.Impact;
			Weapon.Stats.Range += Weapon.PerkTable[i].Column[0].Stats.Range;
			Weapon.Stats.Stability += Weapon.PerkTable[i].Column[0].Stats.Stability;
			Weapon.Stats.Handling += Weapon.PerkTable[i].Column[0].Stats.Handling;
			Weapon.Stats.Reload += Weapon.PerkTable[i].Column[0].Stats.Reload;
			Weapon.Stats.Magazine += Weapon.PerkTable[i].Column[0].Stats.Magazine;
		}

		UWeaponPickupWidget* CastedWidget = Cast<UWeaponPickupWidget>(WeaponWidgetComponent->GetWidget());
		CastedWidget->SetupRef(this);
	}
}


TArray<FPerk> AWeaponPickup::GenerateRandomPerkColumn(FPerkTable PerkTable)
{
	// Local variables
	TArray<FPerk> PerkHold;
	TArray<FName> PerkList = PerkTable.Perks;

	for (int j = 0; j < PerkTable.Amount; j++)
	{
		int Index = FMath::RandRange(0, PerkList.Num() - 1);
		FPerk* RowPerk = FPerkDataTable->FindRow<FPerk>(PerkList[Index], FString("Couldn't Find"), true);
		PerkHold.Add(*RowPerk);
		PerkList.RemoveAt(Index);
	}
	return PerkHold;
}

// Called to pickup the weapon
void AWeaponPickup::PickupWeapon()
{
	// Destroy the pickup
	Destroy();
}

// Called whenever the rarity colour is needed
FLinearColor AWeaponPickup::GetRarityColour(ERarityType Rarity)
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


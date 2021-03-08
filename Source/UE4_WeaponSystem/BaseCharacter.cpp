// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "BaseWeapon.h"
#include "WeaponInventoryComponent.h"
#include "WeaponPickup.h"
#include "BaseHUD.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Add components
	// Setup First Person Mesh
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));
	FirstPersonMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	FirstPersonMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));

	// Setup First Person Camera
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCamera->SetRelativeLocation(FVector(0.0f, 1.75f, 74.0f));
	FirstPersonCamera->bUsePawnControlRotation = true;

	// Setup Third Person Mesh
	ThirdPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Third Person Mesh"));
	ThirdPersonMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	ThirdPersonMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));

	// Setup Third Person Camera on Sprint Arm
	ThirdPersonSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Third Person Spring Arm"));
	ThirdPersonSpringArm->SetRelativeLocation(FVector(0.0f, 60.0f, 0.0f));
	ThirdPersonSpringArm->bUsePawnControlRotation = true;
	ThirdPersonSpringArm->TargetArmLength = 300.0f;

	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));
	ThirdPersonCamera->SetupAttachment(ThirdPersonSpringArm, USpringArmComponent::SocketName);

	// Setup Menu Camera
	MenuCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Menu Camera"));
	MenuCamera->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	MenuCamera->SetRelativeLocation(FVector(500.0f, 0.0f, 0.0f));
	MenuCamera->bUsePawnControlRotation = false;

	// Setup Weapon Child Actors
	KineticWeaponComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Kinetic Weapon Component"));
	EnergyWeaponComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Energy Weapon Component"));
	HeavyWeaponComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Heavy Weapon Component"));

	// Setup Weapon Inventory Component
	WeaponInventoryComponent = CreateDefaultSubobject<UWeaponInventoryComponent>(TEXT("Weapon Inventory"));

	// Make Third Person Components Hidden, set FPCamera to main viewport
	FirstPersonCamera->SetActive(true, true);
	ThirdPersonMesh->SetVisibility(false, false);
	ThirdPersonCamera->SetActive(false, false);
	MenuCamera->SetActive(false, false);

	// Set the base state for the player
	bIsThirdPerson = false;
	bIsInMenu = false;
	CurrentSlot = SlotOne;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set the reference to the HUD
	HUDRef = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	HUDRef->GetPlayerRef(this);

	// Setup Child Actor Components with the ABaseWeapons
	// Kinetic Weapon
	KineticWeaponComponent->AttachToComponent(FirstPersonMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), FName("GripPoint"));

	// Energy Weapon
	EnergyWeaponComponent->AttachToComponent(ThirdPersonMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), FName("SecondarySocket"));
	EnergyWeaponComponent->SetVisibility(false, false);

	// Heavy Weapon
	HeavyWeaponComponent->AttachToComponent(ThirdPersonMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), FName("TertiarySocket"));
	HeavyWeaponComponent->SetVisibility(false, false);

	// Create the reference to the player controller
	PC = Cast<APlayerController>(GetController());
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add Axis Binds
	PlayerInputComponent->BindAxis("MoveX", this, &ABaseCharacter::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &ABaseCharacter::MoveY);
	PlayerInputComponent->BindAxis("RotateX", this, &ABaseCharacter::RotateX);
	PlayerInputComponent->BindAxis("RotateY", this, &ABaseCharacter::RotateY);
	PlayerInputComponent->BindAxis("SwitchToNextPrevious", this, &ABaseCharacter::SwitchToNextPrevious);

	// Add Action Binds
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &ABaseCharacter::Interact);
	PlayerInputComponent->BindAction("SwitchCamera", IE_Pressed, this, &ABaseCharacter::SwitchCamera);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &ABaseCharacter::Inventory);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("SwitchToKinetic", IE_Pressed, this, &ABaseCharacter::SwitchToKinetic);
	PlayerInputComponent->BindAction("SwitchToEnergy", IE_Pressed, this, &ABaseCharacter::SwitchToEnergy);
	PlayerInputComponent->BindAction("SwitchToHeavy", IE_Pressed, this, &ABaseCharacter::SwitchToHeavy);

}

void ABaseCharacter::MoveX(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		if (bIsInMenu == false)
		{
			// Move on the X axis based on the input's axis value
			AddMovementInput(GetActorForwardVector(), AxisValue, false);
		}
	}
}

void ABaseCharacter::MoveY(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		if (bIsInMenu == false)
		{
			// Move on the Y axis based on the input's axis value
			AddMovementInput(GetActorRightVector(), AxisValue, false);
		}
	}
}

void ABaseCharacter::RotateX(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		if (bIsInMenu == false)
		{
			// Rotate on the X axis based on the input's axis value
			AddControllerYawInput(AxisValue);
		}
	}
}

void ABaseCharacter::RotateY(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		if (bIsInMenu == false)
		{
			// Rotate on the Y axis based on the input's axis value
			AddControllerPitchInput(AxisValue);
		}
	}
}

void ABaseCharacter::Interact()
{
	// Trace items infront of the player
	// Generate information for the trace
	FHitResult TraceHit = FHitResult(ForceInit);
	FVector TraceStart = FirstPersonCamera->GetComponentLocation() + (GetActorForwardVector() * 100);
	FVector TraceEnd = (TraceStart + (GetActorForwardVector() * 150));
	ECollisionChannel TraceChannel = ECC_GameTraceChannel1;

	FCollisionQueryParams TraceParams(FName(TEXT("Interact Trace")), true, NULL);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = true;

	bool bInteractTrace = GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, TraceChannel, TraceParams);
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 5.f, ECC_WorldStatic, 1.f);
	if (bInteractTrace)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor"));
		DrawDebugBox(GetWorld(), TraceHit.ImpactPoint, FVector(2.f, 2.f, 2.f), FColor::Blue, false, 5.f, ECC_WorldStatic, 1.f);
		if (TraceHit.Actor->GetClass()->GetName() == "BP_WeaponPickup_C")
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Pickup"));
			WeaponToPickup = Cast<AWeaponPickup>(TraceHit.Actor);

			// Check if the inventory that the weapon will be placed into is filled or not
			if (WeaponInventoryComponent->GetInventorySize(WeaponToPickup->Weapon.Base.Slot) < 10)
			{
				PickupWeapon();
			}
		}
	}
}

void ABaseCharacter::PickupWeapon()
{
	// Get Weapon property from WeaponToPickup, dont pass through WeaponToPickup itself
	WeaponInventoryComponent->AddWeaponToInventory(WeaponToPickup->Weapon);
	// Check if it is the first weapon in the inventory
	if (WeaponInventoryComponent->GetInventorySize(WeaponToPickup->Weapon.Base.Slot) == 1)
	{
		SetupNewWeapon(WeaponToPickup->Weapon.Base.Slot);
	}
	WeaponToPickup->PickupWeapon();
}

void ABaseCharacter::SetupNewWeapon(ESlotType SlotType)
{
	UChildActorComponent* CurrentSlotComponent = nullptr;
	FWeapon* CurrentInventoryWeapon = nullptr;
	ABaseWeapon* CurrentWeaponClass = nullptr;

	// Get a reference to the current slot component and matching array
	if (SlotType == SlotOne)
	{
		CurrentSlotComponent = KineticWeaponComponent;
		CurrentInventoryWeapon = &(WeaponInventoryComponent->KineticInventory[0]);
		CurrentWeaponClass = KineticWeapon;
	}
	else if (SlotType == SlotTwo)
	{
		CurrentSlotComponent = EnergyWeaponComponent;
		CurrentInventoryWeapon = &(WeaponInventoryComponent->EnergyInventory[0]);
		CurrentWeaponClass = EnergyWeapon;
	}
	else if (SlotType == SlotThree)
	{
		CurrentSlotComponent = HeavyWeaponComponent;
		CurrentInventoryWeapon = &(WeaponInventoryComponent->HeavyInventory[0]);
		CurrentWeaponClass = HeavyWeapon;
	}

	// Set the child actor class and cast to it
	CurrentSlotComponent->SetChildActorClass(CurrentInventoryWeapon->Class);
	CurrentWeaponClass = Cast<ABaseWeapon>(CurrentSlotComponent->GetChildActor());

	// Check if the weapon has a sight perk
	for (int i = 0; i < CurrentInventoryWeapon->PerkTable.Num(); i++)
	{
		// If the perk at Column i, index CurrentSelected has a Type of Sight, then...
		if (CurrentInventoryWeapon->PerkTable[i].Column[CurrentInventoryWeapon->PerkTable[i].CurrentSelected].Type == Sight)
		{
			// Call function SetSight
			CurrentWeaponClass->SetupWeaponBase(CurrentInventoryWeapon->Base.Slot, true);
		}
	}
	
	// If the base wasen't set up (no sight perk was found)
	if (CurrentWeaponClass->ThisWeapon == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("NoSight"))
		CurrentWeaponClass->SetupWeaponBase(CurrentInventoryWeapon->Base.Slot, false);
	}

	// Set pointers to induvidual slots
	if (SlotType == SlotOne)
	{
		KineticWeapon = CurrentWeaponClass;
	}
	else if (SlotType == SlotTwo)
	{
		EnergyWeapon = CurrentWeaponClass;
	}
	else if (SlotType == SlotThree)
	{
		HeavyWeapon = CurrentWeaponClass;
	}

	// Check if it is the current weapon in the first person socket.  If it is, set it to be
	if (KineticWeaponComponent->GetAttachSocketName() == "GripPoint")
	{
		CurrentWeapon = KineticWeapon;
	}
	else if (EnergyWeaponComponent->GetAttachSocketName() == "GripPoint")
	{
		CurrentWeapon = EnergyWeapon;
	}
	else if (HeavyWeaponComponent->GetAttachSocketName() == "GripPoint")
	{
		CurrentWeapon = HeavyWeapon;
	}

	// Update HUD Elements
	HUDRef->UpdateHUDElements();
}


void ABaseCharacter::Reload()
{
	// Check if the player can reload
	
}

void ABaseCharacter::SwitchCamera()
{
	if (bIsInMenu == false)
	{
		// Check if in first person.  If true...
		if (bIsThirdPerson ==  false)
		{
			// Swap to Third Person Camera, make back weapons visible
			FirstPersonCamera->SetActive(false, false);
			FirstPersonMesh->SetVisibility(false, false);

			ThirdPersonCamera->SetActive(true, true);
			ThirdPersonMesh->SetVisibility(true, true);

			bIsThirdPerson = true;
		}
		// If false...
		else if (bIsThirdPerson == true)
		{
			FirstPersonCamera->SetActive(true, true);
			FirstPersonMesh->SetVisibility(true, true);

			ThirdPersonCamera->SetActive(false, false);
			ThirdPersonMesh->SetVisibility(false, false);

			bIsThirdPerson = false;
		}
	}
}

void ABaseCharacter::Inventory()
{
	HUDRef->ToggleMenu();

	// Check to see if currently in the menu
	if (bIsInMenu == false)
	{
		// Go to the menu camera
		if (bIsThirdPerson == true)
		{
			// Swap to the MenuCamera from third person
			ThirdPersonCamera->SetActive(false, false);
			MenuCamera->SetActive(true, true);
		}
		else if (bIsThirdPerson == false)
		{
			// Swap to the MenuCamera from first person
			FirstPersonCamera->SetActive(false, false);
			FirstPersonMesh->SetVisibility(false, false);
			ThirdPersonMesh->SetVisibility(true, true);
			MenuCamera->SetActive(true, true);
		}

		// Enable Mouse Cursor
		if (PC)
		{
			PC->bShowMouseCursor = true;
			PC->bEnableClickEvents = true;
			PC->bEnableMouseOverEvents = true;
		}

		bIsInMenu = true;
	}
	else if (bIsInMenu == true)
	{
		// Exit the menu and return to the previous view (first or third person)
		if (bIsThirdPerson == true)
		{
			// Go back to being in third person
			ThirdPersonCamera->SetActive(true, true);
			MenuCamera->SetActive(false, false);
		}
		else if (bIsThirdPerson == false)
		{
			// Go back to first person
			FirstPersonCamera->SetActive(true, true);
			FirstPersonMesh->SetVisibility(true, true);
			ThirdPersonMesh->SetVisibility(false, false);
			MenuCamera->SetActive(false, false);
		}

		// Disable Mouse Cursor
		if (PC)
		{
			PC->bShowMouseCursor = false;
			PC->bEnableClickEvents = false;
			PC->bEnableMouseOverEvents = false;
		}

		bIsInMenu = false;
	}
}

void ABaseCharacter::PrimaryFire()
{

}

void ABaseCharacter::SecondaryFire()
{

}

void ABaseCharacter::SwitchToKinetic()
{
	if (CurrentSlot != SlotOne)
	{
		SwitchWeapon(SlotOne);
	}
}

void ABaseCharacter::SwitchToEnergy()
{
	if (CurrentSlot != SlotTwo)
	{
		SwitchWeapon(SlotTwo);
	}
}

void ABaseCharacter::SwitchToHeavy()
{
	if (CurrentSlot != SlotThree)
	{
		SwitchWeapon(SlotThree);
	}
}

void ABaseCharacter::SwitchToNextPrevious(float AxisValue)
{
	switch (CurrentSlot) {
	case SlotOne:
		// If AxisValue is 1, go to the next weapon
		if (AxisValue == 1)
		{
			SwitchWeapon(SlotTwo);
		}
		// If AxisValue is -1, go to the previous weapon
		else if (AxisValue == -1)
		{
			SwitchWeapon(SlotThree);
		}
		break;

	case SlotTwo:
		// If AxisValue is 1, go to the next weapon
		if (AxisValue == 1)
		{
			SwitchWeapon(SlotThree);
		}
		// If AxisValue is -1, go to the previous weapon
		else if (AxisValue == -1)
		{
			SwitchWeapon(SlotOne);
		}
		break;

	case SlotThree:
		// If AxisValue is 1, go to the next weapon
		if (AxisValue == 1)
		{
			SwitchWeapon(SlotOne);
		}
		// If AxisValue is -1, go to the previous weapon
		else if (AxisValue == -1)
		{
			SwitchWeapon(SlotTwo);
		}
		break;

	default:

		break;
	}
}

void ABaseCharacter::SwitchWeapon(ESlotType SlotToSwitch)
{
	UChildActorComponent* CurrentSlotComponent = nullptr;
	FName NewSocket;
	// Get a reference to the current slot
	if (CurrentSlot == SlotOne)
	{
		CurrentSlotComponent = KineticWeaponComponent;
	}
	else if (CurrentSlot == SlotTwo)
	{
		CurrentSlotComponent = EnergyWeaponComponent;
	}
	else if (CurrentSlot == SlotThree)
	{
		CurrentSlotComponent = HeavyWeaponComponent;
	}

	// Swap the current slot weapon and the new slot weapons
	switch (SlotToSwitch) {
	case SlotOne:
		NewSocket = KineticWeaponComponent->GetAttachSocketName();
		CurrentSlotComponent->AttachToComponent(ThirdPersonMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), NewSocket);
		CurrentSlotComponent->SetVisibility(false, false);
		KineticWeaponComponent->AttachToComponent(FirstPersonMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), FName("GripPoint"));
		KineticWeaponComponent->SetVisibility(true, true);
		CurrentWeapon = KineticWeapon;
		CurrentSlot = SlotOne;

		// Update HUD Elements
		HUDRef->UpdateHUDElements();
		break;

	case SlotTwo:
		NewSocket = EnergyWeaponComponent->GetAttachSocketName();
		CurrentSlotComponent->AttachToComponent(ThirdPersonMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), NewSocket);
		CurrentSlotComponent->SetVisibility(false, false);
		EnergyWeaponComponent->AttachToComponent(FirstPersonMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), FName("GripPoint"));
		EnergyWeaponComponent->SetVisibility(true, true);
		CurrentWeapon = EnergyWeapon;
		CurrentSlot = SlotTwo;

		// Update HUD Elements
		HUDRef->UpdateHUDElements();
		break;

	case SlotThree:
		NewSocket = HeavyWeaponComponent->GetAttachSocketName();
		CurrentSlotComponent->AttachToComponent(ThirdPersonMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), NewSocket);
		CurrentSlotComponent->SetVisibility(false, false);
		HeavyWeaponComponent->AttachToComponent(FirstPersonMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), FName("GripPoint"));
		HeavyWeaponComponent->SetVisibility(true, true);
		CurrentWeapon = HeavyWeapon;
		CurrentSlot = SlotThree;

		// Update HUD Elements
		HUDRef->UpdateHUDElements();
		break;

	default:
		break;
	}
}

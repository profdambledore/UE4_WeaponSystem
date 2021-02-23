// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "BaseWeapon.h"

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
	FirstPersonCamera->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
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

	// Setup Child Actor Components with the ABaseWeapons
	// Kinetic Weapon
	KineticWeaponComponent->AttachToComponent(FirstPersonMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), FName("PrimarySocket"));

	// Energy Weapon
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

void ABaseCharacter::SwitchToNextPrevious(float AxisValue)
{

}

void ABaseCharacter::Interact()
{

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

}

void ABaseCharacter::SwitchToEnergy()
{

}

void ABaseCharacter::SwitchToHeavy()
{

}


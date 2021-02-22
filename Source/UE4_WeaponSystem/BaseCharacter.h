// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "Components/ChildActorComponent.h"

#include "WeaponStatLibrary.h"

#include "BaseCharacter.generated.h"

UCLASS()
class UE4_WEAPONSYSTEM_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Player Movement
	void MoveX(float AxisValue);
	void MoveY(float AxisValue);
	void RotateX(float AxisValue);
	void RotateY(float AxisValue);
	void SwitchToNextPrevious(float AxisValue);

	void Interact();
	void Reload();
	void SwitchCamera();
	void PrimaryFire();
	void SecondaryFire();
	void SwitchToKinetic();
	void SwitchToEnergy();
	void SwitchToHeavy();

public:	
	// BaseCharacter Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* DefaultSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* FirstPersonMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* ThirdPersonMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent* FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USpringArmComponent* ThirdPersonSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent* ThirdPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent* MenuCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UChildActorComponent* KineticWeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UChildActorComponent* EnergyWeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UChildActorComponent* HeavyWeaponComponent;

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
		bool bIsThirdPerson;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
		bool bIsInMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
		TEnumAsByte<ESlotType> CurrentSlot;

	// Weapon Class Properties
	// The current selected weapon
	UPROPERTY()
		class ABaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
		class ABaseWeapon* KineticWeapon = nullptr;

	UPROPERTY()
		class ABaseWeapon* EnergyWeapon = nullptr;

	UPROPERTY()
		class ABaseWeapon* HeavyWeapon = nullptr;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"

#include "WeaponStatLibrary.h"

#include "BaseWeapon.generated.h"

class UWeaponInventoryComponent;

UCLASS()
class UE4_WEAPONSYSTEM_API ABaseWeapon : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void SetupWeaponBase(ESlotType SlotType, bool bHasSight);

	UFUNCTION()
		void SetSight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Base Weapon Components
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		//USceneComponent* WeaponRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* SightMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* MagazineMesh;

	UPROPERTY(VisibleAnywhere, Category = "Testing")
		class ABaseCharacter * PlayerRef = nullptr;

protected:
	FWeapon* ThisWeapon = nullptr;

};

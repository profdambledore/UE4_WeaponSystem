// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/DataTable.h"

#include "WeaponStatLibrary.h"

#include "WeaponPickup.generated.h"

class ABaseCharacter;
class UWeaponPickupWidget;

UCLASS()
class UE4_WEAPONSYSTEM_API AWeaponPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponPickup();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to setup the dropped weapon
	UFUNCTION()
		void SetWeaponToPickup(FName DroppedWeapon);

	// Called whenever the rarity colour is needed
	UFUNCTION(BlueprintCallable)
		FLinearColor GetRarityColour(ERarityType Rarity);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Overlap Functions
	UFUNCTION()
		void OnWidgetOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnWidgetOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	TArray<FPerk> GenerateRandomPerkColumn(FPerkTable PerkTable);

public:	
	// WeaponPickup Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* WeaponRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* SightMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* MagazineMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* WeaponParticleSys;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USphereComponent* WeaponWidgetRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UWidgetComponent* WeaponWidgetComponent;

	// Properties
	// Data Tables
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UDataTable* FGetWeaponDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UDataTable* FArchetypeDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UDataTable* FPerkDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "This Weapon")
		FWeapon Weapon;

	FGenTable NewPerkColumn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName testName;
};

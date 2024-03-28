// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Weapon.generated.h"

class AMyFieldSystemActor;
class UBoxComponent;
/**
 * 
 */
UCLASS()
class SLASH_API AWeapon : public AItem
{
	GENERATED_BODY()

public:
	//===============================================================================
	// PROPERTIES & VARIABLES
	//===============================================================================

	//===============================================================================
	// FUNCTIONS
	//===============================================================================
	AWeapon();
	void Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner, APawn* NewInstigator);
	void AttachMeshToSocket(USceneComponent* InParent, FName InSocketName) const;

	FORCEINLINE UBoxComponent* GetWeaponBox() const { return WeaponBox; }
	FORCEINLINE void EmptyIgnoreActors() { IgnoreActors.Empty(); }

protected:
	//===============================================================================
	// PROPERTIES & VARIABLES
	//===============================================================================
	UPROPERTY(EditAnywhere, Category="Weapon Properties")
	TObjectPtr<USoundBase> EquipSound;
	UPROPERTY(VisibleAnywhere, Category="WeaponProperties")
	TObjectPtr<UBoxComponent> WeaponBox;
	UPROPERTY(EditAnywhere, Category="WeaponProperties")
	float Damage = 20.f;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> BoxTraceStart;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> BoxTraceEnd;

	TArray<TObjectPtr<AActor>> IgnoreActors;
	UPROPERTY(VisibleAnywhere, Category="FieldSystem")
	TObjectPtr<AMyFieldSystemActor> MyFieldSystemActor;
	//===============================================================================
	// FUNCTIONS
	//===============================================================================
	virtual void BeginPlay() override;
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                                  const FHitResult& SweepResult) override;
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                       const FHitResult& SweepResult);
};

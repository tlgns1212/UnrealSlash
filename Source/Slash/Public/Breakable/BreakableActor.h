// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HitInterface.h"
#include "BreakableActor.generated.h"

class UCapsuleComponent;
class ATreasure;

UCLASS()
class SLASH_API ABreakableActor : public AActor, public IHitInterface
{
	GENERATED_BODY()
	
public:	
	//===============================================================================
	// PROPERTIES & VARIABLES
	//===============================================================================

	//===============================================================================
	// FUNCTIONS
	//===============================================================================
	ABreakableActor();
	
	virtual void Tick(float DeltaTime) override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;
protected:
	//===============================================================================
	// PROPERTIES & VARIABLES
	//===============================================================================
	UPROPERTY(VisibleAnywhere, Category="Geometry")
	TObjectPtr<UGeometryCollectionComponent> GeometryCollection;

	UPROPERTY(EditAnywhere, Category="Sounds")
	TObjectPtr<USoundBase> PotBreakSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCapsuleComponent> Capsule;

	UPROPERTY(EditAnywhere, Category="Drop")
	TSubclassOf<ATreasure> TreasureClass;
	
	//===============================================================================
	// FUNCTIONS
	//===============================================================================
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnChaosBreakEvent(const FChaosBreakEvent& BreakEvent);
};

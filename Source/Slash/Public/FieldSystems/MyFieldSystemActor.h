// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Field/FieldSystemActor.h"
#include "MyFieldSystemActor.generated.h"

class USphereComponent;
class UFieldSystemMetaDataFilter;
class URadialVector;
class URadialFalloff;
/**
 * 
 */
UCLASS()
class SLASH_API AMyFieldSystemActor : public AFieldSystemActor
{
	GENERATED_BODY()

public:
	//===============================================================================
	// PROPERTIES & VARIABLES
	//===============================================================================

	//===============================================================================
	// FUNCTIONS
	//===============================================================================
	AMyFieldSystemActor();
	UFUNCTION()
	void CreateFieldForce(const FVector& ImpactPoint) const;
protected:
	//===============================================================================
	// PROPERTIES & VARIABLES
	//===============================================================================
	UPROPERTY(VisibleAnywhere, Category="Radial")
	TObjectPtr<URadialFalloff> RadialFalloff;
	UPROPERTY(VisibleAnywhere, Category="Radial")
	TObjectPtr<URadialVector> RadialVector;
	UPROPERTY(VisibleAnywhere, Category="MetaData")
	TObjectPtr<UFieldSystemMetaDataFilter> MetaDataFilter;
	UPROPERTY(VisibleAnywhere, Category="Component")
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditAnywhere, Category="Magnitude")
	float RadialFalloffMagnitude;
	UPROPERTY(EditAnywhere, Category="Magnitude")
	float RadialVectorMagnitude;
	UPROPERTY(EditAnywhere, Category="Magnitude")
	float Radius;
	
	//===============================================================================
	// FUNCTIONS
	//===============================================================================
};

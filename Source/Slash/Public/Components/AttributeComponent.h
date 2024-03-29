// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SLASH_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//===============================================================================
	// PROPERTIES & VARIABLES
	//===============================================================================

	//===============================================================================
	// FUNCTIONS
	//===============================================================================
	UAttributeComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void ReceiveDamage(float Damage);
	FORCEINLINE float GetHealthPercent() const { return Health / MaxHealth; }
	FORCEINLINE bool IsAlive() const {return Health > 0.f;};
protected:
	//===============================================================================
	// PROPERTIES & VARIABLES
	//===============================================================================

	//===============================================================================
	// FUNCTIONS
	//===============================================================================
	virtual void BeginPlay() override;

private:
	//===============================================================================
	// PROPERTIES & VARIABLES
	//===============================================================================
	UPROPERTY(EditAnywhere, Category="ActorAttributes")
	float Health;
	UPROPERTY(EditAnywhere, Category="ActorAttributes")
	float MaxHealth;

	//===============================================================================
	// FUNCTIONS
	//===============================================================================
};

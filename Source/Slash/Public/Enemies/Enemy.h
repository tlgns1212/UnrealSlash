// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "Enemy.generated.h"

class UHealthBarComponent;
class UAttributeComponent;

UCLASS()
class SLASH_API AEnemy : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	//===============================================================================
	// PROPERTIES & VARIABLES
	//===============================================================================

	//===============================================================================
	// FUNCTIONS
	//===============================================================================
	AEnemy();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

	void PlayHitReactMontage(const FName& SectionName);

protected:
	//===============================================================================
	// PROPERTIES & VARIABLES
	//===============================================================================

	/**
		* Animation montages
	*/
	UPROPERTY(EditDefaultsOnly, Category="Montages")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(EditAnywhere, Category="Sounds")
	TObjectPtr<USoundBase> HitSound;

	UPROPERTY(EditAnywhere, Category="VisualEffects")
	TObjectPtr<UParticleSystem> HitParticles;

	UPROPERTY(VisibleAnywhere, Category="Attributes")
	TObjectPtr<UAttributeComponent> Attributes;

	UPROPERTY(VisibleAnywhere, Category="Widgets")
	TObjectPtr<UHealthBarComponent> HealthBarWidget;
	//===============================================================================
	// FUNCTIONS
	//===============================================================================
	virtual void BeginPlay() override;

	void DirectionalHitReact(const FVector& ImpactPoint);
};

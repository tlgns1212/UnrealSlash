// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "Enemy.generated.h"

class UPawnSensingComponent;
class AAIController;
class UHealthBarComponent;
class UAttributeComponent;

UENUM(BlueprintType)
enum class EDeathPose : uint8
{
	EDP_Alive UMETA(DisplayName="Alive"),
	EDP_Death1 UMETA(DisplayName="Death1"),
	EDP_Death2 UMETA(DisplayName="Death2"),
	EDP_Death3 UMETA(DisplayName="Death3"),
	EDP_Death4 UMETA(DisplayName="Death4"),
	EDP_Death5 UMETA(DisplayName="Death5")
};

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	EES_Patrolling UMETA(DisplayName="Patrolling"),
	EES_Chasing UMETA(DisplayName="Chasing"),
	EES_Attacking UMETA(DisplayName="Attacking")
};

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
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	                         class AController* EventInstigator, AActor* DamageCauser) override;

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
	UPROPERTY(EditDefaultsOnly, Category="Montages")
	TObjectPtr<UAnimMontage> DeathMontage;

	UPROPERTY(EditAnywhere, Category="Sounds")
	TObjectPtr<USoundBase> HitSound;

	UPROPERTY(EditAnywhere, Category="VisualEffects")
	TObjectPtr<UParticleSystem> HitParticles;

	/**
		 * Components
	 */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeComponent> Attributes;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UHealthBarComponent> HealthBarWidget;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPawnSensingComponent> PawnSensing;

	EEnemyState EnemyState = EEnemyState::EES_Patrolling;
	UPROPERTY(BlueprintReadOnly)
	EDeathPose DeathPose = EDeathPose::EDP_Alive;

	UPROPERTY()
	TObjectPtr<AActor> CombatTarget;
	UPROPERTY(EditAnywhere)
	double CombatRadius = 1000.f;
	UPROPERTY(EditAnywhere)
	double AttackRadius = 150.f;

	/**
	 * Navigation
	 */
	UPROPERTY()
	TObjectPtr<AAIController> EnemyController;
	// 현재 Patrol Target 
	UPROPERTY(EditInstanceOnly, Category="AI Navigation")
	TObjectPtr<AActor> PatrolTarget;
	UPROPERTY(EditInstanceOnly, Category="AI Navigation")
	TArray<TObjectPtr<AActor>> PatrolTargets;
	UPROPERTY(EditAnywhere)
	double PatrolRadius = 200.f;
	FTimerHandle PatrolTimer;
	UPROPERTY(EditAnywhere, Category="AI Navigation")
	float PatrolWaitMin = 5.f;
	UPROPERTY(EditAnywhere, Category="AI Navigation")
	float PatrolWaitMax = 10.f;
	//===============================================================================
	// FUNCTIONS
	//===============================================================================
	virtual void BeginPlay() override;
	void TickCombatTarget();
	void TickPatrolTarget();
	void TickRotateHealthBar();

	void DirectionalHitReact(const FVector& ImpactPoint);
	void Die();
	bool InTargetRange(const AActor* Target, double Radius) const;
	void MoveToTarget(const AActor* Target) const;

	void PatrolTimerFinished();
	AActor* ChoosePatrolTarget();

	UFUNCTION()
	void PawnSeen(APawn* Pawn);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Enemy.generated.h"

class UPawnSensingComponent;
class AAIController;
class UHealthBarComponent;

UENUM(BlueprintType)
enum class EDeathPose : uint8
{
	EDP_Death1 UMETA(DisplayName="Death1"),
	EDP_Death2 UMETA(DisplayName="Death2"),
	EDP_Death3 UMETA(DisplayName="Death3"),
	EDP_Death4 UMETA(DisplayName="Death4"),
	EDP_Death5 UMETA(DisplayName="Death5")
};

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	EES_Dead UMETA(DisplayName="Dead"),
	EES_Patrolling UMETA(DisplayName="Patrolling"),
	EES_Chasing UMETA(DisplayName="Chasing"),
	EES_Attacking UMETA(DisplayName="Attacking"),
	EES_Engaged UMETA(DisplayName="Engaged")
};

UCLASS()
class SLASH_API AEnemy : public ABaseCharacter
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
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	                         class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;
	virtual void Destroyed() override;

protected:
	//===============================================================================
	// PROPERTIES & VARIABLES
	//===============================================================================

	/**
		 * Components
	 */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UHealthBarComponent> HealthBarWidget;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPawnSensingComponent> PawnSensing;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY(BlueprintReadOnly)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;
	UPROPERTY(BlueprintReadOnly)
	EDeathPose DeathPose;

	UPROPERTY()
	TObjectPtr<AActor> CombatTarget;
	UPROPERTY(EditAnywhere)
	double CombatRadius = 1000.f;
	UPROPERTY(EditAnywhere)
	double AttackRadius = 130.f;

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

	/** AI Behavior */
	UPROPERTY(EditAnywhere, Category = "Combat")
	float PatrollingSpeed = 125.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float ChasingSpeed = 300.f;

	/** Combat */
	FTimerHandle AttackTimer;
	UPROPERTY(EditAnywhere, Category="Combat")
	float AttackMin = 0.5f;
	UPROPERTY(EditAnywhere, Category="Combat")
	float AttackMax = 1.f;
	//===============================================================================
	// FUNCTIONS
	//===============================================================================
	virtual void BeginPlay() override;
	void TickCombatTarget();
	void TickPatrolTarget();
	void TickRotateHealthBar();
	
	virtual void Attack() override;
	virtual bool CanAttack() override;
	virtual void HandleDamage(float DamageAmount) override;
	
	virtual void Die() override;
	bool InTargetRange(const AActor* Target, double Radius) const;
	void MoveToTarget(const AActor* Target) const;

	void PatrolTimerFinished();
	AActor* ChoosePatrolTarget();

	UFUNCTION()
	void PawnSeen(APawn* Pawn);

	/** AI Behavior */
	void HideHealthBar();
	void ShowHealthBar();
	void LoseInterest();
	void StartPatrolling();
	void ChaseTarget();
	bool IsOutsideCombatRadius();
	bool IsOutsideAttackRadius();
	bool IsInsideAttackRadius();
	bool IsChasing();
	bool IsAttacking();
	bool IsDead();
	bool IsEngaged();
	void ClearPatrolTimer();

	/** Combat */
	void StartAttackTimer();
	void ClearAttackTimer();
};

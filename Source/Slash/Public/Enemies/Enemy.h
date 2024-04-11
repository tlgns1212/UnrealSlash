// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Enemy.generated.h"

class UPawnSensingComponent;
class AAIController;
class UHealthBarComponent;

UENUM(BlueprintType)
enum EDeathPose
{
	EDP_Death1 UMETA(DisplayName="Death1"),
	EDP_Death2 UMETA(DisplayName="Death2"),
	EDP_Death3 UMETA(DisplayName="Death3"),
	EDP_Death4 UMETA(DisplayName="Death4"),
	EDP_Death5 UMETA(DisplayName="Death5"),

	EDP_MAX UMETA(DisplayName="DefaultMAX")
};

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	EES_Dead UMETA(DisplayName="Dead"),
	EES_Patrolling UMETA(DisplayName="Patrolling"),
	EES_Chasing UMETA(DisplayName="Chasing"),
	EES_Attacking UMETA(DisplayName="Attacking"),
	EES_Engaged UMETA(DisplayName="Engaged"),

	EES_NoState UMETA(DisplayName="NoState")
};

UCLASS()
class SLASH_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemy();
	/** <AActor> */
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	                         class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Destroyed() override;
	/** </AActor> */

	/** <IHitInterface> */
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;
	/** </IHitInterface> */
protected:
	/** <AActor> */
	virtual void BeginPlay() override;
	/** </AActor> */

	/** <ABaseCharacter> */
	virtual void Die() override;
	virtual void Attack() override;
	virtual bool CanAttack() override;
	virtual void AttackEnd() override;
	virtual void HandleDamage(float DamageAmount) override;
	virtual int32 PlayDeathMontage() override;
	/** </ABaseCharacter> */
	
	UPROPERTY(BlueprintReadOnly)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;
	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EDeathPose> DeathPose;
private:
	/** AI Behavior */
	void InitializeEnemy();
	void TickRotateHealthBar();
	void TickCombatTarget();
	void TickPatrolTarget();
	void PatrolTimerFinished();
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
	void StartAttackTimer();
	void ClearAttackTimer();
	bool InTargetRange(const AActor* Target, double Radius) const;
	void MoveToTarget(const AActor* Target) const;
	AActor* ChoosePatrolTarget();
	void SpawnDefaultWeapon();
	
	UFUNCTION()
	void PawnSeen(APawn* Pawn); // Callback for OnPawnSeen in UPawnSensingComponent

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UHealthBarComponent> HealthBarWidget;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPawnSensingComponent> PawnSensing;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> WeaponClass;
	UPROPERTY()
	TObjectPtr<AActor> CombatTarget;
	UPROPERTY(EditAnywhere)
	double CombatRadius = 1000.f;
	UPROPERTY(EditAnywhere)
	double AttackRadius = 150.f;
	UPROPERTY()
	TObjectPtr<AAIController> EnemyController;
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
	UPROPERTY(EditAnywhere, Category = "Combat")
	float PatrollingSpeed = 125.f;

	FTimerHandle AttackTimer;
	UPROPERTY(EditAnywhere, Category="Combat")
	float AttackMin = 0.5f;
	UPROPERTY(EditAnywhere, Category="Combat")
	float AttackMax = 1.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float ChasingSpeed = 300.f;
	UPROPERTY(EditAnywhere, Category="Combat")
	float DeathLifeSpan = 3.0f;
};

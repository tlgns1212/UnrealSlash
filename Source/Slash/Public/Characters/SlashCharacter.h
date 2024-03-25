// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SlashCharacter.generated.h"

class USlashAnimInstance;
class AWeapon;
class AItem;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Unequipped UMETA(DisplayName = "Unequipped"),
	ECS_EquippedOneHandedWeapon UMETA(DisplayName = "EquippedOneHandedWeapon"),
	ECS_EquippedTwoHandedWeapon UMETA(DisplayName = "EquippedTwoHandedWeapon")
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	EAS_Unoccupied UMETA(DisplayName="Unoccupied"),
	EAS_Attacking UMETA(DisplayName="Attacking"),
	EAS_EquippingWeapon UMETA(DisplayName="EquippingWeapon")
};

UCLASS()
class SLASH_API ASlashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	//===============================================================================
	// PROPERTIES & VARIABLES
	//===============================================================================

	//===============================================================================
	// FUNCTIONS
	//===============================================================================
	ASlashCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	
	FORCEINLINE void SetOverlappingItem(AItem* ItemIn) { OverlappingItem = ItemIn; }
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }

	UFUNCTION(BlueprintCallable)
	void SetWeaponCollision(ECollisionEnabled::Type CollisionEnabled);
	
	void Arm() const;
	void Disarm() const;

	void FinishEquipping();
	void EndAttack();
	
protected:
	//===============================================================================
	// PROPERTIES & VARIABLES
	//===============================================================================
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> SlashContext;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MovementAction;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> EKeyPressedAction;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> AttackAction;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> DodgeAction;

	UPROPERTY(VisibleAnywhere, Category= "Anim")
	TObjectPtr<USlashAnimInstance> SlashAnimInstance;

	//===============================================================================
	// FUNCTIONS
	//===============================================================================
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump();
	void EKeyPressed();
	void Attack();
	void Dodge();

	void PlayAttackMontage();
	bool CanAttack() const;
	void PlayEquipMontage(const FName& SectionName);
	bool CanDisarm() const;
	bool CanArm() const;

private:
	//===============================================================================
	// PROPERTIES & VARIABLES
	//===============================================================================
	UPROPERTY(VisibleAnywhere)
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
	UPROPERTY(VisibleAnywhere)
	EActionState ActionState = EActionState::EAS_Unoccupied;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> ViewCamera;
	UPROPERTY(VisibleAnywhere, Category = "Hair")
	TObjectPtr<UGroomComponent> Hair;
	UPROPERTY(VisibleAnywhere, Category = "Hair")
	TObjectPtr<UGroomComponent> Eyebrows;

	UPROPERTY(VisibleInstanceOnly, Category="Item")
	TObjectPtr<AItem> OverlappingItem;

	UPROPERTY(VisibleAnywhere, Category="Weapon")
	TObjectPtr<AWeapon> EquippedWeapon;

	/**
	* Animation montages
	*/
	UPROPERTY(EditDefaultsOnly, Category="Montages")
	TObjectPtr<UAnimMontage> AttackMontage;
	UPROPERTY(EditDefaultsOnly, Category="Montages")
	TObjectPtr<UAnimMontage> EquipMontage;

	//===============================================================================
	// FUNCTIONS
	//===============================================================================
};

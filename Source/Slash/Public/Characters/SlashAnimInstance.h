// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SlashAnimInstance.generated.h"

class UCharacterMovementComponent;
class ASlashCharacter;
enum class ECharacterState : uint8;
/**
 * 
 */
UCLASS()
class SLASH_API USlashAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	//===============================================================================
	// PROPERTIES & VARIABLES
	//===============================================================================
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ASlashCharacter> SlashCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	TObjectPtr<UCharacterMovementComponent> SlashCharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsFalling;

	UPROPERTY(BlueprintReadOnly, Category = "Movement | Character State")
	ECharacterState CharacterState;

	//===============================================================================
	// FUNCTIONS
	//===============================================================================
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UFUNCTION()
	void AnimNotify_Arm() const;
	UFUNCTION()
	void AnimNotify_Disarm() const;
	UFUNCTION()
	void AnimNotify_FinishEquip() const;
	UFUNCTION()
	void AnimNotify_EnableBoxCollision() const;
	UFUNCTION()
	void AnimNotify_DisableBoxCollision() const;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SlashCharacter.generated.h"

class AItem;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;

enum class ECharacterState 
{
	
};

UCLASS()
class SLASH_API ASlashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASlashCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE void SetOverlappingItem(AItem* ItemIn){OverlappingItem = ItemIn; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Input)
		UInputMappingContext* SlashContext;
	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* MovementAction;
	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* EKeyPressedAction;
	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* AttackAction;
	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* DodgeAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump();
	void EKeyPressed();
	void Attack();
	void Dodge();

private:
	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* ViewCamera;
	UPROPERTY(VisibleAnywhere, Category = "Hair")
		UGroomComponent* Hair;
	UPROPERTY(VisibleAnywhere, Category = "Hair")
		UGroomComponent* Eyebrows;

	UPROPERTY(VisibleInstanceOnly, Category="Item")
	AItem* OverlappingItem;
};

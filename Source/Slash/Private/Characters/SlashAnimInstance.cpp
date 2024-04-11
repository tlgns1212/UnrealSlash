// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Characters/SlashAnimInstance.h"
#include "Characters/SlashCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void USlashAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	SlashCharacter = Cast<ASlashCharacter>(TryGetPawnOwner());
	if (SlashCharacter)
	{
		SlashCharacterMovement = SlashCharacter->GetCharacterMovement();
	}
}

void USlashAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (SlashCharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(SlashCharacterMovement->Velocity);
		bIsFalling = SlashCharacterMovement->IsFalling();
		CharacterState = SlashCharacter->GetCharacterState();
	}
	// USlashAnimInstance::AnimNotify_EndCombo()
}

void USlashAnimInstance::AnimNotify_Arm() const
{
	if(SlashCharacter)
	{
		SlashCharacter->AttachWeaponToHand();
	}
}

void USlashAnimInstance::AnimNotify_Disarm() const
{
	if(SlashCharacter)
	{
		SlashCharacter->AttachWeaponToBack();
	}
}

void USlashAnimInstance::AnimNotify_FinishEquip() const
{
	if(SlashCharacter)
	{
		SlashCharacter->FinishEquipping();
	}
}

void USlashAnimInstance::AnimNotify_EnableBoxCollision() const
{
	if(SlashCharacter)
	{
		SlashCharacter->SetWeaponCollision(ECollisionEnabled::QueryOnly);
	}
}

void USlashAnimInstance::AnimNotify_DisableBoxCollision() const
{
	if(SlashCharacter)
	{
		SlashCharacter->SetWeaponCollision(ECollisionEnabled::NoCollision);
	}
}

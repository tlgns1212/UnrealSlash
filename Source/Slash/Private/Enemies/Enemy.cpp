// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemy.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Slash/DebugMacros.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::GetHit(const FVector& ImpactPoint)
{
	DirectionalHitReact(ImpactPoint);

	if(HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,HitSound, ImpactPoint);	
	}
}

void AEnemy::PlayHitReactMontage(const FName& SectionName)
{
	 UAnimInstance* AnimInstance =  GetMesh()->GetAnimInstance();
	if(AnimInstance && HitReactMontage)
	{
		AnimInstance->Montage_Play(HitReactMontage);
		AnimInstance->Montage_JumpToSection(SectionName, HitReactMontage);
	}
}

void AEnemy::DirectionalHitReact(const FVector& ImpactPoint)
{
	const FVector Forward = GetActorForwardVector();
	// Forward랑 ImpactLowered가 평행을 이루도록 해야 각도 계산하기가 훨씬 좋음(z축 무시)
	const FVector ImpactLowered{ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z};
	const FVector ToHit = (ImpactLowered - GetActorLocation()).GetSafeNormal();

	// Forward . ToHit = |Forward||ToHit| * cos(theta)
	// |Forward| = 1, |ToHit| = 1, so Forward . ToHit = cos(theta)
	const double CosTheta = FVector::DotProduct(Forward, ToHit);
	// inverse cosine(arc-cosine) of cos(theta) to get theta
	double Theta = FMath::Acos(CosTheta);
	// convert from radians to degrees
	Theta = FMath::RadiansToDegrees(Theta);

	// CrossProduct가 위를 가르키면 오른쪽, 아래면 왼쪽 (왼손 법칙)
	const FVector CrossProduct =  FVector::CrossProduct(Forward, ToHit);
	if(CrossProduct.Z < 0)
	{
		Theta *= -1.f;
	}

	FName Section{"FromBack"};
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(2,5.f,FColor::Blue,FString::SanitizeFloat(Theta));
	}
	if(Theta >= -45.f && Theta < 45.f)
	{
		Section = FName{"FromFront"};
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1,5.f,FColor::Red,Section.ToString());
		}
	}
	else if(Theta >= -135.f && Theta < -45.f)
	{
		Section = FName{"FromLeft"};
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1,5.f,FColor::Red,Section.ToString());
		}
	}
	else if(Theta >= 45.f && Theta < 135.f)
	{
		Section = FName{"FromRight"};
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1,5.f,FColor::Red,Section.ToString());
		}
	}
	
	PlayHitReactMontage(Section);
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemy.h"

#include "Components/AttributeComponent.h"
#include "Components/CapsuleComponent.h"
#include "HUD/HealthBarComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Slash/DebugMacros.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));
	HealthBarWidget = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(HealthBarWidget)
	{
		const FVector CameraLocation = UGameplayStatics::GetPlayerCameraManager(this, 0)->GetCameraLocation();
		const FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CameraLocation);
		SetActorRotation(NewRotation);
	}
}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::GetHit_Implementation(const FVector& ImpactPoint)
{
	DirectionalHitReact(ImpactPoint);

	if(HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,HitSound, ImpactPoint);	
	}
	if(HitParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this,HitParticles,ImpactPoint);
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
	if(Theta >= -45.f && Theta < 45.f)
	{
		Section = FName{"FromFront"};
	}
	else if(Theta >= -135.f && Theta < -45.f)
	{
		Section = FName{"FromLeft"};
	}
	else if(Theta >= 45.f && Theta < 135.f)
	{
		Section = FName{"FromRight"};
	}
	
	PlayHitReactMontage(Section);
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if(Attributes)
	{
		Attributes->ReceiveDamage(DamageAmount);
		if(HealthBarWidget)
		{
			HealthBarWidget->SetHealthPercent(Attributes->GetHealthPercent());	
		}
	}
	return DamageAmount;
}
#include "Characters/BaseCharacter.h"

#include "Components/AttributeComponent.h"
#include "Components/BoxComponent.h"
#include "Items/Weapons/Weapon.h"
#include "Kismet/GameplayStatics.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::Attack()
{
}

void ABaseCharacter::Die()
{
}

void ABaseCharacter::PlayAttackMontage()
{
	if(AttackMontageSections.Num() <= 0) return;
	const int32 MaxSectionIndex = AttackMontageSections.Num() - 1;
	const int32 Selection = FMath::RandRange(0,MaxSectionIndex);
	PlayMontageSection(AttackMontage, AttackMontageSections[Selection]);
}

void ABaseCharacter::PlayHitReactMontage(const FName& SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && HitReactMontage)
	{
		AnimInstance->Montage_Play(HitReactMontage);
		AnimInstance->Montage_JumpToSection(SectionName, HitReactMontage);
	}
}

void ABaseCharacter::DirectionalHitReact(const FVector& ImpactPoint)
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
	const FVector CrossProduct = FVector::CrossProduct(Forward, ToHit);
	if (CrossProduct.Z < 0)
	{
		Theta *= -1.f;
	}

	FName Section{"FromBack"};
	if (Theta >= -45.f && Theta < 45.f)
	{
		Section = FName{"FromFront"};
	}
	else if (Theta >= -135.f && Theta < -45.f)
	{
		Section = FName{"FromLeft"};
	}
	else if (Theta >= 45.f && Theta < 135.f)
	{
		Section = FName{"FromRight"};
	}

	PlayHitReactMontage(Section);
}

void ABaseCharacter::PlayHitSound(const FVector& ImpactPoint)
{
	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, ImpactPoint);
	}
}

void ABaseCharacter::SpawnHitParticles(const FVector& ImpactPoint)
{
	if (HitParticles && GetWorld())
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, ImpactPoint);
	}
}

void ABaseCharacter::HandleDamage(float DamageAmount)
{
	if (Attributes)
	{
		Attributes->ReceiveDamage(DamageAmount);
	}
}

void ABaseCharacter::PlayMontageSection(UAnimMontage* Montage, const FName& SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance && Montage)
	{
		AnimInstance->Montage_Play(Montage);
		AnimInstance->Montage_JumpToSection(SectionName, Montage);
	}
}

bool ABaseCharacter::CanAttack()
{
	return true;
}

bool ABaseCharacter::IsAlive()
{
	return Attributes && Attributes->IsAlive();
}

void ABaseCharacter::EndAttack()
{
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::SetWeaponCollision(ECollisionEnabled::Type CollisionEnabled)
{
	if(EquippedWeapon && EquippedWeapon->GetWeaponBox())
	{
		EquippedWeapon->EmptyIgnoreActors();
		EquippedWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
	}
}

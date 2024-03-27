// Fill out your copyright notice in the Description page of Project Settings.


#include "FieldSystems/MyFieldSystemActor.h"

#include "Components/SphereComponent.h"
#include "Field/FieldSystemComponent.h"
#include "Field/FieldSystemObjects.h"

#include "DrawDebugHelpers.h"

AMyFieldSystemActor::AMyFieldSystemActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RadialFalloff = CreateDefaultSubobject<URadialFalloff>(TEXT("RadialFalloff"));
	RadialVector = CreateDefaultSubobject<URadialVector>(TEXT("RadialVector"));
	MetaDataFilter = CreateDefaultSubobject<UFieldSystemMetaDataFilter>(TEXT("MetaDataFilter"));
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());

	RadialFalloffMagnitude = 500000.f;
	RadialVectorMagnitude = 25000000.f;
}

void AMyFieldSystemActor::CreateFieldForce(const FVector& ImpactPoint) const
{
	if (RadialFalloff)
	{
		RadialFalloff->SetRadialFalloff(RadialFalloffMagnitude, 0.08f, 1.f, 0, 200, ImpactPoint, EFieldFalloffType::Field_FallOff_None);
	}
	if (RadialVector)
	{
		RadialVector->SetRadialVector(RadialVectorMagnitude, ImpactPoint);
	}
	if (MetaDataFilter)
	{
		MetaDataFilter->SetMetaDataFilterType(EFieldFilterType::Field_Filter_Dynamic,
		                                      EFieldObjectType::Field_Object_Destruction,
		                                      EFieldPositionType::Field_Position_CenterOfMass);
	}
	if (GetFieldSystemComponent())
	{
		GetFieldSystemComponent()->ApplyPhysicsField(true, EFieldPhysicsType::Field_ExternalClusterStrain, nullptr,
		                                             RadialFalloff);
		GetFieldSystemComponent()->ApplyPhysicsField(true, EFieldPhysicsType::Field_LinearForce, MetaDataFilter,
		                                             RadialVector);
	}

	DrawDebugSphere(GetWorld(), ImpactPoint, 25.f, 12, FColor::Blue, false, 5.f);
}

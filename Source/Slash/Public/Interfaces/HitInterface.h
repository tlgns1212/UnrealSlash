// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HitInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHitInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SLASH_API IHitInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 이건 블루프린트랑 C++ 둘다 가능하게 해줌, 단 C++은 이름 뒤에 _Implement붙여줘야하고, 사용할때 IHitInterface::ExecuteGetHit() 이런식으로 사용
	UFUNCTION(BlueprintNativeEvent)
	void GetHit(const FVector& ImpactPoint);

	// 이건 순수 가상함수, 이건 그냥 override하고 GetHit() 이런식으로 사용
	// virtual void GetHit(const FVector& ImpactPoint) = 0;
};

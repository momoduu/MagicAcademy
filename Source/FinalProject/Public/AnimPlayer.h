// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimPlayer.generated.h"


UCLASS()
class FINALPROJECT_API UAnimPlayer : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY()
		class AFinalProjectCharacter* me;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bAir = false;
};

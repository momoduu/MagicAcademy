// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RidingTeacherFSM.h"
#include "RidingTeacherAnim.generated.h"

UCLASS()
class FINALPROJECT_API URidingTeacherAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FSM)
	ERidingTeacherState animState;
	
};

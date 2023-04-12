// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TeacherFSM.h"
#include "Teacher_2Anim.generated.h"



UCLASS()
class FINALPROJECT_API UTeacher_2Anim : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FSM)
 		ETeacherState animState;


	// 		//공격 상태 재생할지 여부
	// 		UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = FSM)
	// 		bool bAttackPlay = false;

			//공격 애니메이션이 끝나는 이벤트 함수
	// 		UFUNCTION(BlueprintCallable, Category = FSMEvent)
	// 		void OnEndAttackAnimation();

			// 애니메이션 재생 함수
	UFUNCTION(BlueprintImplementableEvent, Category = FSMEvent)
		void Teacher_2_Montage(FName sectionName);


};

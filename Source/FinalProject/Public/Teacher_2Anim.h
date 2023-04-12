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


	// 		//���� ���� ������� ����
	// 		UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = FSM)
	// 		bool bAttackPlay = false;

			//���� �ִϸ��̼��� ������ �̺�Ʈ �Լ�
	// 		UFUNCTION(BlueprintCallable, Category = FSMEvent)
	// 		void OnEndAttackAnimation();

			// �ִϸ��̼� ��� �Լ�
	UFUNCTION(BlueprintImplementableEvent, Category = FSMEvent)
		void Teacher_2_Montage(FName sectionName);


};

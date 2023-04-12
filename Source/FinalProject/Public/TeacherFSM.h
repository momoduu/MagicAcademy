// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include "TeacherFSM.generated.h"

//����� ���� ���� 
UENUM(BlueprintType)
enum class ETeacherState :uint8
{
	Idle,
	Explo,
	Move,
	Study,
	RandomClass
};



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FINALPROJECT_API UTeacherFSM : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTeacherFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	//���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)// VisibleAnywhere, BlueprintReadOnly, Category = FSM)
		ETeacherState mState = ETeacherState::Idle;

	//��� ����
	void IdleState();

	//Ž�� ����
	void ExploState();

	//move ����
	void MoveState();

	//���� ���� Ÿ�̸�
	UFUNCTION(BlueprintCallable)
		void StudyState();

	UFUNCTION(BlueprintCallable)
 		void RandomState();

	//���� ���� �̼� ����
	UFUNCTION(BlueprintCallable)
		void Random();

	//Jar ���� ������
	bool bMove = false;
	//Jar ����
	float JarRange = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 passClass = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 falseClass = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 test;
	//�ǰ� �� ��� �ִ��Լ�		
// 	UFUNCTION(BlueprintCallable)
// 		void DamageAnim(int32 attackIdx);

	//ó�� ��ġ�� ��� ���� ����
	FVector originPos;

	//���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AHJ_Teacher_2* me;

	//Ÿ�� �׾Ƹ�
	UPROPERTY(VisibleAnywhere, Category = FSM)
		class AJar* jar;
	UPROPERTY(VisibleAnywhere, Category = FSM)
		class AFinalProjectCharacter* target;



	//��� �ð�
	float currentTime = 0;

	//��� �ð�
	UPROPERTY(EditDefaultsOnly, Category = FSM)
		float idleDelayTime = 2;

		float StudyDelayTime = 4;

	//��� ���� �ִϸ��̼� �������Ʈ
	UPROPERTY()
		class UTeacher_2Anim* anim;

	// 	Teacher_2 �� �����ϰ� �ִ� AIController
	UPROPERTY()
		class AAIController* ai;

	//�� ã�� ����� ���� ��ġ
	FVector randomPos;
	//���� ��ġ ��������
	bool GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest);

	UPROPERTY(EditAnywhere)
	TArray<AActor*> randPos;
};

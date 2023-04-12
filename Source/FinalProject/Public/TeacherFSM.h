// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include "TeacherFSM.generated.h"

//사용자 상태 정의 
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
	//상태 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)// VisibleAnywhere, BlueprintReadOnly, Category = FSM)
		ETeacherState mState = ETeacherState::Idle;

	//대기 상태
	void IdleState();

	//탐색 상태
	void ExploState();

	//move 상태
	void MoveState();

	//수업 진행 타이머
	UFUNCTION(BlueprintCallable)
		void StudyState();

	UFUNCTION(BlueprintCallable)
 		void RandomState();

	//수업 랜덤 이수 상태
	UFUNCTION(BlueprintCallable)
		void Random();

	//Jar 까지 갔느냐
	bool bMove = false;
	//Jar 범위
	float JarRange = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 passClass = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 falseClass = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 test;
	//피격 시 재생 애님함수		
// 	UFUNCTION(BlueprintCallable)
// 		void DamageAnim(int32 attackIdx);

	//처음 위치를 담아 놓을 변수
	FVector originPos;

	//소유 액터
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AHJ_Teacher_2* me;

	//타깃 항아리
	UPROPERTY(VisibleAnywhere, Category = FSM)
		class AJar* jar;
	UPROPERTY(VisibleAnywhere, Category = FSM)
		class AFinalProjectCharacter* target;



	//경과 시간
	float currentTime = 0;

	//대기 시간
	UPROPERTY(EditDefaultsOnly, Category = FSM)
		float idleDelayTime = 2;

		float StudyDelayTime = 4;

	//사용 중인 애니메이션 블루프린트
	UPROPERTY()
		class UTeacher_2Anim* anim;

	// 	Teacher_2 를 소유하고 있는 AIController
	UPROPERTY()
		class AAIController* ai;

	//길 찾기 수행시 랜덤 위치
	FVector randomPos;
	//랜덤 위치 가져오기
	bool GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest);

	UPROPERTY(EditAnywhere)
	TArray<AActor*> randPos;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RidingTeacherFSM.generated.h"

UENUM(BlueprintType)
enum class ERidingTeacherState :uint8
{
	Idle,
	Move,
	Study,
	Follow
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FINALPROJECT_API URidingTeacherFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URidingTeacherFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERidingTeacherState bState = ERidingTeacherState::Idle;

	UPROPERTY()
	class URidingTeacherAnim* anim;

	void IdleState();

	void MoveState();

	void StudyState();

	void FollowState();
	
	UPROPERTY(EditAnywhere)
	float broomRange = 250.0f;

	FVector originPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ARidingTeacher* me;

	UPROPERTY(VisibleAnywhere, Category = FSM)
		class ATeacherBroom* broom;

	UPROPERTY(VisibleAnywhere, Category = FSM)
		class AFinalProjectCharacter* target;

	UPROPERTY()
		class AAIController* ai;

	FVector randomPos;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> randPos;

	UPROPERTY(EditAnywhere)
	FVector prevBroomPos; 

	float currTime; 

	bool bIsPlay = false;


	float currentTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float idleDelayTime = 2;
};

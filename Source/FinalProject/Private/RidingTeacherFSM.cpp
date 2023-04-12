// Fill out your copyright notice in the Description page of Project Settings.


#include "RidingTeacherFSM.h"
#include "RidingTeacher.h"
#include <AIModule/Classes/AIController.h>
#include <NavigationSystem.h>
#include "TeacherBroom.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "../FinalProjectCharacter.h"
#include <LevelSequence/Public/LevelSequencePlayer.h>
#include <LevelSequence/Public/LevelSequence.h>
#include "RidingTeacherAnim.h"

// Sets default values for this component's properties
URidingTeacherFSM::URidingTeacherFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URidingTeacherFSM::BeginPlay()
{
	Super::BeginPlay();

 	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATeacherBroom::StaticClass());
 
 	broom = Cast<ATeacherBroom>(actor);

	me = Cast<ARidingTeacher>(GetOwner());
	me->GetCharacterMovement()->MaxWalkSpeed = 200;

	target = Cast<AFinalProjectCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AFinalProjectCharacter::StaticClass()));
	
	ai = Cast<AAIController>(me->GetController());

	anim = Cast<URidingTeacherAnim>(me->GetMesh()->GetAnimInstance());

	originPos = me->GetActorLocation();
	
	prevBroomPos = broom->GetActorLocation();
}


// Called every frame
void URidingTeacherFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (bState)
	{
	case ERidingTeacherState::Idle:
		IdleState();
		break;
	case ERidingTeacherState::Move:
		MoveState();
		break;
	case ERidingTeacherState::Study:
		StudyState();
		break;
	case ERidingTeacherState::Follow:
		FollowState();
		break;
	}
}

void URidingTeacherFSM::IdleState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > idleDelayTime)
	{
		bState = ERidingTeacherState::Move;
		anim->animState = bState;

		currentTime = 0;

		//anim->Teacher_2_Montage(TEXT("Walk0"));
		//anim->Teacher_2_Montage(FName sectionName);
		int32 rand = FMath::RandRange(0, randPos.Num() - 1);
		randomPos = randPos[rand]->GetActorLocation();

	}
}

void URidingTeacherFSM::MoveState()
{
	if (!bIsPlay)
	{
		EPathFollowingRequestResult::Type result = ai->MoveToLocation(randomPos);
		if (result == EPathFollowingRequestResult::AlreadyAtGoal)
		{
			//idle 상태로
			bState = ERidingTeacherState::Idle; 
			anim->animState = bState;
			//anim->Teacher_2_Montage(TEXT("Idle0"));
			//anim->animState = mState;
		}
	}
	else
	{
		bState = ERidingTeacherState::Study;
	}

}

void URidingTeacherFSM::StudyState()
{
	 	FVector dir = broom->GetActorLocation() - me->GetActorLocation();
	 	
	 	//ai->MoveToLocation(FVector(1781.0f, 1575.0f, -1.0f));
	  	EPathFollowingRequestResult::Type result = ai->MoveToLocation(FVector(1410.0f, 1791.0f, 16.0f));
	  	if (result == EPathFollowingRequestResult::AlreadyAtGoal)
	  	{
			anim->animState = bState;
			target->bIsCreateKeyWG = true;
			me->bisStudy = true;
			//anim->Teacher_2_Anim(TEXT("Walk1"));
	  	}
	 
	  	//teacher 가 broom 범위 안에 들어오면
// 	  	if (dir.Length() < broomRange)
// 	  	{
// 	  		bState = ERidingTeacherState::Study;
// 	  	}
}

void URidingTeacherFSM::FollowState()
{
	
}

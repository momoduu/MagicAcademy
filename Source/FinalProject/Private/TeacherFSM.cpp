// Fill out your copyright notice in the Description page of Project Settings.


#include "TeacherFSM.h"
#include <Kismet/GameplayStatics.h>

#include "HJ_Teacher_2.h"
#include <Components/CapsuleComponent.h>
#include "Teacher_2Anim.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <AIModule/Classes/AIController.h>
#include <NavigationSystem.h>
#include "Jar.h"
#include "Timer.h"
#include "../FinalProjectCharacter.h"


// Sets default values for this component's properties
UTeacherFSM::UTeacherFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}


// Called when the game starts
void UTeacherFSM::BeginPlay()
{
	Super::BeginPlay();

	//월드에서 APlayer_KYI 타깃 찾아오기
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), AJar::StaticClass());

	//APlayer_KYI 타입으로 캐스팅
	jar = Cast<AJar>(actor);

	//소유 객체 가져오기
	me = Cast<AHJ_Teacher_2>(GetOwner());
	me->GetCharacterMovement()->MaxWalkSpeed = 200;

	//AIController 할당하기
	ai = Cast<AAIController>(me->GetController());

	originPos = me->GetActorLocation();

	//UTeacher_2Anim 할당하기
	anim = Cast <UTeacher_2Anim>(me->GetMesh()->GetAnimInstance());

}


// Called every frame
void UTeacherFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (mState)
	{
	case ETeacherState::Idle:
		IdleState();
		break;
	case ETeacherState::Explo:
		ExploState();
		break;
	case ETeacherState::Move:
		MoveState();
		break;
	case ETeacherState::Study:
		StudyState();
		break;
	case ETeacherState::RandomClass:
		RandomState();
		break;
	}
}

void UTeacherFSM::IdleState()
{
	// 	 	int32 index = FMath::RandRange(0, 1);
	// 	 	FString sectionName = FString::Printf(TEXT("Idle%d"), index);
	//     	anim->Teacher_2_Montage(FName(*sectionName));

			//2초 흐르면 Explo 상태로 가라
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > idleDelayTime)
	{
		mState = ETeacherState::Explo;

		//경과 시간 초기화
		currentTime = 0;
		anim->animState = mState;

		anim->Teacher_2_Montage(TEXT("Walk0"));
		//anim->Teacher_2_Montage(FName sectionName);
		int32 rand = FMath::RandRange(0, randPos.Num() - 1);
		randomPos = randPos[rand]->GetActorLocation();

	}

}

void UTeacherFSM::ExploState()
{

	//anim->Teacher_2_Montage(TEXT("Walk0"));

	EPathFollowingRequestResult::Type result = ai->MoveToLocation(randomPos);
	if (result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		//idle 상태로
		mState = ETeacherState::Idle;
		anim->Teacher_2_Montage(TEXT("Idle0"));
		anim->animState = mState;

	}


	////UNavigationSystemV1* ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	//auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	////랜덤 위치 얻어오기
	//FNavLocation loc;

	//ns->GetRandomReachablePointInRadius(originPos, 50, loc);
	//randomPos = loc.Location;


	//EPathFollowingRequestResult::Type result = ai->MoveToLocation(randomPos);

	//if (result == EPathFollowingRequestResult::AlreadyAtGoal)
	//{
	//	//idle 상태로
	//	ETeacherState::Idle;
	//}
	//else
	//{
	//	ETeacherState::Idle;
	//}

// 	GetRandomPositionInNavMesh(me->GetActorLocation(), 300, randomPos);
// 	FVector destination = jar->GetActorLocation();
// 
// 	// 	NavigationSystem 객체 얻어오기
// 	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());
// 
// 	//목적지 길 찾기 경로 데이터 검색
// 	FPathFindingQuery query;
// 	FAIMoveRequest req;
// 
// 	//목적지에서 인지할 수 있는 범위
// 	req.SetAcceptanceRadius(1);
// 	req.SetGoalLocation(destination);
// 
// 	//길 찾기 위한 쿼리 생성
// 	ai->BuildPathfindingQuery(req, query);
// 
// 	//길 찾기 결과 가져오기
// 	FPathFindingResult r = ns->FindPathSync(query);
// 
// 	if (r.Result == ENavigationQueryResult::Success)
// 	{
// 		//랜덤 위치로 이동
// 		auto result = ai->MoveToLocation(randomPos);
// 		//목적지에 도착하면
// 		if (result == EPathFollowingRequestResult::AlreadyAtGoal)
// 		{
// 			GetRandomPositionInNavMesh(me->GetActorLocation(), 300, randomPos);
// 		}
// 	}
// 
// 	else
// 	{
// 		//랜덤 위치로 이동
// 		auto result = ai->MoveToLocation(randomPos);
// 		//목적지에 도착하면
// 		if (result == EPathFollowingRequestResult::AlreadyAtGoal)
// 		{
// 			GetRandomPositionInNavMesh(me->GetActorLocation(), 300, randomPos);
// 		}
// 
// 	}
// 	if (mState == ETeacherState::Move)
// 	{
// 		ai->StopMovement();
// 	}
}

void UTeacherFSM::MoveState()
{


	anim->animState = mState;


	//1. 타겟을 향하는 방향을 구하고(target - me)
	FVector dir = jar->GetActorLocation() - me->GetActorLocation();
	bool bStudy = false;


	if (bMove == false)
	{

		//anim->Teacher_2_Montage(TEXT("Walk0"));

		//2.그 방향으로 이동하고 싶다.
		ai->MoveToLocation(FVector(-3310, 1658, 132));

		currentTime += GetWorld()->DeltaTimeSeconds;

		//teacher 가 Jar 범위 안에 들어오면
		if (dir.Length() < JarRange && currentTime > idleDelayTime)
		{

			currentTime = 0;
			bStudy = true;

		}
	}


	//만약에 bStudy가 true 라면 study 상태로 변경
	if (bStudy == true)
	{
		mState = ETeacherState::Study;
		anim->animState = mState;
		anim->Teacher_2_Montage(TEXT("Magic0"));

		// 		mState = ETeacherState::Study;
		// 		anim->animState = mState;

	}




}

void UTeacherFSM::StudyState()
{

	//anim->animState = mState;
	//anim->Teacher_2_Anim(TEXT("Magic1"));

	target = Cast<AFinalProjectCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AFinalProjectCharacter::StaticClass()));

	//target = Cast<AMainPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AMainPlayer::StaticClass()));

	//target->timer->SetVisibility(ESlateVisibility::Visible);
}

void UTeacherFSM::RandomState()
{

}

//수업 진행 현황 -> 랜덤으로 통과 불합격
void UTeacherFSM::Random()
{
	bool bRand = false;

	if (bRand == false)
	{
		//랜덤한 값을 뽑는다 o,x
		int32 rand = FMath::RandRange(1, 100);
		//test = UKismetMathLibrary::RandomIntegerInRangeFromStream(falseClass, passClass, rand);
		UE_LOG(LogTemp, Log, TEXT("rand = %d"), rand);

		//만약에 랜덤한 값이 50보다 작으면(50%)
		if (rand < 70)
		{
			passClass += 1;
			UE_LOG(LogTemp, Log, TEXT("pass!!!!!!!!!"));
		}
		else
		{
			passClass;
			UE_LOG(LogTemp, Log, TEXT("false!!!!!!!!!"));
		}
		bRand = true;
	}
}



//랜덤 위치 가져오기
bool UTeacherFSM::GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest)
{
	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FNavLocation loc;
	bool result = ns->GetRandomReachablePointInRadius(centerLocation, radius, loc);
	dest = loc.Location;
	return result;

}


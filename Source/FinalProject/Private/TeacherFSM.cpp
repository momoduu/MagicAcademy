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

	//���忡�� APlayer_KYI Ÿ�� ã�ƿ���
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), AJar::StaticClass());

	//APlayer_KYI Ÿ������ ĳ����
	jar = Cast<AJar>(actor);

	//���� ��ü ��������
	me = Cast<AHJ_Teacher_2>(GetOwner());
	me->GetCharacterMovement()->MaxWalkSpeed = 200;

	//AIController �Ҵ��ϱ�
	ai = Cast<AAIController>(me->GetController());

	originPos = me->GetActorLocation();

	//UTeacher_2Anim �Ҵ��ϱ�
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

			//2�� �帣�� Explo ���·� ����
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > idleDelayTime)
	{
		mState = ETeacherState::Explo;

		//��� �ð� �ʱ�ȭ
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
		//idle ���·�
		mState = ETeacherState::Idle;
		anim->Teacher_2_Montage(TEXT("Idle0"));
		anim->animState = mState;

	}


	////UNavigationSystemV1* ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	//auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	////���� ��ġ ������
	//FNavLocation loc;

	//ns->GetRandomReachablePointInRadius(originPos, 50, loc);
	//randomPos = loc.Location;


	//EPathFollowingRequestResult::Type result = ai->MoveToLocation(randomPos);

	//if (result == EPathFollowingRequestResult::AlreadyAtGoal)
	//{
	//	//idle ���·�
	//	ETeacherState::Idle;
	//}
	//else
	//{
	//	ETeacherState::Idle;
	//}

// 	GetRandomPositionInNavMesh(me->GetActorLocation(), 300, randomPos);
// 	FVector destination = jar->GetActorLocation();
// 
// 	// 	NavigationSystem ��ü ������
// 	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());
// 
// 	//������ �� ã�� ��� ������ �˻�
// 	FPathFindingQuery query;
// 	FAIMoveRequest req;
// 
// 	//���������� ������ �� �ִ� ����
// 	req.SetAcceptanceRadius(1);
// 	req.SetGoalLocation(destination);
// 
// 	//�� ã�� ���� ���� ����
// 	ai->BuildPathfindingQuery(req, query);
// 
// 	//�� ã�� ��� ��������
// 	FPathFindingResult r = ns->FindPathSync(query);
// 
// 	if (r.Result == ENavigationQueryResult::Success)
// 	{
// 		//���� ��ġ�� �̵�
// 		auto result = ai->MoveToLocation(randomPos);
// 		//�������� �����ϸ�
// 		if (result == EPathFollowingRequestResult::AlreadyAtGoal)
// 		{
// 			GetRandomPositionInNavMesh(me->GetActorLocation(), 300, randomPos);
// 		}
// 	}
// 
// 	else
// 	{
// 		//���� ��ġ�� �̵�
// 		auto result = ai->MoveToLocation(randomPos);
// 		//�������� �����ϸ�
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


	//1. Ÿ���� ���ϴ� ������ ���ϰ�(target - me)
	FVector dir = jar->GetActorLocation() - me->GetActorLocation();
	bool bStudy = false;


	if (bMove == false)
	{

		//anim->Teacher_2_Montage(TEXT("Walk0"));

		//2.�� �������� �̵��ϰ� �ʹ�.
		ai->MoveToLocation(FVector(-3310, 1658, 132));

		currentTime += GetWorld()->DeltaTimeSeconds;

		//teacher �� Jar ���� �ȿ� ������
		if (dir.Length() < JarRange && currentTime > idleDelayTime)
		{

			currentTime = 0;
			bStudy = true;

		}
	}


	//���࿡ bStudy�� true ��� study ���·� ����
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

//���� ���� ��Ȳ -> �������� ��� ���հ�
void UTeacherFSM::Random()
{
	bool bRand = false;

	if (bRand == false)
	{
		//������ ���� �̴´� o,x
		int32 rand = FMath::RandRange(1, 100);
		//test = UKismetMathLibrary::RandomIntegerInRangeFromStream(falseClass, passClass, rand);
		UE_LOG(LogTemp, Log, TEXT("rand = %d"), rand);

		//���࿡ ������ ���� 50���� ������(50%)
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



//���� ��ġ ��������
bool UTeacherFSM::GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest)
{
	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FNavLocation loc;
	bool result = ns->GetRandomReachablePointInRadius(centerLocation, radius, loc);
	dest = loc.Location;
	return result;

}


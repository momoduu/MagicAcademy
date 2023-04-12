// Fill out your copyright notice in the Description page of Project Settings.


#include "HJ_Teacher_2.h"
#include "TeacherFSM.h"
#include <GameFramework/Character.h>
#include "Components/PrimitiveComponent.h"
#include <Components/InputComponent.h>
#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>


// Sets default values
AHJ_Teacher_2::AHJ_Teacher_2()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//1.���̷�Ż�޽� ������ �ε�
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("SkeletalMesh'/Game/SHJ/Character/Teacher/Peasant_Girl.Peasant_Girl'"));
	//1-1.������ �ε� �����ϸ�
	if (tempMesh.Succeeded())
	{
		//1-2. ������ �Ҵ�
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		//1-3.�޽� ��ġ �� ȸ�� ����
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, 0));
	}

	//EnemyFSM ������Ʈ �߰�
	fsm = CreateDefaultSubobject<UTeacherFSM>(TEXT("FSM"));

	//�ִϸ��̼� �������Ʈ �Ҵ��ϱ�
	ConstructorHelpers::FClassFinder<UAnimInstance>tempClass(TEXT("AnimBlueprint'/Game/SHJ/Anim/Teacher_Anim.Teacher_Anim_C'"));
	if (tempClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(tempClass.Class);
	}
	//���忡 ��ġ�ǰų� ������ �� �ڵ�����
	//AIController ���� Possess �� �� �ֵ��� ����
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
}


// Called when the game starts or when spawned
void AHJ_Teacher_2::BeginPlay()
{
	Super::BeginPlay();

	//�����̴� �������� ���� �ڵ����� ȸ���϶�� �ɼ�
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called every frame
void AHJ_Teacher_2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHJ_Teacher_2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHJ_Teacher_2::SetActive(bool bActive)
{
	//���࿡ bActive �� true ��� /Ȱ��ȭ
// 	if (bActive)
// 	{
// 		//�浹Ȱ��
// 		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
// 		//���� ��ġ �缳��
// 		fsm->originPos = GetActorLocation();
// 
// 	}
// 	//��Ȱ��ȭ
// 	else
// 	{
// 		//�浹 �ȵǰ� ����
// 		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
// 	}
// 	//�޽� ��Ȱ��ȭ
// 	GetMesh()->SetActive(bActive);
// 	//�޽��� ���̰�  / �Ⱥ��̰�
// 	GetMesh()->SetVisibility(bActive);
// 	//ĳ���� �����Ʈ Ȱ�� /��Ȱ��
// 	GetCharacterMovement()->SetActive(bActive);
// 	//fsm Ȱ�� /��Ȱ��
// 	fsm->SetActive(bActive);
}


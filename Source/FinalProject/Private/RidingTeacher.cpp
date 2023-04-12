// Fill out your copyright notice in the Description page of Project Settings.


#include "RidingTeacher.h"
#include <Components/CapsuleComponent.h>
#include <Engine/SkeletalMesh.h>
#include "RidingTeacherFSM.h"
#include <GameFramework/CharacterMovementComponent.h>

// Sets default values
ARidingTeacher::ARidingTeacher()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh>tempMesh(TEXT("SkeletalMesh'/Game/Blueprints/teachar/Mesh/character.character'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, 0));
	}

	fsm = CreateDefaultSubobject<URidingTeacherFSM>(TEXT("FSM"));

	//애니메이션 블루프린트 할당하기
 	ConstructorHelpers::FClassFinder<UAnimInstance>tempClass(TEXT("AnimBlueprint'/Game/Blueprints/Animation/AnimBlueprint/ABP_RidingTeacher.ABP_RidingTeacher_C'"));
 	if (tempClass.Succeeded())
 	{
 		GetMesh()->SetAnimInstanceClass(tempClass.Class);
 	}
 
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ARidingTeacher::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called every frame
void ARidingTeacher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARidingTeacher::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


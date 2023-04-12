// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Character.h"
#include <Components/SkeletalMeshComponent.h>
#include <Components/SceneCaptureComponent2D.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "MyGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include "AnimPlayer.h"

AUI_Character::AUI_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMesh"));

	BodyMesh->SetRelativeLocation(FVector(0, 0, -90));
	BodyMesh->SetRelativeRotation(FRotator(0));
	BodyMesh->SetupAttachment(RootComponent);
	BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	hairMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairMesh"));
	hairMesh->SetupAttachment(BodyMesh, TEXT("HeadSocket"));
	hairMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//hairMesh->SetRelativeLocation(FVector(-4, 0, 156));
 
//  	Camera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Camera"));
//  	Camera->SetupAttachment(BodyMesh);

	compSpr = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	compSpr->SetupAttachment(BodyMesh);
	compSpr->TargetArmLength = 200.0f; 
	compSpr->SetRelativeLocation(FVector(0.0f, 60.0f, 100.0f));
	compSpr->SetRelativeRotation(FRotator(0.0f, 170.0f, 0.0f));

	compCam = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	compCam->SetupAttachment(compSpr);

 	ConstructorHelpers::FClassFinder<UAnimPlayer> tempAnim(TEXT("AnimBlueprint'/Game/Blueprints/Animation/AnimBlueprint/ABP_Player.ABP_Player_C'"));
 	if (tempAnim.Succeeded())
 	{
 		BodyMesh->SetAnimInstanceClass(tempAnim.Class);
 	}

}

void AUI_Character::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BodyMesh->SetSkeletalMesh(GameInstance->currSKMesh);
	hairMesh->SetSkeletalMesh(GameInstance->currHairMesh);

	
}

void AUI_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	prevPos = compSpr->GetRelativeLocation();
	
	if (bIsHair)
	{
		FVector newPos = FVector(-150.0f, 40.0f, 160.0f);

		FVector pos = FMath::Lerp(prevPos, newPos, DeltaTime*2);

		compSpr->SetRelativeLocation(pos);
	}
	else
	{
		FVector newPos = FVector(0.0f, 60.0f, 100.0f);

		FVector pos = FMath::Lerp(prevPos, newPos, DeltaTime * 2);

		compSpr->SetRelativeLocation(pos);
	}
}


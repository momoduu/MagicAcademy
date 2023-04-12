// Copyright Epic Games, Inc. All Rights Reserved.

#include "FinalProjectCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include <Engine/SkeletalMesh.h>
#include "InventoryWidget.h"
#include "PlayerMoveComponent.h"
#include "Inventory.h"
#include "Item.h"
#include <Kismet/GameplayStatics.h>
#include "MyGameInstance.h"
#include "MainWidget.h"
#include "BroomStick.h"
#include "EquipmentComponent.h"
#include <Components/SkeletalMeshComponent.h>
#include "KeyWG.h"
#include "TeacherBroom.h"
#include <Math/UnrealMathUtility.h>
#include <Components/ProgressBar.h>
#include "SucceedWG.h"
#include "SelectClassWidget.h"
#include <Components/Button.h>

AFinalProjectCharacter::AFinalProjectCharacter()
{
	//GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, 0, 0));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	compMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairMesh"));
	compMesh->SetupAttachment(GetMesh(), TEXT("HeadSocket"));
	compMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 

// 	GetCharacterMovement()->JumpZVelocity = 700.f;
// 	GetCharacterMovement()->AirControl = 0.35f;
// 	GetCharacterMovement()->MaxWalkSpeed = 500.f;
// 	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
// 	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; 
	CameraBoom->bUsePawnControlRotation = true; 
	CameraBoom->SetRelativeLocation(FVector(0.0f, 50.0f, 50.0f));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false;

// 	ConstructorHelpers::FClassFinder<UMainWidget>tempmainUI(TEXT("WidgetBlueprint'/Game/SHJ/UI/BP_MainWidget.BP_MainWidget_C'"));
// 	if (tempmainUI.Succeeded())
// 	{
// 		MainWGFactory = tempmainUI.Class;
// 	}
 
   	ConstructorHelpers::FClassFinder<UKeyWG>tempUI(TEXT("WidgetBlueprint'/Game/Blueprints/WG/Progress/WG/TabKey_WG.TabKey_WG_C'"));
  	if (tempUI.Succeeded())
  	{
 		keyWGFactory = tempUI.Class;
	}  
	
	ConstructorHelpers::FClassFinder<USucceedWG>tempSucceedUI(TEXT("WidgetBlueprint'/Game/Blueprints/WG/BP_succeed.BP_succeed_C'"));
	if (tempSucceedUI.Succeeded())
	{
		SucceedWGFactory = tempSucceedUI.Class;
	}

	PlayerMoveComp = CreateDefaultSubobject<UPlayerMoveComponent>(TEXT("MoveComp"));
	EquipmentComp = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComp"));

	Credit = 0;
}

void AFinalProjectCharacter::BeginPlay()
{
	Super::BeginPlay();
	//item = Cast<AItem>(UGameplayStatics::GetActorOfClass(GetWorld(), AItem::StaticClass()));
	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->SetCredit(Credit);
	GetMesh()->SetSkeletalMesh(GameInstance->currSKMesh);
	GetMesh()->SetAnimInstanceClass(GameInstance->AnimPlayerClass);
	compMesh->SetSkeletalMesh(GameInstance->currHairMesh);
	//compMesh->SetStaticMesh(GameInstance->currSTMesh);

	MainWG = CreateWidget<UMainWidget>(GetWorld(), MainWGFactory);
	MainWG->AddToViewport();
//	inventory = MainWG->inventoryContainer;
}

void AFinalProjectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (keyWG != nullptr)
	{
		if (bIsPlayProgressBar)
		{
			float newValue = FMath::Lerp(progressValue, goalValue, DeltaTime/2);
			progressValue = newValue;
			keyWG->ProgressBar->SetPercent(newValue);
			if (progressValue <= goalValue)
			{
				keyWG->FailedAction();
				//bIsPlayProgressBar = false;
			}
		}
	}
	//UE_LOG(LogTemp, Warning, TEXT("progressbarValue %f"), progressValue)
}

void AFinalProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerMoveComp->SetupInputBinding(PlayerInputComponent);
	//PlayerInputComponent->BindAction(TEXT("InventoryOpen"), IE_Pressed, this, &AFinalProjectCharacter::OpenInventory);
	PlayerInputComponent->BindAction(TEXT("PickUp"), IE_Pressed, this, &AFinalProjectCharacter::PickUpItem);
	PlayerInputComponent->BindAction(TEXT("BroomUpkey"), IE_Pressed, this, &AFinalProjectCharacter::PressedKey);
}

void AFinalProjectCharacter::PickUpItem()
{
	FVector startPos = GetActorLocation();
	FVector endPos = startPos /** GetActorForwardVector() * PickUpDistance*/;
	FHitResult hitInfo;
	FCollisionQueryParams param;
	param.AddIgnoredActor(this);

	bool bHit = GetWorld()->SweepSingleByObjectType(hitInfo, startPos, endPos, FQuat::Identity,
		ECC_GameTraceChannel5, FCollisionShape::MakeSphere(sphereDistance), param);

	if (bHit)
	{
		AActor* actor = hitInfo.GetActor();
		broom = Cast<ABroomStick>(actor);
		UE_LOG(LogTemp, Warning, TEXT("actor = %s"), *actor->GetName())
		if (broom)
		{
			GetWorld()->GetTimerManager().SetTimer(WGTimerHandle, this, &AFinalProjectCharacter::openMap, WGtime);

		}
	}	
// 	if (bHit)
// 	{
// 		AActor* actor = hitInfo.GetActor();
// 		item = Cast<AItem>(actor);
// 		if (item)
// 		{
// 			FString Name = item->ItemInfo.itemName;
// 			FName itemName = FName(*Name);
// 			inventory->LoadData(itemName);
// 			item->Destroy();
// 		}
// 	}

	//DrawDebugSphere(GetWorld(), endPos, sphereDistance, 30, FColor::Purple, false, 1, 0, 10);
}

// void AFinalProjectCharacter::OpenInventory()
// {
// 	InventoryWG = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWGFactory);
// 	InventoryWG->AddToViewport();
// }

void AFinalProjectCharacter::AttachToMesh(USkeletalMeshComponent* meshComp)
{
// 	ABroomStick* broomPawn = Cast<ABroomStick>(UGameplayStatics::GetActorOfClass(GetWorld(), ABroomStick::StaticClass()));
// 	broomPawn = GetWorld()->SpawnActor<ABroomStick>(BroomClass);
	FName SocketName(TEXT("RightHandSocket"));
	USkeletalMeshComponent* CharacterMesh = GetMesh();
 	FVector BroomLocation = CharacterMesh->GetSocketLocation(SocketName);
	if (CharacterMesh !=nullptr)
	{
// 		broomPawn->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
// 		UE_LOG(LogTemp, Warning, TEXT("loc = %f,%f,%f"), broomPawn->GetActorLocation().X,
// 		broomPawn->GetActorLocation().Y, broomPawn->GetActorLocation().Z)
		//meshComp->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Character mesh component is null"));
	}
}

void AFinalProjectCharacter::CreateWG()
{
	if (bIsCreateKeyWG)
	{
		keyWG = CreateWidget<UKeyWG>(GetWorld(), keyWGFactory);
		keyWG->AddToViewport();
		bIsActiveKey = true;
	}
}

void AFinalProjectCharacter::succeedWG()
{
	SucceedWG = CreateWidget<USucceedWG>(GetWorld(), SucceedWGFactory);
	SucceedWG->AddToViewport();

	if (bisRemove)
	{
		SucceedWG->RemoveFromParent();
	}
}

void AFinalProjectCharacter::PressedKey()
{
	if (bIsActiveKey)
	{
		UE_LOG(LogTemp, Warning, TEXT("ketpush"))
		keyWG->SetImageValue();
	}
}

void AFinalProjectCharacter::openMap()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMap"));
	EquipmentComp->AddItem(broom->broomInfo);
	//MainWG->SelectWG->Btn_PotionClass->SetVisibility(ESlateVisibility::Visible);
	//MainWG->SelectWG->bIsVisible = true;
}

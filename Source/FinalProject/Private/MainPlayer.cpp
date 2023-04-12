// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"
#include "MyGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include "ScheduleWidget.h"
#include "PlayerMoveComponent.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/CapsuleComponent.h>
#include "SelectClassWidget.h"
#include "CourseSlotWidget.h"
#include "ScheduleContainer.h"
#include "InventoryWidget.h"
#include "Item.h"
#include "Inventory.h"
#include <Engine/SkeletalMesh.h>
#include <Components/StaticMeshComponent.h>
#include "RingActor.h"


// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	GetMesh()->SetRelativeLocation(FVector(0,0,-90));
	GetMesh()->SetRelativeRotation(FRotator(0, 0, 0));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HairMesh"));
	compMesh->SetupAttachment(RootComponent);
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));
	compMesh->SetRelativeLocation(FVector(-4, 0, 60));

	ConstructorHelpers::FObjectFinder<USkeletalMesh>tempSkMesh(TEXT("SkeletalMesh'/Game/Blueprints/CHar_Mesh/Female.Female'"));
	if (tempSkMesh.Succeeded())
	{
		compSkeletal = tempSkMesh.Object;
	}

	ConstructorHelpers::FClassFinder<USelectClassWidget>tempSelectUI(TEXT("WidgetBlueprint'/Game/Blueprints/BP_SelectClass.BP_SelectClass_C'"));
	if (tempSelectUI.Succeeded())
	{
		SelectWGFactory = tempSelectUI.Class;
	}	
	
	ConstructorHelpers::FClassFinder<UScheduleWidget>tempScheduleUI(TEXT("WidgetBlueprint'/Game/Blueprints/BP_ScheduleWidget.BP_ScheduleWidget_C'"));
	if (tempScheduleUI.Succeeded())
	{
		ScheduleWGFactory = tempScheduleUI.Class;
	}	
	
	ConstructorHelpers::FClassFinder<UInventoryWidget>tempInventoryUI(TEXT("WidgetBlueprint'/Game/Blueprints/BP_InventoryWidget.BP_InventoryWidget_C'"));
	if (tempInventoryUI.Succeeded())
	{
		InventoryWGFactory = tempInventoryUI.Class;
	}
	
	GetMesh()->SetSkeletalMesh(compSkeletal);

	PlayerMoveComp = CreateDefaultSubobject<UPlayerMoveComponent>(TEXT("MoveComp"));

	compSpr = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	compSpr->SetupAttachment(RootComponent);
	compSpr->TargetArmLength = 250;
	compSpr->SetRelativeLocation(FVector(0.0f, 50.0f, 50.0f));

	compCam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	compCam->SetupAttachment(compSpr);

	Credit = 0; 
	Pass = 0;

	inventory = NewObject<UInventory>();
}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

	//item = Cast<AItem>(UGameplayStatics::GetActorOfClass(GetWorld(), AItem::StaticClass()));
	//GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//GameInstance->SetCredit(Credit);
	//GetMesh()->SetSkeletalMesh(GameInstance->currSKMesh);
	//compMesh->SetStaticMesh(GameInstance->currSTMesh);

	//ScheduleWG->SetVisibility(ESlateVisibility::Visible);
	SelectWG = CreateWidget<USelectClassWidget>(GetWorld(), SelectWGFactory);
	SelectWG->AddToViewport();
	SelectWG->SetVisibility(ESlateVisibility::Hidden);
	
	ring = Cast<ARingActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ARingActor::StaticClass()));

  	if(ring)
  	{
  		ring->RingPassDelegate.BindUObject(this, &AMainPlayer::PassCount);
  	}
}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerMoveComp->SetupInputBinding(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("SelectWGOpen"), IE_Pressed, this, &AMainPlayer::OpenSelect);
	PlayerInputComponent->BindAction(TEXT("SchedulerOpen"), IE_Pressed, this, &AMainPlayer::OpenScheduler);
	PlayerInputComponent->BindAction(TEXT("InventoryOpen"), IE_Pressed, this, &AMainPlayer::OpenInventory);
	PlayerInputComponent->BindAction(TEXT("PickUp"), IE_Pressed, this, &AMainPlayer::PickUpItem);
}

void AMainPlayer::PickUpItem()
{	
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("PickUp"));

	FVector startPos = GetActorLocation();
	FVector endPos = startPos /** GetActorForwardVector() * PickUpDistance*/;
	FHitResult hitInfo;
	FCollisionQueryParams param;
	param.AddIgnoredActor(this);
	
	bool bHit = GetWorld()->SweepSingleByObjectType(hitInfo, startPos, endPos, FQuat::Identity,
	ECC_GameTraceChannel4, FCollisionShape::MakeSphere(sphereDistance), param);

	if (bHit)
	{	
		AActor* actor = hitInfo.GetActor();
		item = Cast<AItem>(actor);
		if (item)
		{
			FString Name = item->ItemInfo.itemName;
			FName itemName = FName(*Name);
			inventory->LoadData(itemName);
			item->Destroy();
		}
	}

	DrawDebugSphere(GetWorld(), endPos, sphereDistance, 30, FColor::Purple, false, 1, 0, 10);
}

void AMainPlayer::OpenSelect()
{
	bIsSelectWGOpen = !bIsSelectWGOpen;
	if (bIsSelectWGOpen)
	{
		FInputModeUIOnly inputUIOnly;
		GetWorld()->GetFirstPlayerController()->SetInputMode(inputUIOnly);
		SelectWG->SetVisibility(ESlateVisibility::Visible);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	}
	else
	{
		FInputModeGameAndUI InputGameAndUI;
		GetWorld()->GetFirstPlayerController()->SetInputMode(InputGameAndUI);
		SelectWG->SetVisibility(ESlateVisibility::Hidden);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	}
}

void AMainPlayer::OpenScheduler()
{
	bIsScheduleWGOpen = !bIsScheduleWGOpen;
	if (bIsScheduleWGOpen)
	{
		//SelectWG->ScheduleCT->LoadCourse();
		ScheduleWG->AddToViewport();
		ScheduleWG->SetVisibility(ESlateVisibility::Visible);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	}
	else
	{
		ScheduleWG->SetVisibility(ESlateVisibility::Hidden);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	}
}

void AMainPlayer::OpenInventory()
{
	InventoryWG = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWGFactory);
	InventoryWG->AddToViewport();
}

void AMainPlayer::PassCount()
{
	Pass++;
	UE_LOG(LogTemp, Warning, TEXT("pass = %d"), Pass);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "BroomStick.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Components/SceneComponent.h>
#include "PlayerMoveComponent.h"
#include "../FinalProjectCharacter.h"
#include <Components/SkeletalMeshComponent.h>
#include "MyGameInstance.h"
#include <Components/CapsuleComponent.h>
#include <Engine/Texture2D.h>

// Sets default values
ABroomStick::ABroomStick()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	compBox->SetupAttachment(RootComponent);
	compBox->SetRelativeLocation(FVector(0));
	compBox->SetRelativeRotation(FRotator(0));
	compBox->SetBoxExtent(FVector(100,50,100));

	compMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	compMesh->SetupAttachment(compBox);
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));
	compMesh->SetRelativeLocation(FVector(0,0,-30));

	compSpr = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	compSpr->SetupAttachment(RootComponent);
	compSpr->TargetArmLength = 300;
	compSpr->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));
	compSpr->bUsePawnControlRotation = true;

	compCam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	compCam->SetupAttachment(compSpr);
	compCam->bUsePawnControlRotation = false;

	hairMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairMesh"));
	hairMesh->SetupAttachment(compBox);
	hairMesh->SetVisibility(false);
	hairMesh->SetCollisionProfileName(TEXT("NoCollision"));
	hairMesh->SetRelativeLocation(FVector(-4, 0, 60));

	Attach = CreateDefaultSubobject<USceneComponent>(TEXT("Attach"));
	Attach->SetupAttachment(compBox);
	
	Rider = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Rider"));
	Rider->SetupAttachment(Attach);
	Rider->SetVisibility(false);
	Rider->SetRelativeLocation(FVector(0, 0, -90));
	Rider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Detach = CreateDefaultSubobject<USceneComponent>(TEXT("Detach"));
	Detach->SetupAttachment(compBox);
	Detach->SetRelativeLocation(FVector(0, -70, 0));

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	broomInfo.itemName = FString("BroomStick");
	ConstructorHelpers::FObjectFinder<UTexture2D> TextureObj(TEXT("Texture2D'/Game/Blueprints/Image/iconbroom.iconbroom'"));
	if (TextureObj.Succeeded())
	{
		broomInfo.Thumbnail = TextureObj.Object;
	}
	broomInfo.SkeletalComp = compMesh;
}

// Called when the game starts or when spawned
void ABroomStick::BeginPlay()
{
	Super::BeginPlay();

	bUseControllerRotationYaw = true;
	
	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	Rider->SetSkeletalMesh(GameInstance->currSKMesh);
	hairMesh->SetSkeletalMesh(GameInstance->currHairMesh);
	Rider->SetAnimInstanceClass(GameInstance->AnimBroomClass);

	gravityScale = GetWorld()->GetGravityZ() * -1;
}

// Called every frame
void ABroomStick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
 	delta += DeltaTime;
 	//UE_LOG(LogTemp, Error, TEXT("delta = %f"), delta)

 	Move(DeltaTime);
// 	Flying(DeltaTime);

	FVector TargetLocation = FMath::Lerp(compSpr->GetComponentLocation(), compBox->GetComponentLocation(), DeltaTime);
	FRotator TargetRotation = FMath::Lerp(compSpr->GetComponentRotation(), compBox->GetComponentRotation(), DeltaTime);

	compSpr->SetWorldLocation(TargetLocation);
	compSpr->SetWorldRotation(TargetRotation);

}

// Called to bind functionality to input
void ABroomStick::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Move Right / Left"), this, &ABroomStick::InputHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Move Forward / Backward"), this, &ABroomStick::InputVertical);
	PlayerInputComponent->BindAxis(TEXT("Move Up/Down"), this, &ABroomStick::InputUpDown);
	PlayerInputComponent->BindAxis(TEXT("Look Up / Down Mouse"), this, &ABroomStick::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn Right / Left Mouse"), this, &ABroomStick::Turn);
	PlayerInputComponent->BindAxis(TEXT("Booster"), this, &ABroomStick::Booster);
	PlayerInputComponent->BindAction(TEXT("Ride"), IE_Pressed, this, &ABroomStick::GetOffBroom);
}

// void ABroomStick::NotifyActorBeginOverlap(AActor* OtherActor)
// {
// 	if (OtherActor->GetName().Contains(TEXT("Floor")))
// 	{
// 		gravityScale = GetWorld()->GetGravityZ();
// 	}
// 	else
// 	{
// 		gravityScale = GetWorld()->GetGravityZ() * -1;
// 	}
// }

void ABroomStick::InputHorizontal(float value)
{
	h = value;
 	float speedFactor = RLspeedFactor * h;
 	RLSpeed = FMath::FInterpTo(RLSpeed, speedFactor, delta * 2, interpSpeed);
}

void ABroomStick::InputVertical(float value)
{
	v = value;
	float speedFactor = FBspeedFactor * v;
	FBSpeed = FMath::FInterpTo(FBSpeed, speedFactor, delta * 2, interpSpeed);
}

void ABroomStick::Move(float deltatime)
{
	// 	FVector p = GetActorLocation();
	// 	FVector dir = FVector::ForwardVector * v + FVector::RightVector * h;
	// 	FVector vt = dir.GetSafeNormal() * deltatime * gravityScale;
	// 
	// 	SetActorLocation(p + vt);

//  	FVector p = GetActorLocation();
//  	FVector dir = GetActorForwardVector() * v + GetActorRightVector() * h;
//  
//  	FVector vt = dir.GetSafeNormal() * speed;
//  	vt += dir * deltatime * gravityScale;
//  
// 	SetActorLocation(p + vt); 	
	
// 	FVector p = GetActorLocation();
// 	FVector dir = GetActorForwardVector() * FBSpeed + GetActorRightVector() * RLSpeed + GetActorUpVector() * UDSpeed;
// 	FVector vt = dir * deltatime;
// 
// 	FVector deltaLocation = vt;
// 
// 	AddActorWorldOffset(deltaLocation);


	FVector p = GetActorLocation();
	FVector dir = GetActorForwardVector() * FBSpeed + GetActorRightVector() * RLSpeed + GetActorUpVector() * UDSpeed;

	float factor = 0.5f; 
	FBSpeed *= factor;
	UDSpeed *= factor;

	FVector vt = dir * deltatime;

	FVector deltaLocation = vt;

	AddActorWorldOffset(deltaLocation);
}

void ABroomStick::LookUp(float Rate)
{
	//AddControllerPitchInput(Rate);
}

void ABroomStick::Turn(float Rate)
{
	AddControllerYawInput(Rate);
}

void ABroomStick::InputUpDown(float value)
{
	f = value;
	//AddControllerPitchInput(f);
	float speedFactor = UDspeedFactor * f;
	UDSpeed = FMath::FInterpTo(UDSpeed, speedFactor, delta*2, interpSpeed);
}

void ABroomStick::Flying(float deltatime)
{
	FVector p = GetActorLocation();
	FVector dir = FVector::UpVector * f;
	FVector vt = dir.GetSafeNormal() * speed;
	vt += dir *  deltatime * gravityScale;

	SetActorLocation(p + vt);
}

void ABroomStick::Booster(float value)
{
	if (value > 0)
	{
		FBspeedFactor = MaxSpeed;
		RLspeedFactor = MaxSpeed;
		UDspeedFactor = MaxSpeed;
	}
	
	if(value == 0)
	{
		FBspeedFactor = DefaultSpeed;
		RLspeedFactor = DefaultSpeed;
		UDspeedFactor = DefaultSpeed;
	}
}

void ABroomStick::GetOffBroom()
{
	AFinalProjectCharacter* player = Cast<AFinalProjectCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), 
	AFinalProjectCharacter::StaticClass()));
	if (player != nullptr)
	{
		FVector startPos = GetActorLocation();
		FVector endPos = startPos;
		FHitResult hitInfo;
		FCollisionQueryParams param;
		param.AddIgnoredActor(this);
		
 		bool bHit = GetWorld()->SweepSingleByChannel(hitInfo, startPos, endPos, FQuat::Identity, ECC_Visibility,
 			FCollisionShape::MakeSphere(sphereDistance), param);

// 		bool bHit = GetWorld()->SweepSingleByObjectType(hitInfo, startPos, endPos, FQuat::Identity,
// 			ECC_GameTraceChannel5, FCollisionShape::MakeSphere(sphereDistance), param);

		if (bHit)
		{
			Rider->SetVisibility(false);
			hairMesh->SetVisibility(false);
			player->GetCapsuleComponent()->SetVisibility(true);
			player->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			player->GetMesh()->SetVisibility(true);
			player->compMesh->SetVisibility(true);
			GetWorld()->GetFirstPlayerController()->Possess(player);
			player->SetActorLocation(GetActorLocation());
		}
		//DrawDebugSphere(GetWorld(), endPos, sphereDistance, 30, FColor::Blue, false, 1, 0, 10);
	}
 }

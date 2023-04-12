// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMoveComponent.h"
#include <Components/InputComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/PlayerController.h>
#include <Kismet/GameplayStatics.h>
#include "BroomStick.h"
#include "../FinalProjectCharacter.h"
#include <Components/CapsuleComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Components/StaticMeshComponent.h>


void UPlayerMoveComponent::BeginPlay()
{
	Super::BeginPlay();
	
	me->GetCharacterMovement()->MaxWalkSpeed = speed;
	me->JumpMaxCount = 2;
	me->GetCharacterMovement()->JumpZVelocity = 600;


}

void UPlayerMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Velocity = (FVector::UpVector * GetWorld()->GetGravityZ()) * gravityScale * DeltaTime;

	//FlyMove(DeltaTime);
	Move(DeltaTime);
}

void UPlayerMoveComponent::SetupInputBinding(class UInputComponent* PlayerInputComponent)
{
	Super::SetupInputBinding(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move Right / Left"), this, &UPlayerMoveComponent::InputHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Move Forward / Backward"), this, &UPlayerMoveComponent::InputVertical);
	PlayerInputComponent->BindAxis(TEXT("Look Up / Down Mouse"), this, &UPlayerMoveComponent::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn Right / Left Mouse"), this, &UPlayerMoveComponent::Turn);
	//PlayerInputComponent->BindAxis(TEXT("Move Up/Down"), this, &UPlayerMoveComponent::InputUpDown);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &UPlayerMoveComponent::Jump);
	//PlayerInputComponent->BindAction(TEXT("Fly"), IE_Pressed, this, &UPlayerMoveComponent::InputFly);
	PlayerInputComponent->BindAction(TEXT("Ride"), IE_Pressed, this, &UPlayerMoveComponent::RidingBroom);
}

void UPlayerMoveComponent::Move(float deltatime)
{
 	FVector p = me->GetActorLocation();
 	FVector dir = me->GetActorForwardVector() * v + me->GetActorRightVector() * h;
 	FVector vt = dir.GetSafeNormal() * speed * deltatime;
 
 	//me->SetActorLocation(p + vt);

	me->AddMovementInput(dir.GetSafeNormal());
}

void UPlayerMoveComponent::InputHorizontal(float value)
{
	h = value;

	if (h > 0)
	{
		me->GetMesh()->SetRelativeRotation(FRotator(0, 90, 0));
	}
	else if(h < 0)
	{
		me->GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	}

//		me->SetActorRotation(FRotator(0, value, 0));
//		me->AddActorWorldRotation(FRotator(0, value, 0));
//   	FVector right = me->GetActorRightVector();
//   	me->AddMovementInput(right, value);
}

void UPlayerMoveComponent::InputVertical(float value)
{
	v = value;

	if (v > 0)
	{
		me->GetMesh()->SetRelativeRotation(FRotator(0, 0, 0));
	}
	else if (v < 0)
	{
		me->GetMesh()->SetRelativeRotation(FRotator(0, 180, 0));
	}

// 	float gravityScale = -1.0f;
// 	me->GetCharacterMovement()->GravityScale = gravityScale;
// 
//  	FVector forward = me->GetActorForwardVector();
//  	me->AddMovementInput(forward, value);
}

void UPlayerMoveComponent::LookUp(float AxisValue)
{
	if (me != nullptr)
	{
		me->AddControllerPitchInput(AxisValue);
	}
}

void UPlayerMoveComponent::Turn(float AxisValue)
{
	me->AddControllerYawInput(AxisValue);
}
	
void UPlayerMoveComponent::Jump()
{
	me->Jump();
}

void UPlayerMoveComponent::InputFly()
{
	bIsFlying = !bIsFlying;
	//me->AddMovementInput(me->compCam->GetForwardVector());
	if (bIsFlying)
	{
		me->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Fly"));
		me->GetCharacterMovement()->bOrientRotationToMovement = false;
		me->GetCharacterMovement()->bUseControllerDesiredRotation = true;
		me->GetCharacterMovement()->MaxFlySpeed = 5000;
		speed = 1000;
// 		me->compSpr->bEnableCameraLag = true;
// 		me->compSpr->bEnableCameraRotationLag = true;
// 		me->compSpr->CameraLagSpeed = 8.0f;
// 		me->compSpr->CameraRotationLagSpeed = 6.0f;
	}
	else
	{
		me->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Walking"));
		me->GetCharacterMovement()->bOrientRotationToMovement = true;
		me->GetCharacterMovement()->bUseControllerDesiredRotation = false;
		me->CameraBoom->bEnableCameraLag = false;
		me->CameraBoom->bEnableCameraRotationLag = false;
		speed = 500;
	}
	
	//me->GetCharacterMovement()->GravityScale = 0.0f;
}

void UPlayerMoveComponent::InputUpDown(float value)
{
	me->AddMovementInput(FVector::UpVector, value);
	//me->GetMesh()->SetupAttachment(broom->compMesh, TEXT("SitPos"));

}

void UPlayerMoveComponent::RidingBroom()
{
	broom = Cast<ABroomStick>(UGameplayStatics::GetActorOfClass(GetWorld(), ABroomStick::StaticClass()));

	if (broom != nullptr)
	{
		FVector startPos = me->GetActorLocation();
		FVector endPos = startPos;
		FHitResult hitInfo;
		FCollisionQueryParams param;
		param.AddIgnoredActor(me);

		bool bHit = GetWorld()->SweepSingleByObjectType(hitInfo, startPos, endPos, FQuat::Identity,
			ECC_GameTraceChannel5, FCollisionShape::MakeSphere(sphereDistance), param);

		if (bHit)
		{
			AActor* actor = hitInfo.GetActor();
			broom = Cast<ABroomStick>(actor);
			if (broom)
			{
				broom->Rider->SetVisibility(true);
				broom->hairMesh->SetVisibility(true);
				me->GetCapsuleComponent()->SetVisibility(false);
				me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				me->GetMesh()->SetVisibility(false);
				me->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				me->compMesh->SetVisibility(false);
				me->compMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				GetWorld()->GetFirstPlayerController()->Possess(broom);
			}
		}

		//DrawDebugSphere(GetWorld(), endPos, sphereDistance, 30, FColor::Purple, false, 1, 0, 10);
// 		FName SocketName(TEXT("SitPos"));
// 		FVector BroomLocation = broom->compMesh->GetSocketLocation(SocketName);
// 		me->AttachToComponent(broom->compMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
// 
// 		GetWorld()->GetFirstPlayerController()->Possess(broom);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ItemStruct.h"
#include "BroomStick.generated.h"

UCLASS()
class FINALPROJECT_API ABroomStick : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABroomStick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

/*	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;*/
public:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* compBox;

// 	UPROPERTY(EditAnywhere)
// 	class UStaticMeshComponent* compMesh;

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* compMesh;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* compSpr;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* compCam;

	UPROPERTY(EditAnywhere)
	class USceneComponent* Attach;

	UPROPERTY(EditAnywhere)
	class USceneComponent* Detach;

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* Rider;

	UPROPERTY(EditAnywhere)
	class UMyGameInstance* GameInstance;

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* hairMesh;

public:
	void InputHorizontal(float value);
	void InputVertical(float value);
	void Move(float deltatime);
	void LookUp(float Rate);
	void Turn(float Rate);
	void InputUpDown(float value);
	void Flying(float deltatime);
	void Booster(float value);
	void GetOffBroom();

public:
	float h = 0;
	float v = 0;
	float f = 0;
	float gravityScale;

	UPROPERTY(EditAnywhere)
	float speed = 1;
	float moveSpeed = 1000;
	UPROPERTY(EditAnywhere)
	float acceleration = 3;
	float maxSpeed = 5;
	float CameraInterpSpeed = 10;

	float FBspeedFactor = 1000;
	float RLspeedFactor = 1000;
	float UDspeedFactor = 1000;
	float FBSpeed;
	float RLSpeed;
	float UDSpeed;
	float interpSpeed = 1000;
	float delta = 0;
	float MaxSpeed = 5000;
	float DefaultSpeed = 1000;

	UPROPERTY(EditAnywhere)
	float sphereDistance = 200;

public:
	FItemIf broomInfo;
};

// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FinalProjectCharacter.generated.h"

UCLASS(config=Game)
class AFinalProjectCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* FollowCamera;
public:
	AFinalProjectCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere)
		class UMyGameInstance* GameInstance;

	UPROPERTY(EditAnywhere)
		class UPlayerMoveComponent* PlayerMoveComp;

	UPROPERTY(EditAnywhere)
		class UEquipmentComponent* EquipmentComp;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMainWidget> MainWGFactory;

	UPROPERTY(EditAnywhere)
		class UMainWidget* MainWG;	
		
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UKeyWG> keyWGFactory;

	UPROPERTY(EditAnywhere)
		class UKeyWG* keyWG;
		
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USucceedWG> SucceedWGFactory;

	UPROPERTY(EditAnywhere)
		class USucceedWG* SucceedWG;

	UPROPERTY(EditAnywhere)
		class AItem* item;;

	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* compMesh;

	UPROPERTY(EditAnywhere)
	class ABroomStick* broom;
// 	
// 	UPROPERTY(EditAnywhere)
// 		class ABroomStick* broomPawn;

public:
	UPROPERTY(EditAnywhere)
	float PickUpDistance = 50;
	float sphereDistance = 300;
	float currTime = 0;
	float progressValue; 
	float goalValue = 0.0f;
	int32 Credit;

	bool bIsActiveKey = false;
	bool bIsCreateKeyWG = false;
	bool bIsPlayProgressBar = false;
	bool bisRemove = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPassed = false;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsFailed = false;

	FTimerHandle WGTimerHandle;

	float WGtime = 2.0f;

public:
	void PickUpItem();
	//void OpenInventory();
	void AttachToMesh(USkeletalMeshComponent* meshComp);
	void CreateWG();
	void succeedWG();
	void PressedKey();
	void openMap();



	//hj
public:
	UPROPERTY(EditAnywhere)
		class UTimer* timer;
};


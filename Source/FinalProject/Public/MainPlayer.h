// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"

UCLASS()
class FINALPROJECT_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	class UMyGameInstance* GameInstance;

	UPROPERTY(EditAnywhere)
	class UPlayerMoveComponent* PlayerMoveComp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class USelectClassWidget> SelectWGFactory;	
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UScheduleWidget> ScheduleWGFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInventoryWidget> InventoryWGFactory;

	UPROPERTY(EditAnywhere)
	class USelectClassWidget* SelectWG;	
	
	UPROPERTY(EditAnywhere)
	class UScheduleWidget* ScheduleWG;	
	
	UPROPERTY(EditAnywhere)
	class UInventoryWidget* InventoryWG;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* compSpr;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* compCam;

	UPROPERTY(EditAnywhere)
	class AItem* item;

	UPROPERTY(EditAnywhere)
	class USkeletalMesh* compSkeletal;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compMesh;

	UPROPERTY(EditAnywhere)
	class ARingActor* ring; 

public:
	UPROPERTY(EditAnywhere)
	float PickUpDistance = 50;
	float sphereDistance = 100;

	int32 Credit;
	int32 Pass;

	bool bIsSelectWGOpen = false;
	bool bIsScheduleWGOpen = false;
public:
	void PickUpItem();
	void OpenSelect();
	void OpenScheduler();
	void OpenInventory();
	void PassCount();

private:
	class UInventory* inventory;

	//hj
public:
 	UPROPERTY(EditAnywhere)
 	class UTimer* timer;

};

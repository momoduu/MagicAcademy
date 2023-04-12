// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UI_Character.generated.h"

UCLASS()
class FINALPROJECT_API AUI_Character : public APawn
{
	GENERATED_BODY()
	
public:	
	AUI_Character();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:

// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 		class USceneCaptureComponent2D* Camera;

	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* BodyMesh;

 	UPROPERTY(EditAnywhere)
 		class USkeletalMeshComponent* hairMesh;
 
  	UPROPERTY(EditAnywhere)
  		class USpringArmComponent* compSpr;
  
  	UPROPERTY(EditAnywhere)
  		class UCameraComponent* compCam;

	UPROPERTY(EditAnywhere)
		class UMyGameInstance* GameInstance;
	
	FVector prevPos;
	bool bIsHair = false;
};

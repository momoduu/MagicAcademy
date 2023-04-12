// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RidingTeacher.generated.h"

UCLASS()
class FINALPROJECT_API ARidingTeacher : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARidingTeacher();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FSMComponent)
		class URidingTeacherFSM* fsm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bisStudy = false;
};

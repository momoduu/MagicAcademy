// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseComponent.h"
#include "PlayerMoveComponent.generated.h"

//DECLARE_EVENT(UPlayerMoveComponent, FMoveEvent, float);
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FINALPROJECT_API UPlayerMoveComponent : public UPlayerBaseComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(EditAnywhere)
	class ABroomStick* broom;

public:
	float h = 0;
	float v = 0;
	float f = 0;

	UPROPERTY(EditAnywhere)
	float speed = 700;

	float sphereDistance = 100;

	bool bIsFlying = false;

public:
	void Move(float deltatime);
	void InputHorizontal(float value);
	void InputVertical(float value);
	void LookUp(float AxisValue);
	void Turn(float AxisValue);
	void Jump();
	void InputFly();
	void InputUpDown(float value);
	void Flying(float DeltaTime);
	void RidingBroom();

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RidingClassWG.generated.h"

UCLASS()
class FINALPROJECT_API URidingClassWG : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere)
	class UButton* StartBtn;

	UPROPERTY(EditAnywhere)
	class ARidingTeacher* teacher;

	UFUNCTION()
	void OnPlay();
	
};

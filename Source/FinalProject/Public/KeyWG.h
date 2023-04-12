// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeyWG.generated.h"


UCLASS()
class FINALPROJECT_API UKeyWG : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UImage* ProgressBorder;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* Passed;	
	
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* Failed;

	UPROPERTY(EditAnywhere)
	class AFinalProjectCharacter* player;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ProgressBar;

	void SetImageValue();
	void FailedAction();
	void CreateWG();
	void OpenLV();

	float createtime = 2.0f;
	float Playtime = 5.0f;

	FTimerHandle WidgetTimerHandle;
	FTimerHandle OpenLevelTimerHandle;
	FTimerHandle PlayAnimTimerHandle;
};

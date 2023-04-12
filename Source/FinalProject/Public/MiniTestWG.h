// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/CanvasPanelSlot.h>
#include "MiniTestWG.generated.h"

UCLASS()
class FINALPROJECT_API UMiniTestWG : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
// 	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
// 	class UImage* Start;	
// 	
// 	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
// 	class UImage* EndImage;

 	UCanvasPanelSlot* startslot;
 	UCanvasPanelSlot* endslot;

	FVector2D startPos;
	FVector2D endPos;

	void Pos();

	FTimerHandle TimerHandle_Pos;
};
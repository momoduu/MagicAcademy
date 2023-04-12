// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CourseSlotWidget.generated.h"


UCLASS()
class FINALPROJECT_API UCourseSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UImage* Thumbnail_Img;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CourseName_txt;

	void SetSlot(const FString& courseName, UTexture2D* thumbnail);
};

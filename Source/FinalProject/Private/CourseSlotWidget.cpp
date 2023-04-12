// Fill out your copyright notice in the Description page of Project Settings.


#include "CourseSlotWidget.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>

void UCourseSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UCourseSlotWidget::SetSlot(const FString& courseName, UTexture2D* thumbnail)
{
	UE_LOG(LogTemp, Warning, TEXT("courseName = %s"), *courseName)
	UE_LOG(LogTemp, Warning, TEXT("thumbnail = %s"), *thumbnail->GetPathName())
	CourseName_txt->SetText(FText::FromString(courseName));
	Thumbnail_Img->SetBrushFromTexture(thumbnail);
}


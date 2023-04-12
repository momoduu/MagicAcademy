// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectClassWidget.h"
#include <Components/Button.h>
#include "ScheduleContainer.h"
#include <Kismet/GameplayStatics.h>
#include "CourseData.h"
#include "CourseSlotWidget.h"
#include <Components/WidgetSwitcher.h>
#include <Components/CanvasPanel.h>
#include "ScheduleWidget.h"
#include <Components/Image.h>

void USelectClassWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	//CourseData = NewObject<UCourseData>();
	//ScheduleCT = NewObject<UScheduleContainer>();
	//ScheduleCT->Initilize(GetWorld());

	Btn_AeronauticsClass->OnPressed.AddDynamic(this, &USelectClassWidget::OnAeronauticsClassClicked);
	Btn_PotionClass->OnPressed.AddDynamic(this, &USelectClassWidget::OnPotionClassClicked);
	Btn_Complete->OnPressed.AddDynamic(this, &USelectClassWidget::OnCompleteClicked);
	Btn_Complete_2->OnPressed.AddDynamic(this, &USelectClassWidget::OnPotionComplete);
	Btn_Reset->OnPressed.AddDynamic(this, &USelectClassWidget::OnResetClicked);
	BtnTab1->OnPressed.AddDynamic(this, &USelectClassWidget::OnClickedTab1);
	BtnTab2->OnPressed.AddDynamic(this, &USelectClassWidget::OnClickedTab2);
	Close_Btn->OnPressed.AddDynamic(this, &USelectClassWidget::OnClickedClose);
	MoveBtn_1->OnPressed.AddDynamic(this, &USelectClassWidget::OnBroomMove);
	MoveBtn_2->OnPressed.AddDynamic(this, &USelectClassWidget::OnPotionMove);
// 	if (!bIsVisible)
// 	{
// 		Btn_PotionClass->SetVisibility(ESlateVisibility::Hidden);
// 	}
// 	else
// 	{
		Btn_PotionClass->SetVisibility(ESlateVisibility::Visible);
	//}
}

void USelectClassWidget::OnAeronauticsClassClicked()
{
	bIsAeronauticsClass = !bIsAeronauticsClass;
	if (bIsAeronauticsClass)
	{
		ScriptSwitcher->SetActiveWidgetIndex(1);
	}
	else
	{
		ScriptSwitcher->SetActiveWidgetIndex(0);
	}
	//ScheduleCT->AddToArray(CourseData->AeronauticsClass);
}

void USelectClassWidget::OnPotionClassClicked()
{
	bIsPotionClass = !bIsPotionClass;
	if (bIsPotionClass)
	{
		ScriptSwitcher->SetActiveWidgetIndex(2);
	}
	else
	{
		ScriptSwitcher->SetActiveWidgetIndex(0);
	}
	//ScheduleCT->AddToArray(CourseData->PotionClass);
}

void USelectClassWidget::OnCompleteClicked()
{
	broomIcon->SetVisibility(ESlateVisibility::Visible);
	MoveBtn_1->SetVisibility(ESlateVisibility::Visible);
	//ScheduleCT->SaveCourse();
	//ScheduleCT->LoadCourse();
}

void USelectClassWidget::OnPotionComplete()
{
	potionIcon->SetVisibility(ESlateVisibility::Visible);
	MoveBtn_2->SetVisibility(ESlateVisibility::Visible);
}

void USelectClassWidget::OnResetClicked()
{
	//ScheduleCT->ResetArray();
}

void USelectClassWidget::OnClickedTab1()
{
	ContentSwitcher->SetActiveWidgetIndex(0);
}

void USelectClassWidget::OnClickedTab2()
{
	ContentSwitcher->SetActiveWidgetIndex(1);
	//ScheduleCT->LoadCourse();
}

void USelectClassWidget::OnClickedClose()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void USelectClassWidget::OnBroomMove()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("BroomClass"));
}

void USelectClassWidget::OnPotionMove()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Aisle"));
}

// void USelectClassWidget::ButtonVisible()
// {
// 	if (bIsVisible)
// 	{
// 		Btn_PotionClass->SetVisibility(ESlateVisibility::Visible);
// 	}
// }

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectClassWidget.generated.h"

UCLASS()
class FINALPROJECT_API USelectClassWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* Btn_AeronauticsClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* Btn_PotionClass;	
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* Btn_Complete;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* Btn_Complete_2;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* Btn_Reset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* BtnTab1;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* BtnTab2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* Close_Btn;	
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* MoveBtn_1;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* MoveBtn_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UWidgetSwitcher* ContentSwitcher;	
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UWidgetSwitcher* ScriptSwitcher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UCanvasPanel* CP_SelectClass;	
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UCanvasPanel* CP_Schedule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UWrapBox* WrapBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* broomIcon;	
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* potionIcon;

	UPROPERTY()
		class UScheduleContainer* ScheduleCT;	

	UPROPERTY()
		class UCourseData* CourseData;

	UFUNCTION()
		void OnAeronauticsClassClicked();

	UFUNCTION()
		void OnPotionClassClicked();	
		
	UFUNCTION()
		void OnCompleteClicked();		
		
	UFUNCTION()
		void OnPotionComplete();
		
	UFUNCTION()
		void OnResetClicked();

	UFUNCTION()
		void OnClickedTab1();

	UFUNCTION()
		void OnClickedTab2();

	UFUNCTION()
		void OnClickedClose();	
		
	UFUNCTION()
		void OnBroomMove();	
		
	UFUNCTION()
		void OnPotionMove();

		//void ButtonVisible();

public:
	UPROPERTY(EditAnywhere)
	bool bIsAeronauticsClass = false;	
	
	UPROPERTY(EditAnywhere)
	bool bIsPotionClass = false;

	bool bIsVisible = false;

};

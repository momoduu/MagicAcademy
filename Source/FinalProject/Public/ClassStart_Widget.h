// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClassStart_Widget.generated.h"





UCLASS()
class FINALPROJECT_API UClassStart_Widget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* btn_play;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* btn_exit;

// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
// 		class UButton* btn_reverse;
// 
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
// 		class UButton* btn_forward;
	
	class AHJ_Teacher_2* teacher;


	public:
	UFUNCTION(BlueprintCallable)
		void Play();

	UFUNCTION()
		void Exit();



};

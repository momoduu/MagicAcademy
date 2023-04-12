// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemStruct.h"
#include "EquipmentSlotWidget.generated.h"


UCLASS()
class FINALPROJECT_API UEquipmentSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
		virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
		class UButton* Slot_Btn;

	UPROPERTY(meta = (BindWidget))
		class UImage* ItemImg;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FItemIf newData;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABroomStick> BroomFactory;	
		
	UPROPERTY(EditAnywhere)
		class ABroomStick* SpawnedBroom;

public:
	bool bisCliked = false;

public:
	//void SetSlot(int32 itemNum, UTexture2D* const itemImage);
	void SetSlot(const FItemIf& broomData);

	UFUNCTION()
	void OnClickedButton();
};

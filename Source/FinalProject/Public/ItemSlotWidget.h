// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.h"
#include "ItemSlotWidget.generated.h"

UCLASS()
class FINALPROJECT_API UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* Slot_Btn;

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImg;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemNum_txt;

public:
	//void SetSlot(int32 itemNum, UTexture2D* const itemImage);
	void SetSlot(const FItemData& ItemData);

public:
	int32 slotIndex = 0;
};

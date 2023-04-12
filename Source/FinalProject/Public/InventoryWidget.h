// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.h"
#include "InventoryWidget.generated.h"

UCLASS()
class FINALPROJECT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UWrapBox* WrapBox;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UItemSlotWidget> slotWGFactory;

	UPROPERTY(EditAnywhere)
	class UItemSlotWidget* slotWG;

	int32 maxSize = 10;

	void AddSlot(const TArray<FItemData>& InventoryItems);

};

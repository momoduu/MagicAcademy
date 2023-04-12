// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemStruct.h"
#include "EquipmentWidget.generated.h"


UCLASS()
class FINALPROJECT_API UEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
		class UWrapBox* WrapBox;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UEquipmentSlotWidget> slotWGFactory;

	UPROPERTY(EditAnywhere)
		class UEquipmentSlotWidget* slotWG;

	int32 maxSize = 10;

	void AddSlot(const TArray<FItemIf>& InventoryItems);
};

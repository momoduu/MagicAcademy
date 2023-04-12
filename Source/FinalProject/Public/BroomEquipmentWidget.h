// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemStruct.h"
#include "BroomEquipmentWidget.generated.h"

UCLASS()
class FINALPROJECT_API UBroomEquipmentWidget : public UUserWidget
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

	UPROPERTY(meta = (BindWidget))
	class UButton* Close_Btn;

	int32 maxSize = 10;

	UFUNCTION()
	void Close();
	void AddSlot(const TArray<FItemIf>& InventoryItems);
};

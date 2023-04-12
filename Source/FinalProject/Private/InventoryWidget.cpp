// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "ItemSlotWidget.h"
#include <Components/WrapBox.h>

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

 	slotWGFactory = LoadClass<UItemSlotWidget>(nullptr, TEXT("WidgetBlueprint'/Game/Blueprints/BP_ItemSlotWG.BP_ItemSlotWG_C'"));

}

void UInventoryWidget::AddSlot(const TArray<FItemData>& InventoryItems)
{

		for (int32 i = 0; i < InventoryItems.Num(); i++)
		{
			slotWG = CreateWidget<UItemSlotWidget>(GetWorld(), slotWGFactory);
			if (slotWG != nullptr)
			{
				//slotWG->SetSlot(InventoryItems[i].itmeNum, InventoryItems[i].Thumbnail);
				slotWG->SetSlot(InventoryItems[i]);
				WrapBox->AddChild(slotWG);
			}
		}
}


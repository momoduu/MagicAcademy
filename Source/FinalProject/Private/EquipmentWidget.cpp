// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentWidget.h"
#include "EquipmentSlotWidget.h"
#include <Components/WrapBox.h>

void UEquipmentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	slotWGFactory = LoadClass<UEquipmentSlotWidget>(nullptr, TEXT("WidgetBlueprint'/Game/Blueprints/WG/equipmentWG/BP_EquipmentSlotWG.BP_EquipmentSlotWG_C'"));

}

void UEquipmentWidget::AddSlot(const TArray<FItemIf>& InventoryItems)
{

	for (int32 i = 0; i < InventoryItems.Num(); i++)
	{
		slotWG = CreateWidget<UEquipmentSlotWidget>(GetWorld(), slotWGFactory);
		if (slotWG != nullptr)
		{
			slotWG->SetSlot(InventoryItems[i]);
			WrapBox->AddChild(slotWG);
		}
	}
}

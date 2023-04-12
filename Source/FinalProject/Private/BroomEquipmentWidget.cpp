// Fill out your copyright notice in the Description page of Project Settings.


#include "BroomEquipmentWidget.h"
#include "EquipmentSlotWidget.h"
#include <Components/WrapBox.h>
#include <Components/Button.h>


void UBroomEquipmentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	slotWGFactory = LoadClass<UEquipmentSlotWidget>(nullptr, TEXT("WidgetBlueprint'/Game/Blueprints/WG/equipmentWG/BP_EquipmentSlotWG.BP_EquipmentSlotWG_C'"));

	Close_Btn->OnPressed.AddDynamic(this, &UBroomEquipmentWidget::Close);
}

void UBroomEquipmentWidget::Close()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UBroomEquipmentWidget::AddSlot(const TArray<FItemIf>& InventoryItems)
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
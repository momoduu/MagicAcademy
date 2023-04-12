// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include <Components/Button.h>
#include "SelectClassWidget.h"
#include "InventoryWidget.h"
#include "Inventory.h"
#include "EquipmentWidget.h"
#include "BroomEquipmentWidget.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SelectWGFactory = LoadClass<USelectClassWidget>(nullptr, TEXT("WidgetBlueprint'/Game/Blueprints/BP_SelectClass.BP_SelectClass_C'"));

	SelectWG = CreateWidget<USelectClassWidget>(GetWorld(), SelectWGFactory);
	SelectWG->AddToViewport();
	SelectWG->SetVisibility(ESlateVisibility::Hidden);	

	equipmentWGFactory = LoadClass<UEquipmentWidget>(nullptr, TEXT("WidgetBlueprint'/Game/Blueprints/WG/equipmentWG/BP_MainEquipmentWG.BP_MainEquipmentWG_C'"));
	equipmentWG = CreateWidget<UEquipmentWidget>(GetWorld(), equipmentWGFactory);
	equipmentWG->AddToViewport();
	equipmentWG->SetVisibility(ESlateVisibility::Hidden);	
	
	BroomequipmentWGFactory = LoadClass<UBroomEquipmentWidget>(nullptr, TEXT("WidgetBlueprint'/Game/Blueprints/WG/equipmentWG/BP_BroomEquipmentWG.BP_BroomEquipmentWG_C'"));
	BroomequipmentWG = CreateWidget<UBroomEquipmentWidget>(GetWorld(), BroomequipmentWGFactory);
	BroomequipmentWG->AddToViewport();
	BroomequipmentWG->SetVisibility(ESlateVisibility::Hidden);
	
//	InventoryWGFactory = LoadClass<UInventoryWidget>(nullptr, TEXT("WidgetBlueprint'/Game/Blueprints/BP_InventoryWidget.BP_InventoryWidget_C'"));

// 	InventoryWG = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWGFactory);
// 	InventoryWG->AddToViewport();
// 	InventoryWG->SetVisibility(ESlateVisibility::Hidden);

	Btn_SelectClass->OnPressed.AddDynamic(this, &UMainWidget::OnClickedSelectClass);
	//Btn_Inventory->OnPressed.AddDynamic(this, &UMainWidget::OnClickedInventory);
	Btn_BroomEquipment->OnPressed.AddDynamic(this, &UMainWidget::OnClickedBroomEquipment);

// 	inventoryContainer = NewObject<UInventory>();
// 	inventoryContainer->Initilize(GetWorld());
}

void UMainWidget::OnClickedSelectClass()
{
	SelectWG->SetVisibility(ESlateVisibility::Visible);
}

// void UMainWidget::OnClickedInventory()
// {
// 	equipmentWG->SetVisibility(ESlateVisibility::Visible);
// 	//InventoryWG->SetVisibility(ESlateVisibility::Visible);
// }

void UMainWidget::OnClickedBroomEquipment()
{
	BroomequipmentWG->SetVisibility(ESlateVisibility::Visible);
}

// void UMainWidget::GetCloakData(const TArray<FItemIf>& CloakItems)
// {
// 	if (equipmentWG != nullptr)
// 	{
// 		equipmentWG->AddSlot(CloakItems);
// 	}
// }

void UMainWidget::GetBroomData(const TArray<FItemIf>& BroomItems)
{
	if (BroomequipmentWG != nullptr)
	{
		BroomequipmentWG->AddSlot(BroomItems);
	}
}

// void UMainWidget::GetData(const TArray<FItemData>& InventoryItems)
// {
// 	if (InventoryWG != nullptr)
// 	{
// 		InventoryWG->AddSlot(InventoryItems);
// 	}
// }

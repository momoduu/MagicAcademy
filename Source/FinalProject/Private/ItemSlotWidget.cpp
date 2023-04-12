// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include "Inventory.h"

void UItemSlotWidget::SetSlot(const FItemData& ItemData)
{
	ItemNum_txt->SetText(FText::AsNumber(ItemData.itmeNum));
	ItemImg->SetBrushFromTexture(ItemData.Thumbnail);
}

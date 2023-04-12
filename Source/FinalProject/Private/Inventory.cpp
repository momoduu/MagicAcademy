// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "ItemSlotWidget.h"
#include "InventoryWidget.h"
#include <Engine/World.h>
#include <Kismet/GameplayStatics.h>
#include "../FinalProjectCharacter.h"
#include "MainWidget.h"
#include <Engine/DataTable.h>

UInventory::UInventory()
{
	//FString dataPath = TEXT("DataTable'/Game/Blueprints/Item/ItemData.ItemData'");
	ConstructorHelpers::FObjectFinder<UDataTable>temptable(TEXT("DataTable'/Game/Blueprints/Item/ItemData.ItemData'"));
	if (temptable.Succeeded())
	{
		ItemDataTable = temptable.Object;
	}
}

void UInventory::Initilize(class UWorld* w)
{
	world = w;
}

void UInventory::LoadData(FName itemName)
{
	if (ItemDataTable != nullptr)
	{
		ItemData = ItemDataTable->FindRow<FItemData>(itemName, FString(""));
		if (ItemData != nullptr)
		{ 
			bool bItemFound = false;

			for (const FItemData& InventoryItem : InventoryItems)
			{
				if (InventoryItem.itemName == ItemData->itemName)
				{
					bItemFound = true;
					break;
				}
			}
			if (!bItemFound)
			{
				InventoryItems.Add(*ItemData);
				player = Cast<AFinalProjectCharacter>(UGameplayStatics::GetActorOfClass(world, AFinalProjectCharacter::StaticClass()));
				//player->MainWG->GetData(InventoryItems);
			}
		}
	}
}
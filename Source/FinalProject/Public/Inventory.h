// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Engine/DataTable.h>
#include "Inventory.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FString itemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		int32 itmeNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		class UTexture2D* Thumbnail;
};

UCLASS()
class FINALPROJECT_API UInventory : public UObject
{
	GENERATED_BODY()

public:
	UInventory();

public:
	FItemData* ItemData;
	
	UPROPERTY()
	class UDataTable* ItemDataTable;

	UPROPERTY(EditAnywhere)
	TArray<FItemData> InventoryItems;	

	UPROPERTY()
	class UWorld* world;

	UPROPERTY()
	class AFinalProjectCharacter* player;

public:

public:
	void Initilize(class UWorld* w);
	void LoadData(FName itemName);

};

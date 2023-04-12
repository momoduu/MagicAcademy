// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.h"
#include "ItemStruct.h"
#include "MainWidget.generated.h"

UCLASS()
class FINALPROJECT_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Btn_SelectClass;
	
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
// 	class UButton* Btn_Inventory;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Btn_BroomEquipment;	

	UPROPERTY(EditAnywhere)
	class USelectClassWidget* SelectWG;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class USelectClassWidget> SelectWGFactory;	
	
	UPROPERTY(EditAnywhere)
	class UEquipmentWidget* equipmentWG;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UEquipmentWidget> equipmentWGFactory;	
	
	UPROPERTY(EditAnywhere)
	class UBroomEquipmentWidget* BroomequipmentWG;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UBroomEquipmentWidget> BroomequipmentWGFactory;

// 	UPROPERTY(EditAnywhere)
// 	class UInventoryWidget* InventoryWG;

// 	UPROPERTY(EditAnywhere)
// 	TSubclassOf<class UInventoryWidget> InventoryWGFactory;

// 	UPROPERTY(EditAnywhere)
// 	class UInventory* inventoryContainer;

public:
	UFUNCTION()
	void OnClickedSelectClass();	
	
// 	UFUNCTION()
// 	void OnClickedInventory();	
	
	UFUNCTION()
	void OnClickedBroomEquipment();

// 	UFUNCTION()
// 	void GetCloakData(const TArray<FItemIf>& CloakItems);
	
	UFUNCTION()
	void GetBroomData(const TArray<FItemIf>& BroomItems);	

	//void GetData(const TArray<FItemData>& InventoryItems);

// 	virtual void NativeConstruct() override;
// 
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
// 		class UButton* btn_play;
//

public:
	bool bisOpenEM = false;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterCreateWidget.generated.h"


UCLASS()
class FINALPROJECT_API UCharacterCreateWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Btn_Create;	
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Btn_Female;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Btn_Male;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Btn_Hair_1;		
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Btn_Hair_2;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Btn_Hair_3;		
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Tab_1;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Tab_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* NameTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(EditAnywhere)
	class AUI_Character* UIplayer;

	UPROPERTY(EditAnywhere)
	class UMyGameInstance* GameInstance;

	UPROPERTY(EditAnywhere)
	class USkeletalMesh* FemaleMesh;

	UPROPERTY(EditAnywhere)
	class USkeletalMesh* MaleMesh;	
	
	UPROPERTY(EditAnywhere)
	class USkeletalMesh* hairMesh;	
	
	UPROPERTY(EditAnywhere)
	class UClass* AnimFemaleClass;	
	
	UPROPERTY(EditAnywhere)
	class UClass* AnimMaleClass;	
	
	UPROPERTY(EditAnywhere)
	class UClass* AnimBroomClass;

public:
	UFUNCTION()
	void OnClicked();
	
	UFUNCTION()
	void OnClickedFemale();
	
	UFUNCTION()
	void OnClickedMale();	
	
	UFUNCTION()
	void OnClickedHair_1();	
	
	UFUNCTION()
	void OnClickedHair_2();	
	
	UFUNCTION()
	void OnClickedHair_3();			

	UFUNCTION()
	void OnClickedTab1();

	UFUNCTION()
	void OnClickedTab2();

	bool bisClicked = false;
};

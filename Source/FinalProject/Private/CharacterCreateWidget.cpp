// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCreateWidget.h"
#include <Components/EditableTextBox.h>
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>
#include <Engine/SkeletalMesh.h>
#include "MyGameInstance.h"
#include <Engine/StaticMesh.h>
#include "../FinalProjectCharacter.h"
#include <Components/WidgetSwitcher.h>
#include "UI_Character.h"
#include "AnimPlayer.h"
#include <UObject/Class.h>
#include "PlayerMoveComponent.h"
#include "RiderAnim.h"

void UCharacterCreateWidget::NativeConstruct()
{
	UIplayer = Cast<AUI_Character>(UGameplayStatics::GetActorOfClass(GetWorld(), AUI_Character::StaticClass()));
	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	AnimFemaleClass = LoadClass<UAnimPlayer>(nullptr,
	TEXT("AnimBlueprint'/Game/Blueprints/Animation/AnimBlueprint/ABP_Player.ABP_Player_C'"));	
	
	AnimMaleClass = LoadClass<UAnimPlayer>(nullptr,
	TEXT("AnimBlueprint'/Game/Blueprints/Animation/AnimBlueprint/ABP_MalePlayer.ABP_MalePlayer_C'"));	
	
// 	AnimBroomClass = LoadClass<URiderAnim>(nullptr,
// 	TEXT("AnimBlueprint'/Game/Blueprints/Animation/AnimBlueprint/BroomAnimBlueprint.BroomAnimBlueprint_C'"));

	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	Btn_Create->OnPressed.AddDynamic(this, &UCharacterCreateWidget::OnClicked);
	Btn_Female->OnPressed.AddDynamic(this, &UCharacterCreateWidget::OnClickedFemale);
	Btn_Male->OnPressed.AddDynamic(this, &UCharacterCreateWidget::OnClickedMale);
	Btn_Hair_1->OnPressed.AddDynamic(this, &UCharacterCreateWidget::OnClickedHair_1);
	Btn_Hair_2->OnPressed.AddDynamic(this, &UCharacterCreateWidget::OnClickedHair_2);
	Btn_Hair_3->OnPressed.AddDynamic(this, &UCharacterCreateWidget::OnClickedHair_3);
	Tab_1->OnPressed.AddDynamic(this, &UCharacterCreateWidget::OnClickedTab1);
	Tab_2->OnPressed.AddDynamic(this, &UCharacterCreateWidget::OnClickedTab2);
}

void UCharacterCreateWidget::OnClicked()
{
	FString CharacterName = NameTextBox->GetText().ToString();
	if(CharacterName.Len() <= 0 /*|| bisClicked == false*/) return;
	
	GameInstance->SetName(NameTextBox->GetText());
	GameInstance->ChangeMesh(UIplayer->BodyMesh->SkeletalMesh);
	GameInstance->ChangeHairMesh(UIplayer->hairMesh->SkeletalMesh);
	GameInstance->SetAnimClss(UIplayer->BodyMesh->GetAnimClass());
	//GameInstance->BroomAnimClass(AnimBroomClass);
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMap"));
}

void UCharacterCreateWidget::OnClickedFemale()
{
	bisClicked = true;
	FemaleMesh = LoadObject<USkeletalMesh>(nullptr, 
	TEXT("SkeletalMesh'/Game/Blueprints/CHar_Mesh/Female.Female'"));
	UIplayer->BodyMesh->SetSkeletalMesh(FemaleMesh);

	hairMesh = LoadObject<USkeletalMesh>(nullptr,
		TEXT("SkeletalMesh'/Game/Blueprints/CHar_Mesh/Hair/FeMale_hairfbx.FeMale_hairfbx_FM_hairfbx'"));
	UIplayer->hairMesh->SetSkeletalMesh(hairMesh);

	if (AnimFemaleClass != nullptr)
	{
		UIplayer->BodyMesh->SetAnimInstanceClass(AnimFemaleClass);
	}
	//player->BodyMesh->SetSkeletalMesh(nullptr);
}

void UCharacterCreateWidget::OnClickedMale()
{
	bisClicked = true;
	MaleMesh = LoadObject<USkeletalMesh>(nullptr, 
	TEXT("SkeletalMesh'/Game/Blueprints/CHar_Mesh/Male/Male2.Male2'"), nullptr, LOAD_None, nullptr);
	UIplayer->BodyMesh->SetSkeletalMesh(MaleMesh);

	hairMesh = LoadObject<USkeletalMesh>(nullptr,
		TEXT("SkeletalMesh'/Game/Blueprints/CHar_Mesh/ShortHair/shorhair.shorhair'"));
	UIplayer->hairMesh->SetSkeletalMesh(hairMesh);

	if (AnimMaleClass != nullptr)
	{
		UIplayer->BodyMesh->SetAnimInstanceClass(AnimMaleClass);
	}
}

void UCharacterCreateWidget::OnClickedHair_1()
{
	hairMesh = LoadObject<USkeletalMesh>(nullptr,
	TEXT("SkeletalMesh'/Game/Blueprints/CHar_Mesh/Hair/FeMale_hairfbx.FeMale_hairfbx_FM_hairfbx'"));
	
	UIplayer->hairMesh->SetSkeletalMesh(hairMesh);
}

void UCharacterCreateWidget::OnClickedHair_2()
{
	hairMesh = LoadObject<USkeletalMesh>(nullptr,
	TEXT("SkeletalMesh'/Game/Blueprints/CHar_Mesh/LongHair/RongHair.RongHair'"));

	UIplayer->hairMesh->SetSkeletalMesh(hairMesh);
}

void UCharacterCreateWidget::OnClickedHair_3()
{
	hairMesh = LoadObject<USkeletalMesh>(nullptr,
	TEXT("SkeletalMesh'/Game/Blueprints/CHar_Mesh/ShortHair/shorhair.shorhair'"));

	UIplayer->hairMesh->SetSkeletalMesh(hairMesh);
}

void UCharacterCreateWidget::OnClickedTab1()
{
	UIplayer->bIsHair = false;
	WidgetSwitcher->SetActiveWidgetIndex(0);
}

void UCharacterCreateWidget::OnClickedTab2()
{
	UIplayer->bIsHair = true;
	WidgetSwitcher->SetActiveWidgetIndex(1);
}




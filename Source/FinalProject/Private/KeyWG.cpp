// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyWG.h"
#include <Components/Image.h>
#include <Materials/MaterialInstanceDynamic.h>
#include <Animation/WidgetAnimation.h>
#include "../FinalProjectCharacter.h"
#include <Kismet/GameplayStatics.h>
#include <Components/ProgressBar.h>

void UKeyWG::NativeConstruct()
{
	Super::NativeConstruct();

	player = Cast<AFinalProjectCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AFinalProjectCharacter::StaticClass()));
	player->bIsPlayProgressBar = true;
	player->progressValue = 1.0f;
	ProgressBar->SetPercent(player->progressValue);
}

void UKeyWG::SetImageValue()
{
	UMaterialInstanceDynamic* DynMaterial = ProgressBorder->GetDynamicMaterial();
	if (DynMaterial != nullptr)
	{
		// 스칼라 파라미터 값을 증가시킴
		float CurrentValue;
		DynMaterial->GetScalarParameterValue(TEXT("Progress"), CurrentValue);
		float NewValue = CurrentValue + 0.1f;
		DynMaterial->SetScalarParameterValue("Progress", NewValue); 
		ProgressBorder->SetBrushFromMaterial(DynMaterial);

		if (NewValue >= 1.0f)
		{
			PlayAnimation(Passed, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
			player->bIsPassed = true;
			GetWorld()->GetTimerManager().SetTimer(WidgetTimerHandle, this, &UKeyWG::CreateWG, createtime);
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(PlayAnimTimerHandle, this, &UKeyWG::FailedAction, Playtime);
		}
	}
}

void UKeyWG::FailedAction()
{
	PlayAnimation(Failed, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
}

void UKeyWG::CreateWG()
{
	player->succeedWG();
	GetWorld()->GetTimerManager().SetTimer(OpenLevelTimerHandle, this, &UKeyWG::OpenLV, createtime);
}

void UKeyWG::OpenLV()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("NewMap1"));
	player->bisRemove = true;
}

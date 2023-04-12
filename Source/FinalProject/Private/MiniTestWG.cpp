// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniTestWG.h"
#include <Components/CanvasPanelSlot.h>
#include <Components/Widget.h>

void UMiniTestWG::NativeConstruct()
{
	Super::NativeConstruct();

	UWidget* StartIMG = GetWidgetFromName(TEXT("Start"));
	startslot = Cast<UCanvasPanelSlot>(StartIMG->Slot);
	
	UWidget* EndMG = GetWidgetFromName(TEXT("End"));
	endslot = Cast<UCanvasPanelSlot>(EndMG->Slot);

	startPos = startslot->GetPosition();
	endPos = endslot->GetPosition();

	UE_LOG(LogTemp, Warning, TEXT("s = %f"), startPos.X)
	UE_LOG(LogTemp, Warning, TEXT("e = %f"), endPos.X)

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Pos, this, &UMiniTestWG::Pos, 2.f, false);
}

void UMiniTestWG::Pos()
{
// 	if (startPos == endPos)
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("����"))
// 	}
	// lerp ���� ����
	float LerpRatio = 1.0f;

	// lerp�� ����Ͽ� startPos ��ġ ����
 	FVector2D NewPos = FMath::Lerp(startPos, endPos, LerpRatio);
 	startslot->SetPosition(NewPos);


	UE_LOG(LogTemp, Warning, TEXT("s = %f"), startslot->GetPosition().X)
	UE_LOG(LogTemp, Warning, TEXT("e = %f"), endslot->GetPosition().X)
}

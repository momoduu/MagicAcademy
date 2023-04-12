// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentSlotWidget.h"
#include <Components/Image.h>
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>
#include "../FinalProjectCharacter.h"
#include "BroomStick.h"

void UEquipmentSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	BroomFactory = LoadClass<ABroomStick>(nullptr, TEXT("Blueprint'/Game/Blueprints/BP_BroomStick.BP_BroomStick_C'"));

	Slot_Btn->OnPressed.AddDynamic(this, &UEquipmentSlotWidget::OnClickedButton);
}

void UEquipmentSlotWidget::SetSlot(const FItemIf& broomData)
{
	newData = broomData;
	ItemImg->SetBrushFromTexture(broomData.Thumbnail);
}

void UEquipmentSlotWidget::OnClickedButton()
{
	bisCliked = !bisCliked;

	if (bisCliked) 
	{
		AFinalProjectCharacter* Character = Cast<AFinalProjectCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AFinalProjectCharacter::StaticClass()));
		FVector SpawnLocation = Character->GetActorLocation() + Character->GetActorForwardVector() * 100.f; // 캐릭터 앞쪽에서 100cm 떨어진 위치
		FRotator SpawnRotation = FRotator::ZeroRotator; // 회전값은 0으로 설정
		SpawnedBroom = GetWorld()->SpawnActor<ABroomStick>(BroomFactory, SpawnLocation, SpawnRotation);
	}
	else
	{
		SpawnedBroom->Destroy();
	}
}
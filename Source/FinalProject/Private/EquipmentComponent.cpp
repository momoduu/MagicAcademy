// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"
#include "BroomStick.h"
#include "../FinalProjectCharacter.h"
#include "MainWidget.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	//Tick 안써서 false로 바꿈
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}


// Called every frame
void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UEquipmentComponent::AddItem(FItemIf data)
{
//  	ABroomStick* newBroom = new broom(data.itemName, data.Thumbnail);
//  	BroomItems.Add(newBroom);
	Iteminfo.Add(data);

	me->MainWG->GetBroomData(Iteminfo);
	//me->MainWG->GetCloakData(Iteminfo);
}


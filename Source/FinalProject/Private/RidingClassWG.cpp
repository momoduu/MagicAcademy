// Fill out your copyright notice in the Description page of Project Settings.


#include "RidingClassWG.h"
#include <Components/Button.h>
#include "RidingTeacher.h"
#include <Kismet/GameplayStatics.h>
#include "RidingTeacherFSM.h"

void URidingClassWG::NativeConstruct()
{
	Super::NativeConstruct();

	teacher = Cast<ARidingTeacher>(UGameplayStatics::GetActorOfClass(GetWorld(), 
	ARidingTeacher::StaticClass()));
	
	StartBtn = Cast<UButton>(GetWidgetFromName(TEXT("Start_Btn")));

	StartBtn->OnPressed.AddDynamic(this, &URidingClassWG::OnPlay);
}

void URidingClassWG::OnPlay()
{
	if (teacher->fsm != nullptr)
	{
		teacher->fsm->bIsPlay = true;
	}
	RemoveFromParent();
}

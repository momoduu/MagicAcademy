// Fill out your copyright notice in the Description page of Project Settings.


#include "ClassStart_Widget.h"
#include "Components/Button.h"
#include "TeacherFSM.h"
#include <Kismet/GameplayStatics.h>
#include "HJ_Teacher_2.h"
#include "Teacher_2Anim.h"

void UClassStart_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	teacher = Cast <AHJ_Teacher_2>(UGameplayStatics::GetActorOfClass(GetWorld(),AHJ_Teacher_2::StaticClass()));

	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	btn_play->OnClicked.AddUniqueDynamic(this, &UClassStart_Widget::Play);
	btn_exit->OnClicked.AddUniqueDynamic(this, &UClassStart_Widget::Exit);
	// 	btn_reverse->OnPressed.AddDynamic(this, &UMovieWidget::Reverse);
  // btn_forward->OnPressed.AddDynamic(this, &UMovieWidget::Forward);
}



void UClassStart_Widget::Play()
{
	
	teacher->fsm->mState = ETeacherState::Move;
	teacher->fsm->anim->Teacher_2_Montage(TEXT("Walk0"));
	

}

void UClassStart_Widget::Exit()
{
	RemoveFromParent();
 }

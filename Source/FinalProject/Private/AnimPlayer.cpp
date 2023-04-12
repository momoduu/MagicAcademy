// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimPlayer.h"
#include "../FinalProjectCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>

void UAnimPlayer::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	APawn* pawn = TryGetPawnOwner();

	me = Cast<AFinalProjectCharacter>(pawn);
}

void UAnimPlayer::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (me != nullptr)
	{
		bAir = me->GetCharacterMovement()->IsFalling();
	}
}

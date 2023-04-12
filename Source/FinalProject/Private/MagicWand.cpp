// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicWand.h"

AMagicWand::AMagicWand()
{

}

void AMagicWand::BeginPlay()
{
	Super::BeginPlay();

	SetItem();
}

void AMagicWand::SetItem()
{
	ItemInfo.itemName = FString("MagicWand");
	ItemInfo.itmeNum = 1;
}



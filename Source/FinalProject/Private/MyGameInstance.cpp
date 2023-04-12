// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include <UObject/Class.h>

void UMyGameInstance::SetCredit(int32 credit)
{
	Credit = credit;
}

void UMyGameInstance::ChangeMesh(USkeletalMesh* newMesh)
{
	currSKMesh = newMesh;
}

void UMyGameInstance::SetName(FText newName)
{
	userName = newName;
}

void UMyGameInstance::ChangeHairMesh(USkeletalMesh* newHairMesh)
{
	currHairMesh = newHairMesh;
}

void UMyGameInstance::SetAnimClss(UClass* newAnimClass)
{
	AnimPlayerClass = newAnimClass;
}

void UMyGameInstance::BroomAnimClass(UClass* newAnimClass)
{
	AnimBroomClass = newAnimClass;
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"


UCLASS()
class FINALPROJECT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	class USkeletalMesh* currSKMesh;

	UPROPERTY(EditAnywhere)
	class USkeletalMesh* currHairMesh;

	UPROPERTY(EditAnywhere)
	class UClass* AnimPlayerClass;	
	
	UPROPERTY(EditAnywhere)
	class UClass* AnimBroomClass;
	
	int32 Credit;

	FText userName;

	void SetCredit(int32 credit);
	void ChangeMesh(USkeletalMesh* newMesh);
	void SetName(FText newName);
	void ChangeHairMesh(USkeletalMesh* staticMesh);
	void SetAnimClss(UClass* newAnimClass);
	void BroomAnimClass(UClass* newAnimClass);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "MagicWand.generated.h"

UCLASS()
class FINALPROJECT_API AMagicWand : public AItem
{
	GENERATED_BODY()

public:
	AMagicWand();

protected:
	virtual void BeginPlay() override;

public:
	void SetItem();
};

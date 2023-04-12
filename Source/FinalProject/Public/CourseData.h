// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CourseData.generated.h"

USTRUCT(BlueprintType)
struct FCourseInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Course")
	FString CourseName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Course")
	int32 Credit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Course")
	class UTexture2D* Thumbnail;
};


UCLASS(Blueprintable, BlueprintType)
class FINALPROJECT_API UCourseData : public UObject
{
	GENERATED_BODY()

public:
	UCourseData();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Course")
	FCourseInfo AeronauticsClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Course")
	FCourseInfo PotionClass;
};

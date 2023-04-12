// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CourseData.h"
#include "ScheduleContainer.generated.h"


UCLASS()
class FINALPROJECT_API UScheduleContainer : public UObject
{
	GENERATED_BODY()

public:
// 	void AddCourse(const FCourseDataStruct& newCourse);
// 	void RemoveCourse(int32 courseindex);

	UScheduleContainer();

public:
	UPROPERTY()
	class UWorld* world;

	UPROPERTY(EditAnywhere)
	TArray<FCourseInfo> arrayCourse;

	UPROPERTY(EditAnywhere)
	class UCourseSlotWidget* slotWG;		
		
	UPROPERTY(EditAnywhere)
	class UScheduleWidget* ScheduleWG;

	UPROPERTY(EditAnywhere)
	class USelectClassWidget* selectWG;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCourseSlotWidget> slotWGFactory;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UScheduleWidget> scheduleWGFactory;	
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class USelectClassWidget> selectWGFactory;

	//void CreateCourse();
	void Initilize(class UWorld* w);
	void AddToArray(const FCourseInfo& newCourse);
	void ResetArray();
	void SaveCourse();
	void LoadCourse();
	void CreateCourse(const FCourseInfo& newCourse);

	FString thumbnailPath;
};

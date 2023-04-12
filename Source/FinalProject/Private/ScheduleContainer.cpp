// Fill out your copyright notice in the Description page of Project Settings.


#include "ScheduleContainer.h"
#include "CourseSlotWidget.h"
#include "ScheduleWidget.h"
#include <Components/WrapBox.h>



#include <Kismet/GameplayStatics.h>
#include "SelectClassWidget.h"
#include "../FinalProjectCharacter.h"
#include "MainWidget.h"

UScheduleContainer::UScheduleContainer()
{
	ConstructorHelpers::FClassFinder<UCourseSlotWidget>tempslotUI(TEXT("WidgetBlueprint'/Game/Blueprints/BP_CourseWG.BP_CourseWG_C'"));
	if (tempslotUI.Succeeded())
	{
		slotWGFactory = tempslotUI.Class;
	}	
	ConstructorHelpers::FClassFinder<UScheduleWidget>tempUI(TEXT("WidgetBlueprint'/Game/Blueprints/BP_ScheduleWidget.BP_ScheduleWidget_C'"));
	if (tempUI.Succeeded())
	{
		scheduleWGFactory = tempUI.Class;
	}
}

void UScheduleContainer::Initilize(class UWorld* w)
{
	world = w;
}

 void UScheduleContainer::AddToArray(const FCourseInfo& newCourse)
 {
	 UE_LOG(LogTemp, Warning, TEXT("arrayCoures = %d"), arrayCourse.Num())
  	for (int32 i = 0; i < arrayCourse.Num(); i++)
  	{
  		if (arrayCourse[i].CourseName == newCourse.CourseName)
  		{
  			return;
  		}
  	}
	arrayCourse.Add(newCourse);
 }

void UScheduleContainer::ResetArray()
{
	arrayCourse.Empty();
}

void UScheduleContainer::SaveCourse()
{
	TArray<TSharedPtr<FJsonValue>> jsonArray;
	for (int32 i = 0; i < arrayCourse.Num(); i++)
	{
		TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject());
		jsonObject->SetStringField("CourseName", arrayCourse[i].CourseName);
		jsonObject->SetNumberField("Credit", arrayCourse[i].Credit);
	
		if (arrayCourse[i].Thumbnail != nullptr)
		{
			FSoftObjectPath AssetRef(arrayCourse[i].Thumbnail);
			FString AssetPath = AssetRef.ToString();
			
			TSharedPtr<FJsonObject> thumbnailObj = MakeShareable(new FJsonObject());
			thumbnailObj->SetStringField("ThumbnailPath", AssetPath);
			jsonObject->SetObjectField("Thumbnail", thumbnailObj);
		}

		jsonArray.Add(MakeShareable(new FJsonValueObject(jsonObject)));
	}

	FString jsonString;
	TSharedRef<TJsonWriter<>> jsonWrite = TJsonWriterFactory<>::Create(&jsonString);
	FJsonSerializer::Serialize(jsonArray, jsonWrite);

	FString filepath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Course.txt"));
	FFileHelper::SaveStringToFile(jsonString, *filepath);
}

void UScheduleContainer::LoadCourse()
{
	arrayCourse.Empty();
	
	FString jsonString;

	FString filePath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Course.txt"));
	FFileHelper::LoadFileToString(jsonString, *filePath);
	UE_LOG(LogTemp, Warning, TEXT("load : %s"), *jsonString)

	TArray<TSharedPtr<FJsonValue>> jsonArray;
	TSharedRef<TJsonReader<>> jsonReader = TJsonReaderFactory<>::Create(jsonString);
	FJsonSerializer::Deserialize(jsonReader, jsonArray);

	for (int32 i = 0; i < jsonArray.Num(); i++)
	{
		TSharedPtr<FJsonObject> jsonObject = jsonArray[i]->AsObject();
		FString CourseName = jsonObject->GetStringField("CourseName");
		int32 Credit = jsonObject->GetNumberField("Credit");

		UTexture2D* thumbnail = nullptr;
		TSharedPtr<FJsonObject> thumbnailObj = jsonObject->GetObjectField("Thumbnail");
		if (thumbnailObj.IsValid())
		{
			thumbnailPath = thumbnailObj->GetStringField("ThumbnailPath");
			thumbnail = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *thumbnailPath));
		}

		FCourseInfo newCourse = { CourseName, Credit, thumbnail };

		CreateCourse(newCourse);
	}
}

void UScheduleContainer::CreateCourse(const FCourseInfo& newCourse)
{
	arrayCourse.Add(newCourse);

 	for (int32 i = 0; i < arrayCourse.Num(); i++)
 	{
 		slotWG = CreateWidget<UCourseSlotWidget>(world, slotWGFactory);
 		slotWG->SetSlot(arrayCourse[i].CourseName, arrayCourse[i].Thumbnail);
 	}
	AFinalProjectCharacter* player = Cast<AFinalProjectCharacter>(UGameplayStatics::GetActorOfClass(world, AFinalProjectCharacter::StaticClass()));
	player->MainWG->SelectWG->WrapBox->AddChild(slotWG);

// 	ScheduleWG = CreateWidget<UScheduleWidget>(world, scheduleWGFactory);
// 	
// 	for (int32 i = 0; i < arrayCourse.Num(); i++)
// 	{
// 		slotWG = CreateWidget<UCourseSlotWidget>(world, slotWGFactory);
// 		slotWG->SetSlot(arrayCourse[i].CourseName, arrayCourse[i].Thumbnail);
// 		ScheduleWG->WrapBox->AddChild(slotWG);
// 	}


	//Cast<AFinalProjectCharacter>(UGameplayStatics::GetActorOfClass(world, AFinalProjectCharacter::StaticClass()))->ScheduleWG=ScheduleWG;
}

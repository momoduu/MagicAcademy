// Fill out your copyright notice in the Description page of Project Settings.


#include "CourseData.h"

UCourseData::UCourseData()
{
	AeronauticsClass.CourseName = FString("AeronauticsClass");
	AeronauticsClass.Credit = 1;
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextureObj(TEXT("Texture2D'/Game/Blueprints/Image/iconbroom.iconbroom'"));
	if (TextureObj.Succeeded())
	{
		AeronauticsClass.Thumbnail = TextureObj.Object;
	}

	PotionClass.CourseName = FString("PotionClass");
	PotionClass.Credit = 1;

	static ConstructorHelpers::FObjectFinder<UTexture2D> textureObj(TEXT("Texture2D'/Game/Blueprints/Image/iconpotion.iconpotion'"));
	if (textureObj.Succeeded())
	{
		PotionClass.Thumbnail = textureObj.Object;
	}
}

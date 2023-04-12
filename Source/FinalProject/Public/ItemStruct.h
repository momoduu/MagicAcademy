#pragma once
#include "ItemStruct.generated.h"

USTRUCT(BlueprintType)
struct FItemIf
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BroomItem")
		FString itemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BroomItem")
		class UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BroomItem")
		class USkeletalMeshComponent* SkeletalComp;
};
// Fill out your copyright notice in the Description page of Project Settings.


#include "TeacherBroom.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "../FinalProjectCharacter.h"
#include "KeyWG.h"

// Sets default values
ATeacherBroom::ATeacherBroom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	compBox->SetupAttachment(RootComponent);
	compBox->SetRelativeLocation(FVector(0));
	compBox->SetRelativeRotation(FRotator(0));
	compBox->SetBoxExtent(FVector(100, 50, 100));

	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	compMesh->SetupAttachment(compBox);
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));
	compMesh->SetRelativeLocation(FVector(0, 0, -90));
}

// Called when the game starts or when spawned
void ATeacherBroom::BeginPlay()

{
	Super::BeginPlay();
	
}

// Called every frame
void ATeacherBroom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeacherBroom::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AFinalProjectCharacter* player = Cast<AFinalProjectCharacter>(OtherActor);
	if (player)
	{
		player->CreateWG();
		//player->bIsActiveKey = true;
	}
}

void ATeacherBroom::NotifyActorEndOverlap(AActor* OtherActor)
{
	AFinalProjectCharacter* player = Cast<AFinalProjectCharacter>(OtherActor);
	if (player)
	{
		if (player->keyWG != nullptr)
		{
			player->keyWG->RemoveFromParent();
			player->bIsPlayProgressBar = false;
			player->bIsActiveKey = false;
		}
	}
}
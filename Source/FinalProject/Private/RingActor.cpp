// Fill out your copyright notice in the Description page of Project Settings.


#include "RingActor.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include "BroomStick.h"
#include "../FinalProjectCharacter.h"

// Sets default values
ARingActor::ARingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	compSphere->SetupAttachment(RootComponent);
	compSphere->SetSphereRadius(1000);
	compSphere->SetCollisionProfileName(TEXT("Ring"));

	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	compMesh->SetupAttachment(compSphere);

	ConstructorHelpers::FObjectFinder<UStaticMesh>tempMesh(TEXT("StaticMesh'/Game/Blueprints/Ring.Ring'"));
	if (tempMesh.Succeeded())
	{
		compMesh->SetStaticMesh(tempMesh.Object);
	}
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));

	Pass = 0;
}

// Called when the game starts or when spawned
void ARingActor::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AFinalProjectCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AFinalProjectCharacter::StaticClass()));
}

// Called every frame
void ARingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARingActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ABroomStick* broom = Cast<ABroomStick>(OtherActor);
	if (broom)
	{
// 		RingPassDelegate.ExecuteIfBound();
// 		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Pass"));
	}
}

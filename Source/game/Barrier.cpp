// Fill out your copyright notice in the Description page of Project Settings.

#include "game.h"
#include "Barrier.h"


// Sets default values
ABarrier::ABarrier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    
    // create static mesh component
    WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
    RootComponent = WallMesh;

}

// Called when the game starts or when spawned
void ABarrier::BeginPlay()
{
	Super::BeginPlay();
	
}
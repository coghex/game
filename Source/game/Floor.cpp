// Fill out your copyright notice in the Description page of Project Settings.

#include "game.h"
#include "Floor.h"


// Sets default values
AFloor::AFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    
    // create static mesh component
    FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
    RootComponent = FloorMesh;

}

// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	Super::BeginPlay();
	
}
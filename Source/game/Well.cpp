// Fill out your copyright notice in the Description page of Project Settings.

#include "game.h"
#include "Well.h"


// Sets default values
AWell::AWell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    
    WellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Well"));
    RootComponent = WellMesh;
    CylMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cyl"));
    CylMesh->AttachTo(RootComponent);
    BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block"));
    BlockMesh->AttachTo(RootComponent);
    PitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pit"));
    PitMesh->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AWell::BeginPlay()
{
	Super::BeginPlay();
	
}
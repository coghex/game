// Fill out your copyright notice in the Description page of Project Settings.

#include "game.h"
#include "Well.h"


// Sets default values
AWell::AWell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    
    WellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Well"));
    WellMesh->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AWell::BeginPlay()
{
	Super::BeginPlay();
	
}
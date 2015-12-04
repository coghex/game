// Fill out your copyright notice in the Description page of Project Settings.

#include "game.h"
#include "Arrow.h"


// Sets default values
AArrow::AArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    Arrowpointer = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
    RootComponent = Arrowpointer;
}

// Called when the game starts or when spawned
void AArrow::BeginPlay()
{
	Super::BeginPlay();
	
}
// Fill out your copyright notice in the Description pagof Project Settings.

#include "game.h"
#include "Tree.h"


// Sets default values
ATree::ATree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATree::BeginPlay()
{
    Super::BeginPlay();
    int i;
    // Create the head
    World = GetWorld();
    if (World) {
        head = BuildTile(NULL, 1);
        
        for (i=0; i<10; i++) {
            BuildTile(current[0], 10);
        }
        
        BuildTile(current[0], 2);
    }
}


void ATree::BuildNextTiles() {
    
    AttachPoints = current[0]->GetAttachPoints();
    nexttile = (ATile *)World->SpawnActorDeferred<ATile>(SpawnTile, AttachPoints[0], nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
    if (nexttile)
    {
        nexttile->init(10, current[0], this);
        UGameplayStatics::FinishSpawningActor(nexttile, AttachPoints[0]);
    }
    current.Empty();
    current.Add(nexttile);
    tail = nexttile;
}

void ATree::AddT(int32 tpoints)
{
    this->T += tpoints;
}

ATile * ATree::BuildTile(ATile* prev, int32 type) {
    if (prev != NULL) {
        AttachPoints = prev->GetAttachPoints();
        nexttile = (ATile *)World->SpawnActorDeferred<ATile>(SpawnTile, AttachPoints[0], nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
        if (nexttile)
        {
            nexttile->init(type, prev, this);
            UGameplayStatics::FinishSpawningActor(nexttile, AttachPoints[0]);
        }
    }
    else {
        nexttile = (ATile *)World->SpawnActorDeferred<ATile>(SpawnTile, FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
        if (nexttile)
        {
            nexttile->init(type, prev, this);
            UGameplayStatics::FinishSpawningActor(nexttile, FTransform::Identity);
        }
    }

    current.Empty();
    current.Add(nexttile);
    tail = nexttile;
    return nexttile;
}
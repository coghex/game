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
        head = (ATile *)World->SpawnActorDeferred<ATile>(SpawnTile, FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
        
        if (head)
        {
            head->init(1, NULL);
            UGameplayStatics::FinishSpawningActor(head, FTransform::Identity);
        }
        current.Add(head);
        tail = head;
        
        for (i=0; i<10; i++) {
            AttachPoints = current[0]->GetAttachPoints();
            nexttile = (ATile *)World->SpawnActorDeferred<ATile>(SpawnTile, AttachPoints[0], nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
            if (nexttile)
            {
                nexttile->init(10, current[0]);
                UGameplayStatics::FinishSpawningActor(nexttile, AttachPoints[0]);
            }
            current.Empty();
            current.Add(nexttile);
            tail = nexttile;
        }
    }
}


void ATree::BuildNextTiles() {
    FVector inp = AttachPoints[0].GetLocation();

}

void ATree::BuildTile(ATile* prev, TArray<ATile*> next, int32 type) {

}
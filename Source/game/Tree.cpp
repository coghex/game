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
    AttachPoints.Empty();
    // Create the head
    World = GetWorld();
    if (World) {
        if (level == 0) {
            FVector tempV(0,1,0);
            direction = tempV;
            head = BuildTile(NULL, 1, direction);
            for (i=0; i<10; i++) {
                BuildTile(current[0], 10, direction);
            }
            
            BuildTile(current[0], 2, direction);
        }
        else if (level == 1) {
            FVector tempV(1,0,0);
            direction = tempV;
            head = BuildTile(NULL, 2, direction);
            for (i=0; i<10; i++) {
                if ((rand()%4) > 2) {
                    BuildTile(current[0], 3, direction);
                }
                else {
                    BuildTile(current[0], 10, direction);
                }
            }
            BuildTile(current[0], 1, direction);
        }
    }
}


void ATree::BuildNextTiles() {
    
    AttachPoints = current[0]->GetAttachPoints();
    nexttile = (ATile *)World->SpawnActorDeferred<ATile>(SpawnTile, AttachPoints[0], nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
    if (nexttile)
    {
        //nexttile->init(10, current[0], this);
        UGameplayStatics::FinishSpawningActor(nexttile, AttachPoints[0]);
    }
    current.Empty();
    current.Add(nexttile);
    tail = nexttile;
}

int32 ATree::GetT()
{
    return T;
}

void ATree::AddT(int32 tpoints)
{
    this->T += tpoints;
}

void ATree::BuildWell(ATile * target){
    head->AddWell(100, 100);
}

ATile * ATree::BuildTile(ATile* prev, int32 type, FVector dir) {
    if (prev == NULL) {
        TArray<FTransform> temp;
        
        if (level == 0) {
            temp.Init(FTransform::Identity, 1);
            nextpoint = FTransform::Identity;
            AttachPoints = temp;
        }
        else {
            FVector tempV(800,400,0);
            FTransform tempT(tempV);
            FRotator tempR(0,90,0);
            FQuat tempQ(tempR);
            tempT.SetRotation(tempQ);
            temp.Init(tempT, 1);
            nextpoint = tempT;
            AttachPoints = temp;
        }
    }
    else {
        AttachPoints = prev->GetAttachPoints();
    }
    nexttile = (ATile *)World->SpawnActorDeferred<ATile>(SpawnTile, AttachPoints[0], nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
    if (nexttile)
    {
        FVector tempV(0,0,0);
        rot = direction.Rotation();
        if (type == 3 && prev->Type == 3) {
            type = 10;
        }
        if (level == 0) {
            if (type != 1) {
                tempV += (400*dir);
            }
            else {
                FVector temptempV(400,800,0);
                tempV += temptempV;
            }
        }
        else {
            tempV += (400*dir);
            if (type == 2) {
                FVector temptempV(0,0,0);
                tempV += (temptempV);
            }
            if (type == 3) {
                FRotator tempR(0,90,0);
                tempR += rot;
                direction = (tempR.Vector());
                FVector temptempV(-400,800,0);
                tempV += rot.RotateVector(temptempV);
            }
        }
        rot = direction.Rotation();

        FVector scale(1,1,1);
        FTransform tempT(tempV);
        FRotator tempR(0,90,0);
        nextpoint += tempT;
        nextpoint.SetScale3D(scale);
        FQuat tempQ(rot+tempR);
        nextpoint.SetRotation(tempQ);
        nexttile->init(type, level, NULL, prev, this, nextpoint, SpawnOrb);
        if (prev != NULL) {
            prev->NextTiles.Add(nexttile);
        }
        UGameplayStatics::FinishSpawningActor(nexttile, AttachPoints[0]);
    }

    current.Empty();
    current.Add(nexttile);
    tail = nexttile;
    return nexttile;
}
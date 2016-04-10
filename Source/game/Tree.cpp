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
    int i,j;
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
            head = BuildTile(NULL, 1, direction);
            for (i=0; i<((rand()%10)+length); i++) {
                int rnum = rand()%20;
                if (rnum == 5) {
                    BuildTile(current[0], 3, direction);
                }
                if (rnum == 6) {
                    BuildTile(current[0], 4, direction);
                }
                if (rnum == 7) {
                    BuildTile(current[0], 5, direction);
                    rnum = rand()%4;
                    for (j=0; j<rnum; j++) {
                        BuildTile(current[0], 5, direction);
                    }
                }
                if (rnum == 8) {
                    BuildTile(current[0], 6, direction);
                    rnum = rand()%4;
                    for (j=0; j<rnum; j++) {
                        BuildTile(current[0], 6, direction);
                    }
                }
                if (rnum == 9) {
                    BuildTile(current[0], 7, direction);
                }
                else {
                    BuildTile(current[0], 10, direction);
                }
            }
            BuildTile(current[0], 2, direction);
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
    FTransform nottemp;
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
        if ((type == 5) || (type == 6)) {
            FRotator tempR = direction.Rotation();
            FVector temptempV(direction.Y,-direction.X,0);
            FVector StairElev(0,0,0);
            FRotator StairRot(0,0,0);
            if (type == 5) {
                FRotator temprot(0,0,0);
                FVector tempelev(0,0,-130);
                StairElev = tempelev;
                StairRot = temprot;
            }
            else {
                FRotator temprot(0,180,0);
                FVector tempelev(0,0,0);
                StairElev = tempelev;
                StairRot = temprot;
            }
            FQuat tempQ(tempR + StairRot);
            AttachPoints[0].SetRotation(tempQ);
            if (type == 5) {
                AttachPoints[0].SetLocation((AttachPoints[0].GetLocation())+(StairElev)-(400*temptempV));
            }
            else {
                AttachPoints[0].SetLocation((AttachPoints[0].GetLocation())+(StairElev)-(400*direction));
            }
            FVector scale(1.4,1.4,1);
            AttachPoints[0].SetScale3D(scale);
        }
    }
    if ((type == 5) || (type == 6)) {
        nexttile = (ATile *)World->SpawnActorDeferred<ATile>(StairTile, AttachPoints[0], nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
    }
    else {
        nexttile = (ATile *)World->SpawnActorDeferred<ATile>(SpawnTile, AttachPoints[0], nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
    }
    
    if (nexttile)
    {
        if ((type == 3 && prev->Type == 3) || (type == 4 && prev->Type == 4)) {
            type = 10;
        }
        if (type == 7 && prev->Type == 7) {
            type = rand()%10+1;
        }
        
        FVector tempV(0,0,0);
        FRotator tempR(0,0,0);
        rot = direction.Rotation();
        if (level == 0) {
            if (type == 1) {
                FVector temptempV(400,0,0);
                tempV += temptempV;
            }
            tempV += (400*dir);
        }
        else {
            FRotator temptempR(0,90,0);
            tempR += temptempR;
            if (type == 1) {
                FVector temptempV(0,0,0);
                tempV += (400*dir);
                tempV += (temptempV);
            }
            else if (type == 3) {
                FRotator temptempR(0,90,0);
                temptempR += rot;
                //tempV+=(200*dir);
                direction = (temptempR.Vector());
                tempV+=(800*direction);
                //FVector temptempV(-400,800,0);
                //tempV += rot.RotateVector(temptempV);
            }
            else if (type == 4) {
                FRotator temptempR(0,-90,0);
                temptempR += rot;
                tempV-=(400*direction);
                direction = (temptempR.Vector());
                tempV+=(400*direction);
                //FVector temptempV(-800,-400,0);
                //stempV += rot.RotateVector(temptempV);
            }
            else if (type == 5) {
                FVector StairDown(0,0,-130);
                tempV += (400*direction);
                tempV += StairDown;
            }
            else if (type == 6) {
                FVector StairUp(0,0,130);
                tempV += (400*direction);
                tempV += StairUp;
            }
            else if (type == 7) {
                FVector scale2(1,1,1);
                FRotator temptempR(0,-90,0);
                temptempR += rot;
                tempV-=(400*direction);
                direction = (temptempR.Vector());
                tempV+=(400*direction);
                FTransform tempT2(tempV);
                FQuat tempQ2(direction.Rotation()+tempR);
                tempT2.SetRotation(tempQ2);
                tempT2.SetScale3D(scale2);
                nottemp = tempT2;
                
                FRotator temptemptempR(0,90,0);
                temptempR = temptemptempR + rot;
                tempV-=(1200*direction);
                direction = (temptempR.Vector());
                FVector fudge(direction.Y, -direction.X, 0);
                tempV+=(400*fudge);
            }
            else {
                tempV += (400*dir);
            }
        }
        rot = direction.Rotation();

        FVector scale(1,1,1);
        FTransform tempT(tempV);
        nextpoint += tempT;
        nextpoint.SetScale3D(scale);
        FQuat tempQ(direction.Rotation()+tempR);
        nextpoint.SetRotation(tempQ);
        nexttile->init(type, level, NULL, prev, this, nextpoint, nottemp, SpawnOrb);
        if (prev != NULL) {
            prev->NextTiles.Add(nexttile);
        }
        UGameplayStatics::FinishSpawningActor(nexttile, AttachPoints[0]);
        
//        if (type == 7) {
//            nottemp = nextpoint;
//            fork = (ATree *)World->SpawnActorDeferred<ATree>(ATree::StaticClass(), nottemp, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
//            fork->level = 1;
//            fork->length = 1;
//            FVector fudge(direction.Y, direction.X, 0);
//            fork->direction = fudge;
//            fork->rot = rot;
//            fork->SpawnTile = SpawnTile;
//            fork->StairTile = StairTile;
//            fork->SpawnOrb = SpawnOrb;
//            UGameplayStatics::FinishSpawningActor(fork, nottemp);
//        }
    }

    current.Empty();
    current.Add(nexttile);
    tail = nexttile;
    return nexttile;
}

FTransform ATree::GetLightCoords() {
    FVector tempV(0,0,5);
    FVector temptempV(direction.Y,-direction.X,0);
    tempV += (-200*direction);
    tempV += (-200*temptempV);
    FTransform tempT(tempV);
    return (tempT+nextpoint);
    
    
}
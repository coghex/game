// Fill out your copyright notice in the Description page of Project Settings.

#include "game.h"
#include "Tile.h"


// Sets default values

ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = true;
    BuildTile();
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
    World = GetWorld();
    triggered = false;
    if (Type == 1) {
        DestroyWall(WallBMesh);
        if (Level == 0) {
            AddWell(100,100);
        }
    }
    else if (Type == 10) {
        if (Level == 0) {
            DestroyWall(WallLMesh);
            DestroyWall(WallRMesh);
        }
        else {
            DestroyWall(WallBMesh);
            DestroyWall(WallFMesh);
        }
    }
    else if (Type == 3) {
        DestroyWall(WallFMesh);
        DestroyWall(WallRMesh);
    }
    else if (Type == 4) {
        DestroyWall(WallFMesh);
        DestroyWall(WallLMesh);
    }
    else if (Type == 2) {
        DestroyWall(WallFMesh);
    }
    else if (Type == 5) {
        DestroyWall(WallBMesh);
        DestroyWall(WallFMesh);
    }
}

void ATile::BuildTile()
{
    int32 welllocx = FMath::RandRange(-500, 500);
    int32 welllocy = FMath::RandRange(-1000, 0);
    FVector wellloc(welllocx, welllocy, 0);

    FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
    RootComponent = FloorMesh;
    TopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Top"));
    TopMesh->AttachTo(RootComponent);
    TileTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TileTrigger"));
    TileTrigger->AttachTo(RootComponent);
    WallLMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallL"));
    WallLMesh->AttachTo(RootComponent);
    WallRMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallR"));
    WallRMesh->AttachTo(RootComponent);
    WallFMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallF"));
    WallFMesh->AttachTo(RootComponent);
    WallBMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallB"));
    WallBMesh->AttachTo(RootComponent);

}

void ATile::AddWell(int32 x, int32 y) {
    if (World) {
        FActorSpawnParameters SpawnParams;
        FVector Location(x,y,-50);
        FRotator Rotation;
        AWell* Well = (AWell*)World->SpawnActor<AWell>(SoulWell, Location, Rotation, SpawnParams);
    }
}

void ATile::AddOrb(int32 x, int32 y) {
    if (World) {
        FActorSpawnParameters SpawnParams;
        FVector Location(x,y,0);
        FRotator Rotation;
        AOrb* Orb = (AOrb*)World->SpawnActor<AOrb>(TheOrb, Location, Rotation, SpawnParams);
    }
}

TArray<FTransform> ATile::GetAttachPoints()
{
    return AttachPoints;
}

void ATile::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        if (OtherActor->IsA(APawn::StaticClass()) && (!triggered)) {
            Parent->AddT(1);
            triggered=true;
        }
    }
}

void ATile::init(int32 type, int32 level, ATile * next, ATile * prev, ATree * par, FTransform Location, TSubclassOf<class AOrb> Orb)
{
    this->Type = type;
    this->Parent = par;
    this->Level = level;
    if (next != NULL) {
        this->NextTiles.Add(next);
    }
    if (prev != NULL) {
        this->Prev = prev;
    }
    this->AttachPoints.Add(Location);
}

void ATile::DestroyWall(UObject * ToDestroy)
{
    if (!ToDestroy) return;
    if (!ToDestroy->IsValidLowLevel()) return;

    ToDestroy->ConditionalBeginDestroy();
    ToDestroy = NULL;

    GetWorld()->ForceGarbageCollection(true);
}


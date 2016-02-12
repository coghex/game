// Fill out your copyright notice in the Description page of Project Settings.

#include "game.h"
#include "Tile.h"


// Sets default values

ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = false;
    BuildTile();
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
    if (Type == 1) {
        DestroyWall(WallBMesh);
    }
    else if (Type == 10) {
        DestroyWall(WallBMesh);
        DestroyWall(WallFMesh);
    }
}

void ATile::BuildTile()
{
    int32 welllocx = FMath::RandRange(-500, 500);
    int32 welllocy = FMath::RandRange(-1000, 0);
    FVector wellloc(welllocx, welllocy, 0);

    //TileTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATile::OnOverlapBegin);        // set up a notification for when this component overlaps something
    //TileTrigger->OnComponentEndOverlap.AddDynamic(this, &ATile::OnOverlapEnd);      // set up a notification for when this component overlaps something
    
//    if (Type < 90) {
        FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
        RootComponent = FloorMesh;
        TopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Top"));
        TopMesh->AttachTo(RootComponent);
        TileTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TileTrigger"));
        TileTrigger->AttachTo(RootComponent);
//        
//        AttachPoints;
//        // straight tile
//        if ((Type < 50) && (Type != 0) && (Type != 1)) {
//            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "straight tile");
//            WallLMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallL"));
//            WallLMesh->AttachTo(RootComponent);
//            WallRMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallR"));
//            WallRMesh->AttachTo(RootComponent);
//            FVector tempV(0,-1000,0);
//            FTransform tempT(tempV);
//            AttachPoints.Add(tempT);
//        }
//        // left tile
//        else if (Type >= 50 && Type < 60) {
//            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "left tile");
//            WallRMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallR"));
//            WallRMesh->AttachTo(RootComponent);
//            WallBMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallB"));
//            WallBMesh->AttachTo(RootComponent);
//            FVector tempV(-500,-500,0);
//            FTransform tempT(tempV);
//            AttachPoints.Add(tempT);
//        }
//        // right tile
//        else if (Type >= 60 && Type < 70) {
//            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "right tile");
//            WallLMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallL"));
//            WallLMesh->AttachTo(RootComponent);
//            WallBMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallB"));
//            WallBMesh->AttachTo(RootComponent);
//            FVector tempV(500,-500,0);
//            FTransform tempT(tempV);
//            AttachPoints.Add(tempT);
//        }
//        // fork tile
//        else if (Type >= 70 && Type < 75) {
//            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "fork tile");
//            WallBMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallB"));
//            WallBMesh->AttachTo(RootComponent);
//            FVector tempV1(-500,-500,0);
//            FTransform tempT1(tempV1);
//            AttachPoints.Add(tempT1);
//            FVector tempV2(500,-500,0);
//            FTransform tempT2(tempV2);
//            AttachPoints.Add(tempT2);
//        }
//        // First tile
//        else if (Type == 1) {
//            
//            WallLMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallL"));
//            WallLMesh->AttachTo(RootComponent);
//            WallRMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallR"));
//            WallRMesh->AttachTo(RootComponent);
//            WallFMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallF"));
//            WallFMesh->AttachTo(RootComponent);
//            FVector tempV(0,-1000,0);
//            FTransform tempT(tempV);
//            AttachPoints.Add(tempT);
//        }
//        // Everytile, this is done so UE4 understands all these objects get inherited
//        else if (Type == 0) {
            //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "dont call this");
            WallLMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallL"));
            WallLMesh->AttachTo(RootComponent);
            WallRMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallR"));
            WallRMesh->AttachTo(RootComponent);
            WallFMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallF"));
            WallFMesh->AttachTo(RootComponent);
            WallBMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallB"));
            WallBMesh->AttachTo(RootComponent);
//        }
//        RockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock"));
//        RockMesh->AttachTo(RootComponent);
//    }
//    else {
//        // stairs up tile
//        if (Type < 95) {
//            UpStairMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UStair"));
//            RootComponent = UpStairMesh;
//        }
//        // stairs down tile
//        else {
//            DownStairMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DStair"));
//            RootComponent = DownStairMesh;
//        }
//        WallLMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallL"));
//        WallLMesh->AttachTo(RootComponent);
//        WallRMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallR"));
//        WallRMesh->AttachTo(RootComponent);
//        TopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Top"));
//        TopMesh->AttachTo(RootComponent);
//        
//    }
}

TArray<FTransform> ATile::GetAttachPoints()
{
    return AttachPoints;
}

void ATile::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        if (OtherActor->IsA(APawn::StaticClass())) {
            Type=0;
        }
    }
}

void ATile::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        if (OtherActor->IsA(APawn::StaticClass())) {
            Type=0;
        }
    }
}

void ATile::init(int32 type, ATile * prev)
{
    this->Type = type;
    if (prev != NULL) {
        this->Prev = prev;
        TArray<FTransform> temp = prev->GetAttachPoints();
        FVector tempV(0,400,0);
        FVector scale(1,1,1);
        FTransform tempT(tempV);
        tempT = tempT+temp[0];
        tempT.SetScale3D(scale);
        this->AttachPoints.Add(tempT);
    }
    else {
        FVector tempV(0,400,0);
        FTransform tempT(tempV);
        this->AttachPoints.Add(tempT);
    }
}

void ATile::DestroyWall(UObject * ToDestroy)
{
    if (!ToDestroy) return;
    if (!ToDestroy->IsValidLowLevel()) return;

    ToDestroy->ConditionalBeginDestroy();
    ToDestroy = NULL;

    GetWorld()->ForceGarbageCollection(true);
}


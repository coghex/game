// Fill out your copyright notice in the Description page of Project Settings.

#include "game.h"
#include "Well.h"


// Sets default values
AWell::AWell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    WellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Well"));
    RootComponent = WellMesh;
    CylMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cyl"));
    CylMesh->AttachTo(RootComponent);
    BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block"));
    BlockMesh->AttachTo(RootComponent);
    PitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pit"));
    PitMesh->AttachTo(RootComponent);
    Prompt = CreateDefaultSubobject<UBillboardComponent>(TEXT("Prompt"));
    Prompt->AttachTo(RootComponent);
    
    CylMesh->OnComponentBeginOverlap.AddDynamic(this, &AWell::OnOverlapBegin);        // set up a notification for when this component overlaps something
    CylMesh->OnComponentEndOverlap.AddDynamic(this, &AWell::OnOverlapEnd);      // set up a notification for when this component overlaps something
    Prompt->SetVisibility(false);
    CanDraw = false;
}

// Called when the game starts or when spawned
void AWell::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWell::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        if (OtherActor->IsA(APawn::StaticClass())) {
            Prompt->SetVisibility(true);
            CanDraw = true;
        }
    }
}

void AWell::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        if (OtherActor->IsA(APawn::StaticClass())) {
            Prompt->SetVisibility(false);
            CanDraw = false;
        }
    }
}

void AWell::DrawWell() {
    int32 i;
    struct FTransform relTrans = PitMesh->GetRelativeTransform();
    if (CanDraw) {
        for (i=0; i<100; i++) {
            relTrans.SetLocation(FVector(0.0f, 0.0f, -1.0f));
            PitMesh->SetRelativeTransform(relTrans);
        }
    }
}
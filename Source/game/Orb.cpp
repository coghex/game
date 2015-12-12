// Fill out your copyright notice in the Description page of Project Settings.

#include "game.h"
#include "Orb.h"


// Sets default values
AOrb::AOrb()
{
    DesiredIntensity = 5000.0f;
    Level = 1;
    DesiredColor = FLinearColor(255, 0, 0, .75);
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    
    
    Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
    Sphere->InitSphereRadius(250.0f);
    RootComponent = Sphere;
    
    
    PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
    PointLight->SetIntensity(DesiredIntensity);
    PointLight->SetLightColor(DesiredColor);
    PointLight->SetVisibility(false);
    PointLight->AttachTo(RootComponent);

    OrbMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Orb"));
    OrbMesh->AttachTo(RootComponent);
    StickMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stick"));
    StickMesh->AttachTo(RootComponent);
    
    Prompt = CreateDefaultSubobject<UBillboardComponent>(TEXT("Prompt"));
    Prompt->SetVisibility(false);
    Prompt->AttachTo(RootComponent);
    
    Sphere->OnComponentBeginOverlap.AddDynamic(this, &AOrb::OnOverlapBegin);        // set up a notification for when this component overlaps something
    Sphere->OnComponentEndOverlap.AddDynamic(this, &AOrb::OnOverlapEnd);      // set up a notification for when this component overlaps something
    CanPlayerBlaze = false;
    OrbMesh->SetVisibility(false);
    Multiplier = 1;
}

// Called when the game starts or when spawned
void AOrb::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOrb::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    struct FLinearColor red = FLinearColor(255, 0, 0, .8);
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        if (OtherActor->IsA(APawn::StaticClass())) {
            Prompt->SetVisibility(true);
            CanPlayerBlaze = true;

        }
    }
}

void AOrb::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        if (OtherActor->IsA(APawn::StaticClass())) {
            Prompt->SetVisibility(false);
            CanPlayerBlaze = false;
        }
    }
}


void AOrb::SetLight(struct FLinearColor color, int32 cost)
{
    struct FLinearColor blue = FLinearColor(0,0,255,0.8);
    struct FLinearColor green = FLinearColor(0,225,0,0.8);
    struct FLinearColor purple = FLinearColor(128,0,128,0.8);
    struct FLinearColor orange = FLinearColor(255,100,0,1);
    struct FLinearColor black = FLinearColor(10,10,10,0.2);
    struct FLinearColor white = FLinearColor(255,255,255,1);
    struct FLinearColor darkgreen = FLinearColor(51,102,0,0.2);
    struct FLinearColor yellow = FLinearColor(255,255,10,1);
    
    AGameHUD* currenthud = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
    
    int32 temp;
    int32 playerether = currenthud->GetEther();
    

    if (CanPlayerBlaze && (playerether >= cost)) {
        if (Level == 1) {
            PointLight->SetVisibility(true);
            OrbMesh->SetVisibility(true);
            PointLight->SetLightColor(color);
            PointLight->SetIntensity(500);
        }
        else if (Level == 6) {
            return;
        }
        else {
            PointLight->SetIntensity(500*(Level*Level*Level));
        }
        currenthud->SpendEther(cost);
        Level++;
        
    }
    return;
}
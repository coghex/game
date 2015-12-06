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


void AOrb::SetLight(struct FLinearColor color)
{
    struct FLinearColor blue = FLinearColor(0,0,255,0.8);
    struct FLinearColor green = FLinearColor(0,225,0,0.8);
    struct FLinearColor purple = FLinearColor(128,0,128,0.8);
    struct FLinearColor orange = FLinearColor(255,100,0,1);
    struct FLinearColor black = FLinearColor(10,10,10,0.2);
    struct FLinearColor white = FLinearColor(255,255,255,1);
    struct FLinearColor darkgreen = FLinearColor(51,102,0,0.2);
    struct FLinearColor yellow = FLinearColor(255,255,10,1);
    int32 temp;
    if (CanPlayerBlaze) {
        if (Level == 1) {
            PointLight->SetVisibility(true);
            OrbMesh->SetVisibility(true);
            PointLight->SetLightColor(color);
            PointLight->SetIntensity(500);
            lastcolor = color;
        }
        else if(Level == 6) {
            PointLight->SetLightColor(blue);
            PointLight->SetIntensity(500);
            lastcolor = blue;
            Level = 7;
        }
        else if(Level == 12) {
            PointLight->SetLightColor(green);
            PointLight->SetIntensity(500);
            lastcolor = green;
            Level = 13;
        }
        else if(Level == 18) {
            PointLight->SetLightColor(purple);
            PointLight->SetIntensity(500);
            lastcolor = purple;
            Level = 19;
        }
        else if(Level == 24) {
            PointLight->SetLightColor(orange);
            PointLight->SetIntensity(500);
            lastcolor = orange;
            Level = 25;
        }
        else if(Level == 30) {
            PointLight->SetLightColor(black);
            PointLight->SetIntensity(500);
            lastcolor = black;
            Level = 31;
        }
        else if(Level == 36) {
            PointLight->SetLightColor(white);
            PointLight->SetIntensity(500);
            lastcolor = white;
            Level = 37;
        }
        else if(Level == 42) {
            PointLight->SetLightColor(darkgreen);
            PointLight->SetIntensity(500);
            lastcolor = darkgreen;
            Level = 43;
        }
        else if(Level == 48) {
            PointLight->SetLightColor(yellow);
            PointLight->SetIntensity(500);
            lastcolor = yellow;
            Level = 49;
        }
        else {
            temp = Level%6;
            PointLight->SetLightColor(lastcolor);
            PointLight->SetIntensity((1000*(temp*temp*temp)));
        }
        Level++;
    }
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "game.h"
#include "Orb.h"


// Sets default values
AOrb::AOrb()
{
    DesiredIntensity = 5000.0f;
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
    OrbMesh->SetVisibility(false);
    StickMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stick"));
    StickMesh->AttachTo(RootComponent);
    
    Sphere->OnComponentBeginOverlap.AddDynamic(this, &AOrb::OnOverlapBegin);        // set up a notification for when this component overlaps something
    Sphere->OnComponentEndOverlap.AddDynamic(this, &AOrb::OnOverlapEnd);      // set up a notification for when this component overlaps something
}

// Called when the game starts or when spawned
void AOrb::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOrb::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        if (OtherActor->IsA(APawn::StaticClass())) {
            ToggleLight();
        }
        else {
            OrbMesh->SetVisibility(false);
        }
    }
}

void AOrb::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        if (OtherActor->IsA(APawn::StaticClass())) {
            ToggleLight();
        }
    }
}

void AOrb::ToggleLight()
{
    PointLight->SetVisibility(true);
    OrbMesh->SetVisibility(true);
}
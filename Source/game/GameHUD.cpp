// Fill out your copyright notice in the Description page of Project Settings.

#include "game.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CString.h"
#include "GameHUD.h"

AGameHUD::AGameHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    static ConstructorHelpers::FObjectFinder<UFont>HUDFontOb(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
    HUDFont = HUDFontOb.Object;
}

void AGameHUD::DrawHUD()
{
    FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);
    
    Super::DrawHUD();
    
    FString PowerLevelString = FString::Printf(TEXT("%d"), ether);
    
    DrawText(PowerLevelString, FColor::White, 50, 50, HUDFont);
}
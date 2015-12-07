// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
    AGameHUD(const FObjectInitializer& ObjectInitializer);
    
    UPROPERTY()
    UFont* HUDFont;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    int32 ether;
    
    virtual void DrawHUD() override;
    
    UFUNCTION()
    void SpendEther(int32 amount);
    
    UFUNCTION()
    int32 GetEther();
};

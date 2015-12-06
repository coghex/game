// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Well.generated.h"

UCLASS()
class GAME_API AWell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWell();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    FORCEINLINE class UStaticMeshComponent* GetWellMesh() const {return WellMesh; }
    
private:
    // static mesh components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "well", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* WellMesh;
	
};

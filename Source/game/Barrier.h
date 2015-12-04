// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Barrier.generated.h"

UCLASS()
class GAME_API ABarrier : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABarrier();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    // get mesh
    FORCEINLINE class UStaticMeshComponent* GetMesh() const {return WallMesh; }
	
private:
    // static mesh component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "barrier", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* WallMesh;
    
};

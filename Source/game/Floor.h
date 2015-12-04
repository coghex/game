// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Floor.generated.h"

UCLASS()
class GAME_API AFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    // get mesh
    FORCEINLINE class UStaticMeshComponent* GetMesh() const {return FloorMesh; }
	
private:
    // static mesh component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "floor", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* FloorMesh;
    
};

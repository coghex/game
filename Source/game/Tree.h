// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tile.h"
#include "stdlib.h"
#include "GameFramework/Actor.h"
#include "Tree.generated.h"

UCLASS()
class GAME_API ATree : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATree();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
    UPROPERTY(VisibleAnywhere, Category = "tree")
    int32 numoftiles;
    
    UPROPERTY(VisibleAnywhere, Category = "tree")
    int32 T;
    
    UPROPERTY(VisibleAnywhere, Category = "tree")
    ATile * head;
    
    UPROPERTY(VisibleAnywhere, Category = "tree")
    ATile * nexttile;
    
    UPROPERTY(VisibleAnywhere, Category = "tree")
    UWorld* World;
    
    UPROPERTY(VisibleAnywhere, Category = "tree")
    ATile * tail;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "tree", Meta=(ExposeOnSpawn=true))
    TSubclassOf<class ATile> SpawnTile;
    
    UPROPERTY(VisibleAnywhere, Category = "tree")
    TArray<ATile *> current;
    
    UPROPERTY(VisibleAnywhere, Category = "tree")
    TArray<FTransform> AttachPoints;
    
    UFUNCTION(BlueprintCallable, Category = "tree")
    void BuildNextTiles();
    
    UFUNCTION(BlueprintCallable, Category = "tree")
    void AddT(int32 tpoints);
    
    UFUNCTION(BlueprintCallable, Category = "tree")
    ATile * BuildTile(ATile* prev, int32 type);
};

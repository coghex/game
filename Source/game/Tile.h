// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Well.h"
#include "Orb.h"
#include "Tree.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class GAME_API ATile : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATile();
    
    TSubclassOf<class ATile> TileBlueprint;
    
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    UPROPERTY(VisibleAnywhere, Category = "tile")
    UWorld* World;
    
    UPROPERTY(VisibleAnywhere, Category = "tile")
    bool triggered;
	
    UFUNCTION(BlueprintCallable, Category = "tile")
    void BuildTile();
    
    UFUNCTION(BlueprintCallable, Category = "tile")
    void AddWell(int32 x, int32 y);
    
    UFUNCTION(BlueprintCallable, Category = "tile")
    void AddOrb(int32 x, int32 y);
    
    UFUNCTION(BlueprintCallable, Category = "tile")
    void DestroyWall(UObject * ToDestroy);
    
    UFUNCTION(BlueprintCallable, Category = "tile")
    void init(int32 type, int32 level, ATile * next, ATile * prev, ATree * par, FTransform Location, TSubclassOf<class AOrb> Orb);
    
    UFUNCTION(BlueprintCallable, Category = "tile")
    TArray<FTransform> GetAttachPoints();
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "tile", Meta=(ExposeOnSpawn=true))
    int32 Type;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "tile", Meta=(ExposeOnSpawn=true))
    int32 Level;
    
    UPROPERTY(VisibleAnywhere, Category = "tile")
    TArray<FTransform> AttachPoints;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "tile")
    TArray<ATile *> NextTiles;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "tile")
    ATile * Prev;
    
    UPROPERTY(VisibleAnywhere, Category = "tile")
    ATree * Parent;
    
    UPROPERTY(VisibleAnywhere, Category = "tile")
    struct FTransform RockPoint;
    
    UPROPERTY(VisibleAnywhere, Category = "tile")
    struct FTransform WellPoint;
    
    // static mesh components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "tile", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* FloorMesh;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "tile", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* UpStairMesh;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "tile", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* DownStairMesh;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "tile", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* TopMesh;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "tile", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* WallBMesh;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "tile", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* WallFMesh;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "tile", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* WallLMesh;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "tile", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* WallRMesh;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "tile", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* RockMesh;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "tile", meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* TileTrigger;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "tile", Meta=(ExposeOnSpawn=true))
    TSubclassOf<class AWell> SoulWell;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "tile", Meta=(ExposeOnSpawn=true))
    TSubclassOf<class AOrb> TheOrb;
    
    UFUNCTION(BlueprintCallable, Category = "tile")
    void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};

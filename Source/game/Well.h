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
    FORCEINLINE class UStaticMeshComponent* GetCyllMesh() const {return CylMesh; }
    FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const {return BlockMesh; }
    FORCEINLINE class UStaticMeshComponent* GetPitMesh() const {return PitMesh; }
    
    UFUNCTION()
    void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
    UFUNCTION()
    void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
    
    UPROPERTY()
    bool CanDraw;
    
    UFUNCTION(BlueprintCallable, Category = "orb")
    void DrawWell();
    
    // static mesh components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "well", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* WellMesh;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "well", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* CylMesh;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "well", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* BlockMesh;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "well", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* PitMesh;
    
    UPROPERTY(VisibleAnywhere, category = "well")
    class UBillboardComponent* Prompt;
};

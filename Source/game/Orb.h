// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Orb.generated.h"

UCLASS()
class GAME_API AOrb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrb();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    FORCEINLINE class UStaticMeshComponent* GetStickMesh() const {return StickMesh; }
    
    FORCEINLINE class UStaticMeshComponent* GetOrbMesh() const {return OrbMesh; }
    
    /** the desired intensity for the light */
    UPROPERTY(VisibleAnywhere, Category = "orb")
    float DesiredIntensity;
    
    UPROPERTY(VisibleAnywhere, Category = "orb")
    struct FLinearColor DesiredColor;
    
    /** called when something leaves the sphere component */
    UFUNCTION()
    void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
    
    UFUNCTION(BlueprintCallable, Category = "orb")
    void SetLight(struct FLinearColor color);
    
    UPROPERTY(VisibleAnywhere, Category = "orb")
    bool CanPlayerBlaze;
    
    UPROPERTY(VisibleAnywhere, Category = "orb")
    int32 Level;
    
    UPROPERTY(VisibleAnywhere, Category = "orb")
    struct FLinearColor lastcolor;
    
private:
    
    // static mesh components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "orb", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* OrbMesh;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "orb", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* StickMesh;
	
    UPROPERTY(VisibleAnywhere, Category = "orb")
    class UPointLightComponent* PointLight;
    
    UPROPERTY(VisibleAnywhere, category = "orb")
    class UBillboardComponent* Prompt;
    
    /** sphere component */
    UPROPERTY(VisibleAnywhere, Category = "orb")
    class USphereComponent* Sphere;
    
    /** called when something enters the sphere component */
    UFUNCTION()
    void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
    
    
};

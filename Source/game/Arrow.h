// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Arrow.generated.h"

UCLASS()
class GAME_API AArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArrow();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
    // get arrow component
    FORCEINLINE class UArrowComponent* GetArrow() const {return Arrowpointer; }
    
private:
    // arrow component
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "arrow", meta = (AllowPrivateAccess = "true"))
    class UArrowComponent* Arrowpointer;
	
};

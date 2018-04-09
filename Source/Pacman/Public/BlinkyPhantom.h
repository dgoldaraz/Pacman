// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Phantom.h"
#include "BlinkyPhantom.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API ABlinkyPhantom : public APhantom
{
	GENERATED_BODY()

public:

	//Begin Phantom Interface
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Return a world position (normally a center Tile point) where to go
	virtual FVector GetTargetPosition() override;

	//End Phantom Interface
	
	
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "PacmanPawn.generated.h"

class APacmanActor;

/*
*  Pawn class, only send inputs to the pacman actor
*/

UCLASS()
class PACMAN_API APacmanPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APacmanPawn();

protected:

	void BeginPlay() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	//Player input functions
	void UpInput();
	void DownInput();
	void RightInput();
	void LeftInput();

	void SearchForPlayer();
	
	APacmanActor* PacmanActor = nullptr;
};

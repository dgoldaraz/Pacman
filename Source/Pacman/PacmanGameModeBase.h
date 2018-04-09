// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PacmanGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API APacmanGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


public:

	APacmanGameModeBase();

	//Called when a point is eated, if the point is special, we add more points and start "Frighten Mode"
	void PointEat(bool IsSpecial);

public:

	//Current Total Score
	UPROPERTY(BlueprintReadOnly, Category = "Score")
	float TotalScore = 0.0f;

	//Current Lives
	UPROPERTY(BlueprintReadOnly, Category = "Score")
	int Lives = 3;

	//Initial Lives on Level
	UPROPERTY(EditAnywhere, Category = "Score")
	int InitialLives = 3;

	// Value added to score when one normal point is eaten
	UPROPERTY(EditAnywhere, Category = "Score")
	float NormalPointsValue = 50.0f;

	// Value added to score when one special point is eaten
	UPROPERTY(EditAnywhere, Category = "Score")
	float SpecialPointsValue = 150.0f;

	// Seconds to be on "Eat Mode" for pacman
	UPROPERTY(EditAnywhere, Category = "Score")
	float EatTimeSeconds = 20.0f;

};

// Fill out your copyright notice in the Description page of Project Settings.

#include "PacmanGameModeBase.h"

APacmanGameModeBase::APacmanGameModeBase()
{
	Lives = InitialLives;
}

void APacmanGameModeBase::PointEat(bool IsSpecial)
{
	//Add Points to score,

	
	if (IsSpecial)
	{
		//If is special the pacman can eat phanthom for some time
		TotalScore += SpecialPointsValue;

	}
	else
	{
		TotalScore += NormalPointsValue;
	}
	
}



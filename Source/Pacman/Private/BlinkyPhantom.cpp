// Fill out your copyright notice in the Description page of Project Settings.

#include "BlinkyPhantom.h"

void ABlinkyPhantom::BeginPlay()
{
	Super::BeginPlay();
	CurrentState = EState::Chase;
}

FVector ABlinkyPhantom::GetTargetPosition()
{
	if (Grid)
	{
		if (CurrentState == EState::Chase)
		{
			return Grid->GetGridSpecialPosition(EGridPositions::PlayerPosition);
		}
		else
		{
			return Super::GetTargetPosition();
		}
	}
	return FVector();
}

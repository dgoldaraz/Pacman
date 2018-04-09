// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Point.generated.h"

/*
 Points in the world to increase score
*/
UCLASS()
class PACMAN_API APoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoint();

	void Eat();

	void SetSpecial(bool bSpecial);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Pacman")
	UStaticMeshComponent* PointMesh = nullptr;

	//Special points give more points and ability to eat phantoms
	UPROPERTY(EditAnywhere, Category = "Pacman")
	bool bIsSpecial = false;

	// scale used when point is special
	UPROPERTY(EditAnywhere, Category = "Pacman")
	float SpecialScale= 0.6;

};

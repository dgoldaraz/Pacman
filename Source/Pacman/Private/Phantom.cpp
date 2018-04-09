// Fill out your copyright notice in the Description page of Project Settings.

#include "Phantom.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
APhantom::APhantom()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PhantomMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PhantomMesh"));
	PhantomMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// Set as root component
	RootComponent = PhantomMesh;

	//// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(1.5f);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APhantom::BeginPlay()
{
	Super::BeginPlay();
	//Listen for overlaps
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APhantom::OnOverlap);
}

// Called every frame
void APhantom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Grid)
	{
		//If we arrive cloe enough to the destination, move to position and swap directions (if needed)
		
		int XTileActor, YTileActor = 0;
		Grid->GetTileFromWorld(GetActorLocation(), XTileActor, YTileActor);
		//This is not working properly, as the delta can create a big jump. Check if we are in the tile or not
		if (XTileActor == XTileDestination && YTileActor == YTileDestination)
		{
			//Move actor to destination
			SetActorLocation(Destination);
			//Get next destination and movement
			Destination = Grid->GetNextDestination( GetTargetPosition(), GetActorLocation(), MovementDir, NextMovementDir);
			Grid->GetTileFromWorld(Destination, XTileDestination, YTileDestination);
			//Swap Directions
			MovementDir = NextMovementDir;
		}

		//Move
		FVector NextPosition = GetActorLocation() + (MovementDir * (Speed * SpeedMultiplier * DeltaTime));
		NextPosition.Z = 0;
		SetActorLocation(NextPosition, true);
	}
}

void APhantom::SetGrid(AGrid * NewGrid)
{
	Grid = NewGrid;
	Destination = Grid->GetNextDestination(GetTargetPosition(), GetActorLocation(), MovementDir, NextMovementDir);
	Grid->GetTileFromWorld(Destination, XTileDestination, YTileDestination);
}

void APhantom::ChangeState(EState NewState)
{
	if (NewState != CurrentState)
	{
		//Change Direction
		MovementDir *= -1.0f;
		CurrentState = NewState;
	}
}

void APhantom::OnOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//Deal with Player collision
}

void APhantom::ChangeDirection()
{
	if (Grid)
	{
		MovementDir *= -1.0f;
		Destination = Grid->GetNextDestination(GetTargetPosition(), GetActorLocation(), MovementDir, NextMovementDir);
		Grid->GetTileFromWorld(Destination, XTileDestination, YTileDestination);
	}
}

FVector APhantom::GetTargetPosition()
{
	switch (CurrentState)
	{
	case EState::Chase:
	{
		break;
	}
	case EState::Scatter:
	{
		if (Grid)
		{
			DrawDebugSphere(GetWorld(), Grid->GetGridSpecialPosition(ScatterPosition), 20.0f, 32, FColor::Green, false, 1.0f);
			return Grid->GetGridSpecialPosition(ScatterPosition);
		}
		break;
	}
	case EState::Frightened:
	{
		break;
	}
	default:
		break;
	}
	return FVector();
}

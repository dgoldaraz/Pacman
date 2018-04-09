// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PacmanGrid.generated.h"

class AStaticMeshActor;
class APoint;
class APacmanActor;
class APhantom;

//Direction 
enum class EDirection : uint8
{
	Up,
	Down,
	Left,
	Right,
};

// Special Grid Positions
UENUM(BlueprintType)
enum class EGridPositions : uint8
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
	PlayerPosition
};

//SearchOrder 
enum class ESearchOrder : uint8
{
	MinDistance,
	Random
};


USTRUCT()
struct FTileSelection
{
	GENERATED_USTRUCT_BODY()
	int XTile = 0;
	int YTile = 0;
	FVector TileDirection = FVector(0.0, -1.0f, 0.0f);

	FTileSelection()
	{

	}

	FTileSelection(int NewX, int NewY, FVector NewDir)
	{
		XTile = NewX;
		YTile = NewY;
		TileDirection = NewDir;
	}


	int GetManhattanDistance(int XTargetTile, int YTargetTile)
	{
		return  FMath::Abs(XTargetTile - XTile) + FMath::Abs(YTargetTile - YTile);
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PACMAN_API AGrid : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	AGrid();

	/** Assets to spawn */
	UPROPERTY(EditDefaultsOnly, Category = "Pacman")
	TSubclassOf<AStaticMeshActor> WallClass;

	UPROPERTY(EditDefaultsOnly, Category = "Pacman")
	TSubclassOf<APoint> PointClass;

	UPROPERTY(EditDefaultsOnly, Category = "Pacman")
	TSubclassOf<APacmanActor> PacmanActorClass;

	UPROPERTY(EditDefaultsOnly, Category = "Pacman")
	TArray<TSubclassOf<APhantom>> PhantomClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Pacman")
	int GridScale = 100;

	UFUNCTION(BlueprintCallable, Category = "Pacman")
	APacmanActor* GetPacman() { return PacmanActor; }

	//Return true/false if the movement can be done
	bool CanPlayerMoveInDir(EDirection NewDirection);

	bool CanMoveToTile(const int& XTile, const int& YTile);

	//Function to check if a player can move following the NewDirection
	// the new position that we want to achieve is NewDestination (Normalyy, a center point in the Tile) always
	bool CalculateNewDestination(EDirection NewDirection, FVector& Destination);

	//Return a world position for special cases
	FVector GetGridSpecialPosition(EGridPositions GridChoice);

	// Function that return the next destination 
	// PositionToGo - Position where we want to go in world space
	// CurrentPosition - Current World Positions
	// CurrentDirection - Current Direction of moving
	// NextDirection - Next direction after reaching the destination, the function will change it
	FVector GetNextDestination(const FVector& PositionToGo, const FVector& CurrentPosition, const FVector& CurrentDirection, FVector& NextDirection, ESearchOrder SearchOrder = ESearchOrder::MinDistance);

	// Get Vector direction from EDirection
	FVector GetVectorDirection(const EDirection& NewDirection);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Main Pacman Actor
	APacmanActor* PacmanActor = nullptr;

	//Multiplier to convert from World location to GridLocation
	float Converser = 1.0f;

	//Return the Tile X,Y from a WorldPosition.
	void GetTileFromWorld(const FVector& WorldPosition, int& XTile, int& YTile);

private:
	//Return World Tile center position
	FVector GetWorldFromTile(const int& XTile, const int& YTile);

	//Update the Tile positions on the next direction
	void GetTileInDir(EDirection NextDirection, int& XTile, int& YTile);

	TArray<FTileSelection>GetPossibleTiles(int XTile, int YTile, EDirection CurrentDir);

	EDirection GetDirection(const FVector& Dir);

	TArray<APhantom*> Phantoms;
};

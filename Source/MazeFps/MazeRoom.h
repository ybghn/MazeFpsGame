// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "MazeRoom.generated.h"

UENUM()
enum EWallDirection
{
	Front,Right,Back,Left,NotValid
};
UENUM()
enum EWallStats {
	Wall,
	Way,
	Visited
};
USTRUCT()
struct FWall
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere)
	TEnumAsByte<EWallDirection> direction = EWallDirection::Front;
	UPROPERTY(VisibleAnywhere)
	
	TEnumAsByte<EWallStats> stats = Wall;

};

UCLASS()
class MAZEFPS_API AMazeRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AMazeRoom();
	
	AMazeRoom& operator=(AMazeRoom& copy);
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE FVector2D GetIndex() { return index; }
	void SetIndex(FVector2D _index);
	FORCEINLINE AMazeRoom* GetPrevRoom() { return preRoom; }


	FORCEINLINE void SetPreRoom(AMazeRoom* _preRoom) { preRoom = _preRoom; }
	FORCEINLINE TArray<FWall>&GetWalls() { return walls; }
	FORCEINLINE void SetMeshes(TArray<UStaticMesh*>_meshes);

	void SetWall(EWallDirection direction, EWallStats wallStats);
	
	
	void UpdateDoors();


	FORCEINLINE bool IsVisited() { return isVisited; }
	FORCEINLINE void SetVisited(bool visited = true) { isVisited = visited; }


	FVector2D NeighbourRoom(EWallDirection selectedWall);

	bool HaveEmptyWall();
	EWallDirection PickARandomWall();
protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	UStaticMesh *mesh=nullptr;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* meshComponent_front =nullptr;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* meshComponent_right = nullptr;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* meshComponent_back = nullptr;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* meshComponent_left = nullptr;

	TArray<UStaticMesh*>meshes; //1,2,3,4 doors
	UPROPERTY(VisibleAnywhere)

	TArray<FWall> walls;
	UPROPERTY(VisibleAnywhere)
	FVector2D index;
	AMazeRoom* preRoom = nullptr;
	AMazeRoom* nextRoom = nullptr;

	UPROPERTY(VisibleAnywhere)
	bool isVisited = false;


public:
	void SetNextRoom(AMazeRoom* newRoom);
};

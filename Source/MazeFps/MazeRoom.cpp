// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeRoom.h"

// Sets default values
AMazeRoom::AMazeRoom()
{
	PrimaryActorTick.bCanEverTick = true;

	auto root = CreateDefaultSubobject<USceneComponent>("Root");
	this->SetRootComponent(root);

	meshComponent_front = CreateDefaultSubobject<UStaticMeshComponent>("Mesh_Front");
	meshComponent_front->AttachToComponent(root, FAttachmentTransformRules::KeepRelativeTransform);
	meshComponent_right = CreateDefaultSubobject<UStaticMeshComponent>("Mesh_Right");
	meshComponent_right->AttachToComponent(root, FAttachmentTransformRules::KeepRelativeTransform);
	meshComponent_back = CreateDefaultSubobject<UStaticMeshComponent>("Mesh_Back");
	meshComponent_back->AttachToComponent(root, FAttachmentTransformRules::KeepRelativeTransform);

	meshComponent_left = CreateDefaultSubobject<UStaticMeshComponent>("Mesh_Left");
	meshComponent_left->AttachToComponent(root, FAttachmentTransformRules::KeepRelativeTransform);

	FWall frontWall, backWall, rightWall, leftWall;
	frontWall.direction = Front;
	backWall.direction = Back;
	rightWall.direction = Right;
	leftWall.direction = Left;


	walls.Add(frontWall);
	walls.Add(backWall);
	walls.Add(rightWall);
	walls.Add(leftWall);


	meshComponent_front->SetRelativeLocation(FVector(0, 0, 0));
	meshComponent_right->SetRelativeLocation(FVector(0, 0, 0));
	meshComponent_back->SetRelativeLocation(FVector(0, 0, 0));
	meshComponent_left->SetRelativeLocation(FVector(0, 0, 0));



}

void AMazeRoom::SetIndex(FVector2D _index)
{
	index = _index;
	SetActorLocation(FVector(index.X, index.Y, 0) * 200);
}

void AMazeRoom::SetMeshes(TArray<UStaticMesh*> _meshes)
{
	meshes = _meshes;

}

void AMazeRoom::SetWall(EWallDirection direction, EWallStats wallStats)
{
	
	for (auto &w : walls)
	{
		if (w.direction == direction)
		{
			w.stats = wallStats;
		}
	}



}

void AMazeRoom::UpdateDoors()
{



	if (walls[0].stats != EWallStats::Way)
	{
		meshComponent_front->SetStaticMesh(meshes.Last());
		// (Pitch=0.000000,Yaw=270.000000,Roll=0.000000)
		meshComponent_front->SetRelativeRotation(FRotator(0, 270, 0));

	}
	if (walls[1].stats != EWallStats::Way)
	{
		meshComponent_right->SetStaticMesh(meshes.Last());
		meshComponent_right->SetRelativeRotation(FRotator(0, 0, 0));

		// (Pitch=0.000000,Yaw=0.000000,Roll=0.000000)
	}
	if (walls[2].stats != EWallStats::Way)
	{
		meshComponent_back->SetStaticMesh(meshes.Last());
		meshComponent_back->SetRelativeRotation(FRotator(0, 90, 0));
		// (Pitch=0.000000,Yaw=90.000122,Roll=0.000000)
	}
	if (walls[3].stats != EWallStats::Way)
	{
		meshComponent_left->SetStaticMesh(meshes.Last());
		meshComponent_left->SetRelativeRotation(FRotator(0, 180, 0));
		// (Pitch=0.000000,Yaw=180.000198,Roll=0.000000)
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *this->GetName());
	UE_LOG(LogTemp, Warning, TEXT("%s"), *("Front : " + meshComponent_front->GetRelativeLocation().ToString()));
	UE_LOG(LogTemp, Warning, TEXT("%s"), *("Back : " + meshComponent_back->GetRelativeLocation().ToString()));
	UE_LOG(LogTemp, Warning, TEXT("%s"), *("Right : " + meshComponent_right->GetRelativeLocation().ToString()));
	UE_LOG(LogTemp, Warning, TEXT("%s"), *("Left : " + meshComponent_left->GetRelativeLocation().ToString()));


}

bool AMazeRoom::HaveEmptyWall()
{
	for (auto w :walls) {
		if (w.stats ==EWallStats::Wall) {
			return 1;
		}
	}
	return 0;
}

EWallDirection AMazeRoom::PickARandomWall()
{

	TArray<EWallDirection> tempWallList;

	for (auto w : walls)
	{
		if (w.stats == EWallStats::Wall)
		{
			tempWallList.Push(w.direction.GetValue());
		}
	}

	if (tempWallList.Num() != 0)
	{
		int tempIndex = FMath::RandRange(0, tempWallList.Num()-1);

		return tempWallList[tempIndex];
	}


	return EWallDirection::NotValid;

}

void AMazeRoom::BeginPlay()
{
	Super::BeginPlay();
}


void AMazeRoom::SetNextRoom(AMazeRoom* newRoom)
{
	nextRoom = newRoom;
}

FVector2D AMazeRoom::NeighbourRoom(EWallDirection selectedWall)
{
			
	FVector2D newInd;
	switch (selectedWall) {
	case EWallDirection::Front: {
		newInd = index + FVector2D(0, -1);
		break;
	}
	case EWallDirection::Right: {
		newInd = index + FVector2D(1, 0);
		break;
	}
	case EWallDirection::Back:{
		newInd = index + FVector2D(0, +1);
		break;
	}
	case EWallDirection::Left:

	{
		newInd = index + FVector2D(-1, 0);
		break;
	}
	case EWallDirection::NotValid:
		break;
	}

	return newInd;
}

AMazeRoom& AMazeRoom::operator=(AMazeRoom& copy)
{

	this->index = copy.index;
	this->walls = copy.walls;

	this->preRoom = copy.preRoom;

	return *this;

}

void AMazeRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeCreator.h"



MazeCreator::MazeCreator(int _size, UWorld* _world, TArray<UStaticMesh*>_meshes)
{
	size = _size;
	world = _world;
	meshes = _meshes;

	Create();
	 firstRoomIndex = FVector2D(FMath::RandRange(0, size - 1),FMath::RandRange(0, size - 1));
	AMazeRoom* initialMaze = GetMazeWithIndex(firstRoomIndex);
	initialMaze->SetVisited();
	GoNewRoom(initialMaze);

	for (auto m : maze)
	{
		m->SetMeshes(meshes);
		m->UpdateDoors();
	}
}

MazeCreator::~MazeCreator()
{
}

void MazeCreator::Create()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			AMazeRoom* mazeRoom = Cast<AMazeRoom>(world->SpawnActor(AMazeRoom::StaticClass()));
			//mazeRoom->SetMeshes(meshes);
			mazeRoom->SetIndex(FVector2D(i, j));
			maze.Add(mazeRoom);

		}

	}



}

AMazeRoom* MazeCreator::GetMazeWithIndex(FVector2D _ind)
{
	for (auto m : maze)
	{
		if (m->GetIndex() == _ind)
		{
			return m;
		}
	}
	return nullptr;
}


void MazeCreator::GoNewRoom(AMazeRoom* targetRoom)
{

	if (!targetRoom)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), "Maze Creating is ended because of nullptr");
		return;
	}

	if (!isFirst)
	{

		if (targetRoom->GetIndex() == firstRoomIndex)
		{
			if (!targetRoom->HaveEmptyWall())
			{

				UE_LOG(LogTemp, Warning, TEXT("%s"), "It is returned to starting pos. ");
				return;
			}
		}
	}
	else {
		isFirst = 0;
	}



	EWallDirection selectedWall = targetRoom->PickARandomWall();

	if (selectedWall == EWallDirection::NotValid) {

		GoNewRoom(targetRoom->GetPrevRoom());
		return;
	}


	FVector2D newRoomInd = targetRoom->NeighbourRoom(selectedWall);

	AMazeRoom* newRoom = GetMazeWithIndex(newRoomInd);

	if (newRoom)
	{
		FString newRoomInfo = "Next Room Selected : " + newRoom->GetIndex().ToString();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *newRoomInfo);

		//qDebug() << "Ziyaret Edilmiþ mi ? " << newRoom->IsVisited();

		EWallDirection newDirection = EWallDirection::NotValid;

		if (!newRoom->IsVisited()) {

			targetRoom->SetWall(selectedWall, EWallStats::Way);

			switch (selectedWall) {
			case EWallDirection::Front:
				newDirection = EWallDirection::Back;
				break;
			case EWallDirection::Right:
				newDirection = Left;
				break;
			case Back:
				newDirection = Front;
				break;
			case Left:
				newDirection = Right;
				break;
			case NotValid:
				FString errorText = "There is an unexpected error : " + FString(__FILE__) + " : " + FString::FromInt(__LINE__);
				UE_LOG(LogTemp, Error, TEXT("%s"), *errorText);

				break;

			}

			newRoom->SetWall(newDirection, EWallStats::Way);
			newRoom->SetVisited(1);
			targetRoom->SetNextRoom(newRoom);
			newRoom->SetPreRoom(targetRoom);

			GoNewRoom(newRoom);
			return;

		} // end of room visited control  - if block
		else {

			targetRoom->SetWall(selectedWall, Visited);
			FString wallInfo = "Wall is marked as visited : " +  FString::FromInt(selectedWall);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *wallInfo);

			if (targetRoom->HaveEmptyWall()) {
				GoNewRoom(targetRoom);
				return;
			}
			else {

				GoNewRoom(targetRoom->GetPrevRoom());
				return;
			}

		} // end of visited control 

	}
	else
	{
		targetRoom->SetWall(selectedWall,Visited);
		GoNewRoom(targetRoom);
	}
}
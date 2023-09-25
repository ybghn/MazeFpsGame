// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeRoom.h"
#include "Components/StaticMeshComponent.h"	


class MAZEFPS_API MazeCreator
{
public:
	MazeCreator(int _size,UWorld *_world, TArray<UStaticMesh*>_meshes );
	~MazeCreator();
	virtual void Create();
	TArray<AMazeRoom*> maze;
private:
	int size;
	TArray<UStaticMesh*>meshes; //1,2,3,4 doors
	UWorld* world;
	bool isFirst = 1;
	FVector2D firstRoomIndex;
	AMazeRoom* GetMazeWithIndex(FVector2D _ind);
	void GoNewRoom(AMazeRoom* targetRoom);

};

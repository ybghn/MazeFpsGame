// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "MazeCreator.h"
#include "LevelManager.generated.h"

UCLASS()
class MAZEFPS_API ALevelManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelManager();
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	TArray<AMazeRoom*> maze;
private:	
	UPROPERTY(EditAnywhere)
	TArray<UStaticMesh*>meshes; //1,2,3,4 doors
	UPROPERTY(VisibleAnywhere)
	int mazeSize{ 10 };
	MazeCreator *mazeCreator;
};

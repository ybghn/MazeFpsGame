// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "FpsCharacter.generated.h"

UCLASS()
class MAZEFPS_API AFpsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFpsCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float velocity{ 10 };
	UPROPERTY(Editanywhere)
	float mouseSensivity{4};
	UPROPERTY(Editanywhere)
	int health = 100;
	UPROPERTY(Editanywhere)
	int stamina = 100;

	UPROPERTY(VisibleAnywhere)
	FVector movementDirection;
	APlayerController* playerController;
	UPROPERTY(EditAnywhere)
	UCameraComponent* cameraCompenent;


	void OnForwardAction(float delta);
	void OnRightAction(float delta);



};

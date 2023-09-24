// Fill out your copyright notice in the Description page of Project Settings.


#include "FpsCharacter.h"

AFpsCharacter::AFpsCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	cameraCompenent = CreateDefaultSubobject<UCameraComponent>("Camera");
	cameraCompenent->SetRelativeLocation(FVector(0));
}

void AFpsCharacter::BeginPlay()
{
	Super::BeginPlay();
	playerController = Cast<APlayerController>(GetController());
	if (!playerController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Emerald, "Player Controller Bulunamadý");

	}
	movementDirection = FVector::ZeroVector;

}


void AFpsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!playerController) return;

	float x, y;
	playerController->GetInputMouseDelta(x,y);
	//FString mouseInfo = "X : " + FString::SanitizeFloat(x) + "  y: " + FString::SanitizeFloat(y);
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Emerald, mouseInfo);

	playerController->AddYawInput(x * mouseSensivity);

	auto verticalHeadAngle = cameraCompenent->GetRelativeRotation().Pitch;


	verticalHeadAngle += y * mouseSensivity;
	FMath::ClampAngle(verticalHeadAngle, -70, 70);

	cameraCompenent->SetRelativeRotation(FRotator(verticalHeadAngle, 0, 0));



}

// Called to bind functionality to input
void AFpsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &AFpsCharacter::OnForwardAction);
	PlayerInputComponent->BindAxis("Right", this, &AFpsCharacter::OnRightAction);


}

void AFpsCharacter::OnForwardAction(float delta)
{
	
	GetMovementComponent()->AddInputVector(delta*GetActorForwardVector(), 1);
	


}


void AFpsCharacter::OnRightAction(float delta)
{
	GetMovementComponent()->AddInputVector(delta * GetActorRightVector(), 1);

}

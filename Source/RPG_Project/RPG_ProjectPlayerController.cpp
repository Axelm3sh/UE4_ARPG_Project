// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "RPG_Project.h"
#include "RPG_ProjectPlayerController.h"
#include "RPG_ProjectCharacter.h"
#include "AI/Navigation/NavigationSystem.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Yellow,text)

//Constructor
ARPG_ProjectPlayerController::ARPG_ProjectPlayerController()
{
	bShowMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ARPG_ProjectPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	//Allow us to rotate to mouse cursor (can be set to false I guess for cutscenes?)
	if (bRotateToMouseCursor)
	{
		RotateToMouseCursor();
	}
}

void ARPG_ProjectPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ARPG_ProjectPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ARPG_ProjectPlayerController::MoveToTouchLocation);

	//Movement Axis Binds ("Name of thing in settings", class to call from, Function to call referenced from class)
	InputComponent->BindAxis("MoveForward", this, &ARPG_ProjectPlayerController::MoveForward_XAxis);
	InputComponent->BindAxis("MoveStrafe", this, &ARPG_ProjectPlayerController::MoveStrafe_YAxis);

	//Action Binds
	//TargetMode
	InputComponent->BindAction("Target", IE_Pressed, this, &ARPG_ProjectPlayerController::ToggleTargetMode);

	//Jump
	InputComponent->BindAction("Jump", IE_Pressed, this, &ARPG_ProjectPlayerController::Action_StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ARPG_ProjectPlayerController::Action_StopJump);

}

void ARPG_ProjectPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);

	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ARPG_ProjectPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ARPG_ProjectPlayerController::RotateToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		APawn* const thisControllerPawn = GetPawn();// Get Pawn we wanna rotate

		//Hit.Location(XYZ)- Actor Location(XYZ) to get Vector to look at
		FVector direction = Hit.Location - thisControllerPawn->GetActorLocation();

		//Vector XYZ with Z pointing to ground to compensate for elevation difference (so actor doesn't lean back or forwards)
		direction = FVector(direction.X, direction.Y, 0);

		//X is vector(facing) forward, make a Rotator with degrees pointing in that direction
		FRotator Rot = FRotationMatrix::MakeFromX(direction).Rotator();

		//Set player's new rotation
		SetNewPlayerRotation(Rot);
	}
}

void ARPG_ProjectPlayerController::SetNewPlayerRotation(const FRotator newRotation)
{
	ACharacter *const Character = GetCharacter();

	if (Character)
	{
		Character->SetActorRotation(newRotation);
	}
}

void ARPG_ProjectPlayerController::MoveForward_XAxis(float AxisValue)
{
	ACharacter *const Character = GetCharacter();
	
	if (AxisValue != 0.0)
	{
		if (!bRotateToMouseCursor)
		{
			Character->AddMovementInput(FVector::ForwardVector, AxisValue*100.0f);
		}
		else
		{
			Character->AddMovementInput(FVector::ForwardVector, AxisValue*0.45f);
		}
	}
	
}

void ARPG_ProjectPlayerController::MoveStrafe_YAxis(float AxisValue)
{

	ACharacter *const Character = GetCharacter();

	if (AxisValue != 0.0)
	{
		if (!bRotateToMouseCursor)
		{
			Character->AddMovementInput(FVector::RightVector, AxisValue*100.0f);
		}
		else
		{
			Character->AddMovementInput(FVector::RightVector, AxisValue*0.45f);
		}
		
	}
}

void ARPG_ProjectPlayerController::ToggleTargetMode()
{
	bShowMouseCursor = !bShowMouseCursor;
	bRotateToMouseCursor = !bRotateToMouseCursor;


	if (Role < ROLE_Authority) //Not the Server
	{
		FString printStr = "Toggle State Client: " + FString::FromInt(bShowMouseCursor);
		print(printStr);
		ServerToggleTargetMode();
	}
	else
	{
		FString printStr = "Toggle State Server: " + FString::FromInt(bShowMouseCursor);
		print(printStr);

		ARPG_ProjectCharacter *const Character = Cast<ARPG_ProjectCharacter>(GetCharacter());
		if (Character)
		{
			Character->SetCombatState(bShowMouseCursor);
		}
	}

}

void ARPG_ProjectPlayerController::ServerToggleTargetMode_Implementation()
{
	ARPG_ProjectCharacter *const Character = Cast<ARPG_ProjectCharacter>(GetCharacter());
	if (Character)
	{
		Character->SetCombatState(bShowMouseCursor);
	}
}

bool ARPG_ProjectPlayerController::ServerToggleTargetMode_Validate()
{
	return true;
}

void ARPG_ProjectPlayerController::Action_StartJump()
{
	ACharacter *const Character = GetCharacter();

	if (Character != NULL)
	{
		if (!bRotateToMouseCursor)
		{
			Character->Jump();

		}
	}
}

void ARPG_ProjectPlayerController::Action_StopJump()
{
	ACharacter *const Character = GetCharacter();

	if (Character != NULL)
	{
		if (!bRotateToMouseCursor)
		{
			Character->StopJumping();
		}
	}
}


	

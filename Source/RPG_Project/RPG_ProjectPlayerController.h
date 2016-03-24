// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "RPG_ProjectPlayerController.generated.h"

UCLASS()
class ARPG_ProjectPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARPG_ProjectPlayerController();

protected:
	/** True if the controlled character should rotate to the mouse cursor. */
	bool bRotateToMouseCursor;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	//Touch Support
	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);
	//End Touch Support


	/** Rotates player to current mouse cursor location*/
	void RotateToMouseCursor();

	/** Set Player rotation to mouse cursor location*/
	void SetNewPlayerRotation(const FRotator newRotation);

	/** Input Handlers for Movement */
	void MoveForward_XAxis(float AxisValue);
	void MoveStrafe_YAxis(float AxisValue);

	/** Toggle Targeting Aim Mode*/
	void ToggleTargetMode();

	UFUNCTION(reliable, server, WithValidation)
	void ServerToggleTargetMode();
	virtual void ServerToggleTargetMode_Implementation();
	virtual bool ServerToggleTargetMode_Validate();

	/** Jump Method wrappers*/
	void Action_StartJump();
	void Action_StopJump();
};



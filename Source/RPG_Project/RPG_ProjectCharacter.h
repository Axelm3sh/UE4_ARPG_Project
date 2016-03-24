// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "UnrealNetwork.h"
#include "RPG_ProjectCharacter.generated.h"

UCLASS(Blueprintable)
class ARPG_ProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Custom AnimationInstance to access player state variables for animation control*/
	//class UARPG_Character_AnimInstance* AnimationInstance;

	virtual void BeginPlay();

public:
	ARPG_ProjectCharacter();

	UPROPERTY(Replicated)
	bool bActiveCombat;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Get the AnimInstance Class for this character, Called from BeingPlay*/
	//UARPG_Character_AnimInstance* const ReturnAnimInstance();

	void SetCombatState(bool isActive);

};


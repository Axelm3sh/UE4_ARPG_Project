// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Animation/AnimInstance.h"
#include "RPG_ProjectCharacter.h"
#include "UnrealNetwork.h"
#include "ARPG_Character_AnimInstance.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class RPG_PROJECT_API UARPG_Character_AnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()
	
public:
	//Allow Blueprints to access this variable under Category "Combat Mode" When Using animations
	//Replicated allows syncronization between all clients and server
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Mode", Replicated)
	bool bActiveCombat;

	ARPG_ProjectCharacter * OwningPawn;

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

	//Allows Something to overwrite combat state (cutscenes?)
	void SetActiveCombatState(bool state);
	
	//Replication Call for CombatState
	/**UFUNCTION(reliable, server, WithValidation)
	void ServerToggleAnim_Combat(bool bStateCombat);
	virtual void ServerToggleAnim_Combat_Implementation(bool bStateCombat);
	virtual bool ServerToggleAnim_Combat_Validate(bool bStateCombat);*/

};

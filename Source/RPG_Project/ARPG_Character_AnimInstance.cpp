// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.

#include "RPG_Project.h"
#include "ARPG_Character_AnimInstance.h"

UARPG_Character_AnimInstance::UARPG_Character_AnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//set any default values for your variables here
	bActiveCombat = false;
}

void UARPG_Character_AnimInstance::NativeInitializeAnimation()
{
	//very inportant line
	Super::NativeInitializeAnimation();

	//Try to get Pawn Owner for tick use
	OwningPawn = Cast<ARPG_ProjectCharacter>(TryGetPawnOwner());
}

//Tick
void UARPG_Character_AnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	//Very Important Line
	Super::NativeUpdateAnimation(DeltaTimeX);

	//Always Check Pointers
	if (!OwningPawn)
	{
		return;
	}

	bActiveCombat = OwningPawn->bActiveCombat;
}

/**
//Update Our Animation Instance to get current character combat state
void UARPG_Character_AnimInstance::SetActiveCombatState(bool state)
{
	bActiveCombat = OwningPawn->bActiveCombat;

	// If this next check succeeds, we are *not* the authority, meaning we are a network client.
	// In this case we also want to call the server function to tell it to change the bSomeBool property as well.
	if (OwningPawn->Role < ROLE_Authority)
	{
		ServerToggleAnim_Combat(state);
	}
}

void UARPG_Character_AnimInstance::ServerToggleAnim_Combat_Implementation(bool stateCombat)
{
	//This function is only called on the server (where Role == ROLE_Authority), called over the network by clients.
	//We need to call SetActiveCombatState() to actually change the value of the bool now!
	//Inside that function, Role == ROLE_Authority, so it won't try to call ServerSetSomeBool() again.
	SetActiveCombatState(stateCombat);
}

//Validation Method
bool UARPG_Character_AnimInstance::ServerToggleAnim_Combat_Validate()
{
	return true;
}*/

void UARPG_Character_AnimInstance::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	DOREPLIFETIME(UARPG_Character_AnimInstance, bActiveCombat);//TODO fix client not replicating on server
}


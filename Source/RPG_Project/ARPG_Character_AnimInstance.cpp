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
	OwningPawn = TryGetPawnOwner();
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

	//don't really do anything yet...
	
}

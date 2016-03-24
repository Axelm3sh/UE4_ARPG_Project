// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "RPG_Project.h"
#include "RPG_ProjectCharacter.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Cyan,text)

void ARPG_ProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Store our initial location  
	AnimationInstance = ReturnAnimInstance();
}

ARPG_ProjectCharacter::ARPG_ProjectCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

UARPG_Character_AnimInstance *const ARPG_ProjectCharacter::ReturnAnimInstance()
{
	ARPG_ProjectCharacter *const Actor = Cast<ARPG_ProjectCharacter>(this);

	UARPG_Character_AnimInstance *AnimInst = nullptr;
	if (Actor) 
	{
		TArray<USkeletalMeshComponent*> Components;
		Actor->GetComponents<USkeletalMeshComponent>(Components);
		for (int32 i = 0; i < Components.Num(); i++)
		{
			USkeletalMeshComponent* SkeletalMeshComponent = Components[i];
			

			FString logMsg = SkeletalMeshComponent->GetName();
			print(logMsg);

			AnimInst = Cast<UARPG_Character_AnimInstance>(SkeletalMeshComponent->GetAnimInstance());
		}
	}
	return AnimInst;
}

void ARPG_ProjectCharacter::SetCombatState(bool isActive)
{
	if (AnimationInstance)
	{
		AnimationInstance->bActiveCombat = isActive;
	}
}




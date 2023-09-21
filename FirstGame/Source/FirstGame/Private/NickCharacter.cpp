// Fill out your copyright notice in the Description page of Project Settings.


#include "NickCharacter.h"
//Include the 2 created character components
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
//Only interested in the movement component not the entire character
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ANickCharacter::ANickCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creating 2 components of the created character

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComp->bUsePawnControlRotation = true; //enabled so the camera moves with the mouse
	//Attaching the spring arm to the root of the character, this also acts as the "distance" between the character and the actual camera
	//Root component is the first component within the hierarchy of the character components
	//Has collision checks built in so the camera is never blocked
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");

	//Attaching the camera to the "distance" (spring arm component) between the character and the camera
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ANickCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANickCharacter::MoveForward(float Value)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;

	//AddMovementInput is built into the engine that takes in parameters to directly change the movement of the current "actor"
	AddMovementInput(ControlRotation.Vector(), Value);
}

void ANickCharacter::MoveSideways(float Value)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;

	//need to include the library for access which means slower compilation time in the long run because includes will add up, but this is better for readability
	FVector RightVector = UKismetMathLibrary::GetRightVector(ControlRotation);

	//directly copy/pasting the code from the library which is faster because of no include but is less readable 
	//FVector RightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}

void ANickCharacter::Jump(float Value)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;

	//need to include the library for access which means slower compilation time in the long run because includes will add up, but this is better for readability
	FVector VerticalVector = UKismetMathLibrary::GetUpVector(ControlRotation);

	//directly copy/pasting the code from the library which is faster because of no include but is less readable 
	//FVector RightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);

	AddMovementInput(VerticalVector, Value);
}

// Called every frame
void ANickCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANickCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Create the MoveForward fuction to add forward and backwards movement based on the current vector (+1.0 or -1.0)
	PlayerInputComponent->BindAxis("MoveForward", this, &ANickCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSideways", this, &ANickCharacter::MoveSideways);
	PlayerInputComponent->BindAxis("Jump", this, &ANickCharacter::Jump);

	//Calling a created function within the pawn class to add turning to the character
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "NickCharacter.h"
//Include the 2 created character components
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
//Only interested in the movement component not the entire character
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "NickInteractionComponent.h"

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

	InteractionComp = CreateDefaultSubobject< UNickInteractionComponent>("InteractionComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ANickCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

	//Create the MoveForward function to add forward and backwards movement based on the current vector (+1.0 or -1.0)
	PlayerInputComponent->BindAxis("MoveForward", this, &ANickCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSideways", this, &ANickCharacter::MoveSideways);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ANickCharacter::Jump);

	//Calling a created function within the pawn class to add turning to the character
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ANickCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ANickCharacter::PrimaryInteract);
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

void ANickCharacter::PrimaryAttack()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	//Control rotation is the current direction the character is pointing at
	//Actor location is the center of the current character
	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

	FActorSpawnParameters SpawnParameters;
	//When an actor is spawned into the world, by default it will check the spawn location for any collision and not spawn if there is overlap
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//Spawning actors, need to get the current world first
	//ProjectileClass: Connect to properties within the editor
	//SpawnTM: How to spawn in the new actor (Direction and location)
	//SpawnParameters: Properties for what happens on actor spawn
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParameters);
}

void ANickCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}
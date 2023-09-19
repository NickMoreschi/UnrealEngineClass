// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NickCharacter.generated.h"

//Initilize the 2 classes
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class FIRSTGAME_API ANickCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANickCharacter();

protected:
	//Declare the two components in protected because they wont be needed elsewhere
	//UProperty is an unreal macro that gives it customizability within the GUI in the engine to see the varaibles/properties for the components
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

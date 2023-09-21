// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NickMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class FIRSTGAME_API ANickMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANickMagicProjectile();

protected:
	//basic collision component
	UPROPERTY(visibleAnywhere)
	USphereComponent* SphereComp;

	//can assign velocity to this component to go in a certain direction
	UPROPERTY(visibleAnywhere)
	UProjectileMovementComponent* MovementComp;

	//brings visibility to the component
	UPROPERTY(visibleAnywhere)
	UParticleSystemComponent* EffectComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

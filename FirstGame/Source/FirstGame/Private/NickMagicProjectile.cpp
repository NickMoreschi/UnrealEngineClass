// Fill out your copyright notice in the Description page of Project Settings.

#include "NickMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ANickMagicProjectile::ANickMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetLifeSpan(5);

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile"); //Created custom collision preset in project settings
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject< UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 3000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void ANickMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANickMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "NickInteractionComponent.h"
#include "NickGameplayInterface.h"

// Sets default values for this component's properties
UNickInteractionComponent::UNickInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UNickInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UNickInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UNickInteractionComponent::PrimaryInteract()
{
	FHitResult Hit;
	AActor* MyOwner;
	FVector EyeLocation;
	FRotator EyeRotation;
	FVector End;
	FCollisionObjectQueryParams ObjectQueryParams;

	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	MyOwner = GetOwner(); //Go up all the components and return the RootComponent
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	End = EyeLocation + (EyeRotation.Vector()  * 1000);

	GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams); //Returns what was hit (FHitResult) and populates the "Hit" variable

	AActor* HitActor = Hit.GetActor();
	if (HitActor)
	{
		if (HitActor->Implements<UNickGameplayInterface>())
		{
			APawn* MyPawn = Cast<APawn>(MyOwner);
			INickGameplayInterface::Execute_Interact(HitActor, MyPawn);
		}
	}
}
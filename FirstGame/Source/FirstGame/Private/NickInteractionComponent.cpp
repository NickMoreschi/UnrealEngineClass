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
	AActor* MyOwner;
	FVector EyeLocation;
	FRotator EyeRotation;
	FVector End;
	FCollisionObjectQueryParams ObjectQueryParams;

	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	MyOwner = GetOwner(); //Go up all the components and return the RootComponent
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	End = EyeLocation + (EyeRotation.Vector()  * 1000);

	//FHitResult Hit;
	//GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams); //Returns what was hit (FHitResult) and populates the "Hit" variable

	TArray<FHitResult> Hits;
	FCollisionShape Shape;
	float Radius = 30.0f;
	Shape.SetSphere(Radius);
	
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UNickGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);
				INickGameplayInterface::Execute_Interact(HitActor, MyPawn);
			}
		}

		DrawDebugSphere(GetWorld(), Hit.Location, Radius, 32, LineColor, false, 2.0f);
		break; //if theres more than 1 hit, this will make it so only the first one hit will be interacted with
	}

	DrawDebugLine(GetWorld(), EyeLocation, End, FColor::Red, false, 2.0f, 0, 1.5f);
}
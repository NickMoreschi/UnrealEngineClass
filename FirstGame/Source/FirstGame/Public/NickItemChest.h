// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NickGameplayInterface.h" //include interfaces in the file you are using them
#include "NickItemChest.generated.h" //".generated.h" file includes need to be the last includes in header files

class UStaticMeshComponent;

UCLASS()
class FIRSTGAME_API ANickItemChest : public AActor, public INickGameplayInterface
{
	GENERATED_BODY()

	//Because of UFUNCTION(BlueprintNativeEvent) in the interface header, the "_Implementation" is required by unreal
	//If UFUNCTION wasn't there it would just be "Interact"
	void Interact_Implementation(APawn* InstigatorPawn);

	UPROPERTY(EditAnywhere)
	float TargetPitch;
	
public:	
	// Sets default values for this actor's properties
	ANickItemChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

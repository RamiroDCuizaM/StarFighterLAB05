// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "InventoryActor.generated.h"

/**
 * 
 */
UCLASS()
class STARFIGHTER_API AInventoryActor : public AStaticMeshActor
{
	GENERATED_BODY()

//private:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Datos", meta = (AllowPrivateAccess = "true"))
//	FString InventoryActorName;
public:
	AInventoryActor();

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		float MoveSpeedInventory;

	float MovingAXT;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//funcion que recoge
	virtual void PickUp();

	/* funcion que suelta  y manda un FTRANSFORM = Transformación compuesta de Escala, Rotación(como un cuaternión) y Traslación 
	manda una  variable Ubicacióndelobjetivo */
	virtual void PutDown(FTransform TargetLocation);

	FTimerHandle InvetoryTimerHandle;

	/*FORCEINLINE FString GetInventoryActorName() const { return InventoryActorName; }
	FORCEINLINE void SetInventoryActorName(const FString _InventoryActorName) { InventoryActorName = _InventoryActorName; }*/

	
};

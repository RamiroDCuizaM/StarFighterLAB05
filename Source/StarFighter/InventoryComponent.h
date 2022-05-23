// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryActor.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARFIGHTER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// contenedor vacio que llena objetos de de InventoryActor
	UPROPERTY()
		TArray<AInventoryActor*> CurrentInventory;;
	// Funcion Añadir al inventario

	UFUNCTION()
		int32 AddToInventory(AInventoryActor* ActorToAdd);

	// Funcion Quitar Del Inventario
	UFUNCTION()
		void RemoveFromInventory(AInventoryActor* ActorToRemove);
		
};

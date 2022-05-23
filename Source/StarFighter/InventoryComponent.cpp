// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Establece valores predeterminados para las propiedades de este componente.
UInventoryComponent::UInventoryComponent()
{
	// Configure este componente para que se inicialice cuando comience el juego y para que se marque cada cuadro. Puede convertir estas características
	// Apagado para mejorar el rendimiento si no los necesitas.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Llamado cuando comienza el juego
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Llamado a cada cuadro
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
// Funcion Añadir al inventario
int32 UInventoryComponent::AddToInventory(AInventoryActor* ActorToAdd)
{
	return CurrentInventory.Add(ActorToAdd);
}
//retirar
void UInventoryComponent::RemoveFromInventory(AInventoryActor* ActorToRemove)
{
	CurrentInventory.Remove(ActorToRemove);
}


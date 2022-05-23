// Fill out your copyright notice in the Description page of Project Settings.


#include "Nave.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "UObject/ConstructorHelpers.h"

const FName ANave::MoveForwardBinding("MoveForward");
const FName ANave::MoveRightBinding("MoveRight");
const FName ANave::FireBinding("Fire");

// Sets default values
ANave::ANave()
{
 	// Configure este peón para llamar a Tick() en cada fotograma. Puede desactivarlo para mejorar el rendimiento si no lo necesita.
	PrimaryActorTick.bCanEverTick = true;
	
	// CREAMOS ESTO CON COPY
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Crear el componente de malla
	//CREATEDEFAULTSUBOBJECT Crear un componente o subobjeto, permite crear una clase secundaria y devolver la clase principal.
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	/* El componente que define la transformación(ubicación, rotación, escala)
	de este Actor en el mundo, todos los demás componentes deben adjuntarse a este de alguna manera.*/
	RootComponent = ShipMeshComponent;
	// UCOLLISIONPROFILE Configure y modifique los ajustes de colisión.
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);

	//// Movimiento de Velocidad
	//MoveSpeed = 1000.0f;
	////Energy
	//Energy = 100.0f;

}

// Llamado cuando comienza el juego o cuando se genera
void ANave::BeginPlay()
{
	Super::BeginPlay();
	
}

// Llamado a cada cuadro
void ANave::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Llamado para vincular la funcionalidad a la entrada
void ANave::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


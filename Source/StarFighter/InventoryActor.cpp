// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryActor.h"

AInventoryActor::AInventoryActor():Super()
{
	// Configure este peón para llamar a Tick() en cada fotograma. Puede desactivarlo para mejorar el rendimiento si no lo necesita.
	PrimaryActorTick.bCanEverTick = true;
    // 
	auto MeshAsett = ConstructorHelpers::FObjectFinder<UStaticMesh> (TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (MeshAsett.Object != nullptr) {
		GetStaticMeshComponent()->SetStaticMesh(MeshAsett.Object);
		GetStaticMeshComponent()->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	}
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	SetActorEnableCollision(true);

	InitialLifeSpan = 3.0;

	MoveSpeedInventory = 50;
}
	

void AInventoryActor::BeginPlay()
{
	Super::BeginPlay();
}

void AInventoryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	srand(time(NULL));//toma el tiempo de la computadora y esto hace que no halla randoms iguales

	//MovingAX = rand() % 18 - 10; //random eje X 
	//MovingAY = rand() % 18 - 10; //random eje Y 
	MovingAXT = rand() % -10; //random eje Y 

	const FVector MoveDirection = FVector(-MovingAXT, 0, 0.0f);//formamos un vector direccion con los valores random de X y Y
	const FVector Movement = MoveDirection;

	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();

		FHitResult Hit(1.0f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);


	}
}

void AInventoryActor::PickUp()
{
	// Configure las funciones de marca de este actor para habilitarlas o deshabilitarlas.
	SetActorTickEnabled(false);
	// Establece que el actor se oculte en el juego.
	SetActorHiddenInGame(true);
	// Permite habilitar/deshabilitar la colisión para todo el actor.
	SetActorEnableCollision(false);
}


void AInventoryActor::PutDown(FTransform TargetLocation)
{
	// Configure las funciones de marca de este actor para habilitarlas o deshabilitarlas.
	SetActorTickEnabled(true);
	// Establece que el actor se oculte en el juego.
	SetActorHiddenInGame(false);
	// Permite habilitar/deshabilitar la colisión para todo el actor.
	SetActorEnableCollision(true);
	// Mueve al actor instantáneamente a la ubicación especificada.
	SetActorLocation(TargetLocation.GetLocation());
}

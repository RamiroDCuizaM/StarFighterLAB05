// Copyright Epic Games, Inc. All Rights Reserved.



#include "StarFighterGameModeBase.h"
#include "NaveAcuatica.h"
#include "InventoryActor.h"

int AStarFighterGameModeBase::contadorBalas = 0;

AStarFighterGameModeBase::AStarFighterGameModeBase()
{
	/*UE_LOG(LogTemp, Warning, TEXT("Dentro de constructor en GameModeBase"));
	GetWorld()->SpawnActor<ANaveTerrestreEnemiga01>(FVector::ZeroVector, FRotator::ZeroRotator);*/

	//SpawnNave<ANaveTerrestreEnemiga01>()
}

void AStarFighterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//auto ne = SpawnNave<ANaveTerrestreEnemiga01>();


		//GetWorldTimerManager().SetTimer(AcuaticaTimerHandle, this, &AStarFighterGameModeBase::SpawnNave, 03.0f, true, 2.0f);//cada cierto tiempo creamos una NaveAcuatica extra en el mapa con el SpawnNave

	GetWorldTimerManager().SetTimer(AcuaticaTimerHandle1, this, &AStarFighterGameModeBase::SpawnCapsulas, 02.0f, true, 1.0f);


	SpawnNave();

}

void AStarFighterGameModeBase::SpawnNave()
{
	UE_LOG(LogTemp, Warning, TEXT("aparecio una Naveacuatica"));
	UWorld* const World = GetWorld();


	ejeX = rand() % 2000 + 1;
	ejeY = rand() % 2000 + 1;

	World->SpawnActor<ANaveAcuatica>(FVector(ejeX, ejeY, 112.0f), FRotator::ZeroRotator);//me crea una NaveAcuatica en un cierto lugar aleatorio

}

void AStarFighterGameModeBase::SpawnCapsulas()
{

	UWorld* const World = GetWorld();

	PejeX = rand() % 700 - 500;

	World->SpawnActor<AInventoryActor>(FVector(900, PejeX, 112.0f), FRotator::ZeroRotator);
}

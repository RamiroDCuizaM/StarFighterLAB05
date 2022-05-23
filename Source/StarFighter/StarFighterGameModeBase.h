// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StarFighterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class STARFIGHTER_API AStarFighterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	AStarFighterGameModeBase();//constructor
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;  //lo usaremos al iniciar el juego
	float ejeX; //daremos valores aleatorios 
	float ejeY; //daremos valores aleatorios 

	float PejeX;
	float PejeY;
	float contador;
	FTimerHandle AcuaticaTimerHandle;
	FTimerHandle AcuaticaTimerHandle1;
public:
	static int contadorBalas;

	void SpawnNave();//funcionque hara aparecer una nave en en el mapa
	void SpawnCapsulas();
};

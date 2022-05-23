// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nave.h"
#include "NaveAcuatica.generated.h"

/**
 * 
 */
UCLASS()
class STARFIGHTER_API ANaveAcuatica : public ANave
{
	GENERATED_BODY()
private:

	//===================================================================================================================================================================
	ANaveAcuatica();

	uint32 bCanFire : 1;
	FTimerHandle TimerHandle_ShotTimerExpired; //tiempo que toma de la PC
	FTimerHandle MemberTimerHandle; //caracteristica que usaremos en el BeginPlay
	FTimerHandle MemberTimerHandle1;
public:
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		FVector GunOffset;//es como la distancia que aparecera la proyectil.
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		float FireRate; //propiedad que hara cuanto tardara en desaparecer el proyectil.
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		float MoveSpeedAcuatica; //sera la velocidad usada por la NaveAccuatica

	float MovingAX; //Movimiento que le daremos un valor aleatorio para el eje X
	float MovingAY; //Movimiento que le daremos un valor aleatorio para el eje Y
	//

public:

	virtual void BeginPlay() override;

	void Tick(float DeltaSeconds); //funcion que se actualizara cada frame

	void FireAcuatica(); //funcion que llamara a FireShotAcuatica
	void FireShotAcuatica(FVector FireDirectionEnemigo); //Funcion que tiene la finalidad de disparar un proyectil


	void ShotTimerExpired();

public:
	UFUNCTION()
		virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal,
			FVector NormalImpulse, const FHitResult& Hit)override;//esta funcion nos notifica cada golpe que de la clase.
	TMap<FString, int32>AcuaticaInfo;
	//float Contador;

	void CuentaBalas();
	void MuestraCuentaBalas();
	
};

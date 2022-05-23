// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveAerea.h"
#include "InventoryComponent.h"
#include "NaveAereaJugador.generated.h"

/**
 * 
 */
UCLASS()
class STARFIGHTER_API ANaveAereaJugador : public ANaveAerea
{
	GENERATED_BODY()
	
	/* la camara */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/* El auge de la cámara coloca la cámara sobre el personaje. ()*/
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Datos", meta = (AllowPrivateAccess = "true")) //Blueprint que podemos asignarle un "Dato" en este caso su vida
		FString NaveActorName;

private:

	///* Bandera para controlar disparos  */
	//uint32 bCanFire : 1;

	///** Mango para una gestión eficiente del temporizador ShotTimerExpired */
	//FTimerHandle TimerHandle_ShotTimerExpired;

	//// valor de avance de fuego
	//float FireForwardValue;
	//// valor correcto de fuego
	//float FireRightValue;

public:
	ANaveAereaJugador();

	// Llamado a cada cuadro
	void Tick(float DeltaSeconds);

	// Llamado para vincular la funcionalidad a la entrada
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Fuego
	void Fire();

	/* Dispara un tiro en la dirección especificada */
	void Fireshot(FVector FireDirection);

	/* Manejador para el vencimiento del temporizador de incendio */
	void ShotTimerExpired();

	/** Desplazamiento desde la ubicación de los barcos para generar proyectiles. (disparo)*/
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		FVector GunOffset;

	/* Qué tan rápido disparará el arma (velocidad de fuego) */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FireRate;

	UPROPERTY()
		UInventoryComponent* ShipInventory;

	// tomar artículo
	UFUNCTION()
		void TakeItem(AInventoryActor* InventoryItem);

	// soltar articulo
	UFUNCTION()
		void DropItem();

	// Evento cuando este actor choca contra un objeto bloqueador, o bloquea a otro actor que choca contra él.
	UFUNCTION()
		virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
			bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	//// mostrar inventario
	//UFUNCTION()
	//	void ShowInventory();

	/** Devuelve el subobjeto CameraComponent **/
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	/** Devuelve el subobjeto CameraBoom **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	float Vida; //vida usada para la nave jugador
	uint32 bCanFire : 1;

	FTimerHandle TimerHandle_ShotTimerExpired;

	float FireForwardValue; //valores aleatorios
	float FireRightValue;   //valores aleatorios

	TMap<FString, int32>NaveInfo; //almacenara los datos y valores de mi NaveJgador
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Proyectil.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS()
class STARFIGHTER_API AProyectil : public AActor
{
	GENERATED_BODY()
	
	/** Componente de colisión de esfera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectil", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	/** ProjectileMovementComponent actualiza la posición de otro componente durante su marca. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

public:	
	// Establece valores predeterminados para las propiedades de este actor
	AProyectil();

	/** Función para manejar el proyectil golpeando algo. */
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Devuelve el subobjeto ProjectileMesh **/
	FORCEINLINE UStaticMeshComponent* GetProjectileMesh() const { return ProjectileMesh; }
	/** Devuelve el subobjeto ProjectileMovement **/
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

protected:
	// Llamado cuando comienza el juego o cuando se genera
	virtual void BeginPlay() override;

public:	
	// Llamado a cada cuadro
	virtual void Tick(float DeltaTime) override;

};

// Complete su aviso de derechos de autor en la página Descripción de Configuración del proyecto.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Nave.generated.h"

UCLASS()
class STARFIGHTER_API ANave : public APawn
{
	GENERATED_BODY()
		/* El componente de malla de la nave*/
		UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ShipMeshComponent;

public:
	// Establece valores predeterminados para las propiedades de este peón
	ANave();
	
	/* La velocidad con la que nuestra nave se mueve por el nivel. */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;

	/* El barco de la energía */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float Energy;

	 /** Sonido para jugar cada vez que disparamos */
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* FireSound;


	//variable estatica avanzar vinculante
	static const FName MoveForwardBinding;
	//variable estatica derecha e izquierda
	static const FName MoveRightBinding;
	
	static const FName FireBinding;

protected:
	// Llamado cuando comienza el juego o cuando se genera
	virtual void BeginPlay() override;

public:	
	// Llamado a cada cuadro
	virtual void Tick(float DeltaTime) override;

	// Llamado para vincular la funcionalidad a la entrada
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	/** Devuelve el subobjeto ShipMeshComponent **/
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
	FORCEINLINE void SetShipMeshComponent(class UStaticMeshComponent* _ShipMeshComponent) { ShipMeshComponent = _ShipMeshComponent; }

};

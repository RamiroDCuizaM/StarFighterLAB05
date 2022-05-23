// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveAereaJugador.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Proyectil.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PrimitiveComponent.h"
#include "Fusil.h"
#include "Engine/World.h"
#include "StarFighterGameModeBase.h"

ANaveAereaJugador::ANaveAereaJugador()
{
	//// Guarda en caché nuestro efecto de sonido
	//static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	//FireSound = FireAudio.Object;

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));

	// Crea un boom de cámara...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Crea una Camara.
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	//Inventario
	ShipInventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Ship Inventory"));

	// Arma
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = false;
	FireForwardValue = 1.0f;
	FireRightValue = 0.0f;

	NaveInfo.Add("Vida", 100); //iniciamos con un dato de vida en 100
	Vida = 100;//mi valor de vida sera 100
	NaveInfo.Add("velocidad", 1000);
}



void ANaveAereaJugador::Tick(float DeltaSeconds)
{
	//UE_LOG(LogTemp, Warning, TEXT("Presione una Tecla %f"), DeltaSeconds);
	
	// Encuentra la dirección del movimiento
	// GetInputAxisValue -> Obtiene el valor del eje de entrada si la entrada está habilitada para este actor
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	if (ForwardValue != 0.0f || RightValue != 0.0f) {
		if (ForwardValue != FireForwardValue) {
			FireForwardValue = ForwardValue;
		}
		if (RightValue != FireRightValue) {
			FireRightValue = RightValue;
		}
	}

	// Sujete el tamaño máximo para que (X = 1, Y = 1) no provoque un movimiento más rápido en direcciones diagonales
	// GetClampedToMaxSize -> Cree una copia de este vector, con su magnitud máxima sujeta a MaxSize.
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calcular movimiento
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	// Si no es de tamaño cero, mueve a este autor
	if (Movement.SizeSquared() > 0.0f){
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);

		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}

	// Create fire direction vector
	//const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	//const float FireRightValue = GetInputAxisValue(FireRightBinding);
	//const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f);

	// Intenta disparar un tiro
	//FireShot(FireDirection);

}

void ANaveAereaJugador::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ANaveAereaJugador::Fire);
	PlayerInputComponent->BindAction(TEXT("DropItem"), IE_Pressed, this, &ANaveAereaJugador::DropItem);
    //PlayerInputComponent->BindAction(TEXT("ShowInventory"), IE_Pressed, this, &ANaveAereaJugador::ShowInventory);
	
}


void ANaveAereaJugador::Fire() {

	bCanFire = true;
	UE_LOG(LogTemp, Warning, TEXT("Se presiono la barra espaciadora"));
	// Create fire direction vector

	UE_LOG(LogTemp, Warning, TEXT("FireForwardValue: %f FireRightValue: %f"), FireForwardValue, FireRightValue);
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f).GetClampedToMaxSize(1.0f);
	//const FVector FireDirection = GetActorLocation();
	// Try and fire a shot
	Fireshot(FireDirection);

}

void ANaveAereaJugador::Fireshot(FVector FireDirection)
{
	// Si está bien disparar de nuevo
	if (bCanFire == true)
	{
		// Si estamos presionando el palo de fuego en una dirección
		/*if (FireDirection.SizeSquared() > 0.0f)
		{*/
			const FRotator FireRotation = FireDirection.Rotation();
			// Proyectil de generación en un desplazamiento de este peón
			const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				// generar el proyectil
				World->SpawnActor<AProyectil>(SpawnLocation, FireRotation);
				AStarFighterGameModeBase::contadorBalas++;
				GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("numero balas: %d"), AStarFighterGameModeBase::contadorBalas));//mostramos en pantalla la cantidad de vida
			//UE_LOG(LogTemp, Warning, TEXT("SpawnLocation(X, Y) = %s, %s FireRotation(X, Y) =  s, s"), SpawnLocation.X, SpawnLocation.Y);
			//UE_LOG(LogTemp, Warning, TEXT("World not nullptr"));
			}

			//bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ANaveAereaJugador::ShotTimerExpired, FireRate);

			// intente reproducir el sonido si se especifica
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			bCanFire = false;
		//}
	}
}

void ANaveAereaJugador::ShotTimerExpired()
{
	bCanFire = true;
}

void ANaveAereaJugador::TakeItem(AInventoryActor* InventoryItem)
{
	InventoryItem->PickUp();
	ShipInventory->AddToInventory(InventoryItem);
}

void ANaveAereaJugador::DropItem()
{
	if(ShipInventory->CurrentInventory.Num()==0) {
		return;
	}

	AInventoryActor* Item = ShipInventory->CurrentInventory.Last();
	ShipInventory->RemoveFromInventory(Item);

	FVector ItemOrigin;
	FVector ItemBounds;
	Item->GetActorBounds(false, ItemOrigin, ItemBounds);
	FTransform PutDownLocation = GetTransform() + FTransform(RootComponent->GetForwardVector() * ItemBounds.GetMax());
	Item->PutDown(PutDownLocation);

}

void ANaveAereaJugador::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	AInventoryActor* InventoryItem = Cast<AInventoryActor>(Other);
	if (InventoryItem != nullptr)
	{
		TakeItem(InventoryItem);

		if (InventoryItem != nullptr)
		{
			int n = rand() % 6 + 1;

			switch (n)
			{
			case 1:
			{

				for (auto& Elem : NaveInfo) //usando los datos de la nave
				{
					GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%s = %d"), *Elem.Key, Elem.Value));//mostramos en pantalla la cantidad de vida
				}

				FString nV = "Velocidad";
				for (auto& pair : NaveInfo)
				{
					if (pair.Key == nV)
					{
						if (pair.Value > 0)
						{
							pair.Value = pair.Value + 1000;
							MoveSpeed = MoveSpeed + 1000;

						}



					}
				}
			}
			break;
			case 2:
			{

				for (auto& Elem : NaveInfo) //usando los datos de la nave
				{
					GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%s = %d"), *Elem.Key, Elem.Value));//mostramos en pantalla la cantidad de vida
				}

				FString nV = "Velocidad";
				for (auto& pair : NaveInfo)
				{
					if (pair.Key == nV)
					{
						if (pair.Value > 0)
						{
							pair.Value = pair.Value - 50;
							MoveSpeed = MoveSpeed - 50;
						}



					}
				}
			}
			break;
			case 3:
			{

				for (auto& Elem : NaveInfo) //usando los datos de la nave
				{
					GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%s = %d"), *Elem.Key, Elem.Value));//mostramos en pantalla la cantidad de vida
				}

				FString nVD = "Vida";
				for (auto& pair : NaveInfo)
				{
					if (pair.Key == nVD)
					{
						if (pair.Value > 0)
						{
							pair.Value = pair.Value + 10;

							Vida = Vida + 10; //reducir la vida de 10 en 10 al recibir un impacto
						}

					

					}
				}
			}
			break;
			case 4:
			{

				for (auto& Elem : NaveInfo) //usando los datos de la nave
				{
					GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%s = %d"), *Elem.Key, Elem.Value));//mostramos en pantalla la cantidad de vida
				}

				FString nNV = "Vida";
				for (auto& pair : NaveInfo)
				{
					if (pair.Key == nNV)
					{
						if (pair.Value > 0)
						{
							pair.Value = pair.Value - 10;

							Vida = Vida - 10; //reducir la vida de 10 en 10 al recibir un impacto

							if (Vida == 0) //si mi vida es igual a 0, entonces mi NaveJugador desaparece.
							{


								SetActorTickEnabled(false);
								SetActorHiddenInGame(true);
								SetActorEnableCollision(false);
							}
							break;
						}



					}
				}
			}
			break;
			case 5:
			{
				UE_LOG(LogTemp, Warning, TEXT("balazos"));

				ANaveAereaJugador* avatar = Cast<ANaveAereaJugador>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)); //obtiene la ubicacion de mi Pawn o NaveJugador
				if (!avatar)
				{
					return;

				}
				FVector toPlayerT = avatar->GetActorLocation() - GetActorLocation();

				UWorld* const World = GetWorld();
				World->SpawnActor<AFusil>(toPlayerT + FVector(100, 100, 0), FRotator::ZeroRotator);

			}
			break;
			default:
				break;
			}

		}


	}




	AProyectil* Choque = Cast<AProyectil>(Other);//cada vez que un Proyectil nos haga contacto, hara la siguiente funcion
	if (Choque != nullptr)
	{
		for (auto& Elem : NaveInfo) //usando los datos de la nave
		{
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%s = %d"), *Elem.Key, Elem.Value));//mostramos en pantalla la cantidad de vida
		}

		FString n = "Vida";
		for (auto& pair : NaveInfo)
		{
			if (pair.Key == n)
			{
				if (pair.Value >= 0)
				{
					pair.Value = pair.Value - 10;

					Vida = Vida - 10; //reducir la vida de 10 en 10 al recibir un impacto

					if (Vida == 0) //si mi vida es igual a 0, entonces mi NaveJugador desaparece.
					{

						SetActorTickEnabled(false);
						SetActorHiddenInGame(true);
						SetActorEnableCollision(false);
					}
					break;
				}



			}
		}

	}


}

//void ANaveAereaJugador::ShowInventory() {
//	for (int32 i = 0; i < ShipInventory->ShipInventoryActor.Num(); i++) {
//		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("Actor de Nombre: %s"),
//			*(ShipInventory->ShipInventoryActor[i]->GetInventoryActorName())));
//	}
//}
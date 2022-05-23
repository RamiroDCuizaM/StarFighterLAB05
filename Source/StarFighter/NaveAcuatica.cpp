// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveAcuatica.h"
#include "NaveAereaJugador.h"
#include "Kismet/GameplayStatics.h"
#include "Proyectil.h"
#include "StarFighterGameModeBase.h"

ANaveAcuatica::ANaveAcuatica()
{
	MoveSpeedAcuatica = 50.0f; //para la velocidad
	GunOffset = FVector(90.f, 0.f, 0.f); //para la distancia de aparicion de la bala
	FireRate = 2.0f;
	bCanFire = true;

	MovingAX = 0.0f;
	MovingAY = 0.0f;

	AcuaticaInfo.Add("Disparo", 0);
}

void ANaveAcuatica::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ANaveAcuatica::FireAcuatica, 01.0f, true, 0.0f);//hara la funcion de disparo cada tiempo determinado.

	GetWorldTimerManager().SetTimer(MemberTimerHandle1, this, &ANaveAcuatica::MuestraCuentaBalas, 60.0f, true, 60);//mostrara los disparos en 60 segundos

}

void ANaveAcuatica::Tick(float DeltaSeconds)
{

	srand(time(NULL));//toma el tiempo de la computadora y esto hace que no halla randoms iguales

	MovingAX = rand() % 18 - 10; //random eje X 
	MovingAY = rand() % 18 - 10; //random eje Y 

	const FVector MoveDirection = FVector(MovingAX, MovingAY, 0.0f);//formamos un vector direccion con los valores random de X y Y
	const FVector Movement = MoveDirection * MoveSpeedAcuatica * DeltaSeconds;

	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();

		FHitResult Hit(1.0f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
	}

	ANaveAereaJugador* avatar = Cast<ANaveAereaJugador>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)); //obtiene la ubicacion de mi Pawn o NaveJugador
	if (!avatar)
	{
		return;

	}
	FVector toPlayer = avatar->GetActorLocation() - GetActorLocation();
	toPlayer.Normalize();

	FRotator toPlayerRotation = toPlayer.Rotation(); //unimos el vector que apunta al jugador con una rotacion
	toPlayerRotation.Pitch = 0;
	RootComponent->SetWorldRotation(toPlayerRotation);


}

void ANaveAcuatica::FireAcuatica()
{
	bCanFire = true;
	const FVector FireDirectionAcuatica = FVector(MovingAX, MovingAY, 0.0f).GetClampedToMaxSize(1.0f); //vector que toma valores de NaveAcuatica

	FireShotAcuatica(FireDirectionAcuatica); //llamamos a la funcion FireShot

	CuentaBalas();
}

void ANaveAcuatica::FireShotAcuatica(FVector FireDirectionAcuatica)
{
	if (bCanFire == true)
	{
		if (FireDirectionAcuatica.SizeSquared() > 0.0f)
		{
			ANaveAereaJugador* avatar = Cast<ANaveAereaJugador>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));//obtenemos la ubicacion de la naveJugador
			if (!avatar)
			{
				return;

			}
			FVector toPlayer = avatar->GetActorLocation() - GetActorLocation();

			const FRotator FireRotation = toPlayer.Rotation(); //unimos el vector que apunta al jugador con una rotacion
			const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				World->SpawnActor<AProyectil>(SpawnLocation, FireRotation);
			}

			bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ANaveAcuatica::ShotTimerExpired, FireRate);//funcion que hace desaparecer la bala en un tiempo

		}
	}

}

void ANaveAcuatica::ShotTimerExpired()
{
	bCanFire = true;
}

void ANaveAcuatica::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	AProyectil* Choque = Cast<AProyectil>(Other); //solo en caso de que choque con un proyectil sera ejecutada la funcion de Destroy()
	if (Choque != nullptr)
	{

		Destroy();

	}
}

void ANaveAcuatica::CuentaBalas()
{
	FString VT = "Disparo";
	for (auto& pair : AcuaticaInfo)
	{
		if (pair.Key == VT)
		{
			if (pair.Value >= 0)
			{
				pair.Value = pair.Value + 1;

			}
		}
	}

}

void ANaveAcuatica::MuestraCuentaBalas()
{
	for (auto& Elem : AcuaticaInfo)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%s = %d"), *Elem.Key, Elem.Value));//mostramos en pantalla la cantidad de vida
	}

}

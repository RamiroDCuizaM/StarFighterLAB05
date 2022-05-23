// Fill out your copyright notice in the Description page of Project Settings.


#include "Fusil.h"
#include "Proyectil.h"
#include "NaveAereaJugador.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFusil::AFusil()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MetralletaMeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));

	FusilMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MetralletaMesh0"));
	FusilMesh->SetStaticMesh(MetralletaMeshAsset.Object);
	FusilMesh->SetupAttachment(RootComponent);
	FusilMesh->BodyInstance.SetCollisionProfileName("MetralletaMesh");

	RootComponent = FusilMesh;
	MoveSpeedFusil = 1000;
}

// Called when the game starts or when spawned
void AFusil::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AFusil::FireFusil, 02.0f, true, 3.0f);

}

// Called every frame
void AFusil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ANaveAereaJugador* avatar = Cast<ANaveAereaJugador>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)); //obtiene la ubicacion de mi Pawn o NaveJugador
	if (!avatar)
	{
		return;

	}
	FVector toPlayerR = avatar->GetActorLocation() - GetActorLocation() + FVector(200, 200, 0);
	toPlayerR.Normalize();

	const FVector Movement = toPlayerR * MoveSpeedFusil * DeltaTime;

	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = FRotator::ZeroRotator;

		FHitResult Hit(1.0f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
	}
}

void AFusil::FireFusil()
{
	ANaveAereaJugador* avatar = Cast<ANaveAereaJugador>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)); //obtiene la ubicacion de mi Pawn o NaveJugador
	if (!avatar)
	{
		return;

	}
	FVector toPlayer = avatar->GetActorLocation() - GetActorLocation();
	toPlayer.Normalize();

	bCanFire = true;
	const FVector FireDirectionFusil = toPlayer.GetClampedToMaxSize(1.0f) + FVector(90, 0, 0); //vector que toma valores de NaveAcuatica


	FireShotFusil(FireDirectionFusil); //llamamos a la funcion FireShot
}

void AFusil::FireShotFusil(FVector FireDirectionFusil)
{
	if (bCanFire == true)
	{
		const FRotator FireRotation = FireDirectionFusil.Rotation();

		const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != nullptr)
		{

			World->SpawnActor<AProyectil>(SpawnLocation, FireRotation);

		}
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AFusil::ShotTimerExpired, FireRate);
		bCanFire = false;

	}

}

void AFusil::ShotTimerExpired()
{
	bCanFire = true;
}


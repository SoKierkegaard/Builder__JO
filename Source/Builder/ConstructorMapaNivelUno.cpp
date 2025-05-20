// Fill out your copyright notice in the Description page of Project Settings.

#include "MapaDelJuego.h"
#include "ConstructorMapaNivelUno.h"
#include "BloqueMuro.h"
#include "BloquePiedra.h"
#include "BloqueTransparente.h"
#include "PuertaNivel.h"
#include "Puente.h"
#include "PowerUpBloque.h"


// Sets default values
AConstructorMapaNivelUno::AConstructorMapaNivelUno()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AConstructorMapaNivelUno::BeginPlay()
{
	Super::BeginPlay();

	MapaEnConstruccion = GetWorld()->SpawnActor<AMapaDelJuego>(AMapaDelJuego::StaticClass());
}

// Called every frame
void AConstructorMapaNivelUno::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AConstructorMapaNivelUno::IniciarNuevoMapa()
{
	if (MapaEnConstruccion) {
		for (int32 i = 0; i < MapaEnConstruccion->aMapaBloques.Num(); i++)
		{
			for (int32 j = 0; j < MapaEnConstruccion->aMapaBloques[i].Num(); j++)
			{
				int32 BlockType = MapaEnConstruccion->aMapaBloques[i][j];
				if (BlockType != 0) {
					MapaEnConstruccion->aMapaBloques[i][j] = 0;
				}
			}
		}
	}
}

void AConstructorMapaNivelUno::ConstruirBloqueMuro()
{
	if (MapaEnConstruccion)
	{
		for (int32 i = 0; i < MapaEnConstruccion->aBloqueMuro.Num(); i++)
		{
			for (int32 j = 0; j < MapaEnConstruccion->aBloqueMuro[i].Num(); j++)
			{
				int32 BlockType = MapaEnConstruccion->aBloqueMuro[i][j];
				if (BlockType == 1) {
					GetWorld()->SpawnActor<ABloqueMuro>(
						ABloqueMuro::StaticClass(),
						FVector(MapaEnConstruccion->XInicial + i * 100, MapaEnConstruccion->YInicial + j * 100, MapaEnConstruccion->ZInicial),
						FRotator::ZeroRotator);
				}
			}
		}
	}
}

void AConstructorMapaNivelUno::ConstruirBloquePiedra()
{
	if (MapaEnConstruccion)
	{
		for (int32 i = 0; i < MapaEnConstruccion->aBloquePiedra.Num(); i++)
		{
			for (int32 j = 0; j < MapaEnConstruccion->aBloquePiedra[i].Num(); j++)
			{
				int32 BlockType = MapaEnConstruccion->aBloquePiedra[i][j];
				if (BlockType == 2) {
					GetWorld()->SpawnActor<ABloquePiedra>(
						ABloquePiedra::StaticClass(),
						FVector(MapaEnConstruccion->XInicial + i * 100, MapaEnConstruccion->YInicial + j * 100, MapaEnConstruccion->ZInicial),
						FRotator::ZeroRotator);
				}
			}
		}
	}
}

void AConstructorMapaNivelUno::ConstruirBloqueTransparente()
{
	if (MapaEnConstruccion)
	{
		for (int32 i = 0; i < MapaEnConstruccion->aBloqueTransparente.Num(); i++)
		{
			for (int32 j = 0; j < MapaEnConstruccion->aBloqueTransparente[i].Num(); j++)
			{
				int32 BlockType = MapaEnConstruccion->aBloqueTransparente[i][j];
				if (BlockType == 3) {
					GetWorld()->SpawnActor<ABloqueTransparente>(
						ABloqueTransparente::StaticClass(),
						FVector(MapaEnConstruccion->XInicial + i * 100, MapaEnConstruccion->YInicial + j * 100, MapaEnConstruccion->ZInicial),
						FRotator::ZeroRotator);
				}
			}
		}
	}
}

void AConstructorMapaNivelUno::ConstruirPuerta()
{
	if (MapaEnConstruccion)
	{
		for (int32 i = 0; i < MapaEnConstruccion->aPuertaNivel.Num(); i++)
		{
			for (int32 j = 0; j < MapaEnConstruccion->aPuertaNivel[i].Num(); j++)
			{
				int32 BlockType = MapaEnConstruccion->aPuertaNivel[i][j];
				if (BlockType == 4) {
					GetWorld()->SpawnActor<APuertaNivel>(
						APuertaNivel::StaticClass(),
						FVector(MapaEnConstruccion->XInicial + i * 100, MapaEnConstruccion->YInicial + j * 100, MapaEnConstruccion->ZInicial),
						FRotator::ZeroRotator);
				}
			}
		}
	}
}

void AConstructorMapaNivelUno::ConstruirPuente()
{
	if (MapaEnConstruccion)
	{
		for (int32 i = 0; i < MapaEnConstruccion->aPuente.Num(); i++)
		{
			for (int32 j = 0; j < MapaEnConstruccion->aPuente[i].Num(); j++)
			{
				int32 BlockType = MapaEnConstruccion->aPuente[i][j];
				if (BlockType == 5) {
					GetWorld()->SpawnActor<APuente>(
						APuente::StaticClass(),
						FVector(MapaEnConstruccion->XInicial + i * 100, MapaEnConstruccion->YInicial + j * 100, MapaEnConstruccion->ZInicial),
						FRotator::ZeroRotator);
				}
			}
		}
	}
}

void AConstructorMapaNivelUno::ConstruirPowerUp()
{
	if (MapaEnConstruccion)
	{
		for (int32 i = 0; i < MapaEnConstruccion->aPowerUpBloque.Num(); i++)
		{
			for (int32 j = 0; j < MapaEnConstruccion->aPowerUpBloque[i].Num(); j++)
			{
				int32 BlockType = MapaEnConstruccion->aPowerUpBloque[i][j];
				if (BlockType == 6) {
					GetWorld()->SpawnActor<APowerUpBloque>(
						APowerUpBloque::StaticClass(),
						FVector(MapaEnConstruccion->XInicial + i * 100, MapaEnConstruccion->YInicial + j * 100, MapaEnConstruccion->ZInicial),
						FRotator::ZeroRotator);
				}
			}
		}
	}
}

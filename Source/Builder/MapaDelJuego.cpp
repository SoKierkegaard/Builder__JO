// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h" // Para GetWorld()
#include "MapaDelJuego.h"
#include "BloqueMuro.h"
#include "BloquePiedra.h"
#include "BloqueTransparente.h"
#include "PuertaNivel.h"
#include "Puente.h"
#include "PowerUpBloque.h"

// Sets default values
AMapaDelJuego::AMapaDelJuego()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMapaDelJuego::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMapaDelJuego::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMapaDelJuego::SetBloqueInterno(int32 tipo)
{
	if (tipo == 1 || tipo == 2)
	{
		for (int32 i = 0; i < aBloque.Num(); i++)
		{
			for (int32 j = 0; j < aBloque[i].Num(); j++)
			{
				int32 BlockType = aBloque[i][j];
				if (BlockType == 2) {
					if (tipo == 1)
					{
						GetWorld()->SpawnActor<ABloqueTransparente>(
							ABloqueTransparente::StaticClass(),
							FVector(XInicial + i * 100, YInicial + j * 100, ZInicial),
							FRotator::ZeroRotator);
					}
					else if (tipo == 2)
					{
						GetWorld()->SpawnActor<ABloquePiedra>(
							ABloquePiedra::StaticClass(),
							FVector(XInicial + i * 100, YInicial + j * 100, ZInicial),
							FRotator::ZeroRotator);
					}
					
				}
			}
		}
	}
}


void AMapaDelJuego::SetBloqueMuro(int32 tipo)
{
	if (tipo == 1 || tipo == 2)
	{
		for (int32 i = 0; i < aBloqueMuro.Num(); i++)
		{
			for (int32 j = 0; j < aBloqueMuro[i].Num(); j++)
			{
				int32 BlockType = aBloqueMuro[i][j];
				if (BlockType == 1) {
					if (tipo == 1)
					{
						GetWorld()->SpawnActor<ABloqueMuro>(
							ABloqueMuro::StaticClass(),
							FVector(XInicial + i * 100, YInicial + j * 100, ZInicial),
							FRotator::ZeroRotator);
					}
					else if (tipo == 2)
					{
						GetWorld()->SpawnActor<ABloquePiedra>(
							ABloquePiedra::StaticClass(),
							FVector(XInicial + i * 100, YInicial + j * 100, ZInicial),
							FRotator::ZeroRotator);
					}
					
				}
			}
		}
	}
	else {
		UE_LOG(LogTemp, Error,TEXT("Valor no valido")); return; 
	}
}

void AMapaDelJuego::SetPuerta(bool valor)
{
	if (valor)
	{
		for (int32 i = 0; i < aPuertaNivel.Num(); i++)
		{
			for (int32 j = 0; j < aPuertaNivel[i].Num(); j++)
			{
				int32 BlockType = aPuertaNivel[i][j];
				if (BlockType == 4) {
					GetWorld()->SpawnActor<APuertaNivel>(
						APuertaNivel::StaticClass(),
						FVector(XInicial + i * 100, YInicial + j * 100, ZInicial),
						FRotator::ZeroRotator);
				}
			}
		}
	}
}

void AMapaDelJuego::SetPuente(bool valor)
{
	if (valor)
	{
		for (int32 i = 0; i < aPuente.Num(); i++)
		{
			for (int32 j = 0; j < aPuente[i].Num(); j++)
			{
				int32 BlockType = aPuente[i][j];
				if (BlockType == 5) {
					GetWorld()->SpawnActor<APuente>(
						APuente::StaticClass(),
						FVector(XInicial + i * 100, YInicial + j * 100, ZInicial),
						FRotator::ZeroRotator);
				}
			}
		}
	}
}

void AMapaDelJuego::SetPowerUp(bool valor)
{
	if (valor)
	{
		for (int32 i = 0; i < aPowerUpBloque.Num(); i++)
		{
			for (int32 j = 0; j < aPowerUpBloque[i].Num(); j++)
			{
				int32 BlockType = aPowerUpBloque[i][j];
				if (BlockType == 6) {
					GetWorld()->SpawnActor<APowerUpBloque>(
						APowerUpBloque::StaticClass(),
						FVector(XInicial + i * 100, YInicial + j * 100, ZInicial),
						FRotator::ZeroRotator);
				}
			}
		}
	}
}

/*
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
*/
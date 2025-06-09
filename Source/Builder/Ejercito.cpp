// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h" // Para GetWorld()
#include "Ejercito.h"
#include "Enemigo.h"
#include "EnemigoAereo.h"
#include "EnemigoTerrestre.h"
#include "EnemigoGigante.h"

// Sets default values
AEjercito::AEjercito()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEjercito::SetComandante(int32 tipo)
{
	if (tipo == 1 || tipo == 2 || tipo == 3)
	{
		for (int32 i = 0; i < aComandanteEjercito.Num(); i++)
		{
			for (int32 j = 0; j < aComandanteEjercito[i].Num(); j++)
			{
				int32 BlockType = aComandanteEjercito[i][j];
				if (BlockType == 1) {
					if (tipo == 1)
					{
						GetWorld()->SpawnActor<AEnemigoAereo>(
							AEnemigoAereo::StaticClass(),
							FVector(XInicial + i * 10, YInicial + j * 10, ZInicial),
							FRotator::ZeroRotator);
					}
					else if (tipo == 2)
					{
						GetWorld()->SpawnActor<AEnemigoTerrestre>(
							AEnemigoTerrestre::StaticClass(),
							FVector(XInicial + i * 10, YInicial + j * 10, ZInicial),
							FRotator::ZeroRotator);
					}
					else if (tipo == 3)
					{
						GetWorld()->SpawnActor<AEnemigoGigante>(
							AEnemigoGigante::StaticClass(),
							FVector(XInicial + i * 10, YInicial + j * 10, ZInicial),
							FRotator::ZeroRotator);
					}
				}
			}
		}
	}
}


void AEjercito::SetPrimerEnemigo(int32 tipo)
{
	if (tipo == 1 || tipo == 2 || tipo == 3)
	{
		for (int32 i = 0; i < aPrimerEnemigo.Num(); i++)
		{
			for (int32 j = 0; j < aPrimerEnemigo[i].Num(); j++)
			{
				int32 BlockType = aPrimerEnemigo[i][j];
				if (tipo == 1)
				{
					GetWorld()->SpawnActor<AEnemigoAereo>(
						AEnemigoAereo::StaticClass(),
						FVector(XInicial + i * 10, YInicial + j * 10, ZInicial),
						FRotator::ZeroRotator);
				}
				else if (tipo == 2)
				{
					GetWorld()->SpawnActor<AEnemigoTerrestre>(
						AEnemigoTerrestre::StaticClass(),
						FVector(XInicial + i * 10, YInicial + j * 10, ZInicial),
						FRotator::ZeroRotator);
				}
				else if (tipo == 3)
				{
					GetWorld()->SpawnActor<AEnemigoGigante>(
						AEnemigoGigante::StaticClass(),
						FVector(XInicial + i * 10, YInicial + j * 10, ZInicial),
						FRotator::ZeroRotator);
				}
			}
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Valor no valido")); return;
	}
}

void AEjercito::SetSegundoEnemigo(int32 tipo)
{
	if (tipo == 1 || tipo == 2 || tipo == 3)
	{
		for (int32 i = 0; i < aSegundoEnemigo.Num(); i++)
		{
			for (int32 j = 0; j < aSegundoEnemigo[i].Num(); j++)
			{
				int32 BlockType = aSegundoEnemigo[i][j];
				if (tipo == 1)
				{
					GetWorld()->SpawnActor<AEnemigoAereo>(
						AEnemigoAereo::StaticClass(),
						FVector(XInicial + i * 10, YInicial + j * 10, ZInicial),
						FRotator::ZeroRotator);
				}
				else if (tipo == 2)
				{
					GetWorld()->SpawnActor<AEnemigoTerrestre>(
						AEnemigoTerrestre::StaticClass(),
						FVector(XInicial + i * 10, YInicial + j * 10, ZInicial),
						FRotator::ZeroRotator);
				}
				else if (tipo == 3)
				{
					GetWorld()->SpawnActor<AEnemigoGigante>(
						AEnemigoGigante::StaticClass(),
						FVector(XInicial + i * 10, YInicial + j * 10, ZInicial),
						FRotator::ZeroRotator);
				}
			}
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Valor no valido")); return;
	}
}

// Called when the game starts or when spawned
void AEjercito::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEjercito::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
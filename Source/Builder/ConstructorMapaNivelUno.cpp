// Fill out your copyright notice in the Description page of Project Settings.

#include "MapaDelJuego.h"
#include "ConstructorMapaNivelUno.h"



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

	MapaDelJuego = GetWorld()->SpawnActor<AMapaDelJuego>(AMapaDelJuego::StaticClass());

	MapaDelJuego->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called every frame
void AConstructorMapaNivelUno::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AConstructorMapaNivelUno::ConstruirBloqueMuro()
{
	MapaDelJuego->SetBloqueMuro(1);
}

void AConstructorMapaNivelUno::ConstruirBloqueInterno()
{
	MapaDelJuego->SetBloqueInterno(1);
}


void AConstructorMapaNivelUno::ConstruirPuerta()
{
	MapaDelJuego->SetPuerta(true);
}

void AConstructorMapaNivelUno::ConstruirPuente()
{
	MapaDelJuego->SetPuente(true);
}

void AConstructorMapaNivelUno::ConstruirPowerUp()
{
	MapaDelJuego->SetPowerUp(true);
}

AMapaDelJuego* AConstructorMapaNivelUno::GetMapa()
{
	return MapaDelJuego;
}
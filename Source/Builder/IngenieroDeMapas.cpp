// Fill out your copyright notice in the Description page of Project Settings.


#include "IngenieroDeMapas.h"
#include "ConstructorMapa.h"
#include "ConstructorMapaNivelUno.h"

// Sets default values
AIngenieroDeMapas::AIngenieroDeMapas()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AIngenieroDeMapas::SetConstructorMapa(AActor* Constructor)
{
	ConstructorMapa = Cast<IConstructorMapa>(Constructor);
}

void AIngenieroDeMapas::ConstruirMapa()
{
	ConstructorMapa->ConstruirBloqueMuro();
	ConstructorMapa->ConstruirBloqueInterno();
	ConstructorMapa->ConstruirPuerta();
	ConstructorMapa->ConstruirPuente();
	ConstructorMapa->ConstruirPowerUp();
}

AMapaDelJuego* AIngenieroDeMapas::GetMapa()
{
	return ConstructorMapa->GetMapa();
}

// Called when the game starts or when spawned
void AIngenieroDeMapas::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIngenieroDeMapas::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


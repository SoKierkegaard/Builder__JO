// Copyright Epic Games, Inc. All Rights Reserved.
#include "ConstructorMapaNivelUno.h"
#include "ConstructorEjercitoMiselaneo.h"
#include "BuilderGameMode.h"
#include "BuilderCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "IngenieroDeMapas.h"
#include "IngenieroDeEjercitos.h"
#include "EnemigoAereo.h"
ABuilderGameMode::ABuilderGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
void ABuilderGameMode::BeginPlay()
{
	Super::BeginPlay();
	// Create the Builder and Director
	// Crear el constructor del laberinto
	Constructor = GetWorld()->SpawnActor<AConstructorMapaNivelUno>(AConstructorMapaNivelUno::StaticClass());
	// Crear el director del laberinto
	Director = GetWorld()->SpawnActor<AIngenieroDeMapas>(AIngenieroDeMapas::StaticClass());


	////Set the Builder for the Director and create the Laberinto
	Director->SetConstructorMapa(Constructor);
	Director->ConstruirMapa();
	AMapaDelJuego* Mapa = Director->GetMapa();

	ConstructorEjercito = GetWorld()->SpawnActor<AConstructorEjercitoMiselaneo>(AConstructorEjercitoMiselaneo::StaticClass());
	// Crear el ingeniero de ejercitos
	IngenieroEjercitos = GetWorld()->SpawnActor<AIngenieroDeEjercitos>(AIngenieroDeEjercitos::StaticClass());



	// Set the Builder for the Engineer and create the Army 
	IngenieroEjercitos->SetConstructorEjercito(ConstructorEjercito);
	IngenieroEjercitos->ConstruirEjercito();
	AEjercito* Ejercito = IngenieroEjercitos->GetEjercito();
}

void ABuilderGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
}

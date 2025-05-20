// Copyright Epic Games, Inc. All Rights Reserved.
#include "ConstructorMapaNivelUno.h"
#include "BuilderGameMode.h"
#include "BuilderCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "IngenieroDeMapas.h"
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
	Builder = GetWorld()->SpawnActor<AConstructorMapaNivelUno>(AConstructorMapaNivelUno::StaticClass());
	// Crear el director del laberinto
	Director = GetWorld()->SpawnActor<AIngenieroDeMapas>(AIngenieroDeMapas::StaticClass());


	////Set the Builder for the Director and create the Laberinto
	Director->SetBuilder(Builder);
	//Director->CrearMapaUno();
	Director->CrearMapaDos();
	Director->CrearPuerta();
	Director->CrearPuente();
	Director->CrearPowerUp();
}

void ABuilderGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

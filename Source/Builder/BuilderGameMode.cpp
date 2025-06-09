// Copyright Epic Games, Inc. All Rights Reserved.
#include "ConstructorMapaNivelUno.h"
#include "BuilderGameMode.h"
#include "BuilderCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "IngenieroDeMapas.h"
#include "BloquePiedra.h"
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



	// prototype block
	UWorld* World = GetWorld();
	if (!World) return;

	// se crea y configura un prototipo de bloque de piedra
	// Este bloque se usará como prototipo para clonar
	PrototipoBloqueGranito = World->SpawnActor<ABloquePiedra>(ABloquePiedra::StaticClass(), FVector(200, 200, 0), FRotator::ZeroRotator);
	if (PrototipoBloqueGranito)
	{
		PrototipoBloqueGranito->ConfigurarBloque(200.0f, TEXT("Granito Resistente"));
		PrototipoBloqueGranito->Rename(TEXT("PrototipoOriginal_Granito")); // Cambiar nombre para depuración
		PrototipoBloqueGranito->MostrarDetalles();

		// 2. Clonar el prototipo usando la interfaz IClonable
		IClonable* ClonableOriginal = Cast<IClonable>(PrototipoBloqueGranito);
		if (ClonableOriginal)
		{
			// Crear el primer clon
			AActor* ActorClonado1 = ClonableOriginal->Clonar();
			if (ActorClonado1)
			{
				// Mover el clon para que no esté encima del original
				ActorClonado1->SetActorLocation(FVector(200, 0, 100));
				ABloquePiedra* BloqueClonado1 = Cast<ABloquePiedra>(ActorClonado1);
				if (BloqueClonado1)
				{
					BloqueClonado1->Rename(TEXT("Clon1_Granito"));
					BloqueClonado1->MostrarDetalles(); // Debería tener las mismas propiedades que el prototipo
				}
			}

			ActorClonado1 = World->SpawnActor<ABloquePiedra>(ABloquePiedra::StaticClass(), FVector(400, 400, 0), FRotator::ZeroRotator);
			// Crear el segundo clon y modificarlo ligeramente DESPUÉS de clonar
			AActor* ActorClonado2 = ClonableOriginal->Clonar();
			if (ActorClonado2)
			{
				ActorClonado2->SetActorLocation(FVector(400, 0, 100));
				ABloquePiedra* BloqueClonado2 = Cast<ABloquePiedra>(ActorClonado2);
				if (BloqueClonado2)
				{
					BloqueClonado2->Rename(TEXT("Clon2_Modificado"));
					// Modificamos una propiedad del clon DESPUÉS de la clonación
					BloqueClonado2->ConfigurarBloque(150.0f, TEXT("Mármol Clonado"));
					BloqueClonado2->MostrarDetalles();
				}
			}
			ActorClonado2 = World->SpawnActor<ABloquePiedra>(ABloquePiedra::StaticClass(), FVector(600, 600, 0), FRotator::ZeroRotator);
		}

		// 3. Demostrar que el original no fue afectado por la modificación del clon2
		UE_LOG(LogTemp, Log, TEXT("--- Verificando el original después de clonar y modificar clones ---"));
		PrototipoBloqueGranito->MostrarDetalles();
	}
}

void ABuilderGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
}

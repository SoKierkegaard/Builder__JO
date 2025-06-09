// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemigoTerrestre.h"
#include "UObject/ConstructorHelpers.h" // Para FObjectFinder, usado para localizar assets en el constructor.
#include "Engine/StaticMesh.h"          // Para UStaticMesh.
#include "Materials/Material.h"         // Para UMaterial.

// Constructor de AEnemigoTerrestre.
AEnemigoTerrestre::AEnemigoTerrestre()
{
	// Habilita Tick() para este actor. Si no se va a usar Tick() específicamente en AEnemigoTerrestre
	// (y AEnemigo ya lo habilita), esta línea podría ser redundante, pero no es perjudicial.
	PrimaryActorTick.bCanEverTick = true;

	// MallaEnemigo es heredado de AEnemigo. AEnemigo ya lo crea en su constructor.
	// Aquí, AEnemigoTerrestre está personalizando los assets para esa malla.

	// Intenta cargar y asignar un material específico para EnemigoTerrestre.
	// Nota: MallaEnemigo ya debería haber sido creado por el constructor de AEnemigo antes de que este código se ejecute.
	if (MallaEnemigo) // Buena práctica verificar que el puntero heredado es válido.
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBaseAsset(TEXT("Material'/Game/StarterContent/Materials/M_Tech_Hex_Tile_Pulse.M_Tech_Hex_Tile_Pulse'")); // Ruta al material.
		// Sugerencia: El nombre de la variable FObjectFinder (MaterialBaseAsset) es diferente al que usaste en AEnemigo (MaterialEnemigoAsset), lo cual está bien.
		// Usar nombres consistentes o más descriptivos como 'MaterialTerrestreAsset' podría mejorar la legibilidad si tienes muchos.

		if (MaterialBaseAsset.Succeeded())
		{
			MallaEnemigo->SetMaterial(0, MaterialBaseAsset.Object); // Asigna el material de cromo al slot 0 de la malla.
			// Esto sobrescribirá el material establecido en el constructor de AEnemigo.
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AEnemigoTerrestre: No se pudo cargar MaterialBaseAsset (M_Metal_Chrome)."));
		}

		// Intenta cargar y asignar una malla estática específica para EnemigoTerrestre.
		// Esto también sobrescribirá la malla establecida en el constructor de AEnemigo.
		// Es un poco inusual cambiar la malla estática de esta manera si la clase base ya asignó una,
		// pero es técnicamente posible. A menudo, se usarían diferentes clases de enemigos para diferentes mallas
		// o se configuraría a través de propiedades TSubclassOf para mayor flexibilidad.
		static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaTerrestreAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'")); // Ruta a la malla.
		// Nota: Esta es la misma malla que en AEnemigo. Si la intención es usar la misma malla, esta sección es redundante
		// a menos que AEnemigo no siempre la asigne o quieras asegurarte.
		if (MallaTerrestreAsset.Succeeded())
		{
			MallaEnemigo->SetStaticMesh(MallaTerrestreAsset.Object); // Asigna el modelo a MallaEnemigo.
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AEnemigoTerrestre: No se pudo cargar MallaTerrestreAsset (Shape_QuadPyramid)."));
		}
	}
	else
	{
		// Esto no debería ocurrir si AEnemigo siempre crea MallaEnemigo.
		UE_LOG(LogTemp, Error, TEXT("AEnemigoTerrestre Constructor: MallaEnemigo es NULL. No fue creado en la clase base AEnemigo."));
	}
}

// Se llama cuando el juego comienza o cuando el actor es instanciado.
void AEnemigoTerrestre::BeginPlay()
{
	Super::BeginPlay(); // Importante llamar a la implementación de la clase base.
	// AEnemigo::BeginPlay() llama a CambiarDireccion(), por lo que el enemigo terrestre también lo hará.

// Aquí podrías añadir lógica específica para AEnemigoTerrestre al iniciar el juego.
// Ejemplo: Loguear que un enemigo terrestre ha entrado en juego.
// UE_LOG(LogTemp, Log, TEXT("Un EnemigoTerrestre ha entrado en el campo de batalla: %s"), *GetName());
}

// Se llama en cada frame.
void AEnemigoTerrestre::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Importante llamar a la implementación de la clase base.
	// Esto ejecutará la lógica de movimiento definida en AEnemigo::Tick().

// Si AEnemigoTerrestre tuviera una lógica de Tick diferente o adicional, se implementaría aquí.
// Por ejemplo, si los enemigos terrestres tuvieran una habilidad de 'carga':
// if (bEstaCargando)
// {
//     // Lógica de movimiento de carga
// }
// else
// {
//     Super::Tick(DeltaTime); // Solo ejecutar movimiento normal si no está cargando
// }
}
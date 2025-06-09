#include "Enemigo.h" // Archivo de cabecera de la clase AEnemigo.
#include "GameFramework/CharacterMovementComponent.h" // Incluido, pero UCharacterMovementComponent no se usa explícitamente si MallaEnemigo es el RootComponent y no se usa la lógica de ACharacter.
#include "Math/UnrealMathUtility.h" // Para FMath::RandRange(), utilizado en la generación de movimiento aleatorio.
#include "Engine/World.h"           // Para GetWorld(), necesario para operaciones como LineTrace y SpawnActor.
#include "DrawDebugHelpers.h"       // Para DrawDebugLine, útil para visualizar el trazado de rayos.
#include "Engine/StaticMesh.h"      // Para UStaticMesh, el tipo de asset para modelos 3D estáticos.
#include "Materials/Material.h"     // Para UMaterial, el tipo de asset para materiales.
#include "UObject/ConstructorHelpers.h" // Para FObjectFinder, usado para localizar assets en el constructor.

// Constructor de la clase AEnemigo.
AEnemigo::AEnemigo()
{
	// Habilita la función Tick() para este actor. Es necesario si se implementa lógica en Tick().
	PrimaryActorTick.bCanEverTick = true;

	// Crea el componente de malla estática que representará visualmente al enemigo.
	MallaEnemigo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaEnemigoVisual")); // Se le da un nombre único.
	RootComponent = MallaEnemigo; // Establece MallaEnemigo como el componente raíz del actor.
	// Esto significa que la posición y rotación del actor serán las de esta malla.
	// Sugerencia: Si MallaEnemigo es el RootComponent y AEnemigo hereda de ACharacter,
	// el UCapsuleComponent de ACharacter ya no será el RootComponent, lo cual puede
	// afectar la detección de colisiones y el movimiento proporcionado por UCharacterMovementComponent.
	// Si se desea el movimiento y colisión de ACharacter, el RootComponent debería ser
	// su CapsuleComponent, y MallaEnemigo un hijo de este.
	// Si no se necesita la lógica de ACharacter, considera heredar de APawn.

// Intenta cargar un asset de malla estática desde la ruta especificada.
// ConstructorHelpers::FObjectFinder solo funciona dentro de constructores.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaEnemigoAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
	if (MallaEnemigoAsset.Succeeded())
	{
		MallaEnemigo->SetStaticMesh(MallaEnemigoAsset.Object); // Asigna la malla cargada al componente.
		// MallaEnemigo->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // Redundante si es RootComponent y no hay cambios de escala padre.
		// MallaEnemigo->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f)); // Redundante si es RootComponent.
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No se pudo cargar MallaEnemigoAsset para AEnemigo."));
	}

	// Intenta cargar un asset de material desde la ruta especificada.
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialEnemigoAsset(TEXT("Material'/Game/StarterContent/Materials/M_Tech_Hex_Tile.M_Tech_Hex_Tile'"));
	if (MaterialEnemigoAsset.Succeeded())
	{
		MallaEnemigo->SetMaterial(0, MaterialEnemigoAsset.Object); // Asigna el material al primer slot del componente de malla.
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No se pudo cargar MaterialEnemigoAsset para AEnemigo."));
	}

	// MallaEnemigo->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f)); // SetRelativeScale3D es más común en el constructor. SetWorldScale3D se usa más en tiempo de ejecución si es necesario.
															  // Si es RootComponent, la escala del actor y la malla serán la misma.

	// Inicializa la distancia recorrida para la lógica de movimiento.
	DistanciaRecorrida = 0.0f;
}


// Se llama cuando el juego comienza o cuando el actor es instanciado.
void AEnemigo::BeginPlay()
{
	Super::BeginPlay(); // Llama a la implementación de la clase base.

	// Establece una dirección inicial para el movimiento del enemigo.
	//MovimientoActual = FVector::ZeroVector; // Inicializa el vector de movimiento a cero.
	CambiarDireccion();
}

// Se llama en cada frame.
void AEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Llama a la implementación de la clase base.

	// Calcula la velocidad del movimiento (magnitud constante).
	const float VelocidadMovimiento = 100.0f;
	FVector DesplazamientoEsteFrame = MovimientoActual * VelocidadMovimiento * DeltaTime;

	// Calcula la nueva posición teórica si el enemigo se mueve.
	FVector PosicionActual = GetActorLocation();
	FVector NuevaPosicionCandidata = PosicionActual + DesplazamientoEsteFrame;

	// Comprueba si hay un obstáculo en la dirección del movimiento.
	// La distancia de comprobación es la magnitud del desplazamiento de este frame.
	if (DetectarObstaculo(MovimientoActual, DesplazamientoEsteFrame.Size()))
	{
		// Si hay un obstáculo, cambia de dirección inmediatamente.
		CambiarDireccion();
		DistanciaRecorrida = 0.0f; // Reinicia la distancia al cambiar de dirección por obstáculo.
	}
	else
	{
		// Si no hay obstáculo, mueve al enemigo a la nueva posición.
		SetActorLocation(NuevaPosicionCandidata);
		DistanciaRecorrida += DesplazamientoEsteFrame.Size(); // Acumula la distancia recorrida.

		// Si el enemigo ha recorrido la distancia máxima en la dirección actual, cambia de dirección.
		if (DistanciaRecorrida >= DistanciaMaxima)
		{
			CambiarDireccion();
			DistanciaRecorrida = 0.0f; // Reinicia el contador de distancia.
		}
	}
}

/** Calcula y establece una nueva dirección de movimiento aleatoria (en el plano XY). */
void AEnemigo::CambiarDireccion()
{
	// Genera componentes X e Y aleatorios entre -1.0 y 1.0.
	float RandomX = FMath::RandRange(-1.0f, 1.0f);
	float RandomY = FMath::RandRange(-1.0f, 1.0f);
	// Crea un vector con los componentes aleatorios (Z es 0 para movimiento en el plano) y lo normaliza para obtener solo la dirección.
	MovimientoActual = FVector(RandomX, RandomY, 0.0f).GetSafeNormal();
}

/**
 * Realiza un trazado de rayo (line trace) para detectar obstáculos en una dirección dada.
 * @param Direccion El vector de dirección normalizado hacia donde se intenta mover.
 * @param Distancia La distancia a la que se comprobará el obstáculo.
 * @return true si el rayo golpea un obstáculo (ECC_WorldStatic), false en caso contrario.
 */
bool AEnemigo::DetectarObstaculo(FVector Direccion, float Distancia) // Firma modificada para usar Dirección y Distancia
{
	FHitResult HitResult;
	FVector Inicio = GetActorLocation();
	// Calcula el punto final del rayo basado en la dirección y la distancia.
	FVector Fin = Inicio + Direccion * Distancia;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); // Asegura que el rayo no colisione con el propio enemigo.

	// Realiza el trazado de rayo. ECC_WorldStatic se usa comúnmente para objetos estáticos del entorno como muros.
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Inicio, Fin, ECollisionChannel::ECC_WorldStatic, Params);

	// Dibuja una línea de depuración para visualizar el rayo en el editor (útil para el desarrollo).
	// Verde si no golpea, Rojo si golpea.
	DrawDebugLine(GetWorld(), Inicio, Fin, bHit ? FColor::Red : FColor::Green, false, 0.1f, 0, 1.0f); // Duración más corta para no llenar la pantalla.

	return bHit; // Devuelve true si hubo una colisión.
}
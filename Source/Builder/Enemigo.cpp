#include "Enemigo.h" // Archivo de cabecera de la clase AEnemigo.
#include "GameFramework/CharacterMovementComponent.h" // Incluido, pero UCharacterMovementComponent no se usa expl�citamente si MallaEnemigo es el RootComponent y no se usa la l�gica de ACharacter.
#include "Math/UnrealMathUtility.h" // Para FMath::RandRange(), utilizado en la generaci�n de movimiento aleatorio.
#include "Engine/World.h"           // Para GetWorld(), necesario para operaciones como LineTrace y SpawnActor.
#include "DrawDebugHelpers.h"       // Para DrawDebugLine, �til para visualizar el trazado de rayos.
#include "Engine/StaticMesh.h"      // Para UStaticMesh, el tipo de asset para modelos 3D est�ticos.
#include "Materials/Material.h"     // Para UMaterial, el tipo de asset para materiales.
#include "UObject/ConstructorHelpers.h" // Para FObjectFinder, usado para localizar assets en el constructor.

// Constructor de la clase AEnemigo.
AEnemigo::AEnemigo()
{
	// Habilita la funci�n Tick() para este actor. Es necesario si se implementa l�gica en Tick().
	PrimaryActorTick.bCanEverTick = true;

	// Crea el componente de malla est�tica que representar� visualmente al enemigo.
	MallaEnemigo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaEnemigoVisual")); // Se le da un nombre �nico.
	RootComponent = MallaEnemigo; // Establece MallaEnemigo como el componente ra�z del actor.
	// Esto significa que la posici�n y rotaci�n del actor ser�n las de esta malla.
	// Sugerencia: Si MallaEnemigo es el RootComponent y AEnemigo hereda de ACharacter,
	// el UCapsuleComponent de ACharacter ya no ser� el RootComponent, lo cual puede
	// afectar la detecci�n de colisiones y el movimiento proporcionado por UCharacterMovementComponent.
	// Si se desea el movimiento y colisi�n de ACharacter, el RootComponent deber�a ser
	// su CapsuleComponent, y MallaEnemigo un hijo de este.
	// Si no se necesita la l�gica de ACharacter, considera heredar de APawn.

// Intenta cargar un asset de malla est�tica desde la ruta especificada.
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

	// MallaEnemigo->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f)); // SetRelativeScale3D es m�s com�n en el constructor. SetWorldScale3D se usa m�s en tiempo de ejecuci�n si es necesario.
															  // Si es RootComponent, la escala del actor y la malla ser�n la misma.

	// Inicializa la distancia recorrida para la l�gica de movimiento.
	DistanciaRecorrida = 0.0f;
}


// Se llama cuando el juego comienza o cuando el actor es instanciado.
void AEnemigo::BeginPlay()
{
	Super::BeginPlay(); // Llama a la implementaci�n de la clase base.

	// Establece una direcci�n inicial para el movimiento del enemigo.
	//MovimientoActual = FVector::ZeroVector; // Inicializa el vector de movimiento a cero.
	CambiarDireccion();
}

// Se llama en cada frame.
void AEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Llama a la implementaci�n de la clase base.

	// Calcula la velocidad del movimiento (magnitud constante).
	const float VelocidadMovimiento = 100.0f;
	FVector DesplazamientoEsteFrame = MovimientoActual * VelocidadMovimiento * DeltaTime;

	// Calcula la nueva posici�n te�rica si el enemigo se mueve.
	FVector PosicionActual = GetActorLocation();
	FVector NuevaPosicionCandidata = PosicionActual + DesplazamientoEsteFrame;

	// Comprueba si hay un obst�culo en la direcci�n del movimiento.
	// La distancia de comprobaci�n es la magnitud del desplazamiento de este frame.
	if (DetectarObstaculo(MovimientoActual, DesplazamientoEsteFrame.Size()))
	{
		// Si hay un obst�culo, cambia de direcci�n inmediatamente.
		CambiarDireccion();
		DistanciaRecorrida = 0.0f; // Reinicia la distancia al cambiar de direcci�n por obst�culo.
	}
	else
	{
		// Si no hay obst�culo, mueve al enemigo a la nueva posici�n.
		SetActorLocation(NuevaPosicionCandidata);
		DistanciaRecorrida += DesplazamientoEsteFrame.Size(); // Acumula la distancia recorrida.

		// Si el enemigo ha recorrido la distancia m�xima en la direcci�n actual, cambia de direcci�n.
		if (DistanciaRecorrida >= DistanciaMaxima)
		{
			CambiarDireccion();
			DistanciaRecorrida = 0.0f; // Reinicia el contador de distancia.
		}
	}
}

/** Calcula y establece una nueva direcci�n de movimiento aleatoria (en el plano XY). */
void AEnemigo::CambiarDireccion()
{
	// Genera componentes X e Y aleatorios entre -1.0 y 1.0.
	float RandomX = FMath::RandRange(-1.0f, 1.0f);
	float RandomY = FMath::RandRange(-1.0f, 1.0f);
	// Crea un vector con los componentes aleatorios (Z es 0 para movimiento en el plano) y lo normaliza para obtener solo la direcci�n.
	MovimientoActual = FVector(RandomX, RandomY, 0.0f).GetSafeNormal();
}

/**
 * Realiza un trazado de rayo (line trace) para detectar obst�culos en una direcci�n dada.
 * @param Direccion El vector de direcci�n normalizado hacia donde se intenta mover.
 * @param Distancia La distancia a la que se comprobar� el obst�culo.
 * @return true si el rayo golpea un obst�culo (ECC_WorldStatic), false en caso contrario.
 */
bool AEnemigo::DetectarObstaculo(FVector Direccion, float Distancia) // Firma modificada para usar Direcci�n y Distancia
{
	FHitResult HitResult;
	FVector Inicio = GetActorLocation();
	// Calcula el punto final del rayo basado en la direcci�n y la distancia.
	FVector Fin = Inicio + Direccion * Distancia;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); // Asegura que el rayo no colisione con el propio enemigo.

	// Realiza el trazado de rayo. ECC_WorldStatic se usa com�nmente para objetos est�ticos del entorno como muros.
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Inicio, Fin, ECollisionChannel::ECC_WorldStatic, Params);

	// Dibuja una l�nea de depuraci�n para visualizar el rayo en el editor (�til para el desarrollo).
	// Verde si no golpea, Rojo si golpea.
	DrawDebugLine(GetWorld(), Inicio, Fin, bHit ? FColor::Red : FColor::Green, false, 0.1f, 0, 1.0f); // Duraci�n m�s corta para no llenar la pantalla.

	return bHit; // Devuelve true si hubo una colisi�n.
}
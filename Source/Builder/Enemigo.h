// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemigo.generated.h"

UCLASS()
class BUILDER_API AEnemigo : public ACharacter
{
	GENERATED_BODY()


public:
	/** Constructor por defecto de la clase AEnemigo. */
	AEnemigo();

	/** Componente de malla est�tica para la representaci�n visual del enemigo. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MallaEnemigo")
	// VisibleAnywhere: Permite ver esta propiedad en el editor de Unreal, pero no modificarla directamente desde el panel de detalles.
	// BlueprintReadOnly: Permite que los Blueprints lean el valor de esta propiedad.
	// Category = "MallaEnemigo": Agrupa esta propiedad en la categor�a "MallaEnemigo" en el editor para una mejor organizaci�n.
	UStaticMeshComponent* MallaEnemigo; // Puntero al componente de malla est�tica. Se inicializar� en el constructor.
	// Sugerencia: Si este enemigo siempre usa una malla est�tica y no el SkeletalMeshComponent de ACharacter, considera heredar de APawn y a�adir UFloatingPawnMovement si necesitas movimiento simple, o gestionar el movimiento manualmente. Si usas ACharacter, normalmente se usa su SkeletalMeshComponent (this->GetMesh()).

protected:
	/** Se llama cuando el juego comienza o cuando el actor es instanciado en el mundo. Ideal para l�gica de inicializaci�n. */
	virtual void BeginPlay() override;

public:
	/** Se llama en cada frame. Contiene la l�gica que se actualiza constantemente, como el movimiento.
	 * @param DeltaTime El tiempo en segundos transcurrido desde el �ltimo frame.
	 */
	virtual void Tick(float DeltaTime) override;

	// (Comentario original: Funci?n para mover al enemigo) - Esta secci�n parece agrupar variables relacionadas con el movimiento.

public: // Esta secci�n 'public' es redundante ya que la anterior tambi�n lo era. Se pueden agrupar.
	/** Almacena la direcci�n y magnitud del movimiento actual del enemigo. */
	FVector MovimientoActual;
	/** Acumula la distancia recorrida en la direcci�n de MovimientoActual. */
	float DistanciaRecorrida;
	/** Distancia m�xima que el enemigo recorrer� en una direcci�n antes de intentar cambiarla. */
	const float DistanciaMaxima = 100.0f;

private:
	/** Calcula y establece una nueva direcci�n aleatoria para MovimientoActual. */
	void CambiarDireccion();

	/** Verifica si hay un obst�culo en la trayectoria hacia un destino propuesto.
	 * @param Direccion El vector de direcci�n normalizado hacia donde se intenta mover.
	 * @param Distancia La distancia a la que se comprobar� el obst�culo.
	 * @return true si se detecta un obst�culo, false en caso contrario.
	 */
	bool DetectarObstaculo(FVector Direccion, float Distancia); // Modifiqu� ligeramente la firma para que sea m�s clara (direcci�n y distancia en lugar de un destino absoluto).
	// Podr�as tambi�n considerar usar el sistema de navegaci�n de UE (NavMesh) para un movimiento m�s robusto si planeas niveles complejos.
};
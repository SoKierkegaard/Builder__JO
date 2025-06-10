// BombSystemFacade.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BombSystemFacade.generated.h"

// Forward declarations
class ABomba;
class AActor; // Para el dueño de la bomba
class UWorld;

UCLASS()
class BUILDER_API UBombSystemFacade : public UObject
{
    GENERATED_BODY()

public:
    UBombSystemFacade();

    /**
     * Inicializa la fachada con el contexto del mundo.
     * Debe llamarse antes de usar la fachada.
     */
    void Initialize(UWorld* InWorld);

    /**
     * Intenta colocar una bomba en la posición especificada.
     * @param BombOwner El actor que coloca la bomba (puede ser nullptr).
     * @param TargetLocation La ubicación donde se intentará colocar la bomba.
     * @param BombPower La potencia de la explosión (cuántas casillas se expande, por ahora usaremos el default de Bomba).
     * @return Puntero a la ABomba instanciada si tiene éxito, nullptr en caso contrario.
     */
    ABomba* PlaceBombAtLocation(AActor* BombOwner, FVector TargetLocation, float BombPower = 1.0f);
    // Nota: Por ahora, BombPower no se usa directamente en tu ABomba, pero es una buena adición para el futuro.

    /**
     * (Opcional) Fuerza la detonación de una bomba específica.
     * Esto podría ser útil para power-ups de detonación remota.
     * @param BombToDetonate La bomba a detonar.
     */
    void ForceDetonateBomb(ABomba* BombToDetonate);

    // --- Podrías añadir más métodos según sea necesario ---
    // int GetActiveBombsCount(AActor* BombOwner) const;
    // bool CanPlayerPlaceBomb(AActor* BombOwner) const;

private:
    UPROPERTY()
    UWorld* WorldContext; // Necesario para SpawnActor

    // (Opcional) Podrías llevar un registro de las bombas activas aquí si la fachada necesita gestionarlas más de cerca.
    // UPROPERTY()
    // TArray<ABomba*> ActiveBombs;
};
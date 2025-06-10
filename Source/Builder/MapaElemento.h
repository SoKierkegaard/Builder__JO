// MapaElemento.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MapaElemento.generated.h"

UINTERFACE(MinimalAPI)
class UMapaElemento : public UInterface
{
    GENERATED_BODY()
};

/**
 * Interfaz para cualquier elemento del mapa que pueda ser tratado uniformemente,
 * especialmente para operaciones como la destrucción.
 */
class BUILDER_API IMapaElemento // Reemplaza BOMBERMANPROYECTO_API con tu API de módulo
{
    GENERATED_BODY()

public:
    /**
     * Define cómo el elemento del mapa debe ser destruido.
     * Las implementaciones concretas manejarán su propia lógica de destrucción.
     */
    virtual void DestruirElemento() = 0;

    // Podrías añadir más tarde:
    // virtual bool EsDestructiblePorExplosion() const = 0;
    // virtual void RecibirImpacto(float Dano) = 0;
};
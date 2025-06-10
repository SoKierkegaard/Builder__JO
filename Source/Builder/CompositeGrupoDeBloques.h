// GrupoDeBloquesLogicos.h
// CompositeGrupoDeBloques.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapaElemento.h" // Incluimos la interfaz
#include "CompositeGrupoDeBloques.generated.h"

UCLASS()
class BUILDER_API ACompositeGrupoDeBloques : public AActor, public IMapaElemento // Implementa IMapaElemento
{
    GENERATED_BODY()

public:
    ACompositeGrupoDeBloques();

    // Lista de elementos hijos. Usamos AActor* porque IMapaElemento es una UInterface
    // y los actores que la implementan son AActor.
    // Necesitaremos hacer Cast<IMapaElemento> para usar la interfaz.
    UPROPERTY(EditInstanceOnly, Category = "Composite") // EditInstanceOnly para poder asignar en el editor si lo colocas
    TArray<AActor*> ElementosHijo;

    // --- Métodos para manejar los hijos ---
    UFUNCTION(BlueprintCallable, Category = "Composite") // BlueprintCallable para facilitar pruebas
    void AnadirElemento(AActor* ElementoAAgregar);

    UFUNCTION(BlueprintCallable, Category = "Composite")
    void RemoverElemento(AActor* ElementoARemover);

    // --- Implementación de IMapaElemento ---
    virtual void DestruirElemento() override;

protected:
    virtual void BeginPlay() override;
};
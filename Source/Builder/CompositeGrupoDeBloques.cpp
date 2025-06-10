// GrupoDeBloquesLogicos.cpp
// CompositeGrupoDeBloques.cpp

#include "CompositeGrupoDeBloques.h"
#include "MapaElemento.h" // Para IMapaElemento y el Cast

ACompositeGrupoDeBloques::ACompositeGrupoDeBloques()
{
    PrimaryActorTick.bCanEverTick = false;
    // Este actor es solo un contenedor lógico, no necesita mesh.
    // Pero necesita un RootComponent. Un USceneComponent es lo más ligero.
    USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    RootComponent = SceneRoot;
}

void ACompositeGrupoDeBloques::BeginPlay()
{
    Super::BeginPlay();
}

void ACompositeGrupoDeBloques::AnadirElemento(AActor* ElementoAAgregar)
{
    if (ElementoAAgregar && ElementoAAgregar->Implements<UMapaElemento>())
    {
        ElementosHijo.AddUnique(ElementoAAgregar);
        UE_LOG(LogTemp, Log, TEXT("Elemento %s añadido al grupo %s"), *ElementoAAgregar->GetName(), *GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Intento de añadir elemento nulo o que no implementa IMapaElemento al grupo %s"), *GetName());
    }
}

void ACompositeGrupoDeBloques::RemoverElemento(AActor* ElementoARemover)
{
    if (ElementoARemover)
    {
        ElementosHijo.Remove(ElementoARemover);
        UE_LOG(LogTemp, Log, TEXT("Elemento %s removido del grupo %s"), *ElementoARemover->GetName(), *GetName());
    }
}

void ACompositeGrupoDeBloques::DestruirElemento()
{
    UE_LOG(LogTemp, Log, TEXT("GrupoDeBloquesLogicos (%s) recibiendo orden de destruir sus hijos."), *GetName());

    // Iteramos en reversa por si la destrucción de un hijo lo remueve de alguna lista global
    // o para evitar problemas si la lista se modifica durante la iteración (aunque aquí no debería).
    for (int32 i = ElementosHijo.Num() - 1; i >= 0; --i)
    {
        AActor* ActorHijo = ElementosHijo[i];
        if (ActorHijo) // Comprobar si el actor todavía es válido
        {
            IMapaElemento* ElementoHijo = Cast<IMapaElemento>(ActorHijo);
            if (ElementoHijo)
            {
                ElementoHijo->DestruirElemento(); // Llama al DestruirElemento del hijo
            }
        }
    }
    ElementosHijo.Empty(); // Limpiar la lista de referencias después de intentar destruirlos

    // El grupo lógico en sí mismo también se destruye después de procesar sus hijos.
    Destroy();
}
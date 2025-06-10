// BombSystemFacade.cpp
#include "BombSystemFacade.h"
#include "Bomba.h"       // Incluye tu clase ABomba
#include "Engine/World.h"

UBombSystemFacade::UBombSystemFacade()
{
    WorldContext = nullptr;
}

void UBombSystemFacade::Initialize(UWorld* InWorld)
{
    WorldContext = InWorld;
    if (!WorldContext)
    {
        UE_LOG(LogTemp, Error, TEXT("BombSystemFacade::Initialize - WorldContext no fue proporcionado!"));
    }
}

ABomba* UBombSystemFacade::PlaceBombAtLocation(AActor* BombOwner, FVector TargetLocation, float BombPower)
{
    if (!WorldContext)
    {
        UE_LOG(LogTemp, Error, TEXT("BombSystemFacade::PlaceBombAtLocation - Fachada no inicializada (WorldContext es NULL)."));
        return nullptr;
    }

    // Aquí podrías añadir lógica para verificar si se puede colocar una bomba
    // (ej. límite de bombas por jugador, si la celda está ocupada por algo que no sea una bomba, etc.)
    // if (!CanPlaceBombAt(TargetLocation, BombOwner))
    // {
    //     return nullptr;
    // }

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = BombOwner; // El dueño de la bomba
    SpawnParams.Instigator = Cast<APawn>(BombOwner); // Quién instigó la acción
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    ABomba* NuevaBomba = WorldContext->SpawnActor<ABomba>(ABomba::StaticClass(), TargetLocation, FRotator::ZeroRotator, SpawnParams);

    if (NuevaBomba)
    {
        UE_LOG(LogTemp, Log, TEXT("Bomba colocada en %s por la fachada."), *TargetLocation.ToString());
        // (Opcional) Configurar propiedades adicionales de la bomba si es necesario
        // NuevaBomba->SetPotencia(BombPower);
        // ActiveBombs.Add(NuevaBomba); // Si llevas registro
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("BombSystemFacade: Falló el SpawnActor para ABomba en %s."), *TargetLocation.ToString());
    }

    return NuevaBomba;
}

void UBombSystemFacade::ForceDetonateBomb(ABomba* BombToDetonate)
{
    if (BombToDetonate && !BombToDetonate->IsPendingKill()) // Asegurarse que la bomba es válida
    {
        UE_LOG(LogTemp, Log, TEXT("Fachada forzando detonación de bomba: %s"), *BombToDetonate->GetName());
        // Tu ABomba ya tiene un temporizador para explotar.
        // Si quieres una detonación inmediata, tendrías que:
        // 1. Limpiar sus temporizadores.
        // 2. Llamar directamente a sus funciones Shoot() y explotar().
        //    (O mejor, añadir un método público en ABomba como DetonarInmediatamente())

        // Por ahora, como ejemplo, llamaremos a sus métodos existentes si existiera una forma pública de hacerlo.
        // Esto requeriría que los temporizadores de ABomba se cancelen y se llamen las funciones directamente.
        // Para simplificar, asumiremos que ABomba tiene un método para esto.
        // O, si no, esta función podría no ser necesaria si ABomba se maneja bien sola.

        // Ejemplo si ABomba tuviera un método público:
        BombToDetonate->DetonarInmediatamentePublico();

        // Si quieres solo adelantar su timer (no muy limpio):
        // BombToDetonate->GetWorldTimerManager().ClearTimer(BombToDetonate->TimerHandle_Disparar);
        // BombToDetonate->GetWorldTimerManager().ClearTimer(BombToDetonate->TH_Explosion);
        // BombToDetonate->Shoot();
        // BombToDetonate->explotar();
        // CUIDADO: Llamar a explotar() que hace Destroy() puede ser problemático si hay más código después.

        // Es más limpio que ABomba tenga un método:
        // void ABomba::DetonarAhora()
        // {
        //     GetWorldTimerManager().ClearTimer(TimerHandle_Disparar);
        //     GetWorldTimerManager().ClearTimer(TH_Explosion);
        //     Shoot();
        //     explotar(); // ¡Ojo con el Destroy() aquí!
        // }
        // Y luego aquí: BombToDetonate->DetonarAhora();

        // Por el momento, dejaremos esta función más conceptual.
        // La propia ABomba maneja su detonación por tiempo.
        // Una detonación "forzada" por una explosión en cadena ocurriría si una AExplosion colisiona con otra ABomba.
        // Esa lógica estaría en AExplosion::OnHit.
    }
}
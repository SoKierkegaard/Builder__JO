//BloquePiedra.cpp

// Fill out your copyright notice in the Description page of Project Settings.


#include "BloquePiedra.h"

// Sets default values
ABloquePiedra::ABloquePiedra()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    if (MallaBloque)
    {
        static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Concrete_Panels.M_Concrete_Panels'")); // Ajusta esta ruta si es necesario
        if (MaterialBase.Succeeded())
        {
            MallaBloque->SetMaterial(0, MaterialBase.Object);
        }
    }

    Resistencia = 100.0f;
    TipoPiedra = TEXT("Piedra Gen�rica");
}

// Called when the game starts or when spawned
void ABloquePiedra::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ABloquePiedra::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ABloquePiedra::DestruirElemento()
{
    // Para el BloqueAcero, "DestruirElemento" podría no hacer nada si es indestructible,
    // o podría tener una lógica diferente (ej. dañarse pero no destruirse).
    // Por ahora, para la prueba del patrón, haremos que loguee pero no se destruya.
    UE_LOG(LogTemp, Log, TEXT("BloqueAcero (%s) recibió orden de destruir, pero es indestructible (por ahora)."), *GetName());

    // Si realmente fuera indestructible y DestruirElemento no debiera hacer nada:
    // return;

    // Si quieres que sí se destruya para la prueba (aunque sea "acero"):
    // Destroy();
}

void ABloquePiedra::MostrarDetalles()
{

    UE_LOG(LogTemp, Log, TEXT("Detalles de BloquePiedra (%s): Resistencia=%.2f, Tipo=%s, Posicion=%s"),
        *GetNameSafe(this),             // Usar GetNameSafe para mayor robustez
        Resistencia,
        *TipoPiedra,
        *GetActorLocation().ToString()
    );
}

void ABloquePiedra::ConfigurarBloque(float NuevaResistencia, const FString& NuevoTipoPiedra)
{
    this->Resistencia = NuevaResistencia;   // Usar this-> para asignar al miembro de la clase
    this->TipoPiedra = NuevoTipoPiedra;     // Usar this-> para asignar al miembro de la clase

    UE_LOG(LogTemp, Log, TEXT("Bloque (%s) configurado: Resistencia=%.2f, Tipo=%s"), *GetNameSafe(this), this->Resistencia, *this->TipoPiedra);
}

AActor* ABloquePiedra::Clonar()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("ABloquePiedra::Clonar - World es NULL"));
        return nullptr;
    }

    // 1. Instanciar un nuevo objeto del mismo tipo.
    // Usamos SpawnActor para que est� correctamente en el mundo.
    // La posici�n inicial del clon podr�a ser la misma que el original o (0,0,0) y luego moverlo.
    // Por simplicidad, lo creamos en la misma posici�n y rotaci�n.
    ABloquePiedra* Clon = World->SpawnActor<ABloquePiedra>(this->GetClass(), GetActorLocation(), GetActorRotation());

    if (Clon)
    {
        // 2. Copiar el estado del objeto original al clon.
        Clon->Resistencia = this->Resistencia;
        Clon->TipoPiedra = this->TipoPiedra;

        UE_LOG(LogTemp, Log, TEXT("ABloquePiedra (%s) clonado a -> (%s)"), *this->GetName(), *Clon->GetName());
        return Clon;
    }

    UE_LOG(LogTemp, Error, TEXT("ABloquePiedra::Clonar - Fall� el SpawnActor para el clon."));
    return nullptr;
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ConstructorMapa.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IngenieroDeMapas.generated.h"
class IConstructorMapa; class AMapaDelJuego;
UCLASS()
class BUILDER_API AIngenieroDeMapas : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AIngenieroDeMapas();

public:


    void CrearMapaUno();
    void CrearMapaDos();

    void CrearPuerta();
    void CrearPuente();
    void CrearPowerUp();
    void ConstructorDeMapa();
    void SetBuilder(IConstructorMapa* NewBuilder); // Método para asignar el builder
    /*
    // Método para asignar el builder
    void EstablecerConstructor(AActor* Constructor); // AActor para que puedas pasarle un Actor que implemente IConstructorMapa


    // Método principal para orquestar la construcción
    AMapaDelJuego* GenerarMapa(
        const TArray<TArray<int32>>& DatosCapaPrincipal, // Tu aMapaBloques
        const TArray<TArray<int32>>& DatosCapaPuertas,   // Tu aMapaPuertas
        const TArray<TArray<int32>>& DatosCapaVidrios    // Tu aMapaBloqueVidrios
        // Podrías añadir más capas si es necesario
    );



    // Podrías tener aquí la lógica de qué significa cada número
    // o pasarla como parámetro, o que el builder lo sepa.
    // Por ahora, el director interpretará los números.
    UPROPERTY(EditAnywhere, Category = "Configuración Mapa")
    float TamanoCelda = 100.0f; // Tamaño de cada bloque en unidades de UE
    */


private:
    IConstructorMapa* ConstructorMapa; // El constructor que implementa la interfaz IConstructorMapa
    

protected:
    virtual void BeginPlay() override;
    FVector CalcularPosicionDesdeIndices(int32 Fila, int32 Columna, float AlturaZ = 0.0f);
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

};


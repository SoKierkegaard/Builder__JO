// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ConstructorMapa.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IngenieroDeMapas.generated.h"
class IConstructorMapa; class AMapaDelJuego; class ConstructorMapaNivelUno;
UCLASS()
class BUILDER_API AIngenieroDeMapas : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIngenieroDeMapas();

public:


    void ConstruirMapa();
	void SetConstructorMapa(AActor* Constructor);
	class AMapaDelJuego* GetMapa(); // Método para obtener el mapa construido


private:
	IConstructorMapa* ConstructorMapa; // El constructor que implementa la interfaz IConstructorMapa

protected:
    virtual void BeginPlay() override;
    //FVector CalcularPosicionDesdeIndices(int32 Fila, int32 Columna, float AlturaZ = 0.0f);
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    

};


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ConstructorEjercito.h" // Interfaz
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConstructorEjercitoMiselaneo.generated.h"
class AEnemigoTerrestre; class AEnemigoAereo; class AEnemigoGigante;
UCLASS()
class BUILDER_API AConstructorEjercitoMiselaneo : public AActor, public IConstructorEjercito
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConstructorEjercitoMiselaneo();

protected:

    UPROPERTY() // El producto que se est� construyendo
        class AEjercito* Ejercito;


public:
    // Implementaci�n de IConstructorMapa

    virtual void ConstruirComandante() override;
    virtual void ConstruirPrimerEnemigo() override;
    virtual void ConstruirSegundoEnemigo() override;
    virtual class AEjercito* GetEjercito() override;


    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override; // Podr�a llamar a IniciarNuevoMapa aqu� si el builder se usa solo una vez.
};
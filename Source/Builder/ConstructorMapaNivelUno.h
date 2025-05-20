// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ConstructorMapa.h" // Interfaz
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConstructorMapaNivelUno.generated.h"
class AMapaDelJuego; class ABloqueMuro; class ABloquePiedra; class ABloqueTransparente; class APuertaNivel; class APuente; class APowerUpBloque;
UCLASS()
class BUILDER_API AConstructorMapaNivelUno : public AActor, public IConstructorMapa
{
    GENERATED_BODY()

public:
    AConstructorMapaNivelUno();

protected:
    /*
    UPROPERTY() // El producto que se est� construyendo
        AMapaDelJuego* MapaEnConstruccion;
    */

    class AMapaDelJuego* MapaEnConstruccion;

    /*
    // Clases de los Actores a instanciar (configurables en Blueprint)
    UPROPERTY(EditDefaultsOnly, Category = "Clases de Bloques")
    TSubclassOf<ABloqueMuro> BloqueMuroClass;

    UPROPERTY(EditDefaultsOnly, Category = "Clases de Bloques")
    TSubclassOf<ABloquePiedra> BloquePiedraClass; // Asume que BloquePiedra maneja las variantes 1,2,3

    UPROPERTY(EditDefaultsOnly, Category = "Clases de Bloques")
    TSubclassOf<ABloqueTransparente> BloqueTransparenteClass;

    UPROPERTY(EditDefaultsOnly, Category = "Clases de Objetos")
    TSubclassOf<APuertaNivel> PuertaNivelClass;

    UPROPERTY(EditDefaultsOnly, Category = "Clases de Objetos")
    TSubclassOf<APuente> PuenteClass; // Si existe

    UPROPERTY(EditDefaultsOnly, Category = "Clases de Objetos")
    TSubclassOf<APowerUpBloque> PowerUpBloqueClass;
    */

public:
    // Implementaci�n de IConstructorMapa
    virtual void IniciarNuevoMapa() override;
    virtual void ConstruirBloqueMuro() override;
    virtual void ConstruirBloquePiedra() override;
    virtual void ConstruirBloqueTransparente() override;
    virtual void ConstruirPuerta() override;
    virtual void ConstruirPuente() override;
    virtual void ConstruirPowerUp() override;
    //virtual AMapaDelJuego* ObtenerMapa() override;


    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override; // Podr�a llamar a IniciarNuevoMapa aqu� si el builder se usa solo una vez.
};
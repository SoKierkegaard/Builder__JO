// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "ConstructorMapa.h" // Interfaz
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConstructorMapaNivelUno.generated.h"
class ABloqueMuro; class ABloquePiedra; class ABloqueTransparente; class APuertaNivel; class APuente; class APowerUpBloque;
UCLASS()
class BUILDER_API AConstructorMapaNivelUno : public AActor, public IConstructorMapa
{
    GENERATED_BODY()

public:
    AConstructorMapaNivelUno();

protected:
    
    UPROPERTY() // El producto que se está construyendo
		class AMapaDelJuego* MapaDelJuego;
   

public:
    // Implementación de IConstructorMapa
    
    virtual void ConstruirBloqueMuro() override;
    virtual void ConstruirBloqueInterno() override;
	virtual void ConstruirPuerta() override;
	virtual void ConstruirPuente() override;
	virtual void ConstruirPowerUp() override;
    virtual class AMapaDelJuego* GetMapa() override;


    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override; // Podría llamar a IniciarNuevoMapa aquí si el builder se usa solo una vez.
};
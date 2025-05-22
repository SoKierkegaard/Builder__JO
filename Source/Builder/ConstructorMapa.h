// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ConstructorMapa.generated.h"
class AMapaDelJuego;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UConstructorMapa : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BUILDER_API IConstructorMapa
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    //virtual void IniciarNuevoMapa() = 0;
    virtual void ConstruirBloqueMuro() = 0;
	virtual void ConstruirBloqueInterno() = 0;
    virtual void ConstruirPuerta() = 0;
    virtual void ConstruirPuente() = 0; // Si es un actor específico
    virtual void ConstruirPowerUp() = 0;
    virtual class AMapaDelJuego* GetMapa() = 0;
};

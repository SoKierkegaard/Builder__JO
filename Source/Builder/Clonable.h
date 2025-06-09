// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Clonable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UClonable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BUILDER_API IClonable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * Crea y devuelve un clon de este objeto.
	 * La clase que implementa es responsable de la creación y copia de propiedades.
	 * El clon devuelto debe ser del mismo tipo concreto.
	 */
	virtual AActor* Clonar() = 0; // Devolvemos AActor* ya que ABloquePiedra es un Actor
};

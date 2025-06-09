// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"

#include "EnemigoTerrestre.generated.h"



UCLASS()
class BUILDER_API AEnemigoTerrestre : public AEnemigo
{
	GENERATED_BODY()

public:
	/** Constructor por defecto de la clase AEnemigoTerrestre. */
	AEnemigoTerrestre();

protected:
	/** Se llama cuando el juego comienza o cuando el actor es instanciado.
	 *  Permite a�adir l�gica de inicializaci�n espec�fica para EnemigoTerrestre despu�s de que AEnemigo::BeginPlay() se ejecute.
	 */
	virtual void BeginPlay() override;

public:
	/** Se llama en cada frame.
	 * Permite a�adir o modificar la l�gica de actualizaci�n de AEnemigo para este tipo espec�fico.
	 * @param DeltaTime El tiempo en segundos transcurrido desde el �ltimo frame.
	 */
	virtual void Tick(float DeltaTime) override;

	// Aqu� podr�as a�adir propiedades o m�todos espec�ficos para los enemigos terrestres.
	// Por ejemplo:
	// UPROPERTY(EditAnywhere, Category = "EnemigoTerrestre")
	// float VelocidadDeCarga; // Una habilidad especial de carga.

	// virtual void RealizarAtaqueCarga();
};
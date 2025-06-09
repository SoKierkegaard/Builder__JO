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
	 *  Permite añadir lógica de inicialización específica para EnemigoTerrestre después de que AEnemigo::BeginPlay() se ejecute.
	 */
	virtual void BeginPlay() override;

public:
	/** Se llama en cada frame.
	 * Permite añadir o modificar la lógica de actualización de AEnemigo para este tipo específico.
	 * @param DeltaTime El tiempo en segundos transcurrido desde el último frame.
	 */
	virtual void Tick(float DeltaTime) override;

	// Aquí podrías añadir propiedades o métodos específicos para los enemigos terrestres.
	// Por ejemplo:
	// UPROPERTY(EditAnywhere, Category = "EnemigoTerrestre")
	// float VelocidadDeCarga; // Una habilidad especial de carga.

	// virtual void RealizarAtaqueCarga();
};
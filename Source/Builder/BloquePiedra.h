// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bloque.h"
#include "Clonable.h" // Ensure the header file for IClonable is included
#include "GameFramework/Actor.h"
#include "BloquePiedra.generated.h"


UCLASS()
class BUILDER_API ABloquePiedra : public ABloque, public IClonable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABloquePiedra();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Propiedades Bloque")
	float Resistencia;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Propiedades Bloque")
	FString TipoPiedra;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual AActor* Clonar() override;
	UFUNCTION(BlueprintCallable, Category = "Acciones Bloque")
	void MostrarDetalles();

	UFUNCTION(BlueprintCallable, Category = "Acciones Bloque")
	void ConfigurarBloque(float NuevaResistencia, const FString& NuevoTipoPiedra); // Pasar FString como const referencia

};
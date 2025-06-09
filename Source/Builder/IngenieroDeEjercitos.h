// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ConstructorEjercito.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IngenieroDeEjercitos.generated.h"
class IConstructorEjercito; class AEjercito; class ConstruirEjercitoMiselaneo;
UCLASS()
class BUILDER_API AIngenieroDeEjercitos : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIngenieroDeEjercitos();

public:


	void ConstruirEjercito();
	void SetConstructorEjercito(AActor* Constructor);
	class AEjercito* GetEjercito(); // Método para obtener el mapa construido


private:
	IConstructorEjercito* ConstructorEjercito; // El constructor que implementa la interfaz IConstructorMapa

protected:
	virtual void BeginPlay() override;
	//FVector CalcularPosicionDesdeIndices(int32 Fila, int32 Columna, float AlturaZ = 0.0f);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};

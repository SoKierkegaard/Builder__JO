// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapaElemento.h" // Incluimos la interfaz
#include "Bloque.generated.h"
UCLASS()
class BUILDER_API ABloque : public AActor, public IMapaElemento // Implementa IMapaElemento
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABloque();

protected:
	// Componente de malla est�tica
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componentes")
	UStaticMeshComponent* MallaBloque;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// --- Implementación de IMapaElemento ---
    virtual void DestruirElemento() override;
public:
	
	float FloatSpeed;
	float RotationSpeed;
	bool bPuedeMoverse;

};

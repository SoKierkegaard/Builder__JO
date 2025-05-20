// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "IngenieroDeMapas.h"
#include "ConstructorMapaNivelUno.h"
#include "MapaDelJuego.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cliente.generated.h"

UCLASS()
class BUILDER_API ACliente : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACliente();


private:
	//The Builder Actor
	//class AConstructorMapaUno* Builder;
	//The Engineer Actor
	class AIngenieroDeMapas* Director;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AConstructorMapaNivelUno* Builder;

};

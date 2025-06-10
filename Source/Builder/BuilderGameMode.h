// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "IngenieroDeMapas.h"
#include "ConstructorMapaNivelUno.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BuilderGameMode.generated.h"
class ACompositeGrupoDeBloques;
UCLASS(minimalapi)
class ABuilderGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABuilderGameMode();
private:
	//The Builder Actor
	class AConstructorMapaNivelUno* Constructor;
	//The Engineer Actor
	class AIngenieroDeMapas* Director;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Para probar, podríamos tener una referencia a un grupo
    UPROPERTY()
    ACompositeGrupoDeBloques* GrupoDePrueba;

    // Para la prueba de destrucción
    FTimerHandle TimerHandle_DestruirGrupo;
    void EjecutarDestruccionDePrueba();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class ABloquePiedra* PrototipoBloqueGranito; // Un prototipo que configuraremos
};

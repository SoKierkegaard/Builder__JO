// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "IngenieroDeMapas.h"
#include "ConstructorMapaNivelUno.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BuilderGameMode.generated.h"

UCLASS(minimalapi)
class ABuilderGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABuilderGameMode();
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

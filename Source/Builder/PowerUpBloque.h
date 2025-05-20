// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bloque.h"
#include "PowerUpBloque.generated.h"

/**
 * 
 */
UCLASS()
class BUILDER_API APowerUpBloque : public ABloque
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APowerUpBloque();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

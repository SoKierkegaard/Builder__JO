// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FactoryBloques.h"
#include "FactoryBloques.generated.h"

UCLASS()
class BOMBBOT_API AFactoryBloques : public AActor
{
	GENERATED_BODY()
	
public:	
	virtual ABloqueGeneral* CrearBloque(FString TypeBlock, FVector Position) override;

    TArray<AActor*> Bloques;

    UFUNCTION(BlueprintCallable, Category = "Composite") // BlueprintCallable para facilitar pruebas
    void AnadirElemento(AActor* ElementoAAgregar);

    UFUNCTION(BlueprintCallable, Category = "Composite")
    void RemoverElemento(AActor* ElementoARemover);

};
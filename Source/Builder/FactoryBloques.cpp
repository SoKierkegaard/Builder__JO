// Fill out your copyright notice in the Description page of Project Settings.


#include "World1_FactoryBloques.h"

ABloqueGeneral* AFactoryBloques::CrearBloque(FString TypeBlock, FVector Position)
{
	ABloqueGeneral* Bloque = nullptr;
	if (TypeBlock == "BloqueIndestructible")
	{
		Bloque = GetWorld()->SpawnActor<ABloqueGeneral>(ABloqueGeneral::StaticClass(), Position, FRotator::ZeroRotator);
        AñadirElemento(Bloque);
    
    }
	return Bloque;
}

void AFactoryBloques::AnadirElemento(AActor* ElementoAAgregar)
{
    
        Bloques.AddUnique(ElementoAAgregar);
        UE_LOG(LogTemp, Log, TEXT("Elemento %s añadido al grupo %s"), *ElementoAAgregar->GetName(), *GetName());
    
    
}

void AFactoryBloques::RemoverElemento(AActor* ElementoARemover)
{
   
        Bloques.Remove(ElementoARemover);
        UE_LOG(LogTemp, Log, TEXT("Elemento %s removido del grupo %s"), *ElementoARemover->GetName(), *GetName());

}
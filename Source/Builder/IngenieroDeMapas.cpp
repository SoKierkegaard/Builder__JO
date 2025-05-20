// Fill out your copyright notice in the Description page of Project Settings.


#include "IngenieroDeMapas.h"

// Sets default values
AIngenieroDeMapas::AIngenieroDeMapas()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AIngenieroDeMapas::CrearMapaUno()
{
	if (ConstructorMapa)
	{
		ConstructorMapa->ConstruirBloqueMuro();
		ConstructorMapa->ConstruirBloquePiedra();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Builder is not set!"));
	}
}

void AIngenieroDeMapas::CrearMapaDos()
{
	if (ConstructorMapa)
	{
		ConstructorMapa->ConstruirBloqueMuro();
		ConstructorMapa->ConstruirBloqueTransparente();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Builder is not set!"));
	}
}

void AIngenieroDeMapas::CrearPuerta()
{
	if (ConstructorMapa)
	{
		//ConstructorMapa->ConstruirBloqueMuro();
		//ConstructorMapa->ConstruirBloquePiedra();
		ConstructorMapa->ConstruirPuerta();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Builder is not set!"));
	}
}

void AIngenieroDeMapas::CrearPuente()
{
	if (ConstructorMapa)
	{
		//ConstructorMapa->ConstruirBloqueMuro();
		//ConstructorMapa->ConstruirBloquePiedra();
		ConstructorMapa->ConstruirPuente();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Builder is not set!"));
	}
}

void AIngenieroDeMapas::CrearPowerUp()
{
	if (ConstructorMapa)
	{
		//ConstructorMapa->ConstruirBloqueMuro();
		//ConstructorMapa->ConstruirBloquePiedra();
		ConstructorMapa->ConstruirPowerUp();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Builder is not set!"));
	}
}

void AIngenieroDeMapas::SetBuilder(IConstructorMapa* NewBuilder)
{
	ConstructorMapa = NewBuilder;
}

void AIngenieroDeMapas::ConstructorDeMapa()
{
	ConstructorMapa->ConstruirBloqueMuro();
}





// Called when the game starts or when spawned
void AIngenieroDeMapas::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AIngenieroDeMapas::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




// Fill out your copyright notice in the Description page of Project Settings.


#include "IngenieroDeEjercitos.h"
#include "ConstructorEjercito.h"
#include "ConstructorEjercitoMiselaneo.h"

// Sets default values
AIngenieroDeEjercitos::AIngenieroDeEjercitos()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AIngenieroDeEjercitos::SetConstructorEjercito(AActor* Constructor)
{
	ConstructorEjercito = Cast<IConstructorEjercito>(Constructor);
}

void AIngenieroDeEjercitos::ConstruirEjercito()
{
	ConstructorEjercito->ConstruirComandante();
	ConstructorEjercito->ConstruirPrimerEnemigo();
	ConstructorEjercito->ConstruirSegundoEnemigo();
}

AEjercito* AIngenieroDeEjercitos::GetEjercito()
{
	return ConstructorEjercito->GetEjercito();
}

// Called when the game starts or when spawned
void AIngenieroDeEjercitos::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AIngenieroDeEjercitos::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


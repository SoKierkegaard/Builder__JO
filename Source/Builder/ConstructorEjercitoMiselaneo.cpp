// Fill out your copyright notice in the Description page of Project Settings.
#include "ConstructorEjercitoMiselaneo.h"
#include "Ejercito.h"




// Sets default values
AConstructorEjercitoMiselaneo::AConstructorEjercitoMiselaneo()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AConstructorEjercitoMiselaneo::BeginPlay()
{
	Super::BeginPlay();

	Ejercito = GetWorld()->SpawnActor<AEjercito>(AEjercito::StaticClass());

	Ejercito->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
}


void AConstructorEjercitoMiselaneo::ConstruirComandante()
{
	Ejercito->SetComandante(3);
}

void AConstructorEjercitoMiselaneo::ConstruirPrimerEnemigo()
{
	Ejercito->SetPrimerEnemigo(1);
}


void AConstructorEjercitoMiselaneo::ConstruirSegundoEnemigo()
{
	Ejercito->SetSegundoEnemigo(2);
}


AEjercito* AConstructorEjercitoMiselaneo::GetEjercito()
{
	return Ejercito;
}

// Called every frame
void AConstructorEjercitoMiselaneo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
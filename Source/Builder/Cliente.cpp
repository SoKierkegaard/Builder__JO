// Fill out your copyright notice in the Description page of Project Settings.


#include "Cliente.h"

// Sets default values
ACliente::ACliente()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACliente::BeginPlay()
{
	Super::BeginPlay();
    //Crerar el constructor del ejercito
    ConstructorEjercito = GetWorld()->SpawnActor<AConstructorEjercitoMiselaneo>(AConstructorEjercitoMiselaneo::StaticClass());
    // Crear el ingeniero de ejercitos
    IngenieroEjercitos = GetWorld()->SpawnActor<AIngenieroDeEjercitos>(AIngenieroDeEjercitos::StaticClass());



    // Set the Builder for the Engineer and create the Army 
    IngenieroEjercitos->SetConstructorEjercito(ConstructorEjercito);
    IngenieroEjercitos->ConstruirEjercito();
    AEjercito* Ejercito = IngenieroEjercitos->GetEjercito();
}

// Called every frame
void ACliente::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


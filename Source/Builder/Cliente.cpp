// Fill out your copyright notice in the Description page of Project Settings.

#include "IngenieroDeMapas.h"
#include "ConstructorMapaNivelUno.h"
#include "MapaDelJuego.h"
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



}

// Called every frame
void ACliente::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


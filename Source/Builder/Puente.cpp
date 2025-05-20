// Fill out your copyright notice in the Description page of Project Settings.


#include "Puente.h"

// Sets default values
APuente::APuente()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (MallaBloque)
	{
		// Asignar un material específico para el bloque de césped
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Ground_Grass.M_Ground_Grass'"));
		if (MaterialBase.Succeeded())
		{
			MallaBloque->SetMaterial(0, MaterialBase.Object); // Asignar el material al slot 0
		}
	}

}

// Called when the game starts or when spawned
void APuente::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APuente::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


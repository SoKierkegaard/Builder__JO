// Fill out your copyright notice in the Description page of Project Settings.


#include "PuertaNivel.h"

// Sets default values
APuertaNivel::APuertaNivel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (MallaBloque)
		if (MallaBloque)
		{
			static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/Ladrillo2k.Ladrillo2k'"));
			if (MaterialBase.Succeeded())
			{
				MallaBloque->SetMaterial(0, MaterialBase.Object); // Asignar el material al slot 0
			}
		}

}

// Called when the game starts or when spawned
void APuertaNivel::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APuertaNivel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


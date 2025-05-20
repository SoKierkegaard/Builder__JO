// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpBloque.h"

// Sets default values
APowerUpBloque::APowerUpBloque()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (MallaBloque)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/Burbuja.Burbuja'"));
		if (MaterialBase.Succeeded())
		{
			MallaBloque->SetMaterial(0, MaterialBase.Object);
		}
	}

}

// Called when the game starts or when spawned
void APowerUpBloque::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APowerUpBloque::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


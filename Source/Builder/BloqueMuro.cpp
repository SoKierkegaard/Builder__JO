// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueMuro.h"

// Sets default values
ABloqueMuro::ABloqueMuro()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    if (MallaBloque)
    {
        static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Metal_Chrome.M_Metal_Chrome'"));

        if (MaterialBase.Succeeded())
        {
            MallaBloque->SetMaterial(0, MaterialBase.Object); // Asignar el material al slot 0
        }
    }

}

// Called when the game starts or when spawned
void ABloqueMuro::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ABloqueMuro::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}


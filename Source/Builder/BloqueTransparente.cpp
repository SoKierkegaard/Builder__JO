// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueTransparente.h"

// Sets default values
ABloqueTransparente::ABloqueTransparente()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    if (MallaBloque)
    {
        static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Tech_Panel.M_Tech_Panel'"));

        if (MaterialBase.Succeeded())
        {
            MallaBloque->SetMaterial(0, MaterialBase.Object); // Asignar el material al slot 0
        }
    }

}

// Called when the game starts or when spawned
void ABloqueTransparente::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ABloqueTransparente::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ABloqueTransparente::DestruirElemento()
{
    Super::DestruirElemento();
    UE_LOG(LogTemp, Log, TEXT("BloqueTransparente (%s) destruido."), *GetName());
}


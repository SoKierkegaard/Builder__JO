// Fill out your copyright notice in the Description page of Project Settings.


#include "Bloque.h"
#include "UObject/ConstructorHelpers.h" // Para cargar assets
#include "Components/StaticMeshComponent.h"

// Sets default values
ABloque::ABloque()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MallaBloque = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaBloque"));
	//RootComponent = MeshComp;
	MallaBloque->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjetoMallaBloque(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	if (ObjetoMallaBloque.Succeeded())
	{
		MallaBloque->SetStaticMesh(ObjetoMallaBloque.Object);

		MallaBloque->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

		MallaBloque->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	}

	FloatSpeed = 5.0f;
	RotationSpeed = 3.0f;

	bPuedeMoverse = FMath::RandBool();

	// Tama�o del bloque (se puede modificar desde el editor o c�digo)
	//TamanoBloque = FVector(1.0f, 1.0f, 2.0f); // Escala predeterminada

	// Aplicar el tama�o al bloque
	//MallaBloque->SetWorldScale3D(TamanoBloque);
}

void ABloque::DestruirElemento()
{
    UE_LOG(LogTemp, Log, TEXT("Bloque (%s) siendo destruido."), *GetName());
    // Lógica adicional antes de destruir si es necesario (ej. spawnear power-up)
    Destroy(); // Destruye el actor
}

// Called when the game starts or when spawned
void ABloque::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABloque::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	if (bPuedeMoverse)
	{
		FVector NewLocation = GetActorLocation();
		FRotator NewRotation = GetActorRotation();
		float RunningTime = GetGameTimeSinceCreation();

		// Aleatoriedad en el desplazamiento en Z
		float DeltaHeight = FMath::FRandRange(-1.0f, 1.0f) * FloatSpeed;
		NewLocation.Z += DeltaHeight;

		// Aleatoriedad en la rotaci�n
		float DeltaRotation = FMath::FRandRange(-1.0f, 1.0f) * RotationSpeed;
		NewRotation.Yaw += DeltaRotation;

		SetActorLocationAndRotation(NewLocation, NewRotation);
	}*/
}
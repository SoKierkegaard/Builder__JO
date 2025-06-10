// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomba.h"
#include "Explosion.h"
//Para efecto explosion
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
// Sets default values
ABomba::ABomba()
{
    PrimaryActorTick.bCanEverTick = true;

    MallaBomba = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MallaBomba"));
    RootComponent = MallaBomba; // Importante que la malla sea root, o SetupAttachment

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> ObjetoMallaBomba(TEXT("/Script/Engine.SkeletalMesh'/Game/ActionsCharacter/Bomb/SKM_Robot.SKM_Robot'"));
    if (ObjetoMallaBomba.Succeeded()) {
        MallaBomba->SetSkeletalMesh(ObjetoMallaBomba.Object);
        MallaBomba->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
        MallaBomba->SetRelativeScale3D(FVector(0.9f, 0.9f, 0.9f));
    }

    static ConstructorHelpers::FObjectFinder<UAnimationAsset> AnimacionAsset(TEXT("/Game/ActionsCharacter/Bomb/SKM_Robot_Anim"));
    if (AnimacionAsset.Succeeded()) {
        AnimacionBomba = AnimacionAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<UParticleSystem> ExplosionEffectAsset(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
    if (ExplosionEffectAsset.Succeeded())
    {
        ExplosionEffect = ExplosionEffectAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/Sounds/Bomb/explosion1.explosion1"));

    if (SoundAsset.Succeeded())
    {
        SonidoBomba = SoundAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset2(TEXT("/Script/Engine.SoundWave'/Game/Sounds/Bomb/place_bomb1.place_bomb1'"));
    if (SoundAsset2.Succeeded())
    {
        SonidoColocar = SoundAsset2.Object;
    }
}

// Called when the game starts or when spawned
void ABomba::BeginPlay()
{
    Super::BeginPlay();

    //Reproducir sonido al colocar la bomba
    UGameplayStatics::PlaySoundAtLocation(this,SonidoColocar, GetActorLocation());
    if (AnimacionBomba)
    {
        MallaBomba->PlayAnimation(AnimacionBomba, true);
        GEngine->AddOnScreenDebugMessage(1, 15.0f, FColor::Black, TEXT("Se ha reproducido la animacion de la bomba"));
    }
    GetWorld()->GetTimerManager().SetTimer(TimerHandle_Disparar, this, &ABomba::Shoot, tiempo_explosion, false); // Dispara cada 5 segundos
    GetWorld()->GetTimerManager().SetTimer(TH_Explosion, this, &ABomba::explotar, tiempo_explosion+0.05f, false);
}

// Called every frame
void ABomba::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABomba::Shoot()
{
    Direcciones = {
        FVector(1, 0, 0),
        FVector(-1, 0, 0),
        FVector(0, 1, 0),
        FVector(0, -1, 0)
    };

    for (const FVector& Dir : Direcciones)
    {
        FRotator Rotacion = Dir.Rotation(); // Obtener la rotaci�n que mira en esa direcci�n
        AExplosion* NuevaExplosion = GetWorld()->SpawnActor<AExplosion>(GetActorLocation(), Rotacion);
        if (NuevaExplosion)
        {
            NuevaExplosion->MoveDirection = Dir;
        }
    }
}

void ABomba::explotar()
{

    Destroy();
    FVector ubi_explosion=GetActorLocation();
    efecto_explosion(ubi_explosion);
    //Reproducir el sonido
    UGameplayStatics::PlaySoundAtLocation(this, SonidoBomba, GetActorLocation());

}

void ABomba::efecto_explosion(FVector Location)
{
    if (ExplosionEffect && GetWorld())
    {
        UGameplayStatics::SpawnEmitterAtLocation(
            GetWorld(),
            ExplosionEffect,
            Location,
            FRotator::ZeroRotator,
            ExplosionScale,  // Aqu� se aplica la escala
            true
        );
    }
}

void ABomba::DetonarInmediatamente()
{
   if (IsPendingKill()) return; // Ya se está destruyendo

   GetWorldTimerManager().ClearTimer(TimerHandle_Disparar);
   GetWorldTimerManager().ClearTimer(TH_Explosion);

   // Importante: Shoot() crea explosiones. explotar() destruye la bomba.
   // Hay que tener cuidado con el orden y el estado.
   if (GetWorld()) // Asegurarse que el mundo aún es válido
   {
       Shoot(); // Genera las explosiones
       // explotar() se encarga de efectos visuales/sonido de la detonación de la bomba y Destroy()
       // Es mejor que explotar no llame a Shoot(), sino que Shoot se llame antes de la detonación final.
       // Originalmente, Shoot() se llama justo antes de explotar() por el timer.
       // Así que aquí, si vamos a llamar a explotar(), Shoot() ya debería haber ocurrido
       // o lo llamamos nosotros.

       FVector ubi_explosion = GetActorLocation();
       efecto_explosion(ubi_explosion);
       UGameplayStatics::PlaySoundAtLocation(this, SonidoBomba, GetActorLocation());
       Destroy(); // Destruye la bomba
   }
}
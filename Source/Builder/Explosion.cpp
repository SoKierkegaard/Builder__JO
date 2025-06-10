// Fill out your copyright notice in the Description page of Project Settings.


#include "Explosion.h"
#include "Bloque.h"
#include "BloqueMuro.h"
#include "BloquePiedra.h"

#include <Kismet/GameplayStatics.h>
#include "GameFramework/Character.h"

//Para efecto explosion
//kismet GameplayStatics tambien se usa
#include "Particles/ParticleSystem.h"


// Sets default values
AExplosion::AExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    ExplosionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExplosionMesh"));
    RootComponent = ExplosionMesh;

    ConstructorHelpers::FObjectFinder<UStaticMesh> ExplosionMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
    //ConstructorHelpers::FObjectFinder<UStaticMesh> ExplosionMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/ActionsCharacter/LowPoly_Fireball/Sphere.Sphere'"));
    if (ExplosionMeshAsset.Succeeded())
    {
        ExplosionMesh->SetStaticMesh(ExplosionMeshAsset.Object);
        ExplosionMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
    }
    
    ConstructorHelpers::FObjectFinder<UMaterial> MaterialExplosionAsset(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold'"));
    //ConstructorHelpers::FObjectFinder<UMaterial> MaterialExplosionAsset(TEXT("/Script/Engine.Material'/Game/ActionsCharacter/LowPoly_Fireball/Material_001.Material_001'"));
    if (MaterialExplosionAsset.Succeeded())
    {
        ExplosionMesh->SetMaterial(0, MaterialExplosionAsset.Object);
    }
    //aqui se carga el asset de la explosion para invocarlo con el tick a cada instante que se dibuja la explosion
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ExplosionEffectAsset(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
    if (ExplosionEffectAsset.Succeeded())
    {
        ExplosionEffect = ExplosionEffectAsset.Object;
    }
    
    ExplosionMesh->SetSimulatePhysics(true);
    ExplosionMesh->SetNotifyRigidBodyCollision(true);
    ExplosionMesh->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
    ExplosionMesh->SetEnableGravity(false);
    ExplosionMesh->SetVisibility(false);

    ExplosionMesh->OnComponentHit.AddDynamic(this, &AExplosion::OnHit);
}

// Called when the game starts or when spawned
void AExplosion::BeginPlay()
{
	Super::BeginPlay();
	
    InitialPosition = GetActorLocation();
}

// Called every frame
void AExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    CurrentPosition = GetActorLocation();
    DeltaMove = MoveDirection.GetSafeNormal() * MoveSpeed * DeltaTime;
    NewPosition = CurrentPosition + DeltaMove;
    SetActorLocation(NewPosition);

    efecto_explosion(NewPosition);

    TraveledDistance = FVector::Dist(InitialPosition, NewPosition);
   
    if (TraveledDistance >= TargetDistance)
    {
        Destroy();
    }
}

void AExplosion::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this)
    {
        if (OtherActor->IsA(ABloque::StaticClass()))
        {
            if (OtherActor->IsA(ABloqueMuro::StaticClass()))
            {
                Destroy();
            }
            else
            {
                OtherActor->Destroy();
                //Aqui se puede agregar un Destroy()
            }
        }
        else if (OtherActor->IsA(ABloquePiedra::StaticClass()))
        {
            // Ejemplo: destruir el escudo al contacto
            OtherActor->Destroy();

            // Tal vez tambi�n destruir la explosi�n
            Destroy();
        }
        else if (OtherActor->IsA(ACharacter::StaticClass()))
        {
            OtherActor->Destroy();
        }
        else if (OtherActor->IsA(ABomba::StaticClass()))
        {
            ABomba* OtraBomba = Cast<ABomba>(OtherActor);
            if (OtraBomba && !OtraBomba->IsPendingKill()) // No detonar si ya está explotando
            {
                UE_LOG(LogTemp, Log, TEXT("Explosión alcanzó otra bomba, detonándola en cadena."));
                OtraBomba->DetonarInmediatamente();
            }
            Destroy(); // La explosión se consume al detonar otra bomba
        }
        else
        {
            // Si no es un bloque, escudo o personaje, simplemente destruir la explosión
            Destroy();
        }
    }
}

void AExplosion::efecto_explosion(FVector Location)
{
    if (ExplosionEffect && GetWorld())
    {
        UGameplayStatics::SpawnEmitterAtLocation(
            GetWorld(),
            ExplosionEffect,
            Location,
            FRotator::ZeroRotator,
            //ExplosionScale,  // Aqu� se aplica la escala
            true
        );
    }
}
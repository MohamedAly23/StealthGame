#include "Boomerang.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ABoomerang::ABoomerang()
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    RootComponent = StaticMeshComponent;

    RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));

    BoomerangAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BoomerangAudioComponent"));
    BoomerangAudioComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABoomerang::BeginPlay()
{
    Super::BeginPlay();

    SetActorTickEnabled(false);

    StaticMeshComponent->OnComponentHit.AddDynamic(this, &ABoomerang::OnHit);

    RotatingMovementComponent->RotationRate = FRotator(RollRotate, YawRotate, PitchRotate);
    RotatingMovementComponent->Deactivate();
}

// Called every frame
void ABoomerang::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
 
    if (!bBoomerangReturning) 
    {
        ThrowBoomerang(DeltaTime);
    }
    if (bBoomerangReturning) 
    {
        ReturnToPlayer(DeltaTime);
    }
}
void ABoomerang::ThrowBoomerang(float DeltaTime)
{
    if (ElapsedTime < ThrowDuration)
    {
        RotatingMovementComponent->Activate(true);
        MoveTowardsTarget(StartLocation,TargetLocation, DeltaTime);
    }
    else if (ElapsedTime >= ThrowDuration || HitActor)
    {
        OnBoomerangUpdateState(true, true);
        StartLocation = GetActorLocation();
    }
}

void ABoomerang::ReturnToPlayer(float DeltaTime)
{
    HitActor = nullptr; // clear hit actor 
    FVector SocketLocation = PlayerMesh->GetSocketLocation(FName("hand_rSocket"));
    MoveTowardsTarget(StartLocation,SocketLocation, DeltaTime);
    
    if (FVector::Dist(GetActorLocation(), SocketLocation) < DistanceOfAttachment)
    {
        AttachBoomerangToComponent();
        EnableInputAction();
        OnBoomerangUpdateState(false, false);
        ThrowDuration = CurrentThrowDuration;
        RotatingMovementComponent->Deactivate();
        BoomerangAudioComponent->Stop();
        SetActorEnableCollision(true);
    }
}

APlayerController* ABoomerang::GetPlayerController() const 
{
    return GetWorld()->GetFirstPlayerController();
}

void ABoomerang::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    HitActor = OtherActor;
}

void ABoomerang::MoveTowardsTarget(const FVector& Start , const FVector& Target, float DeltaTime)
{
    ElapsedTime += DeltaTime;
    float Progress = ElapsedTime / ThrowDuration;
    FVector NewLocation = FMath::Lerp(Start, Target, Progress);
    float HorizontalOffset = FMath::Sin(Progress * PI) * ArcHeight;
    NewLocation.Y += HorizontalOffset;
    NewLocation.Z += HorizontalOffset;
    SetActorLocation(NewLocation, true);
}

void ABoomerang::OnBoomerangUpdateState(bool ReturningState, bool TickState)
{
    ElapsedTime = 0.0f;
    bBoomerangReturning = ReturningState;
    if (bBoomerangReturning) 
    {
        SetActorEnableCollision(false);
    }

    SetActorTickEnabled(TickState);
}

void ABoomerang::EnableInputAction()
{
    GetPlayerController()->ResetIgnoreMoveInput();
}

void ABoomerang::AttachBoomerangToComponent()
{
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
    FName SocketName = PlayerMesh->GetSocketBoneName(TEXT("hand_rSocket"));
    AttachToComponent(PlayerMesh, AttachmentRules, SocketName);
}

APawn* ABoomerang::GetPlayerPawn() const
{
    check(GetPlayerController());
    return GetPlayerController()->GetPawn();
}

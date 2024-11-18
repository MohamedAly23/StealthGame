#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Boomerang.generated.h"

// Class representing a boomerang actor in the game (movement, material, ... )
UCLASS() 
class STEALTHGAME_API ABoomerang : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABoomerang();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
    UStaticMeshComponent* StaticMeshComponent;

    UPROPERTY(EditAnywhere, Category = "Boomerang")
    float DistanceOfAttachment = 100.0f;

    // Time taken to reach the target
    UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Boomerang")
    float ThrowDuration = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Boomerang")
    float CurrentThrowDuration = 2.0f;

    // Value of curve
    UPROPERTY(EditAnywhere, Category = "Boomerang")
    float ArcHeight = 25.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadwrite, Category = "Boomerang")
    USkeletalMeshComponent* PlayerMesh;

    UPROPERTY(EditAnywhere, Category = "Boomerang")
    float RollRotate;
    UPROPERTY(EditAnywhere, Category = "Boomerang")
    float YawRotate;
    UPROPERTY(EditAnywhere, Category = "Boomerang")
    float PitchRotate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    UAudioComponent* BoomerangAudioComponent;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadwrite, Category = "Boomerang")
    FVector TargetLocation;

    UPROPERTY(VisibleAnywhere, BlueprintReadwrite, Category = "Boomerang")
    FVector StartLocation;


private:
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    UFUNCTION()
    void MoveTowardsTarget(const FVector& Start,const FVector& Target, float DeltaTime);

    UPROPERTY()
    AActor* HitActor = nullptr;

    UFUNCTION()
    APlayerController* GetPlayerController() const;

    UPROPERTY()
    float ElapsedTime = 0.0f;

    UFUNCTION()
    void ReturnToPlayer(float DeltaTime);

    UFUNCTION()
    void ThrowBoomerang(float DeltaTime);

    UPROPERTY()
    bool bBoomerangReturning = false;

    UFUNCTION()
    APawn* GetPlayerPawn() const;

    UFUNCTION()
    void OnBoomerangUpdateState(bool ReturningState,bool TickState);

    UFUNCTION()
    void EnableInputAction();

    UFUNCTION()
    void AttachBoomerangToComponent();

    UPROPERTY()
    URotatingMovementComponent* RotatingMovementComponent;

};

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameModeStealthGame.h"
#include "Components/CapsuleComponent.h" 

// Sets default values
APlayerCharacter::APlayerCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter::OnPlayerTakeCoin(AActor* OtherActor)
{
    if (ensure(OtherActor))
    {
        OtherActor->Destroy();
    }

    AGameModeStealthGame* StealthGameMode = Cast<AGameModeStealthGame>(UGameplayStatics::GetGameMode(this));

    check(StealthGameMode);
    StealthGameMode->AddScore(CoinPoint);

    IncrementCoinsCollected();

    if (StealthGameMode->GetCoinsNumber() == 0)
    {
        OnAllCoinsCollected.Broadcast();
    }
}

void APlayerCharacter::OnEnemyCatchPlayer()
{
    OnPlayerCaught.Broadcast();
}

void APlayerCharacter::IncrementCoinsCollected()
{
    CoinsCollected++;
}

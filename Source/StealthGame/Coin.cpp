#include "Coin.h"
#include "GameModeStealthGame.h"

// Sets default values
ACoin::ACoin()
{
    // Set this actor to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
    Super::BeginPlay();

    check(CacheGameMode());

    StealthGameMode->AddOneCoinNumber();
}

void ACoin::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    check(StealthGameMode);

    StealthGameMode->DeleteOneCoinNumber();
}

AGameModeStealthGame* ACoin::CacheGameMode()
{
    StealthGameMode = Cast<AGameModeStealthGame>(GetWorld()->GetAuthGameMode());
    return StealthGameMode;
}

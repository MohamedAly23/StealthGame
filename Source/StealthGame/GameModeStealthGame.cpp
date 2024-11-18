#include "GameModeStealthGame.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "StealthGameInstance.h" 
#include "Coin.h"
#include "EnemyCharacter.h"

AGameModeStealthGame::AGameModeStealthGame()
{
    PlayerScore = 0;
    CoinsCount = 0;
    EnemyCount = 0;
}

void AGameModeStealthGame::BeginPlay()
{
    APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
    check(PlayerCharacter);
    PlayerCharacter->OnAllCoinsCollected.AddDynamic(this, &AGameModeStealthGame::BroadcastPlayerWin);
    PlayerCharacter->OnPlayerCaught.AddDynamic(this, &AGameModeStealthGame::BroadcastPlayerLose);

    CacheStealthGameInstance();
}

void AGameModeStealthGame::BroadcastPlayerWin()
{
    OnPlayerWin.Broadcast();
}

void AGameModeStealthGame::BroadcastPlayerLose()
{
    OnPlayerLose.Broadcast();
}

UStealthGameInstance* AGameModeStealthGame::CacheStealthGameInstance() const
{
    GameInstance = Cast<UStealthGameInstance>(UGameplayStatics::GetGameInstance(this));
    return GameInstance;
}

void AGameModeStealthGame::AddScore(int32 Points)
{
    check(GameInstance);

    PlayerScore = GameInstance->GetScore();
    PlayerScore += Points;
    GameInstance->SetScore(PlayerScore);

    OnStatsUpdated.Broadcast(GetScore(), GetCoinsNumber());
}

int32 AGameModeStealthGame::GetEnemiesNumber() const
{
    return EnemyCount;
}

int32 AGameModeStealthGame::GetCoinsNumber() const
{
    return CoinsCount;
}

int32 AGameModeStealthGame::GetScore() const
{
    return GameInstance->GetScore();
}

void AGameModeStealthGame::AddOneCoinNumber()
{
    CoinsCount++;
}

void AGameModeStealthGame::DeleteOneCoinNumber()
{
    CoinsCount--;
}

void AGameModeStealthGame::AddOneEnemyNumber()
{
    EnemyCount++;
}

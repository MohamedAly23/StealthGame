#include "PlayerHUD.h"
#include "EndLevelWidget.h"
#include "GameModeStealthGame.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"

void APlayerHUD::BeginPlay()
{
    Super::BeginPlay();

    check(CacheGameMode());

    GameMode->OnStatsUpdated.AddDynamic(this, &APlayerHUD::UpdateHUD);
    GameMode->OnPlayerWin.AddDynamic(this, &APlayerHUD::HandlePlayerWin);
    GameMode->OnPlayerLose.AddDynamic(this, &APlayerHUD::HandlePlayerLose);

    if (ensureMsgf(EndLevelWidgetClass, TEXT("You Miss Widget Class")))
    {
        EndLevelWidget = CreateWidget<UEndLevelWidget>(GetWorld(), EndLevelWidgetClass);
        if (ensure(EndLevelWidget))
        {
            EndLevelWidget->AddToViewport();
            EndLevelWidget->SetGameInfo(GameMode->GetScore(), GameMode->GetCoinsNumber(), GameMode->GetEnemiesNumber());
        }
    }
}

void APlayerHUD::UpdateHUD(int32 Score, int32 Coins)
{
    if (ensure(EndLevelWidget))
    {
        EndLevelWidget->UpdateScore(Score);
        EndLevelWidget->UpdateCoins(Coins);
    }
}

void APlayerHUD::HandlePlayerWin()
{
    check(GameMode);

    if (ensure(EndLevelWidget))
    {
        EndLevelWidget->ShowWinMessage(GameMode->GetScore());
        StartCameraFade(FadeCameraDuration, FadeCameraColor);
        UGameplayStatics::PlaySound2D(this, WinSound);
    }
    GetOwningPawn()->DisableInput(GetOwningPlayerController());
    GetWorldTimerManager().SetTimer(LevelEndTimerHandle, this, &APlayerHUD::OpenNextLevel, OpenNextLevelDelay, false);
    FocusOnGame();
}

void APlayerHUD::HandlePlayerLose()
{
    check(GameMode);

    if (ensure(EndLevelWidget))
    {
        EndLevelWidget->ShowLoseMessage(GameMode->GetScore());
        StartCameraFade(FadeCameraDuration, FadeCameraColor);
        UGameplayStatics::PlaySound2D(this, LoseSound);
    }

    GetOwningPawn()->DisableInput(GetOwningPlayerController());
    GetWorldTimerManager().SetTimer(LevelEndTimerHandle, this, &APlayerHUD::ResetGameAndScore, OpenNextLevelDelay, false);
    FocusOnGame();
}

void APlayerHUD::FocusOnGame()
{
    APlayerController* PlayerController = GetOwningPlayerController();
    check(PlayerController);
    PlayerController->SetInputMode(FInputModeGameOnly());
    PlayerController->bShowMouseCursor = false;
}

int32 APlayerHUD::GetCurrentLevelIndex() 
{
    const FName CurrentLevelName = FName(*UGameplayStatics::GetCurrentLevelName(GetWorld()));
    return LevelNames.IndexOfByKey(CurrentLevelName);
}

void APlayerHUD::StartCameraFade(float FadeDuration, FLinearColor FadeColor)
{
    APlayerController* PlayerController = GetOwningPlayerController();
    if (ensure(PlayerController))
    {
        PlayerController->PlayerCameraManager->StartCameraFade
        (
            0.0f,
            1.0f, 
            FadeDuration,  
            FadeColor,             
            false,                   
            true
        );
    }
}

void APlayerHUD::OpenNextLevel()
{
    int32 CurrentIndex = GetCurrentLevelIndex();
    if (CurrentIndex != INDEX_NONE && CurrentIndex < LevelNames.Num() - 1)
    {
        FName NextLevelName = LevelNames[CurrentIndex + 1];
        UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
    }
    else
    {
        FName CurrentLevelName = FName(*UGameplayStatics::GetCurrentLevelName(GetWorld()));
        UGameplayStatics::OpenLevel(GetWorld(), CurrentLevelName);
    }
}


void APlayerHUD::ResetGameAndScore()
{
    if (ensure(LevelNames.Num())) 
    {
        GameMode->GameInstance->SetScore(0);
        FName FirstLevel = LevelNames[0];
        UGameplayStatics::OpenLevel(GetWorld(), FirstLevel);
    }
}

AGameModeStealthGame* APlayerHUD::CacheGameMode()
{
    GameMode = Cast<AGameModeStealthGame>(UGameplayStatics::GetGameMode(this));
    return GameMode;
}

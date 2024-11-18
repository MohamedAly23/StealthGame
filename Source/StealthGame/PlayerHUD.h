#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EndLevelWidget.h"
#include "PlayerHUD.generated.h"

// Class to update a game info
UCLASS()
class STEALTHGAME_API APlayerHUD : public AHUD
{
    GENERATED_BODY()

public:
    // Called when the game starts
    virtual void BeginPlay() override;

    UFUNCTION()
    void HandlePlayerWin();

    UFUNCTION()
    void HandlePlayerLose();

protected:

    UPROPERTY(EditAnywhere, Category = "Level Management")
    float OpenNextLevelDelay = 3.0f;

    UPROPERTY(EditAnywhere, Category = "Level Management")
    float FadeCameraDuration = 2.0f;

    UPROPERTY(EditAnywhere, Category = "Level Management")
    FLinearColor FadeCameraColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    USoundBase* WinSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    USoundBase* LoseSound;
private:
    UFUNCTION()
    void StartCameraFade(float FadeDuration, FLinearColor FadeColor);

    UFUNCTION()
    void OpenNextLevel();

    UFUNCTION()
    void ResetGameAndScore();

    int32 GetCurrentLevelIndex();

    UFUNCTION()
    void UpdateHUD(int32 Score, int32 Coins);

    UFUNCTION()
    void FocusOnGame();

    UFUNCTION()
    AGameModeStealthGame* CacheGameMode();

private:
    UPROPERTY(EditAnywhere, Category = "Level Management")
    TArray<FName> LevelNames;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UEndLevelWidget> EndLevelWidgetClass;
    UPROPERTY()
    UEndLevelWidget* EndLevelWidget;

    UPROPERTY()
    FTimerHandle LevelEndTimerHandle;

    UPROPERTY()
    AGameModeStealthGame* GameMode;
};

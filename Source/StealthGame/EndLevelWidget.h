#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndLevelWidget.generated.h"

class UTextBlock;
class UVerticalBox;

// Class To Represent score and info of game
UCLASS()
class STEALTHGAME_API UEndLevelWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateScore(int32 Score);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateCoins(int32 Coins);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void SetGameInfo(int32 Score, int32 Coins, int32 Enemies);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void ShowWinMessage(int32 Score);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void ShowLoseMessage(int32 Score);

protected:

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* MessageAnimation;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ScoreText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* EndScoreText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* CoinsText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* EnemiesText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* EndMessageText;

    UPROPERTY(meta = (BindWidget))
    class UVerticalBox* MessageBox;

private:

    UFUNCTION()
    void FocusOnWidget();

    UFUNCTION()
    void PlayMessageAnimation();
};

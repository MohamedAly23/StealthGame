#include "EndLevelWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

void UEndLevelWidget::NativeOnInitialized()
{
    if (ensure(MessageBox))
    {
        MessageBox->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UEndLevelWidget::PlayMessageAnimation()
{
    if (ensure(MessageAnimation))
    {
        PlayAnimation(MessageAnimation);
    }
}

void UEndLevelWidget::UpdateScore(int32 Score)
{
    ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), Score)));
}

void UEndLevelWidget::UpdateCoins(int32 Coins)
{
    CoinsText->SetText(FText::FromString(FString::Printf(TEXT("Coins: %d"), Coins)));
}

void UEndLevelWidget::SetGameInfo(int32 Score, int32 Coins, int32 Enemies)
{
    EnemiesText->SetText(FText::FromString(FString::Printf(TEXT("Enemies: %d"), Enemies)));
    CoinsText->SetText(FText::FromString(FString::Printf(TEXT("Coins: %d"), Coins)));
    ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), Score)));
}

void UEndLevelWidget::ShowWinMessage(int32 Score)
{
    FocusOnWidget();
    PlayMessageAnimation();
    EndMessageText->SetText(FText::FromString("You Win!"));
    EndMessageText->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
    EndScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), Score)));
    MessageBox->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UEndLevelWidget::ShowLoseMessage(int32 Score)
{
    FocusOnWidget();
    PlayMessageAnimation();
    EndMessageText->SetText(FText::FromString("You Lose!"));
    EndMessageText->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
    EndScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), Score)));
    MessageBox->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UEndLevelWidget::FocusOnWidget()
{
    ensure(GetOwningPlayer());
    GetOwningPlayer()->SetInputMode(FInputModeUIOnly());
    GetOwningPlayer()->bShowMouseCursor = true;
}

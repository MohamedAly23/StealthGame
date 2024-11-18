#pragma once

#include "CoreMinimal.h"
#include "StealthGameInstance.h" 
#include "GameFramework/GameModeBase.h"
#include "GameModeStealthGame.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStatsUpdated, int32, Score, int32, Coins);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerWin);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerLose);

 // class for rules of a game
UCLASS()
class STEALTHGAME_API AGameModeStealthGame : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameModeStealthGame();

	UPROPERTY(BlueprintAssignable, Category = "GameMode")
	FOnStatsUpdated OnStatsUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Game Events")
	FOnPlayerWin OnPlayerWin;

	UPROPERTY(BlueprintAssignable, Category = "Game Events")
	FOnPlayerLose OnPlayerLose;

	UPROPERTY()
	mutable UStealthGameInstance* GameInstance;

	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Points);

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetEnemiesNumber() const;

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetCoinsNumber() const;

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;

	UFUNCTION()
	void AddOneCoinNumber();

	UFUNCTION()
	void DeleteOneCoinNumber();

	UFUNCTION()
	void AddOneEnemyNumber();

private:
	int32 PlayerScore;

	UPROPERTY()
	int32 CoinsCount;

	UPROPERTY()
	int32 EnemyCount;

	UFUNCTION()
	void BroadcastPlayerWin();

	UFUNCTION()
	void BroadcastPlayerLose();

	UFUNCTION()
	UStealthGameInstance* CacheStealthGameInstance() const;
};

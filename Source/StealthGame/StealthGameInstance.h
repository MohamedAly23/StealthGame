// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "StealthGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHGAME_API UStealthGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetScore(int32 NewScore);

	UFUNCTION(BlueprintCallable)
	int32 GetScore();
private:
	UPROPERTY()
	int32 PlayerScore = 0;

};

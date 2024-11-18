#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllCoinsIsCollected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnemyCatchPlayer);

UCLASS()
class STEALTHGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	int32 CoinPoint = 50;

	UFUNCTION(BlueprintCallable)
	void OnPlayerTakeCoin(AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void OnEnemyCatchPlayer();

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAllCoinsIsCollected OnAllCoinsCollected;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FEnemyCatchPlayer OnPlayerCaught;

private:
	int32 CoinsCollected = 0;

	UFUNCTION(BlueprintCallable, Category = "Score")
	void IncrementCoinsCollected();
};

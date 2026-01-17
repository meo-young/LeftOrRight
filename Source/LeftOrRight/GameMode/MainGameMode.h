#pragma once

#include "CoreMinimal.h"
#include "GameMode/BaseGameMode.h"
#include "MainGameMode.generated.h"

class AEnemyBase;

UCLASS()
class LEFTORRIGHT_API AMainGameMode : public ABaseGameMode
{
	GENERATED_BODY()
	
public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	virtual void StartPlay() override;
	
protected:
	void StartGame();
	void StartTimer();
	
protected:
	UPROPERTY(EditDefaultsOnly)
	int32 GameDuration = 60;
	
	UPROPERTY()
	TObjectPtr<AEnemyBase> Enemy;
	
private:
	FTimerHandle GameTimerHandle;
	FTimerHandle GameEventTimerHandle;
	int32 AccumulatedTime = 0;
	
};

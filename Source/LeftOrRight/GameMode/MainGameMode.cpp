#include "GameMode/MainGameMode.h"
#include "LeftOrRight.h"
#include "Enemy/EnemyBase.h"
#include "Kismet/GameplayStatics.h"

void AMainGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AEnemyBase::StaticClass());
	if (AEnemyBase* FoundEnemy = Cast<AEnemyBase>(FoundActor))
	{
		Enemy = FoundEnemy;
	}
}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AMainGameMode::StartPlay()
{
	Super::StartPlay();
	
	float RandomValue = FMath::RandRange(EventInterval - 1.0f, EventInterval + 1.0f);
	GetWorldTimerManager().SetTimer(GameEventTimerHandle, this, &ThisClass::StartGame, RandomValue, true);
	GetWorldTimerManager().SetTimer(GameTimerHandle, this, &AMainGameMode::StartTimer, 1.0f, true);
}

void AMainGameMode::StartGame()
{
	if (Enemy)
	{
		int32 RandomValue = FMath::RandBool() ? 1 : -1;
		Enemy->StartEvent(RandomValue);
	}
}

void AMainGameMode::StartTimer()
{
	AccumulatedTime += 1;
	
	if (AccumulatedTime >= GameDuration)
	{
		LOG(TEXT("게임 종료"))
		GetWorldTimerManager().ClearTimer(GameEventTimerHandle);
	}
}

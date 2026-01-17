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
		LOG(TEXT("Enemy를 발견했습니다"))
	}
}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AMainGameMode::StartPlay()
{
	Super::StartPlay();
	
	GetWorldTimerManager().SetTimer(GameEventTimerHandle, this, &ThisClass::StartGame, 6.0f, true);
	GetWorldTimerManager().SetTimer(GameTimerHandle, this, &AMainGameMode::StartTimer, 1.0f, true);
}

void AMainGameMode::StartGame()
{
	if (Enemy)
	{
		int32 RandomValue = FMath::RandRange(0, 1) == 0 ? -1 : 1;
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

#include "Actor/Clock.h"
#include "LeftOrRight.h"

AClock::AClock()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	ClockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Clock Mesh"));
	ClockMesh->SetupAttachment(Root);
}

void AClock::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentTime = 60;
	ActivateTimer();
}

void AClock::ActivateTimer()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ThisClass::CountTime, TimeInterval, true, true);
}

void AClock::PauseTimer()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void AClock::CountTime()
{
	CurrentTime -= 1;
	
	const int32 Hour = CurrentTime / 60;
	const int32 Minute = CurrentTime % 60;
	
	if (CurrentTime % 60 == 0)
	{
		LOG(TEXT("1시간 경과"));
	}
	
	CurrentTimeAsString = FString::Printf(TEXT("%02d:%02d"), Hour, Minute);
}
#include "Enemy/EnemyBase.h"
#include "LeftOrRight.h"
#include "ActorComponent/FootstepComponent.h"
#include "GameMode/MainGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"

AEnemyBase::AEnemyBase()
{
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(DefaultSceneRoot);
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(DefaultSceneRoot);
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyBase::StartEvent(const int8 Direction)
{
	CurrentDirection = Direction;
	
	PlayRandomAnimation();
	
	// 플레이어를 찾습니다.
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	Player->bIsEnableShot = true;
	
	// 플레이어의 FootstepComponent를 가져옵니다.
	UFootstepComponent* FootstepComponent = Player->FindComponentByClass<UFootstepComponent>();

	// 발자국 소리를 재생합니다.
	FootstepComponent->PlayFootstep(Direction, FootstepSound, EventFinishTime);
	
	if (Direction == 1)
	{
		SetActorTransform(RightTransform);
	}
	else
	{
		SetActorTransform(LeftTransform);	
	}
	
	GetWorldTimerManager().SetTimer(EventFinishTimerHandle, this, &ThisClass::FinishEvent, EventFinishTime, false);
}

void AEnemyBase::StopEvent()
{
	GetWorldTimerManager().ClearTimer(EventFinishTimerHandle);
}

void AEnemyBase::PlayRandomAnimation()
{
	// 랜덤 인덱스를 선택합니다.
	int32 RandomIndex = FMath::RandRange(0, EventAnimations.Num() - 1);
	UAnimSequence* SelectedAnimation = EventAnimations[RandomIndex];
	
	// 애니메이션을 루프로 재생합니다.
	Mesh->PlayAnimation(SelectedAnimation, true);
}

void AEnemyBase::FinishEvent()
{
	// 플레이어를 찾습니다.
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	Player->bIsEnableShot = false;
	
	LOG(TEXT("이벤트 제한시간이 종료됐습니다"))
	
	AMainGameMode* GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->StopGame();
}

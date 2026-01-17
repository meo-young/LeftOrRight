#include "Enemy/EnemyBase.h"
#include "LeftOrRight.h"
#include "ActorComponent/FootstepComponent.h"
#include "Kismet/GameplayStatics.h"

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
	
	// 플레이어를 찾습니다.
	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!Player)
	{
		LOG(TEXT("플레이어를 찾을 수 없습니다."));
		return;
	}

	// 플레이어의 FootstepComponent를 가져옵니다.
	UFootstepComponent* FootstepComponent = Player->FindComponentByClass<UFootstepComponent>();
	if (!FootstepComponent)
	{
		LOG(TEXT("플레이어에게 FootstepComponent가 없습니다."));
		return;
	}

	// 발자국 소리를 재생합니다.
	FootstepComponent->PlayFootstep(Direction, FootstepSound, EventFinishTime);
    
	LOG(TEXT("EnemyBase: 발자국 이벤트 시작 - 방향: %s"), Direction == 1 ? TEXT("오른쪽") : TEXT("왼쪽"));
	
	if (Direction == 1)
	{
		SetActorTransform(RightTransform);
	}
	else
	{
		SetActorTransform(LeftTransform);	
	}
}

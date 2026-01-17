#include "ActorComponent/FootstepComponent.h"
#include "LeftOrRight.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "GameFramework/Actor.h"

UFootstepComponent::UFootstepComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UFootstepComponent::BeginPlay()
{
    Super::BeginPlay();

    // 소유자 액터를 가져옵니다.
    AActor* Owner = GetOwner();
    if (!Owner)
    {
        LOG(TEXT("FootstepComponent: Owner가 없습니다."));
        return;
    }

    // 왼쪽 AudioComponent를 생성합니다.
    LeftAudioComponent = NewObject<UAudioComponent>(Owner, UAudioComponent::StaticClass(), TEXT("LeftAudioComponent"));
    if (LeftAudioComponent)
    {
        LeftAudioComponent->RegisterComponent();
        LeftAudioComponent->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
        LeftAudioComponent->bAutoActivate = false;
        LeftAudioComponent->bAllowSpatialization = true; // 3D 사운드 활성화
        
        // 왼쪽에 배치합니다.
        LeftAudioComponent->SetRelativeLocation(FVector(100.0f, -800.0f, 0.0f));
        
        LOG(TEXT("FootstepComponent: LeftAudioComponent 생성 완료"));
    }

    // 오른쪽 AudioComponent를 생성합니다.
    RightAudioComponent = NewObject<UAudioComponent>(Owner, UAudioComponent::StaticClass(), TEXT("RightAudioComponent"));
    if (RightAudioComponent)
    {
        RightAudioComponent->RegisterComponent();
        RightAudioComponent->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
        RightAudioComponent->bAutoActivate = false;
        LeftAudioComponent->bAllowSpatialization = true; // 3D 사운드 활성화
        
        // 오른쪽에 배치합니다.
        RightAudioComponent->SetRelativeLocation(FVector(100.0f, 800.0f, 0.0f));
        
        LOG(TEXT("FootstepComponent: RightAudioComponent 생성 완료"));
    }
}

void UFootstepComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // 재생 중이면 볼륨을 업데이트합니다.
    if (bIsPlaying)
    {
        UpdateVolume(DeltaTime);
    }
}

void UFootstepComponent::PlayFootstep(int32 Direction, USoundCue* FootstepSound, float Duration)
{
    // 이미 재생 중이면 먼저 중단합니다.
    if (bIsPlaying)
    {
        StopFootstep();
    }

    // 방향에 따라 AudioComponent를 선택합니다.
    if (Direction < 0)
    {
        // 왼쪽
        CurrentAudioComponent = LeftAudioComponent;
        LOG(TEXT("FootstepComponent: 왼쪽에서 발자국 소리 재생"));
    }
    else
    {
        // 오른쪽
        CurrentAudioComponent = RightAudioComponent;
        LOG(TEXT("FootstepComponent: 오른쪽에서 발자국 소리 재생"));
    }

    if (!CurrentAudioComponent)
    {
        LOG(TEXT("FootstepComponent: CurrentAudioComponent가 null입니다."));
        return;
    }

    // 재생 설정을 초기화합니다.
    bIsPlaying = true;
    CurrentPlayTime = 0.0f;
    TotalDuration = Duration;

    // 사운드를 설정하고 재생합니다.
    CurrentAudioComponent->SetSound(FootstepSound);
    CurrentAudioComponent->SetVolumeMultiplier(MinVolume);
    CurrentAudioComponent->Play();

    // Duration 후에 자동으로 종료하도록 타이머를 설정합니다.
    GetWorld()->GetTimerManager().SetTimer(FinishTimerHandle, this, &UFootstepComponent::FinishPlayback, Duration, false);
}

void UFootstepComponent::StopFootstep()
{
    if (!bIsPlaying)
    {
        return;
    }

    // 재생 중단
    bIsPlaying = false;
    CurrentPlayTime = 0.0f;

    // 오디오를 정지합니다.
    if (CurrentAudioComponent && CurrentAudioComponent->IsPlaying())
    {
        CurrentAudioComponent->Stop();
        LOG(TEXT("FootstepComponent: 발자국 소리 중단"));
    }

    // 타이머를 클리어합니다.
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(FinishTimerHandle);
    }

    CurrentAudioComponent = nullptr;
}

void UFootstepComponent::UpdateVolume(float DeltaTime)
{
    if (!CurrentAudioComponent || TotalDuration <= 0.0f)
    {
        return;
    }

    // 재생 시간을 업데이트합니다.
    CurrentPlayTime += DeltaTime;

    // 진행도를 계산합니다 (0.0 ~ 1.0)
    float Progress = FMath::Clamp(CurrentPlayTime / TotalDuration, 0.0f, 1.0f);

    // 볼륨을 점점 크게 합니다.
    float CurrentVolume = FMath::Lerp(MinVolume, MaxVolume, Progress);
    CurrentAudioComponent->SetVolumeMultiplier(CurrentVolume);
}

void UFootstepComponent::FinishPlayback()
{
    // 재생을 종료합니다.
    LOG(TEXT("FootstepComponent: 발자국 소리 재생 완료"));
    StopFootstep();
}
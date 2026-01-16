#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FootstepComponent.generated.h"

class UAudioComponent;
class USoundCue;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LEFTORRIGHT_API UFootstepComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFootstepComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

public:
	/** 발자국 소리를 재생하는 함수입니다. (-1: 왼쪽, 1: 오른쪽) */
	UFUNCTION(BlueprintCallable, Category = "Footstep")
	void PlayFootstep(int32 Direction, USoundCue* FootstepSound, float Duration = 5.0f);

	/** 발자국 소리를 중단하는 함수입니다. */
	UFUNCTION(BlueprintCallable, Category = "Footstep")
	void StopFootstep();

protected:
	/** 볼륨을 업데이트하는 함수입니다. */
	void UpdateVolume(float DeltaTime);

	/** 재생을 종료하는 함수입니다. */
	void FinishPlayback();

protected:
	/** 왼쪽 오디오 컴포넌트입니다. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "변수")
	TObjectPtr<UAudioComponent> LeftAudioComponent;

	/** 오른쪽 오디오 컴포넌트입니다. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "변수")
	TObjectPtr<UAudioComponent> RightAudioComponent;

	/** 최소 볼륨입니다. */
	UPROPERTY(EditDefaultsOnly, Category = "변수")
	float MinVolume = 0.1f;

	/** 최대 볼륨입니다. */
	UPROPERTY(EditDefaultsOnly, Category = "변수")
	float MaxVolume = 1.0f;

private:
	/** 현재 재생 중인 오디오 컴포넌트입니다. */
	UPROPERTY()
	TObjectPtr<UAudioComponent> CurrentAudioComponent;

	/** 재생이 활성화되어 있는지 여부입니다. */
	uint8 bIsPlaying : 1 = false;

	/** 현재 재생 시간입니다. */
	float CurrentPlayTime = 0.0f;

	/** 총 재생 시간입니다. */
	float TotalDuration = 0.0f;

	/** 이벤트 타이머 핸들입니다. */
	FTimerHandle FinishTimerHandle;
};
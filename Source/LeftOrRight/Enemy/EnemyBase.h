#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBase.generated.h"

UCLASS()
class LEFTORRIGHT_API AEnemyBase : public AActor
{
	GENERATED_BODY()
	
public:
	AEnemyBase();
	virtual void BeginPlay() override;
	
public:
	/** 이벤트를 시작하는 함수입니다. (-1 : 왼쪽, 1 : 오른쪽) */
	void StartEvent(const int8 Direction);
	
	/** 이벤트를 종료하는 함수입니다. */
	void StopEvent();
	
private:
	/** 랜덤 애니메이션을 재생하는 함수입니다. */
	void PlayRandomAnimation();
	
	/** 이벤트를 종료하는 함수입니다. */
	void FinishEvent();
	
public:
	int8 CurrentDirection;
	
	/** 이벤트가 종료되는 시간입니다. */
	UPROPERTY(EditDefaultsOnly, Category = "변수")
	float EventFinishTime = 5.0f;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USceneComponent> DefaultSceneRoot;;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> Mesh;
	
	UPROPERTY(EditDefaultsOnly, Category = "변수")
	FTransform LeftTransform;
	
	UPROPERTY(EditDefaultsOnly, Category = "변수")
	FTransform RightTransform;
	
	/** 발자국 소리입니다. */
	UPROPERTY(EditDefaultsOnly, Category = "변수")
	TObjectPtr<USoundCue> FootstepSound;
	
	/** 랜덤으로 재생할 애니메이션 배열입니다. */
	UPROPERTY(EditDefaultsOnly, Category = "변수")
	TArray<TObjectPtr<UAnimSequence>> EventAnimations;
	
private:
	FTimerHandle EventFinishTimerHandle;

};

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
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USceneComponent> DefaultSceneRoot;;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> Mesh;
	
	UPROPERTY(EditDefaultsOnly, Category = "변수")
	FTransform LeftTransform;
	
	UPROPERTY(EditDefaultsOnly, Category = "변수")
	FTransform RightTransform;
	
	/** 이벤트가 종료되는 시간입니다. */
	UPROPERTY(EditDefaultsOnly, Category = "변수")
	float EventFinishTime = 5.0f;
	
	/** 발자국 소리입니다. */
	UPROPERTY(EditDefaultsOnly, Category = "변수")
	TObjectPtr<USoundCue> FootstepSound;

};

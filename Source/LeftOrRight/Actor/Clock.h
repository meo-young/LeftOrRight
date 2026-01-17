#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Clock.generated.h"

UCLASS()
class LEFTORRIGHT_API AClock : public AActor
{
	GENERATED_BODY()
	
public:	
	AClock();
	virtual void BeginPlay() override;
	
public:
	void ActivateTimer();
	void PauseTimer();
	
private:
	void CountTime();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "변수|컴포넌트")
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(EditDefaultsOnly, Category = "변수|컴포넌트")
	TObjectPtr<UStaticMeshComponent> ClockMesh;
	
	UPROPERTY(EditDefaultsOnly, Category = "변수|수치")
	uint8 TimeInterval = 4;
	
	UPROPERTY(BlueprintReadOnly)
	FString CurrentTimeAsString;
	
private:
	FTimerHandle TimerHandle;
	int32 CurrentTime = 0;

};

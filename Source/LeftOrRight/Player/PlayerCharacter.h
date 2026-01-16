#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UInputAction;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class LEFTORRIGHT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	void DoLeftRightAction(const FInputActionValue& InputActionValue);
	void PlayShootAnim();
	void ResetShotState();
	
public:
	uint8 bIsEnableShot : 1 = true;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "변수")
	TObjectPtr<UInputAction> LeftRightAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "변수")
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "변수")
	TObjectPtr<USkeletalMeshComponent> ShotGun;
	
	UPROPERTY(EditDefaultsOnly, Category = "변수")
	TObjectPtr<UAnimMontage> ShootAnimMontage;
	
private:
	FTimerHandle ShotTimerHandle;

};

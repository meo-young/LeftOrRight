// 헤더 파일 (.h)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class USpotLightComponent;
class UNiagaraSystem;
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
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

protected:
    /** 좌우 입력을 처리하는 함수입니다. */
    void DoLeftRightAction(const FInputActionValue& InputActionValue);

    /** 사격 애니메이션을 재생하는 함수입니다. */
    void PlayShootAnim(float Direction);

    /** 사격 가능 상태로 리셋하는 함수입니다. */
    void ResetShotState();

    /** 메시를 원래 위치로 돌리는 함수입니다. */
    void ResetMeshRotation();
    
    /** Muzzle 이펙트를 재생하는 함수입니다. */
    void PlayMuzzleEffect();

    /** SpotLight를 끄는 함수입니다. */
    void TurnOffSpotLight();
    
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
    TObjectPtr<USpotLightComponent> SpotLightComponent;
    
    UPROPERTY(EditDefaultsOnly, Category = "변수")
    TObjectPtr<UAnimMontage> ShootAnimMontage;
    
    /** Muzzle Flash Niagara System입니다. */
    UPROPERTY(EditDefaultsOnly, Category = "변수")
    TObjectPtr<UNiagaraSystem> MuzzleFlashNiagara;

    /** SpotLight가 켜져있는 시간입니다. */
    UPROPERTY(EditDefaultsOnly, Category = "변수")
    float SpotLightDuration = 0.2f;
    
    /** 왼쪽 회전 각도입니다. */
    UPROPERTY(EditDefaultsOnly, Category = "변수")
    float LeftMeshRotationAngle = 30.0f;
    
    /** 오른쪽 회전 각도입니다. */
    UPROPERTY(EditDefaultsOnly, Category = "변수")
    float RightMeshRotationAngle = 15.0f;
    
    UPROPERTY(EditDefaultsOnly, Category = "변수")
    float MeshRotationSpeed = 10.0f;
    
private:
    FTimerHandle ShotTimerHandle;
    FTimerHandle MeshResetTimerHandle;
    FTimerHandle MuzzleEffectTimerHandle;
    FTimerHandle SpotLightTimerHandle;
    
    FRotator OriginalMeshRotation;
    FRotator TargetMeshRotation;
    
    uint8 bIsRotatingMesh : 1 = false;
};
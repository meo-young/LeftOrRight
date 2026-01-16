#include "Player/PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "LeftOrRight.h"
#include "Camera/CameraComponent.h"

APlayerCharacter::APlayerCharacter()
{
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_LeftRightAction(TEXT("/Game/_LeftOrRight/Input/IA_LeftRIght"));
	if (IA_LeftRightAction.Succeeded())
	{
		LeftRightAction = IA_LeftRightAction.Object;
	}
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetMesh(), TEXT("head"));
	CameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	CameraComponent->bUsePawnControlRotation = true;
	CameraComponent->bEnableFirstPersonFieldOfView = true;
	CameraComponent->bEnableFirstPersonScale = true;
	CameraComponent->FirstPersonFieldOfView = 70.0f;
	CameraComponent->FirstPersonScale = 0.6f;
	
	ShotGun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShotGun"));
	ShotGun->SetupAttachment(GetMesh(), TEXT("hand_l"));
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (LeftRightAction)
		{
			EIC->BindAction(LeftRightAction, ETriggerEvent::Started, this, &ThisClass::DoLeftRightAction);
		}
	}
}

void APlayerCharacter::DoLeftRightAction(const FInputActionValue& InputActionValue)
{
	if (!bIsEnableShot) return;
	
	const float LeftActionValue = InputActionValue.Get<float>();
	
	LOG(TEXT("%f"), LeftActionValue);
	PlayShootAnim();
}

void APlayerCharacter::PlayShootAnim()
{
	// AnimInstance를 가져옵니다.
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance)
	{
		LOG(TEXT("AnimInstance가 존재하지 않습니다."))
		return;
	}
	
	// 사격이 불가능한 상태로 변환합니다.
	bIsEnableShot = false;
	
	// AnimMontage를 재생합니다.
	AnimInstance->Montage_Play(ShootAnimMontage, 1.0f);
	
	// 2초 후에 사격을 가능한 상태로 만듭니다.
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ThisClass::ResetShotState, 2.0f, false);
}

void APlayerCharacter::ResetShotState()
{
	bIsEnableShot = true;
}

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

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 메시의 원래 회전값을 저장합니다.
	if (GetMesh())
	{
		OriginalMeshRotation = GetMesh()->GetRelativeRotation();
		TargetMeshRotation = OriginalMeshRotation;
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// 메시가 회전 중이라면 부드럽게 회전시킵니다.
	if (bIsRotatingMesh && GetMesh())
	{
		FRotator CurrentRotation = GetMesh()->GetRelativeRotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetMeshRotation, DeltaTime, MeshRotationSpeed);
		GetMesh()->SetRelativeRotation(NewRotation);

		// 목표 회전에 거의 도달했는지 확인합니다.
		if (FMath::IsNearlyEqual(NewRotation.Yaw, TargetMeshRotation.Yaw, 0.1f))
		{
			bIsRotatingMesh = false;
		}
	}
}

void APlayerCharacter::DoLeftRightAction(const FInputActionValue& InputActionValue)
{
	if (!bIsEnableShot) return;
	
	const float LeftRightActionValue = InputActionValue.Get<float>();
	PlayShootAnim(LeftRightActionValue);
}

void APlayerCharacter::PlayShootAnim(float Direction)
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
	
	// 메시를 회전시킵니다.
	TargetMeshRotation = OriginalMeshRotation;
    
	// 왼쪽(-1)이면 30도, 오른쪽(1)이면 15도 회전합니다.
	if (Direction < 0.0f)
	{
		// 왼쪽
		TargetMeshRotation.Yaw -= LeftMeshRotationAngle;
		LOG(TEXT("메시 왼쪽 회전: %f도"), LeftMeshRotationAngle);
	}
	else
	{
		// 오른쪽
		TargetMeshRotation.Yaw += RightMeshRotationAngle;
		LOG(TEXT("메시 오른쪽 회전: %f도"), RightMeshRotationAngle);
	}
	
	bIsRotatingMesh = true;
	
	// AnimMontage를 재생합니다.
	float MontageDuration = AnimInstance->Montage_Play(ShootAnimMontage, 1.0f);
	
	// 2초 후에 사격을 가능한 상태로 만듭니다.
	float MeshResetTime = MontageDuration * 0.8f;
	GetWorldTimerManager().SetTimer(MeshResetTimerHandle, this, &ThisClass::ResetMeshRotation, MeshResetTime, false);

	// 2초 후에 사격을 가능한 상태로 만듭니다.
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ThisClass::ResetShotState, 2.0f, false);
}

void APlayerCharacter::ResetShotState()
{
	bIsEnableShot = true;
}

void APlayerCharacter::ResetMeshRotation()
{
	// 메시를 원래 위치로 돌립니다.
	TargetMeshRotation = OriginalMeshRotation;
	bIsRotatingMesh = true;
}

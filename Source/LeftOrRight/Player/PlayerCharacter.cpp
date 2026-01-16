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
	const float LeftActionValue = InputActionValue.Get<float>();

	LOG(TEXT("%f"), LeftActionValue);
}

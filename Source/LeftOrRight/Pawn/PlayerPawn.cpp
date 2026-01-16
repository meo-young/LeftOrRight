#include "PlayerPawn.h"
#include "InputAction.h"
#include "LeftOrRight.h"
#include "EnhancedInputComponent.h"

APlayerPawn::APlayerPawn()
{
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_LeftRightAction(TEXT("/Game/_LeftOrRight/Input/IA_LeftRIght"));
	if (IA_LeftRightAction.Succeeded())
	{
		LeftRightAction = IA_LeftRightAction.Object;
	}}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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

void APlayerPawn::DoLeftRightAction(const FInputActionValue& InputActionValue)
{
	const float LeftActionValue = InputActionValue.Get<float>();

	LOG(TEXT("%f"), LeftActionValue);
}

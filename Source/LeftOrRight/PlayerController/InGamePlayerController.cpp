#include "InGamePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

AInGamePlayerController::AInGamePlayerController()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_Player(TEXT("/Game/_LeftOrRight/Input/IMC_Player"));
	if (IMC_Player.Succeeded())
	{
		InputMappingContext = IMC_Player.Object;
	}
}

void AInGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

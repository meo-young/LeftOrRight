#pragma once

#include "CoreMinimal.h"
#include "PlayerController/PlayerControllerBase.h"
#include "InGamePlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class LEFTORRIGHT_API AInGamePlayerController : public APlayerControllerBase
{
	GENERATED_BODY()

public:
	AInGamePlayerController();
	virtual void SetupInputComponent() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "변수")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	
};

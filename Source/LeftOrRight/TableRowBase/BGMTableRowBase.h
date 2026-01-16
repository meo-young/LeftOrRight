#pragma once

#include "CoreMinimal.h"
#include "BGMTableRowBase.generated.h"

enum class EBGM : uint8;

USTRUCT()
struct FBGMTableRowBase : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	EBGM BGM;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<USoundCue> Sound;
	
};
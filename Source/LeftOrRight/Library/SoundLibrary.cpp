#include "SoundLibrary.h"
#include "Subsystem/SoundSubsystem.h"
#include "LeftOrRight.h"
#include "Kismet/GameplayStatics.h"

void USoundLibrary::PlaySFXInLocation(const UObject* WorldContextObject, ESFX SFXType, const FVector& Location)
{
	if (USoundSubsystem* SoundSubsystem = GetSoundSubsystem(WorldContextObject))
	{
		SoundSubsystem->PlaySFXInLocation(SFXType, Location);
	}
}

void USoundLibrary::PlaySFX2D(const UObject* WorldContextObject, ESFX SFXType)
{
	if (USoundSubsystem* SoundSubsystem = GetSoundSubsystem(WorldContextObject))
	{
		SoundSubsystem->PlaySFX2D(SFXType);
	}
}

void USoundLibrary::PlayBGM(const UObject* WorldContextObject, EBGM BGMType)
{
	if (USoundSubsystem* SoundSubsystem = GetSoundSubsystem(WorldContextObject))
	{
		SoundSubsystem->PlayBGM(BGMType);
	}
}

void USoundLibrary::StopBGM(const UObject* WorldContextObject)
{
	if (USoundSubsystem* SoundSubsystem = GetSoundSubsystem(WorldContextObject))
	{
		SoundSubsystem->StopBGM();
	}
}

void USoundLibrary::PauseBGM(const UObject* WorldContextObject)
{
	if (USoundSubsystem* SoundSubsystem = GetSoundSubsystem(WorldContextObject))
	{
		SoundSubsystem->PauseBGM();
	}
}

void USoundLibrary::ResumeBGM(const UObject* WorldContextObject)
{
	if (USoundSubsystem* SoundSubsystem = GetSoundSubsystem(WorldContextObject))
	{
		SoundSubsystem->ResumeBGM();
	}
}

USoundSubsystem* USoundLibrary::GetSoundSubsystem(const UObject* WorldContextObject)
{
	if (const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
	{
		if (USoundSubsystem* SoundSubsystem = GameInstance->GetSubsystem<USoundSubsystem>())
		{
			return SoundSubsystem;
		}
		else
		{
			LOG(TEXT("SoundSubsystem이 유효하지 않습니다"));
			return nullptr;
		}
	}
	else
	{
		LOG(TEXT("GameInstance가 유효하지 않습니다"));
		return nullptr;
	}
}
#include "Player/UI/Setting_Ui.h"
#include "Components/ComboBoxString.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"
#include "Components/Slider.h"
#include "Player/BasePlayerController.h"
#include "Player/Save/BaseSaveGame.h"
#include "Kismet/GameplayStatics.h"


void USetting_Ui::NativeConstruct()
{
	Super::NativeConstruct();

	
	if (ResolutionComboBox)
	{
		UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();

		FIntPoint CurrentResolution = UserSettings->GetScreenResolution();
		FString CurrentResolutionString = FString::Printf(TEXT("%dx%d"), CurrentResolution.X, CurrentResolution.Y);
		ResolutionComboBox->SetSelectedOption(CurrentResolutionString);

		TArray<FString> CommonResolutions = {
			TEXT("1920x1080"),
			TEXT("1280x720"),
			TEXT("2560x1440"),
			TEXT("3840x2160")
		};
		
		for (const FString& Resolution : CommonResolutions)
		{
			ResolutionComboBox->AddOption(Resolution);
		}
	}



	if (ScreenOkButton) {
		if (EWindowMode::Fullscreen) {
			FullScreenCheck->SetIsChecked(true);
		}

		ScreenOkButton->OnClicked.AddDynamic(this, &USetting_Ui::OnchangeScreen);
	}

    
}

void USetting_Ui::OnchangeScreen()
{
	if (GEngine && GEngine->GameUserSettings)
	{
		// 해상도 변경
		FString SelectedResolution = ResolutionComboBox->GetSelectedOption();
		FIntPoint ScreenRes;
		ScreenRes.X = FCString::Atoi(*SelectedResolution.Left(SelectedResolution.Find("x")));
		ScreenRes.Y = FCString::Atoi(*SelectedResolution.RightChop(SelectedResolution.Find("x") + 1));

		// 전체 화면 모드 변경
		bool bIsFullScreen = FullScreenCheck->IsChecked();

		// 설정 적용
		GEngine->GameUserSettings->SetScreenResolution(ScreenRes);
		GEngine->GameUserSettings->SetFullscreenMode(bIsFullScreen ? EWindowMode::Fullscreen : EWindowMode::Windowed);
		GEngine->GameUserSettings->ApplySettings(false);
	}
}




// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/SNGameUserSettings.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Settings/SNGameSetting.h"

#define LOCTEXT_NAMESPACE "GameUserSettings"

USNGameUserSettings::USNGameUserSettings()
{
	const TArray<FOptionNumber> VFXOptions = {
		{LOCTEXT("VFXQualityLow_Loc", "Low"), 0} ,
		{LOCTEXT("VFXQualityMedium_Loc", "Medium"), 1} ,
		{LOCTEXT("VFXQualityHigh_Loc", "High"), 2} ,
		{LOCTEXT("VFXQualityEpic_Loc", "Epic"), 3}
	};

	const TArray<FOptionEnum> WindowModeOptions = {
		{LOCTEXT("WindowmodeOptions_Fullscreen_Loc", "Fullscreen"), EWindowMode::Fullscreen} ,
		{LOCTEXT("WindowmodeOptions_WindowedFullscreen_Loc", "WindowedFullscreen"), EWindowMode::WindowedFullscreen} ,
		{LOCTEXT("WindowmodeOptions_Windowed_Loc", "Windowed"), EWindowMode::Windowed} 
	};

	TArray<FOptionIntPoint> ResolutionOptions;
	TArray<FIntPoint> AllResolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(AllResolutions);
	
	for (FIntPoint Item : AllResolutions)
	{
		ResolutionOptions.Add(FOptionIntPoint{FText::FromString(Item.ToString()), Item});
	}

	{
		USNGameSetting_IntPoint* Setting = NewObject<USNGameSetting_IntPoint>();
		Setting->SetSettingName(LOCTEXT("Resolotion_Loc" , "Resolotion"));
		Setting->SetOptions(ResolutionOptions);
		Setting->AddGetterFunc([&]() { return GetScreenResolution(); } );
		Setting->AddSetterFunc([&](FIntPoint Level) { SetScreenResolution(Level); ApplySettings(false); ApplyResolutionSettings(false); });
		VideoSettings.Add(Setting);
	}

	{
		USNGameSetting_Enum* Setting = NewObject<USNGameSetting_Enum>();
		Setting->SetSettingName(LOCTEXT("WindowMode_Loc" , "WindowMode"));
		Setting->SetOptions(WindowModeOptions);
		Setting->AddGetterFunc([&]() { return GetFullscreenMode(); } );
		Setting->AddSetterFunc([&](EWindowMode::Type Level) { SetFullscreenMode(Level); ApplySettings(false); });
		VideoSettings.Add(Setting);
	}
	
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("AntiAliasing_Loc" , "Anti-Aliasing"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetAntiAliasingQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetAntiAliasingQuality(Level); ApplySettings(false); });
		VideoSettings.Add(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("Textures_Loc" , "Textures"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetTextureQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetTextureQuality(Level); ApplySettings(false); });	
		VideoSettings.Add(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("Shadows_Loc" , "Shadows"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetShadowQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetShadowQuality(Level); ApplySettings(false); });
		VideoSettings.Add(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("Post Processing_Loc" , "Post Processing"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetPostProcessingQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetPostProcessingQuality(Level); ApplySettings(false); });
		VideoSettings.Add(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("Follage_Loc" , "Follage"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetFoliageQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetFoliageQuality(Level); ApplySettings(false); });
		VideoSettings.Add(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("GlobalIllumination_Loc" , "Global Illumination"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetGlobalIlluminationQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetGlobalIlluminationQuality(Level); ApplySettings(false); });
		VideoSettings.Add(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("Reflection_Loc" , "Reflection"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetReflectionQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetReflectionQuality(Level); ApplySettings(false); });
		VideoSettings.Add(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("Shading_Loc" , "Shading"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetShadingQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetShadingQuality(Level); ApplySettings(false); });
		VideoSettings.Add(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("ViewDistance_Loc" , "ViewDistance"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetViewDistanceQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetViewDistanceQuality(Level); ApplySettings(false); });
		VideoSettings.Add(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("VisualEffects_Loc" , "VisualEffects"));
		Setting->SetOptions(VFXOptions);
		/*Setting->AddOption(LOCTEXT("VFXQualityLow_Loc", "Low"), 0);
		Setting->AddOption(LOCTEXT("VFXQualityLow_Loc", "Medium"), 1);*/
		Setting->AddGetterFunc([&]() { return GetVisualEffectQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetVisualEffectQuality(Level); ApplySettings(false); });
		VideoSettings.Add(Setting);
	}
}

USNGameUserSettings* USNGameUserSettings::Get()
{
	return GEngine ? Cast<USNGameUserSettings>(GEngine->GetGameUserSettings()) : nullptr;
}

const TArray<USNGameSetting*>& USNGameUserSettings::GetVideoSettings() const
{
	return VideoSettings;
}

void USNGameUserSettings::RunBenchmark()
{
	RunHardwareBenchmark();
	ApplySettings(false);
	OnVideoSettingsUpdate.Broadcast();
}

#undef LOCTEXT_NAMESPACE
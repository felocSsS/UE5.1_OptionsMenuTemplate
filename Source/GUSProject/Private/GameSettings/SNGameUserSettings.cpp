// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSettings/SNGameUserSettings.h"

#include "SNGameSetting.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameSettings/SNGameSetting.h"

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
		{LOCTEXT("WindowmodeOptions_WindowedFullscreen_Loc", "Windowed Fullscreen"), EWindowMode::WindowedFullscreen} ,
		{LOCTEXT("WindowmodeOptions_Windowed_Loc", "Windowed"), EWindowMode::Windowed} 
	};

	const TArray<FOptionBool> BoolOptions = {
		{LOCTEXT("Bool_On_Loc", "On"), true} ,
		{LOCTEXT("Bool_Off_Loc", "Off"), false} 
	};

	const TArray<FOptionNumber> FrameLimitOptions = {
		{FText::FromString("30"), 30} ,
		{FText::FromString("60"), 60} ,
		{FText::FromString("120"), 120} ,
		{FText::FromString("144"), 144} ,
		{LOCTEXT("FrameLimit_Loc", "Unlimited"), 0} 
	};

	const TArray<FOptionNumber> AAMethodOptions = {
		{LOCTEXT("AAMethod_None", "None"), 0} ,
		{FText::FromString("FXAA"), 1} ,
		{FText::FromString("TAA"), 2} ,
		{FText::FromString("MSAA"), 3} ,
		{FText::FromString("TSR"), 4}
	};

	const TArray<FOptionNumber> MSAACountOptions = {
		{FText::FromString("0"), 0} ,
		{FText::FromString("2"), 2} ,
		{FText::FromString("4"), 4} ,
		{FText::FromString("8"), 8}
	};

	TArray<FOptionIntPoint> ResolutionOptions;
	TArray<FIntPoint> AllResolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(AllResolutions);
	
	for (FIntPoint Item : AllResolutions)
	{
		ResolutionOptions.Add(FOptionIntPoint{FText::FromString(Item.ToString()), Item});
	}

	const auto DisplaySettingsCollection = NewObject<USNGameSettingCollection>();
	DisplaySettingsCollection->SetCollectionName(LOCTEXT("DisplayCollection_Loc" , "Display"));

	{
		USNGameSetting_IntPoint* Setting = NewObject<USNGameSetting_IntPoint>();
		Setting->SetSettingName(LOCTEXT("Resolotion_Loc" , "Resolotion"));
		Setting->SetSettingDescription(LOCTEXT("ResolotionD_Loc", "Resolotion description"));
		Setting->SetOptions(ResolutionOptions);
		Setting->AddGetterFunc([&]() { return GetScreenResolution(); } );
		Setting->AddSetterFunc([&](FIntPoint Level) { SetScreenResolution(Level); ApplySettings(false); ApplyResolutionSettings(false); });
		DisplaySettingsCollection->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Enum* Setting = NewObject<USNGameSetting_Enum>();
		Setting->SetSettingName(LOCTEXT("WindowMode_Loc" , "Window Mode"));
		Setting->SetSettingDescription(LOCTEXT("WindowModeD_Loc", "Window Mode description"));
		Setting->SetOptions(WindowModeOptions);
		Setting->AddGetterFunc([&]() { return GetFullscreenMode(); } );
		Setting->AddSetterFunc([&](EWindowMode::Type Level) { SetFullscreenMode(Level); ApplySettings(false); });
		DisplaySettingsCollection->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Float* Setting = NewObject<USNGameSetting_Float>();
		Setting->SetSettingName(LOCTEXT("ResScale_Loc" , "3D Resolution"));
		Setting->SetSettingDescription(LOCTEXT("ResScaleD_Loc", "3D Resolution description"));
		Setting->AddGetterFunc([&]() { return GetResolutionScaleNormalized(); } );
		Setting->AddSetterFunc([&](float Level){ SetResolutionScaleNormalized(Level); ApplySettings(false); });
		Setting->WidgetType = EWidgetType::Slider;
		Setting->SetMinMaxSliderValue(FMinMaxSliderValue{0.3f, 1.0f});
		DisplaySettingsCollection->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Bool* Setting = NewObject<USNGameSetting_Bool>();
		Setting->SetSettingName(LOCTEXT("VSync_Loc" , "VSync"));
		Setting->SetSettingDescription(LOCTEXT("VSyncD_Loc", "VSync description"));
		Setting->SetOptions(BoolOptions);
		Setting->AddGetterFunc([&]() { return IsVSyncEnabled(); } );
		Setting->AddSetterFunc([&](bool Level) { SetVSyncEnabled(Level); ApplySettings(false); });
		DisplaySettingsCollection->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("FrameLimit_Loc" , "Frame rate limit"));
		Setting->SetSettingDescription(LOCTEXT("FrameLimitD_Loc", "Frame rate limit description"));
		Setting->SetOptions(FrameLimitOptions);
		Setting->AddGetterFunc([&]() { return GetFrameRateLimit(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetFrameRateLimit(Level); ApplySettings(false); });
		DisplaySettingsCollection->AddSettingToCollection(Setting);
	}

	VideoSettings.Add(DisplaySettingsCollection);

	const auto GraphicsQuality = NewObject<USNGameSettingCollection>();
	GraphicsQuality->SetCollectionName(LOCTEXT("GraphicsQuality_Loc" , "Graphics quality"));
	
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("AntiAliasingMethod_Loc" , "Anti-Aliasing Method"));
		Setting->SetSettingDescription(LOCTEXT("AntiAliasingMethodD_Loc", "Anti-Aliasing Method description"));
		Setting->SetOptions(AAMethodOptions);
		Setting->AddGetterFunc([&]() { return GetAAMethod(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetAAMethod(Level); });
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("MSAACount_Loc" , "MSAA Count"));
		Setting->SetSettingDescription(LOCTEXT("MSAACountD_Loc", "MSAA Count description"));
		Setting->SetOptions(MSAACountOptions);
		Setting->AddGetterFunc([&]() { return GetMSAAQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetMSAAQuality(Level); });
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("AntiAliasing_Loc" , "Anti-aliasing quality"));
		Setting->SetSettingDescription(LOCTEXT("AntiAliasingD_Loc", "Anti-aliasing quality description"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetAntiAliasingQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetAntiAliasingQuality(Level); ApplySettings(false); });
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("Textures_Loc" , "Textures quality"));
		Setting->SetSettingDescription(LOCTEXT("TexturesD_Loc", "Textures quality description"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetTextureQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetTextureQuality(Level); ApplySettings(false); });	
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("Shadows_Loc" , "Shadows quality"));
		Setting->SetSettingDescription(LOCTEXT("ShadowsD_Loc", "Shadows quality description"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetShadowQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetShadowQuality(Level); ApplySettings(false); });
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("Post Processing_Loc" , "Post Processing quality"));
		Setting->SetSettingDescription(LOCTEXT("Post ProcessingD_Loc", "Post Processing quality description"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetPostProcessingQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetPostProcessingQuality(Level); ApplySettings(false); });
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("Follage_Loc" , "Follage quality"));
		Setting->SetSettingDescription(LOCTEXT("FollageD_Loc", "Follage quality description"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetFoliageQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetFoliageQuality(Level); ApplySettings(false); });
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("GlobalIllumination_Loc" , "Global Illumination quality"));
		Setting->SetSettingDescription(LOCTEXT("GlobalIlluminationD_Loc", "Global Illumination quality description"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetGlobalIlluminationQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetGlobalIlluminationQuality(Level); ApplySettings(false); });
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("Reflection_Loc" , "Reflection quality"));
		Setting->SetSettingDescription(LOCTEXT("ReflectionD_Loc", "Reflection quality description"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetReflectionQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetReflectionQuality(Level); ApplySettings(false); });
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("Shading_Loc" , "Shading quality"));
		Setting->SetSettingDescription(LOCTEXT("ShadingD_Loc", "Shading quality description"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetShadingQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetShadingQuality(Level); ApplySettings(false); });
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("ViewDistance_Loc" , "ViewDistance quality"));
		Setting->SetSettingDescription(LOCTEXT("ViewDistanceD_Loc", "ViewDistance quality description"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetViewDistanceQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetViewDistanceQuality(Level); ApplySettings(false); });
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("VisualEffects_Loc", "Visual Effects quality"));
		Setting->SetSettingDescription(LOCTEXT("VisualEffectsD_Loc", "Visual Effects quality description"));
		Setting->SetOptions(VFXOptions);
		/*Setting->AddOption(LOCTEXT("VFXQualityLow_Loc", "Low"), 0);
		Setting->AddOption(LOCTEXT("VFXQualityLow_Loc", "Medium"), 1);*/ // как пример применения метода add option
		Setting->AddGetterFunc([&]() { return GetVisualEffectQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetVisualEffectQuality(Level); ApplySettings(false); });
		GraphicsQuality->AddSettingToCollection(Setting);
	}

	VideoSettings.Add(GraphicsQuality);
}

USNGameUserSettings* USNGameUserSettings::Get()
{
	return GEngine ? Cast<USNGameUserSettings>(GEngine->GetGameUserSettings()) : nullptr;
}

const TArray<USNGameSettingCollection*>& USNGameUserSettings::GetVideoSettings() const
{
	return VideoSettings;
}

void USNGameUserSettings::RunBenchmark()
{
	RunHardwareBenchmark();
	ApplySettings(false);
	OnVideoSettingsUpdate.Broadcast();
}

int32 USNGameUserSettings::GetAAMethod() const
{
	return UKismetSystemLibrary::GetConsoleVariableIntValue("r.AntiAliasingMethod");
	
}

void USNGameUserSettings::SetAAMethod(int32 InAntialiasingMethod)
{
	UWorld* world = GEngine->GameViewport->GetWorld();
	
	FString CmdCommand = "r.AntiAliasingMethod " + FString::FromInt(InAntialiasingMethod);
	const TCHAR* TCharCmdCommand = *CmdCommand;
	 
	GEngine->Exec(world->GetWorld(), TCharCmdCommand);

	FString Value = FString::FromInt(InAntialiasingMethod);
	
	GConfig->SetString(TEXT("/Script/Engine.RendererSettings"), TEXT("r.AntiAliasingMethod"), *Value, GEngineIni);
	GConfig->Flush(true, GEngineIni);
}

int32 USNGameUserSettings::GetMSAAQuality() const
{
	return UKismetSystemLibrary::GetConsoleVariableIntValue("r.MSAACount");
}

void USNGameUserSettings::SetMSAAQuality(int32 InMSAAQuality)
{
	UWorld* world = GEngine->GameViewport->GetWorld();
	
	FString CmdCommand = "r.MSAACount " + FString::FromInt(InMSAAQuality);
	const TCHAR* TCharCmdCommand = *CmdCommand;
	
	GEngine->Exec(world->GetWorld(), TCharCmdCommand);

	FString Value = FString::FromInt(InMSAAQuality);
	
	GConfig->SetString(TEXT("/Script/Engine.RendererSettings"), TEXT("r.MSAACount"), *Value, GEngineIni);
	GConfig->Flush(true, GEngineIni);
}

#undef LOCTEXT_NAMESPACE



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
		{LOCTEXT("WindowmodeOptions_WindowedFullscreen_Loc", "WindowedFullscreen"), EWindowMode::WindowedFullscreen} ,
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
	DisplaySettingsCollection->SetCollectionName(FText::FromString("Display"));

	{
		USNGameSetting_IntPoint* Setting = NewObject<USNGameSetting_IntPoint>();
		Setting->SetSettingName(LOCTEXT("Resolotion_Loc" , "Resolotion"));
		Setting->SetOptions(ResolutionOptions);
		Setting->AddGetterFunc([&]() { return GetScreenResolution(); } );
		Setting->AddSetterFunc([&](FIntPoint Level) { SetScreenResolution(Level); ApplySettings(false); ApplyResolutionSettings(false); });
		DisplaySettingsCollection->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Enum* Setting = NewObject<USNGameSetting_Enum>();
		Setting->SetSettingName(LOCTEXT("WindowMode_Loc" , "WindowMode"));
		Setting->SetOptions(WindowModeOptions);
		Setting->AddGetterFunc([&]() { return GetFullscreenMode(); } );
		Setting->AddSetterFunc([&](EWindowMode::Type Level) { SetFullscreenMode(Level); ApplySettings(false); });
		DisplaySettingsCollection->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Float* Setting = NewObject<USNGameSetting_Float>();
		Setting->SetSettingName(LOCTEXT("ResScale_Loc" , "ResScale"));
		Setting->AddGetterFunc([&]() { return GetResolutionScaleNormalized(); } );
		Setting->AddSetterFunc([&](float Level){ SetResolutionScaleNormalized(Level); ApplySettings(false); });
		Setting->WidgetType = EWidgetType::Slider;
		DisplaySettingsCollection->AddSettingToCollection(Setting);
	}

	VideoSettings.Add(DisplaySettingsCollection);

	const auto AdvancedSettingsCollection = NewObject<USNGameSettingCollection>();
	AdvancedSettingsCollection->SetCollectionName(FText::FromString("Advanced settings"));
	
	{
		USNGameSetting_Bool* Setting = NewObject<USNGameSetting_Bool>();
		Setting->SetSettingName(LOCTEXT("VSync_Loc" , "VSync"));
		Setting->SetOptions(BoolOptions);
		Setting->AddGetterFunc([&]() { return IsVSyncEnabled(); } );
		Setting->AddSetterFunc([&](bool Level) { SetVSyncEnabled(Level); ApplySettings(false); });
		AdvancedSettingsCollection->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("FrameLimit_Loc" , "FrameLimit"));
		Setting->SetOptions(FrameLimitOptions);
		Setting->AddGetterFunc([&]() { return GetFrameRateLimit(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetFrameRateLimit(Level); ApplySettings(false); });
		AdvancedSettingsCollection->AddSettingToCollection(Setting);
	}

	VideoSettings.Add(AdvancedSettingsCollection);

	const auto GraphicsQuality = NewObject<USNGameSettingCollection>();
	GraphicsQuality->SetCollectionName(FText::FromString("Graphics Quality"));
	
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("AntiAliasingMethod_Loc" , "Anti-Aliasing Metod"));
		Setting->SetOptions(AAMethodOptions);
		Setting->AddGetterFunc([&]() { return GetAAMethod(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetAAMethod(Level); ApplySettings(false); });
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("MSAACount_Loc" , "MSAA Count"));
		Setting->SetOptions(MSAACountOptions);
		Setting->AddGetterFunc([&]() { return GetMSAAQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetMSAAQuality(Level); ApplySettings(false); });
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("AntiAliasing_Loc" , "Anti-Aliasing"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetAntiAliasingQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetAntiAliasingQuality(Level); ApplySettings(false); });
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("Textures_Loc" , "Textures"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetTextureQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetTextureQuality(Level); ApplySettings(false); });	
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("Shadows_Loc" , "Shadows"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetShadowQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetShadowQuality(Level); ApplySettings(false); });
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("Post Processing_Loc" , "Post Processing"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetPostProcessingQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetPostProcessingQuality(Level); ApplySettings(false); });
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("Follage_Loc" , "Follage"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetFoliageQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetFoliageQuality(Level); ApplySettings(false); });
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("GlobalIllumination_Loc" , "Global Illumination"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetGlobalIlluminationQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetGlobalIlluminationQuality(Level); ApplySettings(false); });
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("Reflection_Loc" , "Reflection"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetReflectionQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetReflectionQuality(Level); ApplySettings(false); });
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("Shading_Loc" , "Shading"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetShadingQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetShadingQuality(Level); ApplySettings(false); });
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("ViewDistance_Loc" , "ViewDistance"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetterFunc([&]() { return GetViewDistanceQuality(); } );
		Setting->AddSetterFunc([&](int32 Level) { SetViewDistanceQuality(Level); ApplySettings(false); });
		GraphicsQuality->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Number* Setting = NewObject<USNGameSetting_Number>();
		Setting->SetSettingName(LOCTEXT("VisualEffects_Loc" , "VisualEffects"));
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
	/*int32 Index =*/ return UKismetSystemLibrary::GetConsoleVariableIntValue("r.AntiAliasingMethod");

	/*switch (Index)
	{
	case 0:
		return EAntialiasing::AA_NONE;

	case 1:
		return EAntialiasing::AA_FXAA;

	case 2:
		return EAntialiasing::AA_TAA;

	case 3:
		return EAntialiasing::AA_MSAA;

	case 4:
		return EAntialiasing::AA_TSR;

	default:
		return EAntialiasing::AA_NONE;
	}*/
}

void USNGameUserSettings::SetAAMethod(int32 InAntialiasingMethod)
{
	UWorld* World = GEngine->GetWorld();

	/*switch (InAntialiasingMethod)
	{
	case EAntialiasing::AA_NONE:
		GEngine->Exec(World, TEXT("r.AntiAliasingMethod 0"));
		
	case EAntialiasing::AA_FXAA:
		GEngine->Exec(World, TEXT("r.AntiAliasingMethod 1"));

	case EAntialiasing::AA_TAA:
		GEngine->Exec(World, TEXT("r.AntiAliasingMethod 2"));

	case EAntialiasing::AA_MSAA:
		GEngine->Exec(World, TEXT("r.AntiAliasingMethod 3"));

	case EAntialiasing::AA_TSR:
		GEngine->Exec(World, TEXT("r.AntiAliasingMethod 4"));
	}*/
	FString CmdCommand = "r.AntiAliasingMethod " + FString::FromInt(InAntialiasingMethod);
	const TCHAR* TCharCmdCommand = *CmdCommand;
	 
	GEngine->Exec(World, TCharCmdCommand);
}

int32 USNGameUserSettings::GetMSAAQuality() const
{
	return UKismetSystemLibrary::GetConsoleVariableIntValue("r.MSAACount");
}

void USNGameUserSettings::SetMSAAQuality(int32 InMSAAQuality)
{
	UWorld* World = GEngine->GetWorld();

	/*switch (InMSAAQuality)
	{
	case EMSAAQuality::MSAA_NONE:
		GEngine->Exec(World, TEXT("r.MSAACount 0"));

	case EMSAAQuality::MSAA_2X:
		GEngine->Exec(World, TEXT("r.MSAACount 2"));

	case EMSAAQuality::MSAA_4X:
		GEngine->Exec(World, TEXT("r.MSAACount 4"));
		
	case EMSAAQuality::MSAA_8X:
		GEngine->Exec(World, TEXT("r.MSAACount 8"));
	}*/
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, FString::FromInt(InMSAAQuality));
	FString CmdCommand = "r.MSAACount " + FString::FromInt(InMSAAQuality);
	const TCHAR* TCharCmdCommand = *CmdCommand;
	
	GEngine->Exec(World, TCharCmdCommand);
}

#undef LOCTEXT_NAMESPACE

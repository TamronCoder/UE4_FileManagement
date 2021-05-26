// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"
#include "Runtime/Core/Public/HAL/PlatformFilemanager.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"

bool UMyBlueprintFunctionLibrary::CreateDirectory(const FString& Path)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	return PlatformFile.CreateDirectory(*Path);
}

bool UMyBlueprintFunctionLibrary::DeleteDirectory(const FString& Path)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	return PlatformFile.DeleteDirectory(*Path);
}

bool UMyBlueprintFunctionLibrary::FindFile(const FString & Path)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.FileExists(*Path))
	{
		return true;
	}
	return false;
}

void UMyBlueprintFunctionLibrary::CreateTextFile(const FString & Path)
{
	FString FileContent = TEXT("This is content by unreal!");
	FFileHelper::SaveStringToFile(FileContent, *Path, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}

bool UMyBlueprintFunctionLibrary::DeleteFile(const FString& Path)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.DeleteFile(*Path))
	{
		return true;
	}
	return false;
}

bool UMyBlueprintFunctionLibrary::MoveFile(const FString & ToPath, const FString & FromPath)
{
	if (!FPaths::FileExists(FromPath))
	{
		UE_LOG(LogTemp, Warning, TEXT("FromPath is not exist"));
	}
	if (!FPaths::DirectoryExists(ToPath))
	{
		UE_LOG(LogTemp, Warning, TEXT("ToPath is not exist"));
	}
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.MoveFile(*ToPath, *FromPath))
	{
		return true;
	}

	//不推荐用，重复操作会造成卡顿
	/*if (IFileManager::Get().Move(*ToPath, *FromPath))
	{
		return true;
	}*/
	return false;
}

FString UMyBlueprintFunctionLibrary::ConvertRelativePathToFull(const FString & Path)
{
	IFileManager& FileManager = IFileManager::Get();
	// FString FullPath = FileManager.GetFilenameOnDisk(*FPaths::ConvertRelativePathToFull(Path));
	FString FullPath = FPaths::ConvertRelativePathToFull(Path);
	return FullPath;
}

bool UMyBlueprintFunctionLibrary::CreatAndMoveFile()
{
#if PLATFORM_ANDROID
	FString CreateFilePath = GetAndroidBaseDir() + "/AlphaDoc.txt";
	CreateTextFile(CreateFilePath);
	FString ProjectSavedPath = GetAndroidBaseDir() + "/UE4Game/" + FApp::GetProjectName() + "/" + FApp::GetProjectName() + "/Saved/";
	FString ProjectSavedFilePath = ProjectSavedPath + "AlphaDoc.txt";
	UE_LOG(LogTemp, Warning, TEXT("ProjectSavedPath: %s"), *ProjectSavedPath);
	if (!FPaths::DirectoryExists(ProjectSavedPath))
	{
		UE_LOG(LogTemp, Warning, TEXT("ProjectSavedPath is not exist!"));
	}
	return MoveFile(ProjectSavedFilePath, CreateFilePath);
#endif
	return false;
}

FString UMyBlueprintFunctionLibrary::GetProjectPersistentDownloadDir()
{
	// 获取项目永久的下载路径，在安卓环境下，可获得绝对路径
	FString Path = FPaths::ProjectPersistentDownloadDir();
	return Path;
}

FString UMyBlueprintFunctionLibrary::GetGameSourceDir()
{
	// 获取项目Source目录
	FString Path = FPaths::GameSourceDir();
	return Path;
}

FString UMyBlueprintFunctionLibrary::GetLaunchDir()
{
	// 获取项目启动路径
	FString LaunchDir = ConvertRelativePathToFull(FPaths::LaunchDir());
	return LaunchDir;
}

FString UMyBlueprintFunctionLibrary::GetEngineDir()
{
	// 获取引擎路径
	FString EngineDir = ConvertRelativePathToFull(FPaths::EngineDir());
	return EngineDir;
}

FString UMyBlueprintFunctionLibrary::GetRootDir()
{
	// 获取引擎根路径
	FString RootDir = ConvertRelativePathToFull(FPaths::RootDir());
	return RootDir;
}

FString UMyBlueprintFunctionLibrary::GetProjectDir()
{
	// 获取项目路径
	FString ProjectDir = ConvertRelativePathToFull(FPaths::ProjectDir());
	return ProjectDir;
}

FString UMyBlueprintFunctionLibrary::GetSandboxesDir()
{
	// 获取项目Sandboxes路径
	FString SandboxesDir = ConvertRelativePathToFull(FPaths::SandboxesDir());
	return SandboxesDir;
}

FString UMyBlueprintFunctionLibrary::GetAndroidBaseDir()
{
#if PLATFORM_ANDROID
	extern FString GFilePathBase;
	return GFilePathBase;
#else
	return FString("");
#endif
}

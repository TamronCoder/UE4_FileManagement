// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UE4_FILEMANAGEMENT_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "FileManagement")
		static bool CreateDirectory(const FString& Path);
	UFUNCTION(BlueprintCallable, Category = "FileManagement")
		static bool DeleteDirectory(const FString& Path);
	UFUNCTION(BlueprintCallable, Category = "FileManagement")
		static bool FindFile(const FString & Path);
	UFUNCTION(BlueprintCallable, Category = "FileManagement")
		static void CreateTextFile(const FString& Path);
	UFUNCTION(BlueprintCallable, Category = "FileManagement")
		static bool DeleteFile(const FString& Path);
	UFUNCTION(BlueprintCallable, Category = "FileManagement")
		static bool MoveFile(const FString& ToPath, const FString& FromPath);

	UFUNCTION(BlueprintCallable, Category = "FileManagement")
		static FString GetLaunchDir();
	UFUNCTION(BlueprintCallable, Category = "FileManagement")
		static FString GetEngineDir();
	UFUNCTION(BlueprintCallable, Category = "FileManagement")
		static FString GetRootDir();
	UFUNCTION(BlueprintCallable, Category = "FileManagement")
		static FString GetProjectDir();
	UFUNCTION(BlueprintCallable, Category = "FileManagement")
		static FString GetSandboxesDir();
	UFUNCTION(BlueprintCallable, Category = "FileManagement")
		static FString GetProjectPersistentDownloadDir();
	UFUNCTION(BlueprintCallable, Category = "FileManagement")
		static FString GetGameSourceDir();
	UFUNCTION(BlueprintCallable, Category = "FileManagement")
		static FString GetAndroidBaseDir();

private:
	static FString ConvertRelativePathToFull(const FString& Path);

public:
	UFUNCTION(BlueprintCallable, Category = "FileManagement")
		static bool CreatAndMoveFile();
};

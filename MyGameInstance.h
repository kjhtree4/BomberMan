// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BomberManFinal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "ParentItem.h"
#include "Blueprint/UserWidget.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Percentage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Number;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TSubclassOf<AParentItem> ItemClass;

};


UCLASS()
class BOMBERMANFINAL_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:

	UMyGameInstance();

	UFUNCTION(BlueprintNativeEvent)
		TArray<FString> GetItemSpawnPercentageFromDataTable();
		virtual TArray<FString> GetItemSpawnPercentageFromDataTable_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		FItemData GetItemStructure(int32 ItemNumber);
		virtual FItemData GetItemStructure_Implementation(int32 ItemNumber);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		UDataTable *ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<FString> ItemSpawnPercentageArray;


	UFUNCTION(BlueprintCallable)
		void ShowMainMenu();
	UFUNCTION()
		void HideMainMenu();
	UFUNCTION()
		void ShowMapSelectMenu();
	UFUNCTION()
		void HideMapSelectMenu();
	UFUNCTION()
		void ShowTimerWidget();
	UFUNCTION()
		void ShowGameOverWidget();



	UPROPERTY()
		APlayerController *myPlayerController;


	UPROPERTY(BlueprintReadWrite)
		FText WhoWin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Time;
	UPROPERTY(BlueprintReadWrite)
		int32 TimeCount;


	UFUNCTION()
		void TimeHandler();

	class UGameOverWidget *myGameOverWidget;
	class UTimerWidget *myTimerWidget;
protected:
	UPROPERTY() 
		UUserWidget* CurrentWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> MainMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> MapSelectMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> TimerWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> GameOverWidget;

	FTimerHandle TimerHandler;
};

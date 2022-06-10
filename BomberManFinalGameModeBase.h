// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "BomberManFinal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/DataTable.h"
#include "ParentItem.h"
#include "MyGameInstance.h"
#include "BomberManFinalGameModeBase.generated.h"

/**
 *
 */

/*
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
*/
//�̰� �����ϸ� �������Ʈ���� ����ü �����ѰŶ� ���� ȿ���� �����༭ ����ü�� �̿��� �����ͺ��̽� ���̺����� ����� ����� �� �ִ�.
  // ����Ҷ� � ����ü�� �̿��Ұ��� �����Ҷ� �ش� ������ ����ü�� �̸��� ���.



UCLASS()
class BOMBERMANFINAL_API ABomberManFinalGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABomberManFinalGameModeBase();

	virtual void BeginPlay() override;


	UPROPERTY(BlueprintReadWrite)
		FText WhoWin;

	UPROPERTY(EditAnywhere)
		int32 Time;

	UPROPERTY()
		int32 TimeCount;

	UFUNCTION()
		void ShowTimer();

	UFUNCTION()
		void GameOver();

	UFUNCTION()
		void TimeHandler();

	//UFUNCTION()
		//TArray<FString> GetItemSpawnPercentageFromDataTable();

	//UFUNCTION()
		//FItemData GetItemStructure(int32 ItemNumber);

	UPROPERTY(EditAnywhere)
		UDataTable *ItemDataTable;


private:

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> TimerWidget;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> GameOverWidget;

	FTimerHandle TimerHandler;

	
};

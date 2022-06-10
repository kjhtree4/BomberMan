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
//이거 선언하면 블루프린트에서 구조체 선언한거랑 같은 효과를 지지녀서 구조체를 이용한 데이터베이스 테이블만들기등 기능을 사용할 수 있다.
  // 사용할때 어떤 구조체를 이용할건지 선택할때 해당 선언한 구조체의 이름이 뜬다.



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

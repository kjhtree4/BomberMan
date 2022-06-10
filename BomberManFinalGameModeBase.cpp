// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "Garbage.h"
#include "Engine/Engine.h"
#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "MyGameInstance.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "BomberManFinalGameModeBase.h"


ABomberManFinalGameModeBase::ABomberManFinalGameModeBase() {
	
	
	DefaultPawnClass = AGarbage::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ItemData(TEXT("DataTable'/Game/MyItemDataTableBP.MyItemDataTableBP'"));

	if (DT_ItemData.Succeeded()) {
		ItemDataTable = DT_ItemData.Object;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Database Load Success"));
		//GLog->Log("DataTableLoadSuccess");
	}
	else {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Database Load failed"));
		//GLog->Log("DataTableLoadfailed");
	}
}

void ABomberManFinalGameModeBase::ShowTimer()
{
	TimeCount = Time;
	GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &ABomberManFinalGameModeBase::TimeHandler, 1.0f, true);
	CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), TimerWidget);
	
}

void ABomberManFinalGameModeBase::GameOver()
{
	CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), GameOverWidget)->AddToViewport();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	TimeCount = Time;
	GetWorld()->GetTimerManager().ClearTimer(TimerHandler);
	
}

void ABomberManFinalGameModeBase::TimeHandler()
{
	--TimeCount;
	if (TimeCount == 0) {
		WhoWin.FromName(FName(TEXT("Draw")));
		GameOver();
	}
	
}

void ABomberManFinalGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UMyGameInstance *myGameinstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	myGameinstance->ShowTimerWidget();
}
/*
TArray<FString> ABomberManFinalGameModeBase::GetItemSpawnPercentageFromDataTable()
{
	TArray<FString> ItemSpawnPercentage;
	
	ItemSpawnPercentage.Add(FString("rr"));

	//FItemData *ItemData = ItemDataTable->FindRow<FItemData>(FName(*(FString::FormatAsNumber(0))), FString(""));
	//ItemSpawnPercentage = UDataTableFunctionLibrary::GetDataTableColumnAsString(ItemDataTable, TEXT("Percentage"));
	
	return ItemSpawnPercentage;

}
*/
/*
FItemData ABomberManFinalGameModeBase::GetItemStructure(int32 ItemNumber)
{
	FItemData *ItemData = ItemDataTable->FindRow<FItemData>(FName(*(FString::FormatAsNumber(ItemNumber))), FString(""));
	FItemData RealItemData = *ItemData;
	return RealItemData;
	
}
*/

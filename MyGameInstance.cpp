// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/DataTableFunctionLibrary.h"
#include "Engine/Engine.h"
#include "TimerWidget.h"
#include "GameOverWidget.h"
#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance() {
	GLog->Log("GAMEINSTANCE");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ItemData(TEXT("DataTable'/Game/MyItemDataTableBP.MyItemDataTableBP'"));
	if (DT_ItemData.Succeeded()) {
		ItemDataTable = DT_ItemData.Object;
		GLog->Log("DataTableLoadSuccess");
	}
	else {
		GLog->Log("DataTableLoadfail");
	}

	Time = 5;
	//myPlayerController = GetWorld()->GetFirstPlayerController(); //이거는 실시간으로 해줘야됨


}
/*
TArray<FString> UMyGameInstance::GetItemSpawnPercentageFromDataTable_Implementation()
{
	TArray<FString> ItemSpawnPercentage;
	ItemSpawnPercentage = UDataTableFunctionLibrary::GetDataTableColumnAsString(ItemDataTable, TEXT("Percentage"));
	GLog->Log("GameInstanceCPP");
	return ItemSpawnPercentage;
}
*/



TArray<FString> UMyGameInstance::GetItemSpawnPercentageFromDataTable_Implementation()
{
	
	TArray<FString> ItemSpawnPercentage;
	ItemSpawnPercentage = UDataTableFunctionLibrary::GetDataTableColumnAsString(ItemDataTable, TEXT("Percentage"));
	FItemData *ItemData = ItemDataTable->FindRow<FItemData>(FName(*(FString::FormatAsNumber(0))), FString(""));
	

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("In BP, if you see this msg, its wrong because is implemented."));

	return ItemSpawnPercentage;
	
}

FItemData UMyGameInstance::GetItemStructure_Implementation(int32 ItemNumber)
{
	
	FItemData *ItemData = ItemDataTable->FindRow<FItemData>(FName(*(FString::FormatAsNumber(ItemNumber))), FString(""));
	FItemData RealItemData = *ItemData;
	return RealItemData;
    

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("In BP, if you see this msg, its wrong because is implemented."));
	return FItemData();
}

void UMyGameInstance::ShowMainMenu() {
	myPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if (MainMenu != nullptr) { 
		CurrentWidget = CreateWidget(myPlayerController, MainMenu);
		if (CurrentWidget) { 
			myPlayerController->SetInputMode(FInputModeUIOnly());
			myPlayerController->bShowMouseCursor = true;
			CurrentWidget->AddToViewport(); 
		} 
	}
}

void UMyGameInstance::HideMainMenu() {
	if (CurrentWidget != nullptr) {
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}
}

void UMyGameInstance::HideMapSelectMenu(){
	if (CurrentWidget != nullptr) {
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}
}

void UMyGameInstance::ShowTimerWidget()
{
	myPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	TimeCount = Time;
	GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &UMyGameInstance::TimeHandler, 1.0f, true);

	if (TimerWidget != nullptr) {
		CurrentWidget= CreateWidget(myPlayerController, TimerWidget);
		myTimerWidget = Cast<UTimerWidget>(CurrentWidget);
		if (CurrentWidget) {
			myTimerWidget->TimerWidgetSetting(TimeCount);
			CurrentWidget->AddToViewport();
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("1111"));
		}
	}
	
}

void UMyGameInstance::ShowGameOverWidget()
{
	myPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (GameOverWidget != nullptr) {
		CurrentWidget = CreateWidget(myPlayerController, GameOverWidget);
		myGameOverWidget = Cast<UGameOverWidget>(CurrentWidget);

		if (CurrentWidget) {

			myGameOverWidget->WhoWinTextSetting(WhoWin);
			CurrentWidget->AddToViewport();
		}
	}

	myPlayerController->SetInputMode(FInputModeUIOnly());
	myPlayerController->bShowMouseCursor = true;

	TimeCount = Time;
	GetWorld()->GetTimerManager().ClearTimer(TimerHandler);
}

void UMyGameInstance::TimeHandler()
{
	--TimeCount;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Timer"));
	if(myTimerWidget!=nullptr)
	myTimerWidget->TimerWidgetSetting(TimeCount);
	

	if (TimeCount == 0) {
		WhoWin= FText::FromName(FName(TEXT("Draw")));
		ShowGameOverWidget();
	}
}

void UMyGameInstance::ShowMapSelectMenu(){
	myPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (MapSelectMenu != nullptr) {
		CurrentWidget = CreateWidget(myPlayerController, MapSelectMenu);

		if (CurrentWidget != nullptr) {
			myPlayerController->SetInputMode(FInputModeUIOnly());
			myPlayerController->bShowMouseCursor = true;
			CurrentWidget->AddToViewport();
		}
	}
}


/*
FItemData UMyGameInstance::GetItemStructure_Implementation(int32 ItemNumber)
{
	FItemData *ItemData = ItemDataTable->FindRow<FItemData>(FName(*(FString::FormatAsNumber(ItemNumber))), FString(""));
	FItemData RealItemData = *ItemData;
	return RealItemData;
}
*/

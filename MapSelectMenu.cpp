// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "MyGameInstance.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Styling/SlateBrush.h"
#include "MapSelectMenu.h"

void UMapSelectMenu::NativeConstruct()
{

	GLog->Log("MapSelectMenu Contruct");

	myGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (myGameInstance != nullptr) {
		GLog->Log("get GameInstance at MapSelect menu success ");
	}
	else {
		GLog->Log("get GameInstance at MapSelect menu failed ");
	}

	RightBTN->OnClicked.AddDynamic(this, &UMapSelectMenu::RightBTN_Func);//이거 보충해서 유저위젯쓰는 법 수정하기
	LeftBTN->OnClicked.AddDynamic(this, &UMapSelectMenu::LeftBTN_Func);
	StartBTN->OnClicked.AddDynamic(this, &UMapSelectMenu::StartBTN_Func);
	BackBTN->OnClicked.AddDynamic(this, &UMapSelectMenu::BackBTN_Func);


	SelectedMap = MapImageArray[SelectedMapNum];
	SetImage();
}

void UMapSelectMenu::RightBTN_Func() {
	if (SelectedMapNum < MapImageArray.Num() - 1) {
		SelectedMapNum++;
		SelectedMap = MapImageArray[SelectedMapNum];
		SetImage();
	}
}

void UMapSelectMenu::LeftBTN_Func() {
	if (SelectedMapNum > 0) {
		SelectedMapNum--;
		SelectedMap = MapImageArray[SelectedMapNum];
		SetImage();
	}
}

void UMapSelectMenu::StartBTN_Func() {
	switch (SelectedMapNum) {
	case 0:
		UGameplayStatics::OpenLevel(GetWorld(), FName("Map1"));//오픈레벨하는법
		break;
	case 1:
		UGameplayStatics::OpenLevel(GetWorld(), FName("Map2"));
		break;
	}

	APlayerController *thisController = UGameplayStatics::GetPlayerController(GetWorld(), 0);//겟 플레이어 컨트롤러 하는법
	
	thisController->SetInputMode(FInputModeGameAndUI());
	thisController->bShowMouseCursor = false;
}

void UMapSelectMenu::BackBTN_Func() {
	myGameInstance->HideMapSelectMenu();
	myGameInstance->ShowMainMenu();
}

void UMapSelectMenu::SetImage()
{
	FSlateBrush ImageBrush;
	UWidgetBlueprintLibrary::MakeBrushFromTexture(SelectedMap, 256, 256);
	
	MapImage->SetBrush(UWidgetBlueprintLibrary::MakeBrushFromTexture(SelectedMap, 256, 256));
}

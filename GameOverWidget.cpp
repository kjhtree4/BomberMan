// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Components/Widget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameOverWidget.h"

void UGameOverWidget::NativeConstruct()
{
	GLog->Log("GameOverWidget Contruct");

	myGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (myGameInstance != nullptr) {
		GLog->Log("get GameInstance at MapSelect menu success ");
	}
	else {
		GLog->Log("get GameInstance at MapSelect menu failed ");
	}

	
	MainMenuBTN->OnClicked.AddDynamic(this, &UGameOverWidget::MainMenuBTN_Func);
}

FText UGameOverWidget::WhoWinText_BindFunc() {
	FText WhoWin;
	WhoWin = myGameInstance->WhoWin;

	return WhoWin;
}

void UGameOverWidget::MainMenuBTN_Func() {
	UGameplayStatics::OpenLevel(this,FName("MainMenu"));
}

void UGameOverWidget::WhoWinTextSetting(FText WhoWin)
{
	WhoWinText->SetText(WhoWin);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "MyGameInstance.h"
#include "Components/TextBlock.h"
//#include "Components/Widget.h"
#include "MainMenu.h"

void UMainMenu::NativeConstruct()
{
	
	GLog->Log("MainMenu Contruct");

	myGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (myGameInstance!=nullptr) {
		GLog->Log("get GameInstance at main menu success ");
	}
	else {
		GLog->Log("get GameInstance at main menu failed ");
	}
	

	GameStartBTN->OnClicked.AddDynamic(this, &UMainMenu::GameStartBTN_Func);
	QuitBTN->OnClicked.AddDynamic(this, &UMainMenu::QuitBTN_Func);
	//Temp->TextDelegate.BindUFunction(this, "SetTimer");
	//Temp->TextDelegate.BindDynamic(this, &UMainMenu::SetTimer);
}

void UMainMenu::GameStartBTN_Func(){
	myGameInstance->HideMainMenu();
	myGameInstance->ShowMapSelectMenu();
}

void UMainMenu::QuitBTN_Func(){
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, true);
}

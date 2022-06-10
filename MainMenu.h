// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BomberManFinal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMANFINAL_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UMyGameInstance *myGameInstance;

	UFUNCTION()
		void GameStartBTN_Func();

	UFUNCTION()
		void QuitBTN_Func();

private:
	UPROPERTY(Meta = (BindWidget))
		class UCanvasPanel *MyCanvasPanel;

	UPROPERTY(Meta = (BindWidget))
		class UButton *GameStartBTN;

	UPROPERTY(Meta = (BindWidget))
		class UButton *QuitBTN;

	//UPROPERTY(Meta = (BindWidget))
	//	class UTextBlock *Temp;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BomberManFinal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMANFINAL_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UMyGameInstance *myGameInstance;

	UFUNCTION()
		FText WhoWinText_BindFunc();
	UFUNCTION()
		void MainMenuBTN_Func();
	UFUNCTION()
		void WhoWinTextSetting(FText WhoWinText);

private:
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock *WhoWinText;

	UPROPERTY(Meta = (BindWidget))
		class UButton *MainMenuBTN;
};

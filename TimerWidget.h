// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BomberManFinal.h"
#include "Blueprint/UserWidget.h"
#include "TimerWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMANFINAL_API UTimerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	//virtual void NativeTick(const FGeometry& Geometry,float DeltaSeconds) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UMyGameInstance *myGameInstance;

	//UFUNCTION(BlueprintCallable)
	//	void TimerText_BindFunc();

	UFUNCTION()
		void TimerWidgetSetting(int32 Time);
	
private:
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock *TimerText;
	
};

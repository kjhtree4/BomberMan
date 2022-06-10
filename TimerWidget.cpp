// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Engine/Engine.h"
#include "Components/TextBlock.h"
#include "TimerWidget.h"

void UTimerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GLog->Log("GameOverWidget Contruct");

	myGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (myGameInstance != nullptr) {
		GLog->Log("get GameInstance at MapSelect menu success ");
	}
	else {
		GLog->Log("get GameInstance at MapSelect menu failed ");
	}

}
/*
void UTimerWidget::NativeTick(const FGeometry& Geometry,float DeltaSeconds)
{
	Super::NativeTick(Geometry, DeltaSeconds);

	TimerText_BindFunc();
}


틱에서 바인딩하려고 만들었는데 게임인스턴스에서 시간초 세는 타이머에서 1초마다 함수부르는게 더 최적화된거라서 이거 안씀
이거 말고 밑에꺼 씀
void UTimerWidget::TimerText_BindFunc() {
	FText Time;
	Time = FText::FromString(FString::FromInt(myGameInstance->TimeCount));

	TimerText->SetText(Time);
}
*/

void UTimerWidget::TimerWidgetSetting(int32 Time) {
	//FText TimeText;
	//TimeText = FText::FromString(FString::FromInt(Time));
	TimerText->SetText(FText::FromString(FString::FromInt(Time)));
}
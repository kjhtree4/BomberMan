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


ƽ���� ���ε��Ϸ��� ������µ� �����ν��Ͻ����� �ð��� ���� Ÿ�̸ӿ��� 1�ʸ��� �Լ��θ��°� �� ����ȭ�ȰŶ� �̰� �Ⱦ�
�̰� ���� �ؿ��� ��
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
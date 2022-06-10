// Fill out your copyright notice in the Description page of Project Settings.



#include "Engine/Engine.h"
#include "SpeedItem.h"

void ASpeedItem::Upgrading(AParentPlayer *Player) {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Upgrading from SpeedItem"));
	Player->IncreaseSpeed(IncreaseNum);
	GLog->Log("Speedincrease");
}
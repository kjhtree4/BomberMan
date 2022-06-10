// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/Engine.h"
#include "CountItem.h"

void ACountItem::Upgrading(AParentPlayer *Player) {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Upgrading from CountItem"));
	Player->IncreaseBombCount(IncreaseNum);
	GLog->Log("BombCountincrease");
}
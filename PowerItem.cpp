// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/Engine.h"
#include "PowerItem.h"

void APowerItem::Upgrading(AParentPlayer *Player) {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Upgrading from PowerItem"));
	Player->IncreaseBombFlameDistance(IncreaseNum);
	GLog->Log("FlameDistanceUpgrade");
}
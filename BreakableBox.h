// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "BomberManFinal.h"
#include "GameFramework/Actor.h"
#include "MyGameInstance.h"
#include "BomberManFinalGameModeBase.h"
#include "BreakableBox.generated.h"

UCLASS()
class BOMBERMANFINAL_API ABreakableBox : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABreakableBox();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent *Cube;
	UPROPERTY(EditAnywhere)
		UBoxComponent *BoxCol;
	UPROPERTY(EditAnywhere)
		USceneComponent *RootComp;


	UFUNCTION()
		void destroy();
	UFUNCTION()
		void ItemSelect(int32 ItemNumber);

	UMyGameInstance *GameInstance;
	ABomberManFinalGameModeBase *myGameMode;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY()
		float RandomSeed;
	UPROPERTY()
		float BeforeSeedNum;
	UPROPERTY()
		int32 WhatToSpawnItem;

};

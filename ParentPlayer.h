// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BomberManFinal.h"
#include "GameFramework/Actor.h"
#include "Bomb.h"
#include "ParentPlayer.generated.h"

UCLASS()
class BOMBERMANFINAL_API AParentPlayer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AParentPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UInputComponent *PlayerInputComponent;

	UPROPERTY()
		float BombCount;

	UPROPERTY()
		float Speed;

	UPROPERTY()
		float BombFlameDistance;

	UPROPERTY()
		USceneComponent *DefaultSceneRootComp;

	UPROPERTY(Category = "Component", EditAnywhere)
		UStaticMeshComponent *Cube;

	UPROPERTY(Category = "Component", EditAnywhere)
		UPointLightComponent *PointLight;

	//UPROPERTY(Category = "Component", EditAnywhere)
	//	class UInputComponent *InputComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)//블루프린트에서 호출하기 위해서 지정하는 매크로
		void RightMove(float AxisValue);
	UFUNCTION(BlueprintCallable)
		void UpMove(float AxisValue);
	UFUNCTION(BlueprintCallable)
		void SpawnBomb();
	UFUNCTION()
		void IncreaseBombFlameDistance(int32 IncreaseNum);
	UFUNCTION()
		void IncreaseSpeed(int32 IncreaseNum);
	UFUNCTION()
		void IncreaseBombCount(int32 IncreaseNum);


	UPROPERTY(EditAnywhere, Category = "Set")//에딧 애니웨어로 블프에서 세팅하고 싶을때는 카테고리 꼭 써주자/ 안쓰면 안나오더라
		TSubclassOf<ABomb> BombBPClass;



};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BomberManFinal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "BombEffect.h"
#include "Bomb.generated.h"

UCLASS()
class BOMBERMANFINAL_API ABomb : public AActor
{
	GENERATED_BODY()

		UTimelineComponent* MyTimeline;

public:
	// Sets default values for this actor's properties
	ABomb();

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABombEffect> BombEffectBP;

	//class ABombEffect *BombEffect;
	class AParentPlayer *ParentPlayer;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent *Sphere;

	UPROPERTY()
		float FlameDistance;

	UFUNCTION()
		void Explode();


	FOnTimelineEvent TimelineFinished;
	FOnTimelineFloat InterpFuntion;


	//TSubclassOf

	UPROPERTY(EditAnywhere, Category = "Timeline")
		UCurveFloat *fCurve;//�̰� Ŀ��� �������Ʈ�󿡼� ������༭ ��������ߵ�


	UPROPERTY(EditAnywhere, Category = "Timeline")
		float ZOffset;

	//Declare our delegate function to be binded with TimelineFloatReturn(float value)
		//FOnTimelineFloat InterpFuntion;
	//Declare our delegate funtion to be binded with OnTimelineFinished()
		//FOnTimelineEvent TimelineFinished;

	UFUNCTION()
		void TimelineFloatReturn(float value);
	UFUNCTION()
		void OnTimelineFinished();
	UFUNCTION()
		void OnBombEndOverlap(AActor *OverlappedActor, AActor * OtherActor);//�𸮾� �����ϰ��� ��������Ʈ�������̳� �¾��Ϳ����� �Ѵ� OverlappedActor�� �ʿ����, �������� ������Ʈ���� �����ִµ� ���Ϳ����� overlappedActor�ȳ����־ ����ص־ߵ�.


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY()
		int32 BoomTime;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

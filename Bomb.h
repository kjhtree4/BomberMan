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
		UCurveFloat *fCurve;//이거 커브는 블루프린트상에서 만들어줘서 지정해줘야됨


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
		void OnBombEndOverlap(AActor *OverlappedActor, AActor * OtherActor);//언리얼 업뎃하고나서 온컴포넌트오버랩이나 온액터오버랩 둘다 OverlappedActor를 필요로함, 블프에는 컴포넌트에는 나와있는데 액터에서는 overlappedActor안나와있어서 기억해둬야됨.


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY()
		int32 BoomTime;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

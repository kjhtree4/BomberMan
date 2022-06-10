// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BomberManFinal.h"
#include "ParentPlayer.h"
#include "GameFramework/Actor.h"
#include "ParentItem.generated.h"

UCLASS()
class BOMBERMANFINAL_API AParentItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AParentItem();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent *Sphere;

	UFUNCTION()
		void OnItemBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void Upgrading(AParentPlayer *Player);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
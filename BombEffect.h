// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "BomberManFinal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "BombEffect.generated.h"

UCLASS()
class BOMBERMANFINAL_API ABombEffect : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABombEffect();

	class AParentPlayer *ContactedPlayer;

	UPROPERTY()
		float FlameDistance;
	UPROPERTY()
		FVector InitialLocation;
	UPROPERTY()
		float Speed;
	UPROPERTY()
		bool StopMoving;


	UPROPERTY(Category = "Component", EditAnywhere)
		UBoxComponent *BoxCol;
	UPROPERTY(Category = "Component", EditAnywhere)
		UArrowComponent *Arrow;
	UPROPERTY(Category = "Component", VisibleAnywhere)
		UParticleSystemComponent *ParticleSystem;
	UFUNCTION()
		void OnBombBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void CheckingWhoDied(AParentPlayer *DiedPlayer);
	UFUNCTION()
		void AfterDelay();

	class UMyGameInstance *myGameInstance;
	class ABomberManFinalGameModeBase *myGameMode;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:



};

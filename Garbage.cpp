// Fill out your copyright notice in the Description page of Project Settings.


#include "Garbage.h"

// Sets default values
AGarbage::AGarbage()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGarbage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGarbage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGarbage::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/Engine.h"
#include "ParentItem.h"

AParentItem::AParentItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Sphere(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SM_Sphere.Succeeded()) {
		Sphere->SetStaticMesh(SM_Sphere.Object);
	}

	RootComponent = Sphere;

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AParentItem::OnItemBeginOverlap);

	Sphere->SetCollisionProfileName(TEXT("ItemCol"));
}

void AParentItem::OnItemBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	AParentPlayer *ParentPlayer;
	//if (OtherActor->ActorHasTag(TEXT("Player")))

	if (OtherActor->GetClass()->IsChildOf(AParentPlayer::StaticClass())) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Item Eat1"));
		ParentPlayer = Cast<AParentPlayer>(OtherActor);
		if (ParentPlayer) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Item Eat2"));
			Upgrading(ParentPlayer);
			this->Destroy();
		}
	}
}

void AParentItem::Upgrading(AParentPlayer * Player)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Upgrading from ParentItem"));
}

// Called when the game starts or when spawned
void AParentItem::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AParentItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
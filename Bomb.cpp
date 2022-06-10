// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentPlayer.h"
#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "BombEffect.h"
#include "Bomb.h"

// Sets default values
ABomb::ABomb()
{
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spehre"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Sphere(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SM_Sphere.Succeeded()) {
		Sphere->SetStaticMesh(SM_Sphere.Object);
	}


	static ConstructorHelpers::FObjectFinder<UCurveFloat>CV_Curve(TEXT("/Game/BombCurve.BombCurve"));
	if (CV_Curve.Succeeded()) {
		GLog->Log("curve  get succeed");
		fCurve = CV_Curve.Object;
	}


	RootComponent = Sphere;

	InterpFuntion.BindUFunction(this, FName("TimelineFloatReturn"));
	TimelineFinished.BindUFunction(this, FName("OnTimelineFinished"));

	BoomTime = 3;
	ZOffset = 50.0f;

	Sphere->SetCollisionProfileName(TEXT("BombColPreset"));


	OnActorEndOverlap.AddDynamic(this, &ABomb::OnBombEndOverlap);
	
}


// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABomb::Explode()
{
	
	TArray<FVector> VectorArray;
	VectorArray.Add(FVector(1, 0, 0));
	VectorArray.Add(FVector(-1, 0, 0));
	VectorArray.Add(FVector(0, 1, 0));
	VectorArray.Add(FVector(0, -1, 0));

	FVector BombLocation;
	FRotator BombRotation;
	FTransform BombTransform;

	for (int i = 0; i < VectorArray.Num(); i++) {

		BombLocation = GetActorLocation();
		BombRotation = UKismetMathLibrary::MakeRotFromX(VectorArray[i]);

		BombTransform.SetLocation(BombLocation);
		BombTransform.SetRotation(BombRotation.Quaternion());
		BombTransform.SetScale3D(FVector(0.6, 0.6, 0.6));

		//ABombEffect *BombEffect = GetWorld()->SpawnActorDeferred<ABombEffect>(BombEffectBP, BombTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::Undefined);
		ABombEffect *BombEffect = GetWorld()->SpawnActorDeferred<ABombEffect>(ABombEffect::StaticClass(), BombTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::Undefined);
		BombEffect->FlameDistance = FlameDistance;
		UGameplayStatics::FinishSpawningActor(BombEffect, BombTransform);

	}
	
}

void ABomb::TimelineFloatReturn(float value)//이게 타임라인 업데이트에 해당하는거
{
	FVector BombSize = FVector(value, value, value);
	Sphere->SetRelativeScale3D(BombSize);
}

void ABomb::OnTimelineFinished()//이게 타임라인 피니쉬에 해당하는거
{
	
	this->Explode();
	if (IsValid(ParentPlayer)) {
		ParentPlayer->IncreaseBombCount(1);
	}
	this->Destroy();
	
}

void ABomb::OnBombEndOverlap(AActor *OverlappedActor, AActor * OtherActor)
{
	
	if (GetOwner() == OtherActor) {
		Sphere->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	}
	
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	
	ParentPlayer = Cast<AParentPlayer>(GetOwner());
	if (ParentPlayer) {
		ParentPlayer->IncreaseBombCount(-1);

		//Check if curve asset reference is valid
		if (fCurve) {
			GLog->Log("curve");//이거하면 실행할때 밑에 출력로그에 나옴
			//Add the float curve to the timeline and connect it to the interpfunction's delegate
			MyTimeline->AddInterpFloat(fCurve, InterpFuntion);
			//Add our on timeline finished function
			MyTimeline->SetTimelineFinishedFunc(TimelineFinished);


			//setting our timeline;s setting before we start it
			MyTimeline->SetLooping(false);
			MyTimeline->SetIgnoreTimeDilation(true);
			//Start our Timeline
			MyTimeline->Play();
			//플레이 말고 ->Reverse()하면 반대로 돌아가는거 실행하고 실행하면서 업데이트에 해당하는 함수실행
		}
		else
			GLog->Log("curve failed");
	}
	
}


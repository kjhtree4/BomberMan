// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/Engine.h"
#include "ParentPlayer.h"

// Sets default values
AParentPlayer::AParentPlayer()
{
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->AutoReceiveInput = EAutoReceiveInput::Player0;//블프에 이런 디폴트지정은 디스->이름 써주고 정수타입이면 =정수 이렇게지정해주고 블프에서 선택하는거면 enum의 약자인 e앞에 붙여서 저런식으로 찾아보면 나옴

	//DefaultSceneRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PlayerInputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("InputComponent"));

	//RootComponent = DefaultSceneRootComp;
	RootComponent = Cube;
	Cube->AttachTo(DefaultSceneRootComp);
	PointLight->AttachTo(Cube);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_CUBE(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (SM_CUBE.Succeeded()) {
		Cube->SetStaticMesh(SM_CUBE.Object);
	}

	PointLight->Intensity = 7000.0f;
	/*
	static ConstructorHelpers::FClassFinder<ABomb> BP_Bomb(TEXT("/Game/MyBomb.MyBomb_C"));//블루프린트클래스쓰고싶으면 경로에다가 _C붙여줘야됨
	if (BP_Bomb.Succeeded()) {
		GLog->Log("getBombSucceed");
		BombBPClass = BP_Bomb.Class;
	}
	else {
		GLog->Log("getBpombnotSuccedd");
	}
	*/
	

	Cube->SetSimulatePhysics(true);
	Cube->SetLinearDamping(10.0);
	Cube->BodyInstance.bLockXRotation = true;//피직스 컨스트레인트는 전부 잠글때 Cube->BodyInstance.bLockRotation쓰지말고 엑스와이제트 다 따로 지정해주자. 한꺼번에 저런식으로하면 왠지는 모르겠는데 말안들음.
	Cube->BodyInstance.bLockYRotation = true;
	Cube->BodyInstance.bLockZRotation = true;
	Cube->BodyInstance.bLockZTranslation = true;


	Cube->SetCollisionProfileName(TEXT("PlayerColPreset"));

	BombFlameDistance = 200;
	Speed = 7000;
	BombCount = 2;
	
}

// Called when the game starts or when spawned
void AParentPlayer::BeginPlay()
{
	
	Super::BeginPlay();
	
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	//PlayerInputComponent->BindAxis("UpMove1", this, &AParentPlayer::UpMove);
	//PlayerInputComponent->BindAxis("RightMove1", this, &AParentPlayer::RightMove);
	
}

//Called every frame
void AParentPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AParentPlayer::UpMove(float AxisValue)
{

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("UpMove"));

	float XVectorValue;
	XVectorValue = AxisValue * Speed;

	FVector Force = FVector{ XVectorValue,0,0 };

	if (IsValid(this)) {
		Cube->AddForce(Force, NAME_None, true);
	}
	
}

void AParentPlayer::RightMove(float AxisValue)
{

	float YVectorValue;
	YVectorValue = AxisValue * Speed;

	FVector Force = FVector{ 0,YVectorValue,0 };

	if (IsValid(this)) {
		Cube->AddForce(Force, NAME_None, true);
	}
	
}

void AParentPlayer::SpawnBomb()
{

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SpawnBombAction"));
	if (BombCount > 0) {
		if (IsValid(this)) {
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SpawnBombAction2"));

			FTransform BombTransform = FTransform(Cube->GetComponentLocation());
			AActor *BombOwner = this;


			FString forDebug = Cube->GetComponentLocation().ToString();
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *forDebug));//벡터 스트링출력하려면 임의의 변수지정하고 포인터값으로 줘야됨.
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), Cube->GetComponentLocation().X));
			forDebug = Cube->GetComponentLocation().ToString();
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *forDebug));


		//	GetWorld()->SpawnActorDeferred<BombBPClass>(ABomb::StaticClass(), BombTransform, BombOwner, nullptr, ESpawnActorCollisionHandlingMethod::Undefined);

			//ABomb *NewBomb = GetWorld()->SpawnActorDeferred<ABomb>(BombBPClass, BombTransform, BombOwner, nullptr, ESpawnActorCollisionHandlingMethod::Undefined);
			ABomb *NewBomb = GetWorld()->SpawnActorDeferred<ABomb>(ABomb::StaticClass(), BombTransform, BombOwner, nullptr, ESpawnActorCollisionHandlingMethod::Undefined);
			NewBomb->FlameDistance = BombFlameDistance;
			UGameplayStatics::FinishSpawningActor(NewBomb, BombTransform);
		}
	}
	
}

void AParentPlayer::IncreaseBombFlameDistance(int32 IncreaseNum)
{
	BombFlameDistance = IncreaseNum + BombFlameDistance;
}

void AParentPlayer::IncreaseSpeed(int32 IncreaseNum)
{
	Speed = Speed + IncreaseNum;
}

void AParentPlayer::IncreaseBombCount(int32 IncreaseNum)
{
	BombCount = BombCount + IncreaseNum;
}
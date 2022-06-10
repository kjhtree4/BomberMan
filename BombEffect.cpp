// Fill out your copyright notice in the Description page of Project Settings.


//#include "MyGameInstance.h"
#include "BreakableBox.h"
#include "ParentItem.h"
#include "ParentPlayer.h"
#include "Engine/Engine.h"
#include "MyGameInstance.h"
#include "BomberManFinalGameModeBase.h"
#include "BombEffect.h"

// Sets default values
ABombEffect::ABombEffect()
{
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCol"));
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));

	RootComponent = BoxCol;
	Arrow->SetupAttachment(BoxCol);
	ParticleSystem->SetupAttachment(BoxCol);

	BoxCol->SetCollisionProfileName(TEXT("BombColPreset"));
	BoxCol->OnComponentBeginOverlap.AddDynamic(this, &ABombEffect::OnBombBeginOverlap);

	ConstructorHelpers::FObjectFinder<UParticleSystem>BombParticle(TEXT("/Game/BombParticle.BombParticle"));

	if (BombParticle.Succeeded()) {
		ParticleSystem->SetTemplate(BombParticle.Object);
	}

	StopMoving = false;
	Speed = 30.0f;

	//myGameMode = Cast<ABomberManFinalGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
}

void ABombEffect::OnBombBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	//if (OtherActor->ActorHasTag(TEXT("Player")))
	if (OtherActor->GetClass()->IsChildOf(AParentPlayer::StaticClass())) {
	ContactedPlayer= Cast<AParentPlayer>(OtherActor);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("ParentPlayerDestroy"));

		if (ContactedPlayer) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("fffff"));
			CheckingWhoDied(ContactedPlayer);
			ContactedPlayer->Destroy();
		}	
	}
	
		//if (OtherActor->ActorHasTag(TEXT("BreakableBox")))

	else if(OtherActor->GetClass()->IsChildOf(ABreakableBox::StaticClass())){
		ABreakableBox *myBreakableBox = Cast<ABreakableBox>(OtherActor);
		if (myBreakableBox) {
			myBreakableBox->destroy();
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("BreakableBoxDestroy"));
		}
	}
			//if (OtherActor->ActorHasTag(TEXT("Item")))
	else if(OtherActor->GetClass()->IsChildOf(AParentItem::StaticClass())){
		AParentItem *myParentItem = Cast<AParentItem>(OtherActor);
		if (myParentItem) {
			myParentItem->Destroy();
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("ParentItemDestroy"));
		}
	}	
}

void ABombEffect::CheckingWhoDied(AParentPlayer * DiedPlayer)
{
	
	//UMyGameInstance *GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	if(DiedPlayer==nullptr){
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("gggggg"));
	}
	
		if (DiedPlayer->ActorHasTag(TEXT("Player1"))) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Player1Destroy"));
			myGameInstance->WhoWin = FText::FromName(FName(TEXT("Player2 Win")));
			myGameInstance->ShowGameOverWidget();
		}
		else if(DiedPlayer->ActorHasTag(TEXT("Player2"))) {
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Player2Destroy"));
				myGameInstance->WhoWin = FText::FromName(FName(TEXT("Player1 Win")));
				myGameInstance->ShowGameOverWidget();
			
		}
	
		
}

void ABombEffect::AfterDelay()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Particle Destroyed"));
	this->Destroy();
}

// Called when the game starts or when spawned
void ABombEffect::BeginPlay()
{

	Super::BeginPlay();
	
	InitialLocation = GetActorLocation();
	FVector EndLocation = GetActorLocation() + GetActorForwardVector()*FlameDistance;

	TArray<TEnumAsByte<EObjectTypeQuery>> ColObjectType;
	ColObjectType.Add(EObjectTypeQuery::ObjectTypeQuery1);
	ColObjectType.Add(EObjectTypeQuery::ObjectTypeQuery8);
	FCollisionObjectQueryParams ColObjectQueryParams(ColObjectType);

	FCollisionShape BoxColShape = FCollisionShape::MakeBox(FVector(43, 43, 43));
	FCollisionQueryParams ColQueryParams(NAME_None, false, this);

	FHitResult HitResult;

	//for debug
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), FlameDistance));

	myGameInstance= Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	bool bResult = GetWorld()->SweepSingleByObjectType(HitResult, InitialLocation, EndLocation, FQuat::Identity, ColObjectQueryParams, BoxColShape, ColQueryParams);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("1"));

	if (bResult) {
		FString temp = UKismetSystemLibrary::GetDisplayName(HitResult.GetActor());
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("%s"), *temp));//스트링출력하려면 임의의 변수지정하고 포인터값으로 줘야됨.

		float DistanceAddForCol = 50.0;
		FlameDistance = HitResult.Distance+DistanceAddForCol;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("%f"), FlameDistance));
		

	}
	else {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("nothing hit"));
	}
	
}

// Called every frame
void ABombEffect::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("test"));

	if (!StopMoving) {
		FVector DeltaLocation = BoxCol->GetForwardVector()*Speed;
		AddActorWorldOffset(DeltaLocation, false, (FHitResult *)nullptr, ETeleportType::None);

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), ((InitialLocation - GetActorLocation()).Size())));
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%f"), FlameDistance));

		if (((InitialLocation - GetActorLocation()).Size()) >= FlameDistance && !StopMoving) {

			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("BombEffect stop"));

			StopMoving = true;

			FTimerHandle UnusedTimer;
			GetWorldTimerManager().SetTimer(UnusedTimer, this, &ABombEffect::AfterDelay, (float)0.5, false, -1);//타이머함수는 5번째꺼의 인텔리센스를 이용하자
		}
	}
	
}


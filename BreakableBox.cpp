// Fill out your copyright notice in the Description page of Project Settings.

#include "ParentItem.h"
#include "Engine/Engine.h"
#include "BreakableBox.h"

// Sets default values
ABreakableBox::ABreakableBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	//BoxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCol"));
	//RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));

	RootComponent = Cube;
	//Cube->AttachTo(RootComponent)
	//BoxCol->AttachTo(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Cube(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (SM_Cube.Succeeded()) {
		Cube->SetStaticMesh(SM_Cube.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> CubeMaterialAsset(TEXT("/Game/StarterContent/Materials/M_Wood_Oak.M_Wood_Oak"));
	if (CubeMaterialAsset.Succeeded())
	{
		Cube->SetMaterial(0, CubeMaterialAsset.Object);
	}

	//myGameMode = Cast<ABomberManFinalGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	//GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));// 이게 심각한문제 처음에 GameInstance = Cast<UMyGameInstance>(GetGameInstance()); 이렇게해서 크래쉬나고 난리도 아니었음 처음부터 다시했었음.

	Cube->SetCollisionProfileName(TEXT("BreakableBox"));

	//BoxCol->SetRelativeScale3D(FVector(1.75, 1.75, 1.75));
	//BoxCol->SetRelativeLocation(FVector(0,0,50.0));

	WhatToSpawnItem = 0;
	RandomSeed = 0;
	BeforeSeedNum = 0;
}

// Called when the game starts or when spawned
void ABreakableBox::BeginPlay()
{
	Super::BeginPlay();
	myGameMode = Cast<ABomberManFinalGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
}

// Called every frame
void ABreakableBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABreakableBox::destroy() {

	
	TArray<FString> ItemSpawnPercentage;
	RandomSeed = (FMath::Rand() % 100) + 1;//1부터 100까지

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("RandomSeed is"));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, FString::Printf(TEXT("%f"), RandomSeed));

	if(IsValid(GameInstance)){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("GameInstance Valid"));
		ItemSpawnPercentage = GameInstance->GetItemSpawnPercentageFromDataTable();
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("GameInstance Invalid"));
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, FString::Printf(TEXT("%d"), GameInstance->GetItemSpawnPercentageFromDataTable().Num()));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, FString::Printf(TEXT("%d"), ItemSpawnPercentage.Num()));

	Destroy(this);

	
	for (int i = 0; i < ItemSpawnPercentage.Num(); i++) {
		FString ItemSpawnPercentageString = ItemSpawnPercentage[i];
		if (i == 0) {
			BeforeSeedNum = FCString::Atof(*ItemSpawnPercentageString);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("BeforeSeedNum Is"));
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%f"), BeforeSeedNum));

			if (RandomSeed <= BeforeSeedNum) {
				WhatToSpawnItem = i + 1;
				ItemSelect(WhatToSpawnItem);
				break;
			}
		}
		
		else {
			if ((RandomSeed > BeforeSeedNum) && (RandomSeed < FCString::Atof(*ItemSpawnPercentageString))) {
				WhatToSpawnItem = i + 1;
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("BeforeSeedNum Is"));
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%f"), BeforeSeedNum));
				ItemSelect(WhatToSpawnItem);
				break;
			}
			else {
				BeforeSeedNum = FCString::Atof(*ItemSpawnPercentageString);
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("BeforeSeedNum Is"));
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%f"), BeforeSeedNum));
			}
			
		}
	}
	
	//Destroy(this);
}

void ABreakableBox::ItemSelect(int32 ItemNumber) {

	FTransform ItemTranform;
	ItemTranform.SetLocation(GetActorLocation());
	FActorSpawnParameters SpawnInfo;

	AParentItem *ItemToSpawn = GetWorld()->SpawnActor<AParentItem>(GameInstance->GetItemStructure(ItemNumber).ItemClass, ItemTranform, SpawnInfo);

}


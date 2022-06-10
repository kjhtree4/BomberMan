// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BomberManFinal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Texture2D.h"
#include "MapSelectMenu.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMANFINAL_API UMapSelectMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UMyGameInstance *myGameInstance;

	UFUNCTION()
		void SetImage();
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<UTexture2D *> MapImageArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTexture2D *SelectedMap;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 SelectedMapNum;

	UFUNCTION()
		void RightBTN_Func();

	UFUNCTION()
		void LeftBTN_Func();

	UFUNCTION()
		void StartBTN_Func();

	UFUNCTION()
		void BackBTN_Func();

	
private:

	UPROPERTY(Meta = (BindWidget))
		class UButton *RightBTN;

	UPROPERTY(Meta = (BindWidget))
		class UButton *LeftBTN;

	UPROPERTY(Meta = (BindWidget))
		class UButton *BackBTN;

	UPROPERTY(Meta = (BindWidget))
		class UButton *StartBTN;

	UPROPERTY(Meta = (BindWidget))
		class UImage *MapImage;
	
	
};

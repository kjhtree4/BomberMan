// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ParentItem.h"
#include "PowerItem.generated.h"

/**
 *
 */
UCLASS()
class BOMBERMANFINAL_API APowerItem : public AParentItem
{
	GENERATED_BODY()

public:

	virtual void Upgrading(AParentPlayer *Player) override;

private:
	UPROPERTY(EditAnywhere)
		int32 IncreaseNum = 100;
};

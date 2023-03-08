// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class CPP_SHOOTING_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	


public:
	UPROPERTY(EditAnyWhere, meta = (bindWidget))
	class UTextBlock* scoreText;

	UPROPERTY(EditAnyWhere, meta = (bindWidget))
	class UTextBlock* scoreData;
};
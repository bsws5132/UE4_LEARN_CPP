// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CPP_SHOOTING_API AShootingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void AddScore(int32 point);

	UPROPERTY(EditAnyWhere)
	TSubclassOf<class UMainWidget> mainWidget;

protected:
	virtual void BeginPlay() override;
private:
	// ���� ���� ����� ����
	int32 currentScore = 0;

	// ���� ����Ʈ�� �ε�� ���� ����� ����

	class UMainWidget* mainUI;

	void PrintScore();
};

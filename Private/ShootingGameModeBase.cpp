// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.h"

void AShootingGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (mainWidget != nullptr)
	{
		// mainWidget �������Ʈ ������ �޸𸮿� �ε�
		mainUI = CreateWidget<UMainWidget>(GetWorld(), mainWidget);

		if (mainUI != nullptr)
		{
			mainUI->AddToViewport();
		}
	}
}


void AShootingGameModeBase::PrintScore()
{
	if (mainUI != nullptr)
	{
		//ScoreData �ؽ�Ʈ ��Ͽ� ���� ���� �� �Է�
		mainUI->scoreData->SetText(FText::AsNumber(currentScore));
	}
}

//���� ���� ����ϴ� �Լ�
void AShootingGameModeBase::AddScore(int32 point)
{
	// �Ű����� point�� ���� �Ѱܹ��� ������ ���� ������ ����
	currentScore += point;

	PrintScore();
}

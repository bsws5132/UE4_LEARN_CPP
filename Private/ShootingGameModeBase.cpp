// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.h"

void AShootingGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (mainWidget != nullptr)
	{
		// mainWidget 블루프린트 파일을 메모리에 로드
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
		//ScoreData 텍스트 블록에 현재 점수 값 입력
		mainUI->scoreData->SetText(FText::AsNumber(currentScore));
	}
}

//현재 점수 계산하는 함수
void AShootingGameModeBase::AddScore(int32 point)
{
	// 매개변수 point를 통해 넘겨받은 점수를 현재 점수에 누적
	currentScore += point;

	PrintScore();
}

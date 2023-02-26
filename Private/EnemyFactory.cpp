// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFactory.h"
#include "Enemy.h"
// Sets default values
AEnemyFactory::AEnemyFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyFactory::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (currentTime > delayTime)
	{
		currentTime = 0;

		//enemy 변수에 할당한 블루프린트 자신의 위치에 소환

		AEnemy* spawnActor = GetWorld()->SpawnActor<AEnemy>(enemy, GetActorLocation(), GetActorRotation());
	}
	else
	{
		currentTime += DeltaTime;
	}
}


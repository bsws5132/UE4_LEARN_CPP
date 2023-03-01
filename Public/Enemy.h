// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class CPP_SHOOTING_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;






public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	//박스 충돌체 컴포넌트
	UPROPERTY(EditAnyWhere)
		class UBoxComponent* boxComp;

	// 스태틱 메시 컴포넌트
	UPROPERTY(EditAnyWhere)
		class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnyWhere)
		int traceRate = 50;

	UPROPERTY(EditAnyWhere)
		float moveSpeed = 800;

	UFUNCTION()
		void OnEnemyOverlap
		(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);
private:
	FVector dir;
};

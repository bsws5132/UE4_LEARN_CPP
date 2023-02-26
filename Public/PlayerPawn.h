// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class CPP_SHOOTING_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//박스 충돌체 컴포넌트
	UPROPERTY(EditAnyWhere)
	class UBoxComponent* boxComp;

	// 스태틱 메시 컴포넌트
	UPROPERTY(EditAnyWhere)
	class UStaticMeshComponent* meshComp;

	// 속력 변수
	UPROPERTY(EditAnyWhere)
	float moveSpeed = 500;

	//총구 위치
	UPROPERTY(EditAnyWhere)
	class UArrowComponent* firePosition;

	// 총알 블루프린트
	UPROPERTY(EditAnyWhere)
	TSubclassOf<class ABullet> bulletFactory;

	// 총알 발사 효과음 파일
	UPROPERTY(EditAnyWhere)
	class USoundBase* fireSound;




private:
	float h;
	float v;

	// 사용자 입력 처리 함수
	void MoveHorizontal(float value);
	void MoveVertical(float value);

	void Fire();
};

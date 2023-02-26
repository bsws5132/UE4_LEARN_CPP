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

	//�ڽ� �浹ü ������Ʈ
	UPROPERTY(EditAnyWhere)
	class UBoxComponent* boxComp;

	// ����ƽ �޽� ������Ʈ
	UPROPERTY(EditAnyWhere)
	class UStaticMeshComponent* meshComp;

	// �ӷ� ����
	UPROPERTY(EditAnyWhere)
	float moveSpeed = 500;

	//�ѱ� ��ġ
	UPROPERTY(EditAnyWhere)
	class UArrowComponent* firePosition;

	// �Ѿ� �������Ʈ
	UPROPERTY(EditAnyWhere)
	TSubclassOf<class ABullet> bulletFactory;

	// �Ѿ� �߻� ȿ���� ����
	UPROPERTY(EditAnyWhere)
	class USoundBase* fireSound;




private:
	float h;
	float v;

	// ����� �Է� ó�� �Լ�
	void MoveHorizontal(float value);
	void MoveVertical(float value);

	void Fire();
};

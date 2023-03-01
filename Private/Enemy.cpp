// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerPawn.h"
#include "EngineUtils.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;


	//�ڽ� �ݶ��̴� ������Ʈ ����
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	
	// ������ �ڽ� �ݶ��̴� ������Ʈ�� �ֻ�� ������Ʈ�� ����
	SetRootComponent(boxComp);

	boxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));


	// ����ƽ �Ž� ������Ʈ ����
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Static Mesh"));

	// �ڽ� �ݶ��̴� ������Ʈ�� �ڽ� ������Ʈ�� ����
	meshComp->SetupAttachment(boxComp); 
	
	// �ݸ��� �������� Enemy ���������� ����
	boxComp->SetCollisionProfileName(TEXT("Enemy"));
	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	//1 ~ 100 ������ ������ ���� �� ��÷!

	int32 drawResult = FMath::RandRange(1, 100);


	//Ȯ���� ��÷�Ǿ�����
	if (drawResult <= traceRate)
	{
		for (TActorIterator<APlayerPawn> player(GetWorld()); player; ++player) //���� ������ APlayerPawn Ŭ������ �� ���� ��� �˻�.
		{
			if (player->GetName().Contains(TEXT("BP_PlayerPawn"))) // ���� �˻��� �����߿� "BP_PlayerPawn"�̶� ���� ���Խ�
			{
				dir = player->GetActorLocation() - GetActorLocation();
				dir.Normalize();
			}
		}
	}
	//Ȯ�� ��÷�� �ȵǾ�����
	else
	{
		dir = GetActorForwardVector(); // ���� ���� ���ؼ� �׳� �����θ� ������.
	}
	
	
	
	//BeginOverlap ��������Ʈ�� OnEnemyOverlap �Լ� ����
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnEnemyOverlap);


}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//BeginPlay���� ������ �������� �̵�.


	FVector newLocation = GetActorLocation() + dir * moveSpeed * DeltaTime;
	SetActorLocation(newLocation);
}

void AEnemy::OnEnemyOverlap
(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	APlayerPawn* player = Cast<APlayerPawn>(OtherActor);

	if (player != nullptr)
	{
		OtherActor->Destroy();
	}

	Destroy();
}
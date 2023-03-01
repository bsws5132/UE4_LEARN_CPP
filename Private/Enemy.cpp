// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerPawn.h"
#include "EngineUtils.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;


	//박스 콜라이더 컴포넌트 생성
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	
	// 생성한 박스 콜라이더 컴포넌트를 최상단 컴포넌트에 설정
	SetRootComponent(boxComp);

	boxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));


	// 스태틱 매쉬 컴포넌트 생성
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Static Mesh"));

	// 박스 콜라이더 컴포넌트의 자식 컴포넌트로 설정
	meshComp->SetupAttachment(boxComp); 
	
	// 콜리전 프리셋을 Enemy 프리셋으로 변경
	boxComp->SetCollisionProfileName(TEXT("Enemy"));
	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	//1 ~ 100 사이의 임의의 정수 값 추첨!

	int32 drawResult = FMath::RandRange(1, 100);


	//확률에 당첨되었을때
	if (drawResult <= traceRate)
	{
		for (TActorIterator<APlayerPawn> player(GetWorld()); player; ++player) //월드 공간에 APlayerPawn 클래스로 된 액터 모두 검색.
		{
			if (player->GetName().Contains(TEXT("BP_PlayerPawn"))) // 만약 검색된 액터중에 "BP_PlayerPawn"이란 문구 포함시
			{
				dir = player->GetActorLocation() - GetActorLocation();
				dir.Normalize();
			}
		}
	}
	//확률 당첨이 안되었을때
	else
	{
		dir = GetActorForwardVector(); // 정면 벡터 구해서 그냥 앞으로만 전진함.
	}
	
	
	
	//BeginOverlap 델리게이트에 OnEnemyOverlap 함수 연결
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnEnemyOverlap);


}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//BeginPlay에서 결정된 방향으로 이동.


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
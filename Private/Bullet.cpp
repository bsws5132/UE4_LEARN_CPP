// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "ShootingGameModeBase.h"
// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxcomp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	SetRootComponent(boxcomp);
	boxcomp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	boxcomp->SetWorldScale3D(FVector(0.75f, 0.25f, 1.0f));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	meshComp->SetupAttachment(boxcomp);

	boxcomp->SetCollisionProfileName(TEXT("Bullet"));
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	// 박스컴포넌트의 충돌 오버랩 이벤트에 OnBulletOverlap 연결
	boxcomp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletOverlap);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// 전방으로 이동될 위치 계산 
	FVector newLocation = GetActorLocation() + GetActorForwardVector() * moveSpeed * DeltaTime;

	// 계산된 위치좌표 갱신
	SetActorLocation(newLocation);
}


void ABullet::OnBulletOverlap
(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	// 충돌 감지 디버그 코드
	FString OtherActorName = OtherActor->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Collided with %s"), *OtherActorName);



	AEnemy* enemy = Cast<AEnemy>(OtherActor);

	if (enemy != nullptr)
	{
		// 충돌한 액터를 제거한다
		OtherActor->Destroy();
		

		// 폭발 이펙트 생성
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFX, GetActorLocation(), GetActorRotation());

		// 현재 게임 모드를 가져온다
		AGameModeBase* currentMode = GetWorld()->GetAuthGameMode();

		// AShootingGameModeBase 클래스로 변환
		AShootingGameModeBase* currentGameModeBase = Cast<AShootingGameModeBase>(currentMode);

		// 만일, 게임 모드 베이스를 가져오면?
		if (currentGameModeBase != nullptr)
		{
			// 게임 모드 베이스의 점수를 1점 추가한다.
			currentGameModeBase->AddScore(1);
		}
	}
	// 자기자신 제거
	Destroy();
}

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
	// �ڽ�������Ʈ�� �浹 ������ �̺�Ʈ�� OnBulletOverlap ����
	boxcomp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletOverlap);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// �������� �̵��� ��ġ ��� 
	FVector newLocation = GetActorLocation() + GetActorForwardVector() * moveSpeed * DeltaTime;

	// ���� ��ġ��ǥ ����
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
	// �浹 ���� ����� �ڵ�
	FString OtherActorName = OtherActor->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Collided with %s"), *OtherActorName);



	AEnemy* enemy = Cast<AEnemy>(OtherActor);

	if (enemy != nullptr)
	{
		// �浹�� ���͸� �����Ѵ�
		OtherActor->Destroy();
		

		// ���� ����Ʈ ����
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFX, GetActorLocation(), GetActorRotation());

		// ���� ���� ��带 �����´�
		AGameModeBase* currentMode = GetWorld()->GetAuthGameMode();

		// AShootingGameModeBase Ŭ������ ��ȯ
		AShootingGameModeBase* currentGameModeBase = Cast<AShootingGameModeBase>(currentMode);

		// ����, ���� ��� ���̽��� ��������?
		if (currentGameModeBase != nullptr)
		{
			// ���� ��� ���̽��� ������ 1�� �߰��Ѵ�.
			currentGameModeBase->AddScore(1);
		}
	}
	// �ڱ��ڽ� ����
	Destroy();
}

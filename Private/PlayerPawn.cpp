// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Bullet.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//�ڽ� �ݶ��̴� ������Ʈ ����
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));

	// ������ �ڽ� �ݶ��̴� ������Ʈ�� �ֻ�� ������Ʈ�� ����
	SetRootComponent(boxComp);

	// ����ƽ �Ž� ������Ʈ ����
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Static Mesh"));

	// �ڽ� �ݶ��̴� ������Ʈ�� �ڽ� ������Ʈ�� ����
	meshComp->SetupAttachment(boxComp);

	FVector boxSize = FVector(50.0f, 50.0f, 50.0f);
	boxComp->SetBoxExtent(boxSize);

	//�ѱ� ǥ�� ������Ʈ ���� �� �ڽ� ������Ʈ�� �ڽ� ������Ʈ�� ����.
	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Fire Position"));
	firePosition->SetupAttachment(boxComp);

	// ������ �̺�Ʈ ON!
	boxComp->SetGenerateOverlapEvents(true);

	//�浹 ������ Query And Physics�� ����
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	//Object Type�� 1�� ä��(Player)�� ����
	boxComp->SetCollisionObjectType(ECC_EngineTraceChannel1);

	boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//������� �Է�Ű�� �̿�,
	// 1. ���� �Է� ���� �¿� �Է� ���� �̿��� ���� ���͸� ����� (������ ����, ���� ���� ���� �� + ���� ���� ���� ��_
	FVector dir = FVector(0, h, v);

	// 2. ���� ������ ���̰� 1�� �ǵ��� ����ȭ
	dir.Normalize();


	// 3. �̵��� ��ġ ��ǥ�� ���Ѵ�( �̵��� ��ġ(p) = ���� ��ġ(p0) + ��ü�� �ӵ�����*��� �ð�(vt) )
	FVector newLocation = GetActorLocation() + dir * moveSpeed * DeltaTime;

	// 4.  ���� ������ ��ġ ��ǥ�� �տ��� ���� �� ��ǥ�� ����

	SetActorLocation(newLocation);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Axis ���ε� ��, �� ����Ű�� �Է����� ���� ���� �Լ��� �����մϴ�.


	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerPawn::MoveHorizontal);
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerPawn::MoveVertical);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerPawn::Fire);
}


void APlayerPawn::MoveHorizontal(float value)
{
	h = value;
}


void APlayerPawn::MoveVertical(float value)
{
	v = value;
}

// ���콺 ���� ��ư �Է� �Լ� ó��

void APlayerPawn::Fire()
{
	ABullet* bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition-> 
		GetComponentLocation(), firePosition->GetComponentRotation());


	UGameplayStatics::PlaySound2D(GetWorld(), fireSound);
}
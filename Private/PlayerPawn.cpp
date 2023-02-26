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

	//박스 콜라이더 컴포넌트 생성
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));

	// 생성한 박스 콜라이더 컴포넌트를 최상단 컴포넌트에 설정
	SetRootComponent(boxComp);

	// 스태틱 매쉬 컴포넌트 생성
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Static Mesh"));

	// 박스 콜라이더 컴포넌트의 자식 컴포넌트로 설정
	meshComp->SetupAttachment(boxComp);

	FVector boxSize = FVector(50.0f, 50.0f, 50.0f);
	boxComp->SetBoxExtent(boxSize);

	//총구 표시 컴포넌트 생성 및 박스 컴포넌트의 자식 컴포넌트로 설정.
	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Fire Position"));
	firePosition->SetupAttachment(boxComp);

	// 오버랩 이벤트 ON!
	boxComp->SetGenerateOverlapEvents(true);

	//충돌 응답을 Query And Physics로 설정
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	//Object Type를 1번 채널(Player)로 설정
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

	//사용자의 입력키를 이용,
	// 1. 상하 입력 값과 좌우 입력 값을 이용해 방향 벡터를 만든다 (벡터의 덧셈, 수직 방향 벡터 값 + 수평 방향 벡터 값_
	FVector dir = FVector(0, h, v);

	// 2. 방향 벡터의 길이가 1이 되도록 정규화
	dir.Normalize();


	// 3. 이동할 위치 좌표를 구한다( 이동할 위치(p) = 현재 위치(p0) + 물체의 속도벡터*경과 시간(vt) )
	FVector newLocation = GetActorLocation() + dir * moveSpeed * DeltaTime;

	// 4.  현재 액터의 위치 좌표를 앞에서 구한 새 좌표로 갱신

	SetActorLocation(newLocation);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Axis 바인딩 값, 즉 방향키를 입력했을 때의 값을 함수에 연결합니다.


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

// 마우스 왼쪽 버튼 입력 함수 처리

void APlayerPawn::Fire()
{
	ABullet* bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition-> 
		GetComponentLocation(), firePosition->GetComponentRotation());


	UGameplayStatics::PlaySound2D(GetWorld(), fireSound);
}
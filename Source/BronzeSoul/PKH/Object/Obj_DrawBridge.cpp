// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Object/Obj_DrawBridge.h"

#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "PKH/Player/BSPlayerCharacter.h"
#include "PKH/UI/InteractWidget.h"

// Sets default values
AObj_DrawBridge::AObj_DrawBridge()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoxComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	DetectComp = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectComp"));
	DetectComp->SetupAttachment(RootComponent);
	DetectComp->SetRelativeLocation(FVector(0, 0, 0));
	DetectComp->OnComponentBeginOverlap.AddDynamic(this, &AObj_DrawBridge::OnDetectPlayer);
	DetectComp->OnComponentEndOverlap.AddDynamic(this, &AObj_DrawBridge::OnLostPlayer);

	UIComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("UIComp"));
	UIComp->SetupAttachment(RootComponent);
	UIComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UIComp->SetWidgetSpace(EWidgetSpace::Screen);
	UIComp->SetDrawSize(FVector2D(200, 120));
	static ConstructorHelpers::FClassFinder<UInteractWidget> UIClassRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/PKH/UI/WBP_Interact.WBP_Interact'"));
	if(UIClassRef.Class)
	{
		UIComp->SetWidgetClass(UIClassRef.Class);
	}
}

// Called when the game starts or when spawned
void AObj_DrawBridge::BeginPlay()
{
	Super::BeginPlay();

	InteractUI = CastChecked<UInteractWidget>(UIComp->GetWidget());
	UIComp->InitWidget();
	InteractUI->UpdateText(TEXT("도개교 내리기"));
	InteractUI->SetVisibility(ESlateVisibility::Hidden);
}

void AObj_DrawBridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if( false == IsDrawing )
	{
		return;
	}

	FRotator TargetRotation = CurState == EBridgeState::Up ? DownRotation : UpRotation;
	MeshComp->SetRelativeRotation(FMath::RInterpConstantTo(MeshComp->GetRelativeRotation(), TargetRotation, DeltaTime, DrawSpeed));
	// 각도 차이가 임계값보다 작아지면 타겟 회전값으로 수정하고 종료 
	if ( FQuat(MeshComp->GetRelativeRotation()).AngularDistance(FQuat(TargetRotation)) < Threshold_DrawRotation )
	{
		MeshComp->SetRelativeRotation(TargetRotation);
		DrawComplete();
	}
}

void AObj_DrawBridge::OnDetectPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
									 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABSPlayerCharacter* Player = Cast<ABSPlayerCharacter>(OtherActor);
	if(nullptr == Player)
	{
		return;
	}

	Player->SetInteractionObj(this);
	IsNearPlayer = true;
	if(false == IsDrawing)
	{
		InteractUI->SetVisibility(ESlateVisibility::Visible);
	}
}

void AObj_DrawBridge::OnLostPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ABSPlayerCharacter* Player = Cast<ABSPlayerCharacter>(OtherActor);
	if(nullptr == Player)
	{
		return;
	}

	Player->SetInteractionObj(nullptr);
	IsNearPlayer = false;
	if (false == IsDrawing)
	{
		InteractUI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AObj_DrawBridge::DrawComplete()
{
	IsDrawing = false;
	// 아직 플레이어가 근처에 있다면 UI 활성화
	if(IsNearPlayer)
	{
		InteractUI->SetVisibility(ESlateVisibility::Visible);
	}

	if(CurState == EBridgeState::Up)
	{
		CurState = EBridgeState::Down;
		InteractUI->UpdateText(TEXT("도개교 올리기"));
	}
	else if( CurState == EBridgeState::Down )
	{
		CurState = EBridgeState::Up;
		InteractUI->UpdateText(TEXT("도개교 내리기"));
	}
}

// Interact override
void AObj_DrawBridge::Interact()
{
	if(IsDrawing)
	{
		return;
	}

	IsDrawing = true;
	// 작동 중에는 UI 감추기
	InteractUI->SetVisibility(ESlateVisibility::Hidden);
}

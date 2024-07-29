
#include "PKH/Player/BSPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PKH/Animation/PaladinAnimInstance.h"
#include "PKH/Component/EquipComponent.h"
#include "PKH/Enemy/EnemyBase.h"

// Sets default values
ABSPlayerCharacter::ABSPlayerCharacter()
{
	// TeamID
	TeamID = FGenericTeamId(1);

	// Tick Disable
	PrimaryActorTick.bCanEverTick = false;

	// Components
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/PKH/Character/Paladin/Mesh/Paladin_J_Nordstrom.Paladin_J_Nordstrom'"));
	if(MeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	}

	CapsuleComp = GetCapsuleComponent();

	MoveComp = GetCharacterMovement();
	MoveComp->bOrientRotationToMovement = true;
	MoveComp->bUseControllerDesiredRotation = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bDoCollisionTest = true;
	SpringArmComp->TargetArmLength = 350.0f;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

	EquipComp = CreateDefaultSubobject<UEquipComponent>(TEXT("EquipComp"));

	WeaponComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponComp"));
	WeaponComp->SetupAttachment(GetMesh(), TEXT("Socket_RightHand"));
	WeaponComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponComp->SetCollisionProfileName(TEXT("Weapon"));
	WeaponComp->OnComponentBeginOverlap.AddDynamic(this, &ABSPlayerCharacter::OnWeaponBeginOverlap);

	// Rotation
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;

	// Animation
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(TEXT("/Game/PKH/Character/Paladin_RootAdded/Blueprint/ABP_Paladin.ABP_Paladin_C"));
	if(AnimInstanceRef.Class)
	{
		GetMesh()->SetAnimClass(AnimInstanceRef.Class);
	}

	// Input
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/PKH/Input/IMC_BSDefault.IMC_BSDefault'"));
	if (InputMappingContextRef.Object)
	{
		InputMappingContext = InputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_MoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_BSMove.IA_BSMove'"));
	if (IA_MoveRef.Object)
	{
		IA_Move = IA_MoveRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_LookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_BSLook.IA_BSLook'"));
	if (IA_LookRef.Object)
	{
		IA_Look = IA_LookRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_DodgeRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_BSDodge.IA_BSDodge'"));
	if ( IA_DodgeRef.Object)
	{
		IA_Dodge = IA_DodgeRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_AttackRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_BSAttack.IA_BSAttack'"));
	if (IA_AttackRef.Object)
	{
		IA_Attack = IA_AttackRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_GuardRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_BSGuard.IA_BSGuard'"));
	if (IA_GuardRef.Object)
	{
		IA_Guard = IA_GuardRef.Object;
	}
}

void ABSPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = CastChecked<UPaladinAnimInstance>(GetMesh()->GetAnimInstance());

	// Mapping
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void ABSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputCompoennt = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputCompoennt->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ABSPlayerCharacter::Move);
	EnhancedInputCompoennt->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ABSPlayerCharacter::Look);

	EnhancedInputCompoennt->BindAction(IA_Attack, ETriggerEvent::Started, this, &ABSPlayerCharacter::Attack);
	EnhancedInputCompoennt->BindAction(IA_Guard, ETriggerEvent::Started, this, &ABSPlayerCharacter::Guard);
	EnhancedInputCompoennt->BindAction(IA_Dodge, ETriggerEvent::Started, this, &ABSPlayerCharacter::Dodge);
}

#pragma region Input
void ABSPlayerCharacter::Move(const FInputActionValue& InputAction)
{
	const FVector2D InputVec = InputAction.Get<FVector2D>();
	DirVec.X = InputVec.X;
	DirVec.Y = InputVec.Y;

	if ( false == CanMove() )
	{
		return;
	}

	const FRotator Rotator = GetController()->GetControlRotation();
	const FRotator YawRotator = FRotator(0, Rotator.Yaw, 0);

	const FVector ForwardVec = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
	const FVector RightVec = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardVec, InputVec.X);
	AddMovementInput(RightVec, InputVec.Y);
}

void ABSPlayerCharacter::Look(const FInputActionValue& InputAction)
{
	const FVector2D InputVec = InputAction.Get<FVector2D>();

	AddControllerPitchInput(InputVec.Y);
	AddControllerYawInput(InputVec.X);
}

void ABSPlayerCharacter::Attack(const FInputActionValue& InputAction)
{
	if (false == CanAttack())
	{
		return;
	}

	EquipComp->Attack();
}

void ABSPlayerCharacter::Guard(const FInputActionValue& InputAction)
{
	EquipComp->Guard();
}

void ABSPlayerCharacter::Dodge(const FInputActionValue& InputAction)
{
	CancelAttack();
	SetState(EPlayerState::Dodging); 

	// Rotate before rolling
	const FRotator Rotator = GetController()->GetControlRotation();
	const FRotator YawRotator = FRotator(0, Rotator.Yaw, 0);
	const FVector ForwardVec = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);

	float TargetDeg = 0;
	if ( DirVec.X == 1 && DirVec.Y == 0 ) TargetDeg = 0;
	else if ( DirVec.X == 0 && DirVec.Y == 1 ) TargetDeg = 90;
	else if ( DirVec.X == -1 && DirVec.Y == 0 ) TargetDeg = 180;
	else if ( DirVec.X == 0 && DirVec.Y == -1 ) TargetDeg = 270;
	
	const FRotator TargetRotation = ForwardVec.RotateAngleAxis(TargetDeg, FVector::UpVector).ToOrientationRotator();
	SetActorRotation(TargetRotation);

	AnimInstance->PlayMontage_Dodge();
}


#pragma endregion

#pragma region PlayerState
bool ABSPlayerCharacter::CanMove()
{
	return (CurState == EPlayerState::Idle || CurState == EPlayerState::Guard);
}

bool ABSPlayerCharacter::CanAttack()
{
	return (CurState == EPlayerState::Idle || CurState == EPlayerState::Attack || CurState == EPlayerState::Guard);
}

void ABSPlayerCharacter::SetState(EPlayerState NewState)
{
	CurState = NewState;
}
#pragma endregion

#pragma region Hp
void ABSPlayerCharacter::StaggerOff()
{
	SetState(EPlayerState::Idle);
}

void ABSPlayerCharacter::SetHp(int32 NewHp)
{
	CurHp = FMath::Clamp(NewHp, 0, MaxHp);
	if(OnHpChanged.IsBound())
	{
		OnHpChanged.Broadcast(CurHp, MaxHp);
	}

	if(CurHp == 0)
	{
		OnDie();
	}
}

void ABSPlayerCharacter::OnDamaged(int32 InDamage, float StaggerTime)
{
	SetState(EPlayerState::Damaged);
	SetHp(CurHp - InDamage);

	// Reset Timer if already timer in active
	if (GetWorldTimerManager().IsTimerActive(StaggerHandle))
	{
		GetWorldTimerManager().ClearTimer(StaggerHandle);
	}
	GetWorldTimerManager().SetTimer(StaggerHandle, this, &ABSPlayerCharacter::StaggerOff, StaggerTime, false);
}

void ABSPlayerCharacter::OnDie()
{
	SetState(EPlayerState::Die);
}

int32 ABSPlayerCharacter::GetCurHp() const
{
	return CurHp;
}
#pragma endregion

#pragma region Stamina
void ABSPlayerCharacter::SetStamina(int32 NewStamina)
{
	CurStamina = FMath::Clamp(NewStamina, 0, MaxStamina);
	if(OnStaminaChanged.IsBound())
	{
		OnStaminaChanged.Broadcast(CurStamina, MaxStamina);
	}
}

int32 ABSPlayerCharacter::GetCurStamina() const
{
	return CurStamina;
}
#pragma endregion

#pragma region Attack
void ABSPlayerCharacter::OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
											  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
	if(nullptr == Enemy)
	{
		return;
	}

	//Enemy->OnDamaged();
}

void ABSPlayerCharacter::CancelAttack()
{
	if(CurState != EPlayerState::Attack)
	{
		return;
	}

	SetState(EPlayerState::Idle);
	EquipComp->ResetCombo();
}

void ABSPlayerCharacter::SetWeaponCollision(bool IsAttacking)
{
	if(IsAttacking)
	{
		WeaponComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); 
	}
	else
	{
		WeaponComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

int32 ABSPlayerCharacter::GetPlayerAtk() const
{
	return PlayerAtk;
}
#pragma endregion

#pragma region Dodge
void ABSPlayerCharacter::DodgeEnd()
{
	SetState(EPlayerState::Idle);
}
#pragma endregion

#pragma region TeamID
FGenericTeamId ABSPlayerCharacter::GetGenericTeamId() const
{
	return TeamID;
}

void ABSPlayerCharacter::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	TeamID = NewTeamID;
}
#pragma endregion
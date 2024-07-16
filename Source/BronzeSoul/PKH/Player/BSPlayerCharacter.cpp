
#include "PKH/Player/BSPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PKH/Component/EquipComponent.h"

// Sets default values
ABSPlayerCharacter::ABSPlayerCharacter()
{
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

	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;

	// Animation
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(TEXT("/Game/PKH/Character/Paladin/Blueprint/ABP_Paladin.ABP_Paladin_C"));
	if(AnimInstanceRef.Class)
	{
		GetMesh()->SetAnimClass(AnimInstanceRef.Class);
		AnimInstance = GetMesh()->GetAnimInstance();
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
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_JumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_BSJump.IA_BSJump'"));
	if (IA_JumpRef.Object)
	{
		IA_Jump = IA_JumpRef.Object;
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
	EnhancedInputCompoennt->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputCompoennt->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

	EnhancedInputCompoennt->BindAction(IA_Attack, ETriggerEvent::Started, this, &ABSPlayerCharacter::Attack);
	EnhancedInputCompoennt->BindAction(IA_Guard, ETriggerEvent::Started, this, &ABSPlayerCharacter::Guard);
}

#pragma region Input
void ABSPlayerCharacter::Move(const FInputActionValue& InputAction)
{
	const FVector2D InputVec = InputAction.Get<FVector2D>();

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
	EquipComp->Attack();
}

void ABSPlayerCharacter::Guard(const FInputActionValue& InputAction)
{
	EquipComp->Guard();
}
#pragma endregion

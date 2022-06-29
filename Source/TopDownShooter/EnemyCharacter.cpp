// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"
#include "TopDownShooterGameModeBase.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GunSocket"));
	Gun->SetOwner(this);

	Health = MaxHealth;



}

bool AEnemyCharacter::isDead() const
{
	return Health <= 0;
}

float AEnemyCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

float AEnemyCharacter::GetHealth() const
{
	return Health;
}


void AEnemyCharacter::SetHealth(float AddedHealth)
{
	Health = AddedHealth;
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AEnemyCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AEnemyCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AEnemyCharacter::LookRight);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AEnemyCharacter::Shoot);

}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageApplied = FMath::Min(Health, DamageApplied);
	Health -= DamageApplied;



	if (isDead()) {

		ATopDownShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ATopDownShooterGameModeBase>();
		if (GameMode != nullptr) GameMode->PawnKilled(this);

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	return DamageApplied;
}

void AEnemyCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AEnemyCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AEnemyCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(LookSpeed * AxisValue * GetWorld()->GetDeltaSeconds());
}

void AEnemyCharacter::Shoot()
{
	Gun->ShootGun();
}


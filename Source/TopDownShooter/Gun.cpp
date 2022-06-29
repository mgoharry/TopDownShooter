// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void AGun::ShootGun()
{

	UGameplayStatics::SpawnSoundAttached(ShotSound, Mesh, TEXT("MuzzleSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	FHitResult Hit;
	FVector ShotDir;
	bool Trace = GunTrace(Hit, ShotDir);

	if (Trace) {

		//DrawDebugPoint(GetWorld(), Hit.Location, 10.f, FColor::Blue, false, 1); 
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFlash, Hit.Location, Hit.GetActor()->GetActorRotation(), true);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, Hit.Location);
		AActor* HitActor = Hit.GetActor();

		if (HitActor != nullptr) {
			FPointDamageEvent DamageEvent(DamagePoints, Hit, ShotDir, nullptr);
			HitActor->TakeDamage(DamagePoints, DamageEvent, OwnerController, this);
			
		}
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleSocket"));

}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDir)
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return false;

	ShotDir = -GetActorRotation().Vector();

	FVector End = OwnerPawn->GetActorLocation() + OwnerPawn->GetActorRotation().Vector() * BulletRange;

	FCollisionQueryParams ShootParams;
	ShootParams.AddIgnoredActor(this);
	//ShootParams.AddIgnoredActor(OwnerPawn);

	return GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation() + GetActorRotation().Vector() * 10.f, End, ECollisionChannel::ECC_GameTraceChannel1, ShootParams);
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class TOPDOWNSHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void ShootGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
		UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere)
		UParticleSystem* HitFlash;
	UPROPERTY(EditAnywhere)
		float BulletRange = 1000.f;
	UPROPERTY(EditAnywhere)
		float DamagePoints = 25.f;
	UPROPERTY(EditAnywhere)
		USoundBase* ShotSound;
	UPROPERTY(EditAnywhere)
		USoundBase* HitSound;

	bool GunTrace(FHitResult& Hit, FVector& ShotDir);
};

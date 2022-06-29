#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class AGun;

UCLASS()
class TOPDOWNSHOOTER_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintPure)
		bool isDead() const;
	UFUNCTION(BlueprintPure)
		float GetHealth() const;
	UFUNCTION(BlueprintPure)
		float GetHealthPercent() const;
	UFUNCTION(BlueprintCallable)
		void SetHealth(float AddedHealth);



	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookRight(float AxisValue);


	UPROPERTY(EditAnywhere, Category = "Player Controls")
		float LookSpeed = 50.f;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AGun> GunClass;
	UPROPERTY()
		AGun* Gun;
	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 100.f;
	UPROPERTY(EditAnywhere)
		float Health = 100.f;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> EnemyHealthBar;

public:
	void Shoot();

};

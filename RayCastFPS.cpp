// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Range = 1000.0f;
	ImpulseAmount = 100000.0f;
	


}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*Gun = GetWorld()->SpawnActor<AGun>(GunClassReference);

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weaponSocket"));
	Gun->SetOwner(this);*/


	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForwardBackward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShooterCharacter::LookUpDown);

	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveLeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AShooterCharacter::LookRightLeft);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed,this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed,this,&AShooterCharacter::Fire);

}

void AShooterCharacter::MoveForwardBackward(float axisvalue)
{
	/*If axis value 1 then forward vector become +ve so forward
	If axis value is -1 then forward vector becomes -ve so backward*/

	AddMovementInput(GetActorForwardVector() * axisvalue);
}

void AShooterCharacter::MoveLeftRight(float axisvalue)
{
	/*If axis value 1 then right vector become +ve so right
	If axis value is -1 then right vector becomes -ve so left*/

	AddMovementInput(GetActorRightVector() * axisvalue);
}

void AShooterCharacter::LookUpDown(float axisvalue)
{
	AddControllerPitchInput(axisvalue);
}

void AShooterCharacter::LookRightLeft(float axisvalue)
{
	AddControllerYawInput(axisvalue);
	
}

void AShooterCharacter::Fire()
{

	/*Attach muzzleflash particle effect to Muzzle_01 socket of Gun
	GetMesh() is to get the parent of the gun mesh i.e wraith character mesh which has gun by default*/
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GetMesh(), TEXT("Muzzle_01"));


	/*Get the starting location and rotation of the Line trace which is the Muzzle_)1 socket location
	in the gun attached to wraith mesh*/

	FVector Start = GetMesh()->GetSocketLocation(TEXT("Muzzle_01"));

	/*The rotation is important to make the line trace to go at proper direction at all rotation*/
	FRotator StartRotation = GetMesh()->GetSocketRotation(TEXT("Muzzle_01"));
	

	/*The end location of line trace is start  added with the rotation Vector() gives forward vector in any 
	rotation multiplied by range(100.0f)*/
	FVector End = Start + ( StartRotation.Vector()* Range);


	//Debug line
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.0f, 0, 1.0f);


	FHitResult HitResult;

	FCollisionQueryParams params;

	params.AddIgnoredActor(this->GetOwner());


	bool DidHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, params);

	if (DidHit)
	{
		UStaticMeshComponent* HitMesh = Cast<UStaticMeshComponent>(HitResult.GetActor()->GetRootComponent());

		if (HitMesh && HitResult.GetActor()->IsRootComponentMovable())
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactEffect,HitResult.Location);

			HitMesh->AddImpulse(FVector(1, 0, 0) * ImpulseAmount);

			
		}
	}


}


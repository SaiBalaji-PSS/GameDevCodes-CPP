// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPositionComponent.h"

// Sets default values for this component's properties
UWorldPositionComponent::UWorldPositionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPositionComponent::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp,Warning,TEXT("Hello World"));

	/*Get the owner of the component (AActor*) and Get its Location and Rotation and 
	print it as s FString using ToString() method*/

	FString ObjectName = GetOwner()->GetName();

	FVector ObjectLocation = GetOwner()->GetActorLocation();
	FRotator ObjectRotation = GetOwner()->GetActorRotation();
	

	UE_LOG(LogTemp, Warning, TEXT("%s"), *ObjectName);

	UE_LOG(LogTemp, Warning, TEXT("Actor Location is %s"), *ObjectLocation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Actor Rotation is %s"), *ObjectRotation.ToString());



	
}


// Called every frame
void UWorldPositionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


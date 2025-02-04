// Copyright 2020-2021 CesiumGS, Inc. and Contributors

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class ECOMAP_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();
	UPROPERTY(BlueprintReadWrite, Category = "Solar Data")
	float GHI;

	UPROPERTY(BlueprintReadWrite, Category = "Solar Data")
	float DNI;

	UPROPERTY(BlueprintReadWrite, Category = "Solar Data")
	float DHI;

	// Function to parse JSON and update variables
	UFUNCTION(BlueprintCallable, Category = "Solar Data")
	void UpdateSolarDataFromJson(const FString& JsonString);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

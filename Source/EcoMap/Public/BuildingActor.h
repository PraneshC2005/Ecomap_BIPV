// Copyright 2020-2021 CesiumGS, Inc. and Contributors

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingActor.generated.h"


USTRUCT(BlueprintType)
struct FBuildingSurfaceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Height; // Height of the building

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Area; // Area of the surface (in square meters)

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TiltAngle; // Tilt angle of the surface

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float OrientationAngle; // Orientation angle of the surface

    FBuildingSurfaceData()
        : Height(0), Area(0), TiltAngle(0), OrientationAngle(0) {
    }
};

UCLASS()
class ECOMAP_API ABuildingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Building Data")
    FBuildingSurfaceData GetBuildingSurfaceData() const { return SurfaceData; }

private:
    // Surface data for the building (height, area, etc.)
    FBuildingSurfaceData SurfaceData;


};

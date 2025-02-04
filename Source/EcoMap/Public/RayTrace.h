#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RayTrace.generated.h"

UCLASS()
class ECOMAP_API ARayTrace : public AActor
{
    GENERATED_BODY()

public:
    ARayTrace();

    /** Function to calculate unshaded area */
    UFUNCTION(BlueprintCallable, Category = "Solar Calculation")
    float CalculateUnshadedArea(float PanelWidth, float PanelLength, const FVector& PanelLocation, const FRotator& PanelOrientation, const FVector& SunPosition, int32 GridRows = 5, int32 GridColumns = 5);

private:
    /** Helper function for line trace */
    bool PerformLineTrace(const FVector& Start, const FVector& End, bool& bHitCesium);
};

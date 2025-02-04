#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BIPVEstimation.generated.h"

/** Enum for panel types */
UENUM(BlueprintType)
enum class EPanelType : uint8
{
    Monocrystalline UMETA(DisplayName = "Monocrystalline"),
    Polycrystalline UMETA(DisplayName = "Polycrystalline"),
    ThinFilm UMETA(DisplayName = "Thin Film")
};

/** Actor class for BIPV Estimation */
UCLASS()
class ECOMAP_API ABIPVEstimation : public AActor
{
    GENERATED_BODY()

public:
    ABIPVEstimation();

    /** Function to estimate hourly BIPV energy output */
    UFUNCTION(BlueprintCallable, Category = "BIPV")
    float EstimateHourlyBIPV(float UnshadedArea, float GHI, float DHI, EPanelType PanelType);
};

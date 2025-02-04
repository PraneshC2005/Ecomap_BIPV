#include "BIPVEstimation.h"

ABIPVEstimation::ABIPVEstimation()
{
    PrimaryActorTick.bCanEverTick = false;
}

float ABIPVEstimation::EstimateHourlyBIPV(float UnshadedArea, float GHI, float DHI, EPanelType PanelType)
{
    if (UnshadedArea <= 0 || GHI <= 0)
    {
        //UE_LOG(LogTemp, Warning, TEXT("Invalid inputs: Unshaded Area or GHI cannot be zero or negative."));
        return 0.0f;
    }

    // Define panel efficiency based on the panel type
    float PanelEfficiency = 0.0f;
    switch (PanelType)
    {
    case EPanelType::Monocrystalline:
        PanelEfficiency = 0.20f; // 20% efficiency
        break;
    case EPanelType::Polycrystalline:
        PanelEfficiency = 0.16f; // 16% efficiency
        break;
    case EPanelType::ThinFilm:
        PanelEfficiency = 0.12f; // 12% efficiency
        break;
    default:
        //UE_LOG(LogTemp, Warning, TEXT("Invalid panel type."));
        return 0.0f;
    }

    // Time factor for converting W to kWh
    const float TimeFactor = 1.0f / 1000.0f; // 1 hour, 1000 to convert W to kW

    // Estimate hourly BIPV energy output (kWh)
    float HourlyEnergy = UnshadedArea * GHI * PanelEfficiency * TimeFactor;

    // Log the results
    //UE_LOG(LogTemp, Log, TEXT("BIPV Estimation - Unshaded Area: %f m², GHI: %f W/m², Efficiency: %f, Hourly Energy: %f kWh"),
        //UnshadedArea, GHI, PanelEfficiency, HourlyEnergy);

    return HourlyEnergy;
}

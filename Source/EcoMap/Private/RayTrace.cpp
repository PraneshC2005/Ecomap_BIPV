#include "RayTrace.h"
#include "DrawDebugHelpers.h"

ARayTrace::ARayTrace()
{
    PrimaryActorTick.bCanEverTick = false;
}

float ARayTrace::CalculateUnshadedArea(float PanelWidth, float PanelLength, const FVector& PanelLocation, const FRotator& PanelOrientation, const FVector& SunPosition, int32 GridRows, int32 GridColumns)
{
    if (GridRows <= 0 || GridColumns <= 0 || PanelWidth <= 0 || PanelLength <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid input dimensions or grid resolution."));
        return 0.0f;
    }

    int32 HitsCount = 0;      // Number of rays hitting the panel
    int32 BlockedCount = 0;   // Number of rays blocked by Cesium3DTileset
    int32 TotalRays = GridRows * GridColumns;

    // Calculate panel's directional vectors
    FVector RightVector = FRotationMatrix(PanelOrientation).GetUnitAxis(EAxis::Y); // Local right
    FVector ForwardVector = FRotationMatrix(PanelOrientation).GetUnitAxis(EAxis::X); // Local forward

    // Loop through grid points
    for (int32 Row = 0; Row < GridRows; ++Row)
    {
        for (int32 Col = 0; Col < GridColumns; ++Col)
        {
            // Calculate grid point position
            float XOffset = (Col + 0.5f) * (PanelWidth / GridColumns) - (PanelWidth / 2);
            float YOffset = (Row + 0.5f) * (PanelLength / GridRows) - (PanelLength / 2);
            FVector GridPoint = PanelLocation + (ForwardVector * XOffset) + (RightVector * YOffset);

            bool bHitCesium = false;

            // Perform line trace
            bool bHitPanel = PerformLineTrace(SunPosition, GridPoint, bHitCesium);

            // Count hits or blocked rays
            if (bHitPanel)
            {
                HitsCount++;
            }
            else if (bHitCesium)
            {
                BlockedCount++;
            }

            // Draw a persistent debug line for every ray in the grid
            FColor LineColor = bHitPanel ? FColor::Red : (bHitCesium ? FColor::Blue : FColor::Green);
            DrawDebugLine(GetWorld(), SunPosition, GridPoint, LineColor, false, 2.0f, 0, 1.0f);

        }
    }

    // Calculate unshaded area
    float PanelArea = PanelWidth * PanelLength;
    float UnshadedArea = (HitsCount / static_cast<float>(TotalRays)) * PanelArea;

    // Log the results
    UE_LOG(LogTemp, Log, TEXT("Total Rays: %d, Hits: %d, Blocked: %d, Unshaded Area: %f"), TotalRays, HitsCount, BlockedCount, UnshadedArea);

    return UnshadedArea;
}

bool ARayTrace::PerformLineTrace(const FVector& Start, const FVector& End, bool& bHitCesium)
{
    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.bTraceComplex = true;
    Params.AddIgnoredActor(this); // Ignore self

    // Perform the line trace
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

    // Check if the ray hits the Cesium3DTileset
    if (bHit && HitResult.GetActor() && HitResult.GetActor()->GetName().Contains(TEXT("Cesium3DTileset")))
    {
        bHitCesium = true;
        return false;
    }

    // Check if the ray hits the panel
    if (bHit && HitResult.GetActor() && HitResult.GetActor()->GetName().Contains(TEXT("BP_BIPVPanel")))
    {
        return true;
    }

    return false;
}

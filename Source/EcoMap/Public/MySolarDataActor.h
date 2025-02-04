#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySolarDataActor.generated.h"

USTRUCT(BlueprintType)
struct FSolarData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Solar Data")
    float GHI;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Solar Data")
    float DHI;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Solar Data")
    FString Time;
};

UCLASS()
class ECOMAP_API AMySolarDataActor : public AActor
{
    GENERATED_BODY()

public:
    AMySolarDataActor();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Solar Data")
    TArray<FSolarData> SolarDataArray;

    UFUNCTION(BlueprintCallable, Category = "Solar Data")
    bool ParseJsonResponse(const FString& JsonResponse, TArray<FSolarData>& OutSolarDataArray);
};

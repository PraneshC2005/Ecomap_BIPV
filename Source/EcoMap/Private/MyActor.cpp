// Copyright 2020-2021 CesiumGS, Inc. and Contributors


#include "MyActor.h"
#include "Json.h" // Include JSON utilities
#include "Misc/OutputDeviceDebug.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::UpdateSolarDataFromJson(const FString& JsonString)
{
    TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
    TSharedPtr<FJsonObject> JsonObject;

    if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
    {
        if (JsonObject->HasField(TEXT("estimated_actuals")))
        {
            const TArray<TSharedPtr<FJsonValue>>& EstimatedActuals = JsonObject->GetArrayField(TEXT("estimated_actuals"));
            if (EstimatedActuals.Num() > 0)
            {
                TSharedPtr<FJsonObject> FirstItem = EstimatedActuals[0]->AsObject();
                if (FirstItem.IsValid())
                {
                    // Update GHI, DNI, DHI values
                    GHI = FirstItem->GetNumberField(TEXT("ghi"));
                    DNI = FirstItem->GetNumberField(TEXT("dni"));
                    DHI = FirstItem->GetNumberField(TEXT("dhi"));
                }
            }
        }
    }
}






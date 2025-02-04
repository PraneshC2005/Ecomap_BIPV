#include "MySolarDataActor.h"
#include "Json.h"
#include "JsonUtilities.h"

AMySolarDataActor::AMySolarDataActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

bool AMySolarDataActor::ParseJsonResponse(const FString& JsonResponse, TArray<FSolarData>& OutSolarDataArray)
{
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonResponse);

    if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
    {
        const TArray<TSharedPtr<FJsonValue>>* EstimatedActualsArray;
        if (JsonObject->TryGetArrayField(TEXT("estimated_actuals"), EstimatedActualsArray))
        {
            OutSolarDataArray.Empty(); 

            for (const TSharedPtr<FJsonValue>& Value : *EstimatedActualsArray)
            {
                if (Value->Type == EJson::Object)
                {
                    TSharedPtr<FJsonObject> DataObject = Value->AsObject();
                    if (DataObject.IsValid())
                    {
                        FSolarData SolarData;
                        SolarData.GHI = DataObject->GetNumberField(TEXT("ghi"));
                        SolarData.DHI = DataObject->GetNumberField(TEXT("dni"));
                        SolarData.Time = DataObject->GetStringField(TEXT("period_end"));

                        OutSolarDataArray.Add(SolarData);
                    }
                }
            }
            return true; 
        }
        else
        {
            //UE_LOG(LogTemp, Error, TEXT("Failed to find 'estimated_actuals' array in JSON response."));
            return false;
        }
    }
    else
    {
        //UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON response."));
        return false;
    }
}




// Project Untitled Game by JDNLY. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PUPlayerEquipmentWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class THIRDPERSONEXAMPLE_API UPUPlayerEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	int32 GetNumberOfPotions() const;
protected:
	UPROPERTY(meta = (BindWidget))
	UImage* HealPotionImage;

	UPROPERTY(meta = (BindWidget))
	UImage* CurrentWeaponImage;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PotionsAmount;

	virtual void NativeOnInitialized() override;

};

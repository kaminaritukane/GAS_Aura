// Copyright Sky Balcony


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidetController == nullptr)
	{
		AttributeMenuWidetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidetControllerClass);
		AttributeMenuWidetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidetController->BindCallbacksToDependencies();
	}
	return AttributeMenuWidetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitalized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitalized, please fill out BP_AuraHUD"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* OWController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(OWController);

	OWController->BroadcastInitialValues();

	Widget->AddToViewport();
}

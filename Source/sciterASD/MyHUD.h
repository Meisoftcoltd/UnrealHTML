#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Texture2D.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include <sciter-x.h>
#include <sciter-x-host-callback.h>
#include <sciter-x-request.hpp>
#include <sciter-x-dom.hpp>
#include <sciter-x-behavior.h>
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class SCITERASD_API AMyHUD : public AHUD
{
	GENERATED_BODY()
public:

	AMyHUD();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	void ProcessEvents();
	void Render();
	virtual void DrawHUD() override;
	virtual void Destroyed() override;
	virtual void Tick(float DeltaSeconds) override;
	
	FVector2D	GetViewportSize();

	UFUNCTION(BlueprintCallable)
	void MouseClick(FKey key, float x, float y);

	UFUNCTION(BlueprintCallable)
	void MouseDown(FKey as);

	UFUNCTION(BlueprintCallable)
	void MouseUp(FKey as);

	float MouseX = 0;
	float MouseY = 0;

	static MOUSE_BUTTONS mbutton;

	static  UINT SC_CALLBACK SciterCallback(LPSCITER_CALLBACK_NOTIFICATION pns, LPVOID callbackParam);
	static UINT DoLoadData(LPSCN_LOAD_DATA pnmld);
	static   UINT DoAttachBehavior(LPSCN_ATTACH_BEHAVIOR lpab);

	UPROPERTY()
	UTexture2D* Texture;
	
	bool bInitialized = false;
};

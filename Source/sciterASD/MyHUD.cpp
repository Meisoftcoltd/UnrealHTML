// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

#define SciterInstanceId ((void *)1)
/*
UE_LOG(LogTemp, Warning, TEXT("Some warning message") );
*/
AMyHUD::AMyHUD() 
{

}


void AMyHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();


    /*InputComponent->BindAction*/

}

FVector2D GetGameResolution()
{
    FVector2D Result = FVector2D(1, 1);

    Result.X = GSystemResolution.ResX;
    Result.Y = GSystemResolution.ResY;

    return Result;
}

void AMyHUD::BeginPlay()
{


    auto playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    playerController->bShowMouseCursor = true;

    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Trying to initialize Sciter"));

    SciterSetOption(NULL, SCITER_SET_SCRIPT_RUNTIME_FEATURES,
        ALLOW_FILE_IO |
        ALLOW_SOCKET_IO |
        ALLOW_EVAL |
        ALLOW_SYSINFO);

    SciterSetOption(NULL, SCITER_SET_DEBUG_MODE, true);

    bool ok;

    ok = SciterProcX(SciterInstanceId, SCITER_X_MSG_CREATE(GFX_LAYER_SKIA, FALSE));

    if (ok)
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Sciter Engine Initialized"));

    FVector2D viewportSize;

    SciterSetCallback(SciterInstanceId, SciterCallback, NULL);
    
    

    SciterProcX(SciterInstanceId, SCITER_X_MSG_RESOLUTION(UINT(100)));

    ok = SciterProcX(SciterInstanceId, SCITER_X_MSG_SIZE(GetViewportSize().X, GetViewportSize().Y));
    if (!ok)
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Couldn't set size"));


    ok = SciterLoadFile(SciterInstanceId, L"fullpath to the file location");

    if (ok)
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("File loaded!"));


    OleInitialize(NULL); // for shell interaction: drag-n-drop, etc.

    Texture = UTexture2D::CreateTransient(GetViewportSize().X, GetViewportSize().Y, PF_B8G8R8A8);

    bInitialized = true;

    SciterProcX(SciterInstanceId, SCITER_X_MSG_FOCUS(true));
}

MOUSE_BUTTONS AMyHUD::mbutton = MOUSE_BUTTONS(0);

void AMyHUD::ProcessEvents()
{

    APlayerController* pc = GetOwningPlayerController();
    pc->GetMousePosition(MouseX, MouseY);

    MOUSE_EVENTS  me = MOUSE_MOVE;
    POINT pos = { int(MouseX),int(MouseY) };

    auto ok = SciterProcX(SciterInstanceId, SCITER_X_MSG_MOUSE(me, mbutton, KEYBOARD_STATES(0), pos));


    //io.MouseDown[0] = pc->IsInputKeyDown(EKeys::LeftMouseButton);
    //io.MouseDown[1] = pc->IsInputKeyDown(EKeys::RightMouseButton);
    //io.MouseDown[2] = pc->IsInputKeyDown(EKeys::MiddleMouseButton);

}

void AMyHUD::Render()
{
    if (!bInitialized)
        return;

    if (Texture == NULL) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Texture not Initialized"));
        return;
    }

    auto on_bitmap = [](LPCBYTE rgba, INT x, INT y, UINT width, UINT height, LPVOID param)
    {
        auto* self = reinterpret_cast<AMyHUD*>(param);

        void* TextureData = self->Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
        FMemory::Memcpy(TextureData, rgba, width * height * 4);

        self->Texture->PlatformData->Mips[0].BulkData.Unlock();
#define UpdateResource UpdateResource
        self->Texture->UpdateResource();


    };

    SCITER_X_MSG_PAINT paint;
    paint.targetType = SPT_RECEIVER;
    paint.target.receiver.param = this;
    paint.target.receiver.callback = on_bitmap;

    auto ok = SciterProcX(SciterInstanceId, paint);

    if (!ok)
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Couldn't render"));

    DrawTexture(Cast<UTexture>(Texture), 1, 1, GetViewportSize().X, GetViewportSize().Y, 0, 0, 1, 1);
}


void AMyHUD::DrawHUD()
{
    SciterProcX(SciterInstanceId, SCITER_X_MSG_HEARTBIT(GetTickCount()));

    ProcessEvents();

    Render();
}


void AMyHUD::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

  /* bool ok =  SciterProcX(SciterInstanceId, SCITER_X_MSG_HEARTBIT(GetTickCount()));

   if(!ok)
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Can't tick"));*/
}

void AMyHUD::Destroyed()
{
	Super::Destroyed();
    SciterProcX(SciterInstanceId, SCITER_X_MSG_DESTROY());

}

FVector2D AMyHUD::GetViewportSize() {
        FVector2D Result = FVector2D(1, 1);

        if (GEngine && GEngine->GameViewport)
        {
            GEngine->GameViewport->GetViewportSize( /*out*/Result);
        }

        return Result;
}

void AMyHUD::MouseClick(FKey key,float x, float y)
{
  /*  bool ok;

    ok = SciterProcX(SciterInstanceId, SCITER_X_MSG_FOCUS(true));

    if (!ok) {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Didn't set focus"));
    }

    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Mouse Clicked"));

    POINT pos = { MouseX, MouseY };
    ok = SciterProcX(SciterInstanceId, SCITER_X_MSG_MOUSE(MOUSE_EVENTS(MOUSE_DOWN), MOUSE_BUTTONS(MAIN_MOUSE_BUTTON), KEYBOARD_STATES(0), pos));

    if (!ok) {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Event didn't work"));
    }*/
}

void AMyHUD::MouseDown(FKey as)
{
    UINT ks = 0;
    mbutton = MAIN_MOUSE_BUTTON;
    MOUSE_EVENTS  me = MOUSE_DOWN;
    POINT pos = { int(MouseX),int(MouseY) };
    SciterProcX(SciterInstanceId, SCITER_X_MSG_MOUSE(me, mbutton, KEYBOARD_STATES(ks), pos));
}

void AMyHUD::MouseUp(FKey as)
{
    UINT ks = 0;
    mbutton = MAIN_MOUSE_BUTTON;
    MOUSE_EVENTS  me = MOUSE_UP;
    POINT pos = { int(MouseX),int(MouseY) };
    SciterProcX(SciterInstanceId, SCITER_X_MSG_MOUSE(me, mbutton, KEYBOARD_STATES(ks), pos));
}

UINT SC_CALLBACK AMyHUD::SciterCallback(LPSCITER_CALLBACK_NOTIFICATION pns, LPVOID callbackParam)
{
    switch (pns->code)
    {
    case SC_LOAD_DATA:          return DoLoadData((LPSCN_LOAD_DATA)pns);
    case SC_ATTACH_BEHAVIOR:    return DoAttachBehavior((LPSCN_ATTACH_BEHAVIOR)pns);
    }
    return 0;
}

UINT AMyHUD::DoLoadData(LPSCN_LOAD_DATA pnmld)
{
    LPCBYTE pb = 0; UINT cb = 0;
    aux::wchars wu = aux::chars_of(pnmld->uri);
    if (wu.like(WSTR("res:*")))
    {
        // then by calling possibly overloaded load_resource_data method
        if (sciter::load_resource_data(GetModuleHandle(NULL), wu.start + 4, pb, cb))
            ::SciterDataReady(pnmld->hwnd, pnmld->uri, pb, cb);
    }
    else if (wu.like(WSTR("this://app/*"))) {
        // try to get them from archive (if any, you need to call sciter::archive::open() first)
        aux::bytes adata = sciter::archive::instance().get(wu.start + 11);
        if (adata.length)
            ::SciterDataReady(pnmld->hwnd, pnmld->uri, adata.start, adata.length);
    }
    return LOAD_OK;
}

UINT AMyHUD::DoAttachBehavior(LPSCN_ATTACH_BEHAVIOR lpab)
{
    sciter::event_handler* pb = sciter::behavior_factory::create(lpab->behaviorName, lpab->element);
    if (pb)
    {
        lpab->elementTag = pb;
        lpab->elementProc = sciter::event_handler::element_proc;
        return TRUE;
    }
    return FALSE;
}


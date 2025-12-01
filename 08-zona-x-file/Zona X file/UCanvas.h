/////////////////////////////////////////////////////////////////////////////
// Unreal Engine MiniSDK Generator by uNrEaL
// Game: APB Reloaded
// File: UCanvas.h
// Date: 06/16/2011 @ 03:01:54.288
/////////////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER
#pragma pack( push, 4 )
#endif

struct UCanvas_execDrawTextureDoubleLine_Parms
{
	struct FVector StartPoint;
	struct FVector EndPoint;
	float Perc;
	float Spacing;
	float Width;
	struct FColor LineColor;
	struct FColor AltLineColor;
	class UTexture2D* Tex;
	float U;
	float V;
	float UL;
	float VL;
};// FUNC_Final FUNC_Native

struct UCanvas_execDrawTextureLine_Parms
{
	struct FVector StartPoint;
	struct FVector EndPoint;
	float Perc;
	float Width;
	struct FColor LineColor;
	class UTexture2D* LineTexture;
	float U;
	float V;
	float UL;
	float VL;
};// FUNC_Final FUNC_Native

struct UCanvas_execDraw2DLine_Parms
{
	float X1;
	float Y1;
	float X2;
	float Y2;
	struct FColor LineColor;
};// FUNC_Final FUNC_Native

struct UCanvas_execDrawRotatedMaterialTile_Parms
{
	class UMaterialInterface* Mat;
	struct FRotator Rotation;
	float XL;
	float YL;
	float U;
	float V;
	float UL;
	float VL;
	float AnchorX;
	float AnchorY;
};// FUNC_Final FUNC_Native

struct UCanvas_execDrawRotatedTile_Parms
{
	class UTexture2D* Tex;
	struct FRotator Rotation;
	float XL;
	float YL;
	float U;
	float V;
	float UL;
	float VL;
	float AnchorX;
	float AnchorY;
};// FUNC_Final FUNC_Native

struct UCanvas_execSetDrawColor_Parms
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char A;
};// FUNC_Final FUNC_Native

struct UCanvas_execDrawBox_Parms
{
	float Width;
	float Height;
};// FUNC_Final

struct UCanvas_execDrawRect_Parms
{
	float RectX;
	float RectY;
	class UTexture2D* Tex;
};// FUNC_Final

struct UCanvas_execDrawIconSection_Parms
{
	struct FCanvasIcon Icon;
	float X;
	float Y;
	float UStartPct;
	float VStartPct;
	float UEndPct;
	float VEndPct;
	float Scale;
};// FUNC_Final

struct UCanvas_execDrawIcon_Parms
{
	struct FCanvasIcon Icon;
	float X;
	float Y;
	float Scale;
};// FUNC_Final

struct UCanvas_execMakeIcon_Parms
{
	class UTexture2D* Texture;
	float U;
	float V;
	float UL;
	float VL;
	struct FCanvasIcon ReturnValue; // CPF_ReturnParm
};// FUNC_Final

struct UCanvas_execDrawTexture_Parms
{
	class UTexture2D* Tex;
	float Scale;
};// FUNC_Final

struct UCanvas_execSetClip_Parms
{
	float X;
	float Y;
};// FUNC_Final

struct UCanvas_execSetOrigin_Parms
{
	float X;
	float Y;
};// FUNC_Final

struct UCanvas_execSetPos_Parms
{
	float PosX;
	float PosY;
};// FUNC_Final FUNC_Native

struct UCanvas_eventReset_Parms
{
	unsigned long bKeepOrigin : 1;
};// FUNC_Event

struct UCanvas_execDrawColorizedTile_Parms
{
	class UTexture2D* Tex;
	float XL;
	float YL;
	float U;
	float V;
	float UL;
	float VL;
	struct FLinearColor LColor;
};// FUNC_Final FUNC_Native

struct UCanvas_execDrawTileStretched_Parms
{
	class UTexture2D* Tex;
	float Left;
	float Top;
	float AWidth;
	float AHeight;
	float U;
	float V;
	float UL;
	float VL;
	struct FLinearColor LDrawColor;
	unsigned long bStretchHorizontally : 1;
	unsigned long bStretchVertically : 1;
	float ScalingFactor;
};// FUNC_Final FUNC_Native

struct UCanvas_execPopTransform_Parms
{
};// FUNC_Final FUNC_Native

struct UCanvas_execPushTranslationMatrix_Parms
{
	struct FVector TranslationVector;
};// FUNC_Final FUNC_Native

struct UCanvas_execProject_Parms
{
	struct FVector Location;
	struct FVector ReturnValue; // CPF_ReturnParm
};// FUNC_Final FUNC_Native

struct UCanvas_execDrawTileClipped_Parms
{
	class UTexture2D* Tex;
	float XL;
	float YL;
	float U;
	float V;
	float UL;
	float VL;
};// FUNC_Final FUNC_Native NativeIndex[0x01D4]

struct UCanvas_execDrawTextRA_Parms
{
	struct FString Text;
	unsigned long CR : 1;
};// FUNC_Final

struct UCanvas_execDrawTextClipped_Parms
{
	struct FString Text;
	unsigned long bCheckHotKey : 1;
	float XScale;
	float YScale;
};// FUNC_Final FUNC_Native

struct UCanvas_execDrawText_Parms
{
	struct FString Text;
	unsigned long CR : 1;
	float XScale;
	float YScale;
};// FUNC_Final FUNC_Native

struct UCanvas_execTextSize_Parms
{
	struct FString String;
	float XL; // CPF_OutParm
	float YL; // CPF_OutParm
};// FUNC_Final FUNC_Native

struct UCanvas_execStrLen_Parms
{
	struct FString String;
	float XL; // CPF_OutParm
	float YL; // CPF_OutParm
};// FUNC_Final FUNC_Native

struct UCanvas_execDrawMaterialTileClipped_Parms
{
	class UMaterialInterface* Mat;
	float XL;
	float YL;
	float U;
	float V;
	float UL;
	float VL;
};// FUNC_Final FUNC_Native

struct UCanvas_execDrawMaterialTile_Parms
{
	class UMaterialInterface* Mat;
	float XL;
	float YL;
	float U;
	float V;
	float UL;
	float VL;
};// FUNC_Final FUNC_Native

struct UCanvas_execDrawQuad_Parms
{
	class UTexture2D* Tex;
	float XL;
	float YL;
	float U1;
	float v1;
	float U2;
	float v2;
	float U3;
	float V3;
	float U4;
	float V4;
};// FUNC_Final FUNC_Native

struct UCanvas_execDrawLine2D_Parms
{
	float XL;
	float YL;
};// FUNC_Final FUNC_Native

struct UCanvas_execDrawTile_Parms
{
	class UTexture2D* Tex;
	float XL;
	float YL;
	float U;
	float V;
	float UL;
	float VL;
};// FUNC_Final FUNC_Native

// (0x40 - 0x94)
class UCanvas : public UObject
{
public:
	class UFont*                                       Font;                                        // 0x0040 (0x0004)
	float                                              OrgX;                                        // 0x0044 (0x0004)
	float                                              OrgY;                                        // 0x0048 (0x0004)
	float                                              ClipX;                                       // 0x004C (0x0004)
	float                                              ClipY;                                       // 0x0050 (0x0004)
	float                                              CurX;                                        // 0x0054 (0x0004)
	float                                              CurY;                                        // 0x0058 (0x0004)
	float                                              CurYL;                                       // 0x005C (0x0004)
	struct FColor                                      DrawColor;                                   // 0x0060 (0x0004)
	unsigned long                                      bCenter : 1;                                 // 0x0064 (0x0004) [0x00000001]
	unsigned long                                      bNoSmooth : 1;                               // 0x0064 (0x0004) [0x00000002]
	int                                                SizeX;                                       // 0x0068 (0x0004)
	int                                                SizeY;                                       // 0x006C (0x0004)
	struct FPointer                                    Canvas;                                      // 0x0070 (0x0004)
	struct FPointer                                    SceneView;                                   // 0x0074 (0x0004)
	unsigned char                                      unknown_data05[ 8 ];                         // 0x0078 (0x0008)
	struct FPlane                                      ColorModulate;                               // 0x0080 (0x0010)
	class UTexture2D*                                  DefaultTexture;                              // 0x0090 (0x0004)

private:
	static UClass* ClassPointer;

public:
	static UClass* StaticClass ()
	{
		if ( !ClassPointer )
			ClassPointer = UObject::FindClass( "Class Engine.Canvas" );

		return ClassPointer;
	};

public:
	void DrawTextureDoubleLine ( struct FVector StartPoint, struct FVector EndPoint, float Perc, float Spacing, float Width, struct FColor LineColor, struct FColor AltLineColor, class UTexture2D* Tex, float U, float V, float UL, float VL )
	{
		static UFunction* pfnDrawTextureDoubleLine = NULL;

		if ( !pfnDrawTextureDoubleLine )
			pfnDrawTextureDoubleLine = UObject::FindObject< UFunction >( "Function Engine.Canvas.DrawTextureDoubleLine" );

		UCanvas_execDrawTextureDoubleLine_Parms DrawTextureDoubleLine_Parms;
		memcpy( &DrawTextureDoubleLine_Parms.StartPoint, &StartPoint, 0xC );
		memcpy( &DrawTextureDoubleLine_Parms.EndPoint, &EndPoint, 0xC );
		DrawTextureDoubleLine_Parms.Perc = Perc;
		DrawTextureDoubleLine_Parms.Spacing = Spacing;
		DrawTextureDoubleLine_Parms.Width = Width;
		memcpy( &DrawTextureDoubleLine_Parms.LineColor, &LineColor, 0x4 );
		memcpy( &DrawTextureDoubleLine_Parms.AltLineColor, &AltLineColor, 0x4 );
		DrawTextureDoubleLine_Parms.Tex = Tex;
		DrawTextureDoubleLine_Parms.U = U;
		DrawTextureDoubleLine_Parms.V = V;
		DrawTextureDoubleLine_Parms.UL = UL;
		DrawTextureDoubleLine_Parms.VL = VL;

		pfnDrawTextureDoubleLine->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnDrawTextureDoubleLine, &DrawTextureDoubleLine_Parms, NULL );
		pfnDrawTextureDoubleLine->FunctionFlags |= 0x400;
	};

	void DrawTextureLine ( struct FVector StartPoint, struct FVector EndPoint, float Perc, float Width, struct FColor LineColor, class UTexture2D* LineTexture, float U, float V, float UL, float VL )
	{
		static UFunction* pfnDrawTextureLine = NULL;

		if ( !pfnDrawTextureLine )
			pfnDrawTextureLine = UObject::FindObject< UFunction >( "Function Engine.Canvas.DrawTextureLine" );

		UCanvas_execDrawTextureLine_Parms DrawTextureLine_Parms;
		memcpy( &DrawTextureLine_Parms.StartPoint, &StartPoint, 0xC );
		memcpy( &DrawTextureLine_Parms.EndPoint, &EndPoint, 0xC );
		DrawTextureLine_Parms.Perc = Perc;
		DrawTextureLine_Parms.Width = Width;
		memcpy( &DrawTextureLine_Parms.LineColor, &LineColor, 0x4 );
		DrawTextureLine_Parms.LineTexture = LineTexture;
		DrawTextureLine_Parms.U = U;
		DrawTextureLine_Parms.V = V;
		DrawTextureLine_Parms.UL = UL;
		DrawTextureLine_Parms.VL = VL;

		pfnDrawTextureLine->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnDrawTextureLine, &DrawTextureLine_Parms, NULL );
		pfnDrawTextureLine->FunctionFlags |= 0x400;
	};

	void Draw2DLine ( float X1, float Y1, float X2, float Y2, struct FColor LineColor )
	{
		static UFunction* pfnDraw2DLine = NULL;

		if ( !pfnDraw2DLine )
			pfnDraw2DLine = UObject::FindObject< UFunction >( "Function Engine.Canvas.Draw2DLine" );

		UCanvas_execDraw2DLine_Parms Draw2DLine_Parms;
		Draw2DLine_Parms.X1 = X1;
		Draw2DLine_Parms.Y1 = Y1;
		Draw2DLine_Parms.X2 = X2;
		Draw2DLine_Parms.Y2 = Y2;
		memcpy( &Draw2DLine_Parms.LineColor, &LineColor, 0x4 );

		pfnDraw2DLine->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnDraw2DLine, &Draw2DLine_Parms, NULL );
		pfnDraw2DLine->FunctionFlags |= 0x400;
	};

	void DrawRotatedMaterialTile ( class UMaterialInterface* Mat, struct FRotator Rotation, float XL, float YL, float U/*CPF_OptionalParm*/, float V/*CPF_OptionalParm*/, float UL/*CPF_OptionalParm*/, float VL/*CPF_OptionalParm*/, float AnchorX/*CPF_OptionalParm*/, float AnchorY/*CPF_OptionalParm*/ )
	{
		static UFunction* pfnDrawRotatedMaterialTile = NULL;

		if ( !pfnDrawRotatedMaterialTile )
			pfnDrawRotatedMaterialTile = UObject::FindObject< UFunction >( "Function Engine.Canvas.DrawRotatedMaterialTile" );

		UCanvas_execDrawRotatedMaterialTile_Parms DrawRotatedMaterialTile_Parms;
		DrawRotatedMaterialTile_Parms.Mat = Mat;
		memcpy( &DrawRotatedMaterialTile_Parms.Rotation, &Rotation, 0xC );
		DrawRotatedMaterialTile_Parms.XL = XL;
		DrawRotatedMaterialTile_Parms.YL = YL;
		DrawRotatedMaterialTile_Parms.U = U;
		DrawRotatedMaterialTile_Parms.V = V;
		DrawRotatedMaterialTile_Parms.UL = UL;
		DrawRotatedMaterialTile_Parms.VL = VL;
		DrawRotatedMaterialTile_Parms.AnchorX = AnchorX;
		DrawRotatedMaterialTile_Parms.AnchorY = AnchorY;

		pfnDrawRotatedMaterialTile->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnDrawRotatedMaterialTile, &DrawRotatedMaterialTile_Parms, NULL );
		pfnDrawRotatedMaterialTile->FunctionFlags |= 0x400;
	};

	void DrawRotatedTile ( class UTexture2D* Tex, struct FRotator Rotation, float XL, float YL, float U, float V, float UL, float VL, float AnchorX/*CPF_OptionalParm*/, float AnchorY/*CPF_OptionalParm*/ )
	{
		static UFunction* pfnDrawRotatedTile = NULL;

		if ( !pfnDrawRotatedTile )
			pfnDrawRotatedTile = UObject::FindObject< UFunction >( "Function Engine.Canvas.DrawRotatedTile" );

		UCanvas_execDrawRotatedTile_Parms DrawRotatedTile_Parms;
		DrawRotatedTile_Parms.Tex = Tex;
		memcpy( &DrawRotatedTile_Parms.Rotation, &Rotation, 0xC );
		DrawRotatedTile_Parms.XL = XL;
		DrawRotatedTile_Parms.YL = YL;
		DrawRotatedTile_Parms.U = U;
		DrawRotatedTile_Parms.V = V;
		DrawRotatedTile_Parms.UL = UL;
		DrawRotatedTile_Parms.VL = VL;
		DrawRotatedTile_Parms.AnchorX = AnchorX;
		DrawRotatedTile_Parms.AnchorY = AnchorY;

		pfnDrawRotatedTile->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnDrawRotatedTile, &DrawRotatedTile_Parms, NULL );
		pfnDrawRotatedTile->FunctionFlags |= 0x400;
	};

	void SetDrawColor ( unsigned char R, unsigned char G, unsigned char B, unsigned char A/*CPF_OptionalParm*/ )
	{
		static UFunction* pfnSetDrawColor = NULL;

		if ( !pfnSetDrawColor )
			pfnSetDrawColor = UObject::FindObject< UFunction >( "Function Engine.Canvas.SetDrawColor" );

		UCanvas_execSetDrawColor_Parms SetDrawColor_Parms;
		SetDrawColor_Parms.R = R;
		SetDrawColor_Parms.G = G;
		SetDrawColor_Parms.B = B;
		SetDrawColor_Parms.A = A;

		pfnSetDrawColor->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnSetDrawColor, &SetDrawColor_Parms, NULL );
		pfnSetDrawColor->FunctionFlags |= 0x400;
	};

	void DrawBox ( float Width, float Height )
	{
		static UFunction* pfnDrawBox = NULL;

		if ( !pfnDrawBox )
			pfnDrawBox = UObject::FindObject< UFunction >( "Function Engine.Canvas.DrawBox" );

		UCanvas_execDrawBox_Parms DrawBox_Parms;
		DrawBox_Parms.Width = Width;
		DrawBox_Parms.Height = Height;

		this->ProcessEvent( pfnDrawBox, &DrawBox_Parms, NULL );
	};

	void DrawRect ( float RectX, float RectY, class UTexture2D* Tex/*CPF_OptionalParm*/ )
	{
		static UFunction* pfnDrawRect = NULL;

		if ( !pfnDrawRect )
			pfnDrawRect = UObject::FindObject< UFunction >( "Function Engine.Canvas.DrawRect" );

		UCanvas_execDrawRect_Parms DrawRect_Parms;
		DrawRect_Parms.RectX = RectX;
		DrawRect_Parms.RectY = RectY;
		DrawRect_Parms.Tex = Tex;

		this->ProcessEvent( pfnDrawRect, &DrawRect_Parms, NULL );
	};

	void DrawIconSection ( struct FCanvasIcon Icon, float X, float Y, float UStartPct, float VStartPct, float UEndPct, float VEndPct, float Scale/*CPF_OptionalParm*/ )
	{
		static UFunction* pfnDrawIconSection = NULL;

		if ( !pfnDrawIconSection )
			pfnDrawIconSection = UObject::FindObject< UFunction >( "Function Engine.Canvas.DrawIconSection" );

		UCanvas_execDrawIconSection_Parms DrawIconSection_Parms;
		memcpy( &DrawIconSection_Parms.Icon, &Icon, 0x14 );
		DrawIconSection_Parms.X = X;
		DrawIconSection_Parms.Y = Y;
		DrawIconSection_Parms.UStartPct = UStartPct;
		DrawIconSection_Parms.VStartPct = VStartPct;
		DrawIconSection_Parms.UEndPct = UEndPct;
		DrawIconSection_Parms.VEndPct = VEndPct;
		DrawIconSection_Parms.Scale = Scale;

		this->ProcessEvent( pfnDrawIconSection, &DrawIconSection_Parms, NULL );
	};

	void DrawIcon ( struct FCanvasIcon Icon, float X, float Y, float Scale/*CPF_OptionalParm*/ )
	{
		static UFunction* pfnDrawIcon = NULL;

		if ( !pfnDrawIcon )
			pfnDrawIcon = UObject::FindObject< UFunction >( "Function Engine.Canvas.DrawIcon" );

		UCanvas_execDrawIcon_Parms DrawIcon_Parms;
		memcpy( &DrawIcon_Parms.Icon, &Icon, 0x14 );
		DrawIcon_Parms.X = X;
		DrawIcon_Parms.Y = Y;
		DrawIcon_Parms.Scale = Scale;

		this->ProcessEvent( pfnDrawIcon, &DrawIcon_Parms, NULL );
	};

	struct FCanvasIcon MakeIcon ( class UTexture2D* Texture, float U/*CPF_OptionalParm*/, float V/*CPF_OptionalParm*/, float UL/*CPF_OptionalParm*/, float VL/*CPF_OptionalParm*/ )
	{
		static UFunction* pfnMakeIcon = NULL;

		if ( !pfnMakeIcon )
			pfnMakeIcon = UObject::FindObject< UFunction >( "Function Engine.Canvas.MakeIcon" );

		UCanvas_execMakeIcon_Parms MakeIcon_Parms;
		MakeIcon_Parms.Texture = Texture;
		MakeIcon_Parms.U = U;
		MakeIcon_Parms.V = V;
		MakeIcon_Parms.UL = UL;
		MakeIcon_Parms.VL = VL;

		this->ProcessEvent( pfnMakeIcon, &MakeIcon_Parms, NULL );

		return MakeIcon_Parms.ReturnValue;
	};

	void DrawTexture ( class UTexture2D* Tex, float Scale )
	{
		static UFunction* pfnDrawTexture = NULL;

		if ( !pfnDrawTexture )
			pfnDrawTexture = UObject::FindObject< UFunction >( "Function Engine.Canvas.DrawTexture" );

		UCanvas_execDrawTexture_Parms DrawTexture_Parms;
		DrawTexture_Parms.Tex = Tex;
		DrawTexture_Parms.Scale = Scale;

		this->ProcessEvent( pfnDrawTexture, &DrawTexture_Parms, NULL );
	};

	void SetClip ( float X, float Y )
	{
		static UFunction* pfnSetClip = NULL;

		if ( !pfnSetClip )
			pfnSetClip = UObject::FindObject< UFunction >( "Function Engine.Canvas.SetClip" );

		UCanvas_execSetClip_Parms SetClip_Parms;
		SetClip_Parms.X = X;
		SetClip_Parms.Y = Y;

		this->ProcessEvent( pfnSetClip, &SetClip_Parms, NULL );
	};

	void SetOrigin ( float X, float Y )
	{
		static UFunction* pfnSetOrigin = NULL;

		if ( !pfnSetOrigin )
			pfnSetOrigin = UObject::FindObject< UFunction >( "Function Engine.Canvas.SetOrigin" );

		UCanvas_execSetOrigin_Parms SetOrigin_Parms;
		SetOrigin_Parms.X = X;
		SetOrigin_Parms.Y = Y;

		this->ProcessEvent( pfnSetOrigin, &SetOrigin_Parms, NULL );
	};

	void SetPos ( float PosX, float PosY )
	{
		static UFunction* pfnSetPos = NULL;

		if ( !pfnSetPos )
			pfnSetPos = UObject::FindObject< UFunction >( "Function Engine.Canvas.SetPos" );

		UCanvas_execSetPos_Parms SetPos_Parms;
		SetPos_Parms.PosX = PosX;
		SetPos_Parms.PosY = PosY;

		pfnSetPos->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnSetPos, &SetPos_Parms, NULL );
		pfnSetPos->FunctionFlags |= 0x400;
	};

	void eventReset ( unsigned long bKeepOrigin/*CPF_OptionalParm*/ )
	{
		static UFunction* pfnReset = NULL;

		if ( !pfnReset )
			pfnReset = UObject::FindObject< UFunction >( "Function Engine.Canvas.Reset" );

		UCanvas_eventReset_Parms Reset_Parms;
		Reset_Parms.bKeepOrigin = bKeepOrigin;

		this->ProcessEvent( pfnReset, &Reset_Parms, NULL );
	};

	void DrawColorizedTile ( class UTexture2D* Tex, float XL, float YL, float U, float V, float UL, float VL, struct FLinearColor LColor )
	{
		static UFunction* pfnDrawColorizedTile = NULL;

		if ( !pfnDrawColorizedTile )
			pfnDrawColorizedTile = UObject::FindObject< UFunction >( "Function Engine.Canvas.DrawColorizedTile" );

		UCanvas_execDrawColorizedTile_Parms DrawColorizedTile_Parms;
		DrawColorizedTile_Parms.Tex = Tex;
		DrawColorizedTile_Parms.XL = XL;
		DrawColorizedTile_Parms.YL = YL;
		DrawColorizedTile_Parms.U = U;
		DrawColorizedTile_Parms.V = V;
		DrawColorizedTile_Parms.UL = UL;
		DrawColorizedTile_Parms.VL = VL;
		memcpy( &DrawColorizedTile_Parms.LColor, &LColor, 0x10 );

		pfnDrawColorizedTile->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnDrawColorizedTile, &DrawColorizedTile_Parms, NULL );
		pfnDrawColorizedTile->FunctionFlags |= 0x400;
	};

	void DrawTileStretched ( class UTexture2D* Tex, float Left, float Top, float AWidth, float AHeight, float U, float V, float UL, float VL, struct FLinearColor LDrawColor, unsigned long bStretchHorizontally/*CPF_OptionalParm*/, unsigned long bStretchVertically/*CPF_OptionalParm*/, float ScalingFactor/*CPF_OptionalParm*/ )
	{
		static UFunction* pfnDrawTileStretched = NULL;

		if ( !pfnDrawTileStretched )
			pfnDrawTileStretched = UObject::FindObject< UFunction >( "Function Engine.Canvas.DrawTileStretched" );

		UCanvas_execDrawTileStretched_Parms DrawTileStretched_Parms;
		DrawTileStretched_Parms.Tex = Tex;
		DrawTileStretched_Parms.Left = Left;
		DrawTileStretched_Parms.Top = Top;
		DrawTileStretched_Parms.AWidth = AWidth;
		DrawTileStretched_Parms.AHeight = AHeight;
		DrawTileStretched_Parms.U = U;
		DrawTileStretched_Parms.V = V;
		DrawTileStretched_Parms.UL = UL;
		DrawTileStretched_Parms.VL = VL;
		memcpy( &DrawTileStretched_Parms.LDrawColor, &LDrawColor, 0x10 );
		DrawTileStretched_Parms.bStretchHorizontally = bStretchHorizontally;
		DrawTileStretched_Parms.bStretchVertically = bStretchVertically;
		DrawTileStretched_Parms.ScalingFactor = ScalingFactor;

		pfnDrawTileStretched->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnDrawTileStretched, &DrawTileStretched_Parms, NULL );
		pfnDrawTileStretched->FunctionFlags |= 0x400;
	};

	void PopTransform ()
	{
		static UFunction* pfnPopTransform = NULL;

		if ( !pfnPopTransform )
			pfnPopTransform = UObject::FindObject< UFunction >( "Function Engine.Canvas.PopTransform" );

		UCanvas_execPopTransform_Parms PopTransform_Parms;

		pfnPopTransform->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnPopTransform, &PopTransform_Parms, NULL );
		pfnPopTransform->FunctionFlags |= 0x400;
	};

	void PushTranslationMatrix ( struct FVector TranslationVector )
	{
		static UFunction* pfnPushTranslationMatrix = NULL;

		if ( !pfnPushTranslationMatrix )
			pfnPushTranslationMatrix = UObject::FindObject< UFunction >( "Function Engine.Canvas.PushTranslationMatrix" );

		UCanvas_execPushTranslationMatrix_Parms PushTranslationMatrix_Parms;
		memcpy( &PushTranslationMatrix_Parms.TranslationVector, &TranslationVector, 0xC );

		pfnPushTranslationMatrix->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnPushTranslationMatrix, &PushTranslationMatrix_Parms, NULL );
		pfnPushTranslationMatrix->FunctionFlags |= 0x400;
	};

	struct FVector Project ( struct FVector Location )
	{
		static UFunction* pfnProject = NULL;

		if ( !pfnProject )
			pfnProject = UObject::FindObject< UFunction >( "Function Engine.Canvas.Project" );

		UCanvas_execProject_Parms Project_Parms;
		memcpy( &Project_Parms.Location, &Location, 0xC );

		pfnProject->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnProject, &Project_Parms, NULL );
		pfnProject->FunctionFlags |= 0x400;

		return Project_Parms.ReturnValue;
	};

	void DrawTileClipped ( class UTexture2D* Tex, float XL, float YL, float U, float V, float UL, float VL )
	{
		static UFunction* pfnDrawTileClipped = NULL;

		if ( !pfnDrawTileClipped )
			pfnDrawTileClipped = UObject::FindObject< UFunction >( "Function Engine.Canvas.DrawTileClipped" );

		UCanvas_execDrawTileClipped_Parms DrawTileClipped_Parms;
		DrawTileClipped_Parms.Tex = Tex;
		DrawTileClipped_Parms.XL = XL;
		DrawTileClipped_Parms.YL = YL;
		DrawTileClipped_Parms.U = U;
		DrawTileClipped_Parms.V = V;
		DrawTileClipped_Parms.UL = UL;
		DrawTileClipped_Parms.VL = VL;

		WORD NativeIndex = pfnDrawTileClipped->iNative;
		pfnDrawTileClipped->iNative = 0;

		pfnDrawTileClipped->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnDrawTileClipped, &DrawTileClipped_Parms, NULL );
		pfnDrawTileClipped->FunctionFlags |= 0x400;

		pfnDrawTileClipped->iNative = NativeIndex;
	};

	void DrawTextRA ( struct FString Text, unsigned long CR/*CPF_OptionalParm*/ )
	{
		static UFunction* pfnDrawTextRA = NULL;

		if ( !pfnDrawTextRA )
			pfnDrawTextRA = UObject::FindObject< UFunction >( "Function Engine.Canvas.DrawTextRA" );

		UCanvas_execDrawTextRA_Parms DrawTextRA_Parms;
		memcpy( &DrawTextRA_Parms.Text, &Text, 0xC );
		DrawTextRA_Parms.CR = CR;

		this->ProcessEvent( pfnDrawTextRA, &DrawTextRA_Parms, NULL );
	};

	void DrawTextClipped ( struct FString Text, unsigned long bCheckHotKey/*CPF_OptionalParm*/, float XScale/*CPF_OptionalParm*/, float YScale/*CPF_OptionalParm*/ )
	{
		static UFunction* pfnDrawTextClipped = NULL;

		if ( !pfnDrawTextClipped )
			pfnDrawTextClipped = UObject::FindObject< UFunction >( "Function Engine.Canvas.DrawTextClipped" );

		UCanvas_execDrawTextClipped_Parms DrawTextClipped_Parms;
		memcpy( &DrawTextClipped_Parms.Text, &Text, 0xC );
		DrawTextClipped_Parms.bCheckHotKey = bCheckHotKey;
		DrawTextClipped_Parms.XScale = XScale;
		DrawTextClipped_Parms.YScale = YScale;

		pfnDrawTextClipped->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnDrawTextClipped, &DrawTextClipped_Parms, NULL );
		pfnDrawTextClipped->FunctionFlags |= 0x400;
	};

	void DrawText ( struct FString Text, unsigned long CR/*CPF_OptionalParm*/, float XScale/*CPF_OptionalParm*/, float YScale/*CPF_OptionalParm*/ )
	{
		static UFunction* pfnDrawText = NULL;

		if ( !pfnDrawText )
			pfnDrawText = UObject::FindObject< UFunction >( "Function Engine.Canvas.DrawText" );

		UCanvas_execDrawText_Parms DrawText_Parms;
		memcpy( &DrawText_Parms.Text, &Text, 0xC );
		DrawText_Parms.CR = CR;
		DrawText_Parms.XScale = XScale;
		DrawText_Parms.YScale = YScale;

		pfnDrawText->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnDrawText, &DrawText_Parms, NULL );
		pfnDrawText->FunctionFlags |= 0x400;
	};

	void TextSize ( struct FString String, float* XL, float* YL )
	{
		static UFunction* pfnTextSize = NULL;

		if ( !pfnTextSize )
			pfnTextSize = UObject::FindObject< UFunction >( "Function Engine.Canvas.TextSize" );

		UCanvas_execTextSize_Parms TextSize_Parms;
		memcpy( &TextSize_Parms.String, &String, 0xC );

		pfnTextSize->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnTextSize, &TextSize_Parms, NULL );
		pfnTextSize->FunctionFlags |= 0x400;

		if ( XL )
			*XL = TextSize_Parms.XL; // CPF_OutParm
		if ( YL )
			*YL = TextSize_Parms.YL; // CPF_OutParm
	};

	void StrLen ( struct FString String, float* XL, float* YL )
	{
		static UFunction* pfnStrLen = NULL;

		if ( !pfnStrLen )
			pfnStrLen = UObject::FindObject< UFunction >( "Function Engine.Canvas.StrLen" );

		UCanvas_execStrLen_Parms StrLen_Parms;
		memcpy( &StrLen_Parms.String, &String, 0xC );

		pfnStrLen->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnStrLen, &StrLen_Parms, NULL );
		pfnStrLen->FunctionFlags |= 0x400;

		if ( XL )
			*XL = StrLen_Parms.XL; // CPF_OutParm
		if ( YL )
			*YL = StrLen_Parms.YL; // CPF_OutParm
	};

	void DrawMaterialTileClipped ( class UMaterialInterface* Mat, float XL, float YL, float U/*CPF_OptionalParm*/, float V/*CPF_OptionalParm*/, float UL/*CPF_OptionalParm*/, float VL/*CPF_OptionalParm*/ )
	{
		static UFunction* pfnDrawMaterialTileClipped = NULL;

		if ( !pfnDrawMaterialTileClipped )
			pfnDrawMaterialTileClipped = UObject::FindObject< UFunction >( "Function Engine.Canvas.DrawMaterialTileClipped" );

		UCanvas_execDrawMaterialTileClipped_Parms DrawMaterialTileClipped_Parms;
		DrawMaterialTileClipped_Parms.Mat = Mat;
		DrawMaterialTileClipped_Parms.XL = XL;
		DrawMaterialTileClipped_Parms.YL = YL;
		DrawMaterialTileClipped_Parms.U = U;
		DrawMaterialTileClipped_Parms.V = V;
		DrawMaterialTileClipped_Parms.UL = UL;
		DrawMaterialTileClipped_Parms.VL = VL;

		pfnDrawMaterialTileClipped->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnDrawMaterialTileClipped, &DrawMaterialTileClipped_Parms, NULL );
		pfnDrawMaterialTileClipped->FunctionFlags |= 0x400;
	};

	void DrawMaterialTile ( class UMaterialInterface* Mat, float XL, float YL, float U/*CPF_OptionalParm*/, float V/*CPF_OptionalParm*/, float UL/*CPF_OptionalParm*/, float VL/*CPF_OptionalParm*/ )
	{
		static UFunction* pfnDrawMaterialTile = NULL;

		if ( !pfnDrawMaterialTile )
			pfnDrawMaterialTile = UObject::FindObject< UFunction >( "Function Engine.Canvas.DrawMaterialTile" );

		UCanvas_execDrawMaterialTile_Parms DrawMaterialTile_Parms;
		DrawMaterialTile_Parms.Mat = Mat;
		DrawMaterialTile_Parms.XL = XL;
		DrawMaterialTile_Parms.YL = YL;
		DrawMaterialTile_Parms.U = U;
		DrawMaterialTile_Parms.V = V;
		DrawMaterialTile_Parms.UL = UL;
		DrawMaterialTile_Parms.VL = VL;

		pfnDrawMaterialTile->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnDrawMaterialTile, &DrawMaterialTile_Parms, NULL );
		pfnDrawMaterialTile->FunctionFlags |= 0x400;
	};

	void DrawQuad ( class UTexture2D* Tex, float XL, float YL, float U1, float v1, float U2, float v2, float U3, float V3, float U4, float V4 )
	{
		static UFunction* pfnDrawQuad = NULL;

		if ( !pfnDrawQuad )
			pfnDrawQuad = UObject::FindObject< UFunction >( "Function Engine.Canvas.DrawQuad" );

		UCanvas_execDrawQuad_Parms DrawQuad_Parms;
		DrawQuad_Parms.Tex = Tex;
		DrawQuad_Parms.XL = XL;
		DrawQuad_Parms.YL = YL;
		DrawQuad_Parms.U1 = U1;
		DrawQuad_Parms.v1 = v1;
		DrawQuad_Parms.U2 = U2;
		DrawQuad_Parms.v2 = v2;
		DrawQuad_Parms.U3 = U3;
		DrawQuad_Parms.V3 = V3;
		DrawQuad_Parms.U4 = U4;
		DrawQuad_Parms.V4 = V4;

		pfnDrawQuad->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnDrawQuad, &DrawQuad_Parms, NULL );
		pfnDrawQuad->FunctionFlags |= 0x400;
	};

	void DrawLine2D ( float XL, float YL )
	{
		static UFunction* pfnDrawLine2D = NULL;

		if ( !pfnDrawLine2D )
			pfnDrawLine2D = UObject::FindObject< UFunction >( "Function Engine.Canvas.DrawLine2D" );

		UCanvas_execDrawLine2D_Parms DrawLine2D_Parms;
		DrawLine2D_Parms.XL = XL;
		DrawLine2D_Parms.YL = YL;

		pfnDrawLine2D->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnDrawLine2D, &DrawLine2D_Parms, NULL );
		pfnDrawLine2D->FunctionFlags |= 0x400;
	};

	void DrawTile ( class UTexture2D* Tex, float XL, float YL, float U, float V, float UL, float VL )
	{
		static UFunction* pfnDrawTile = NULL;

		if ( !pfnDrawTile )
			pfnDrawTile = UObject::FindObject< UFunction >( "Function Engine.Canvas.DrawTile" );

		UCanvas_execDrawTile_Parms DrawTile_Parms;
		DrawTile_Parms.Tex = Tex;
		DrawTile_Parms.XL = XL;
		DrawTile_Parms.YL = YL;
		DrawTile_Parms.U = U;
		DrawTile_Parms.V = V;
		DrawTile_Parms.UL = UL;
		DrawTile_Parms.VL = VL;

		pfnDrawTile->FunctionFlags |= ~0x400;
		this->ProcessEvent( pfnDrawTile, &DrawTile_Parms, NULL );
		pfnDrawTile->FunctionFlags |= 0x400;
	};

};

UClass* UCanvas::ClassPointer = NULL;

#ifdef _MSC_VER
#pragma pack( pop )
#endif
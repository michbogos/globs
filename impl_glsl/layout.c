/*******************************************************************************************
*
*   LayoutName v1.0.0 - Tool Description
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------
static void LabelButton008();                // LabelButton: LabelButton008 logic

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 1900;
    int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "layout_name");

    // layout_name: controls initialization
    //----------------------------------------------------------------------------------
    // Const text
    const char *GroupBox000Text = "SAMPLE TEXT";    // GROUPBOX: GroupBox000
    const char *ToggleGroup001Text = "ONE;TWO;THREE";    // TOGGLEGROUP: ToggleGroup001
    const char *ToggleGroup002Text = "ONE;TWO;THREE";    // TOGGLEGROUP: ToggleGroup002
    const char *Slider003Text = "";    // SLIDER: Slider003
    const char *ToggleGroup005Text = "ONE;TWO;THREE";    // TOGGLEGROUP: ToggleGroup005
    const char *ToggleGroup006Text = "ONE;TWO;THREE";    // TOGGLEGROUP: ToggleGroup006
    const char *ToggleGroup007Text = "ONE;TWO;THREE";    // TOGGLEGROUP: ToggleGroup007
    const char *LabelButton008Text = "SAMPLE TEXT";    // LABELBUTTON: LabelButton008
    const char *ToggleGroup009Text = "ONE;TWO;THREE";    // TOGGLEGROUP: ToggleGroup009
    
    // Define anchors
    Vector2 anchor01 = { 312, 160 };            // ANCHOR ID:1
    Vector2 anchor02 = { 760, 336 };            // ANCHOR ID:2
    
    // Define controls variables
    int ToggleGroup001Active = 0;            // ToggleGroup: ToggleGroup001
    int ToggleGroup002Active = 0;            // ToggleGroup: ToggleGroup002
    float Slider003Value = 0.0f;            // Slider: Slider003
    int ToggleGroup005Active = 0;            // ToggleGroup: ToggleGroup005
    Rectangle ScrollPanel005ScrollView = { 0, 0, 0, 0 };
    Vector2 ScrollPanel005ScrollOffset = { 0, 0 };
    Vector2 ScrollPanel005BoundsOffset = { 0, 0 };            // ScrollPanel: ScrollPanel005
    int ToggleGroup006Active = 0;            // ToggleGroup: ToggleGroup006
    int ToggleGroup007Active = 0;            // ToggleGroup: ToggleGroup007
    int ToggleGroup009Active = 0;            // ToggleGroup: ToggleGroup009
    Color ColorPicker010Value = { 0, 0, 0, 0 };            // ColorPicker: ColorPicker010

    // Define controls rectangles
    Rectangle layoutRecs[11] = {
        (Rectangle){ anchor01.x + 0, anchor01.y + 0, 256, 224 },    // GroupBox: GroupBox000
        (Rectangle){ anchor01.x + 16, anchor01.y + 16, 40, 24 },    // ToggleGroup: ToggleGroup001
        (Rectangle){ anchor01.x + 16, anchor01.y + 56, 40, 24 },    // ToggleGroup: ToggleGroup002
        (Rectangle){ anchor01.x + 1, anchor01.y + 209, 256, 16 },    // Slider: Slider003
        (Rectangle){ 712, 208, 40, 24 },    // ToggleGroup: ToggleGroup005
        (Rectangle){ anchor02.x + 0, anchor02.y + 0, 189, 180 },    // ScrollPanel: ScrollPanel005
        (Rectangle){ anchor02.x + 8, anchor02.y + 72, 40, 24 },    // ToggleGroup: ToggleGroup006
        (Rectangle){ 437, 420, 40, 24 },    // ToggleGroup: ToggleGroup007
        (Rectangle){ anchor02.x + 8, anchor02.y + 8, 120, 24 },    // LabelButton: LabelButton008
        (Rectangle){ anchor02.x + 8, anchor02.y + 32, 40, 24 },    // ToggleGroup: ToggleGroup009
        (Rectangle){ anchor02.x + 8, anchor02.y + 112, 96, 96 },    // ColorPicker: ColorPicker010
    };
    //----------------------------------------------------------------------------------

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            // Draw controls
            GuiGroupBox(layoutRecs[0], GroupBox000Text);
            GuiToggleGroup(layoutRecs[1], ToggleGroup001Text, &ToggleGroup001Active);
            GuiToggleGroup(layoutRecs[2], ToggleGroup002Text, &ToggleGroup002Active);
            GuiSlider(layoutRecs[3], Slider003Text, NULL, &Slider003Value, 0, 100);
            GuiToggleGroup(layoutRecs[4], ToggleGroup005Text, &ToggleGroup005Active);
            GuiScrollPanel((Rectangle){layoutRecs[5].x, layoutRecs[5].y, layoutRecs[5].width - ScrollPanel005BoundsOffset.x, layoutRecs[5].height - ScrollPanel005BoundsOffset.y }, "Scroll Panel", layoutRecs[5], &ScrollPanel005ScrollOffset, &ScrollPanel005ScrollView);
            GuiToggleGroup(layoutRecs[6], ToggleGroup006Text, &ToggleGroup006Active);
            GuiToggleGroup(layoutRecs[7], ToggleGroup007Text, &ToggleGroup007Active);
            if (GuiLabelButton(layoutRecs[8], LabelButton008Text)) LabelButton008();
            GuiToggleGroup(layoutRecs[9], ToggleGroup009Text, &ToggleGroup009Active);
            GuiColorPicker(layoutRecs[10], "Color picker", &ColorPicker010Value);
            //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------
// LabelButton: LabelButton008 logic
static void LabelButton008()
{
    // TODO: Implement control logic
}


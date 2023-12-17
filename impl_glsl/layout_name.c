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

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------
static void BtnOpen();                // Button: btnOpen logic
static void BtnExport();                // Button: btnExport logic
static void BtnHelp();                // Button: btnHelp logic
static void BtnAbout();                // Button: btnAbout logic
static void Center();                // Button: center logic
static void FullScreen();                // Button: fullScreen logic

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "layout_name");

    // layout_name: controls initialization
    //----------------------------------------------------------------------------------
    // Const text
    const char *btnOpenText = "#1#";    // BUTTON: btnOpen
    const char *btnExportText = "#7#";    // BUTTON: btnExport
    const char *showInfoWindowText = "#100#";    // TOGGLE: showInfoWindow
    const char *showEditWindowText = "#140#";    // TOGGLE: showEditWindow
    const char *btnHelpText = "HELP";    // BUTTON: btnHelp
    const char *btnAboutText = "#191#ABOUT";    // BUTTON: btnAbout
    const char *centerText = "#105#";    // BUTTON: center
    const char *zoomText = "ZOOM:";    // SLIDERBAR: zoom
    const char *lblScaleFilterText = "Scale Filter:";    // LABEL: lblScaleFilter
    const char *scaleFilterText = "#34#;#35#";    // TOGGLEGROUP: scaleFilter
    const char *lblBackText = "Back:";    // LABEL: lblBack
    const char *backgroundText = ";;;";    // TOGGLEGROUP: background
    const char *channelsText = "All;R;G;B;A";    // TOGGLEGROUP: channels
    const char *lblChannelsText = "Channels:";    // LABEL: lblChannels
    const char *lblHelpersText = "Helpers:";    // LABEL: lblHelpers
    const char *helperGridText = "#97#";    // TOGGLE: helperGrid
    const char *helperCursorText = "#65#";    // TOGGLE: helperCursor
    const char *helperBoxText = "#38#";    // TOGGLE: helperBox
    const char *fullScreenText = "#53#";    // BUTTON: fullScreen
    
    // Define anchors
    Vector2 anchorFullscreen = { 1296, 48 };            // ANCHOR ID:1
    Vector2 anchorZoom = { 376, 48 };            // ANCHOR ID:2
    Vector2 anchorBack = { 768, 48 };            // ANCHOR ID:3
    Vector2 anchorChannels = { 928, 48 };            // ANCHOR ID:4
    Vector2 anchorHelpers = { 1128, 48 };            // ANCHOR ID:5
    Vector2 anchorMain = { 48, 48 };            // ANCHOR ID:6
    
    // Define controls variables
    bool showInfoWindowActive = true;            // Toggle: showInfoWindow
    bool showEditWindowActive = true;            // Toggle: showEditWindow
    float zoomValue = 0.0f;            // SliderBar: zoom
    int scaleFilterActive = 0;            // ToggleGroup: scaleFilter
    int backgroundActive = 0;            // ToggleGroup: background
    int channelsActive = 0;            // ToggleGroup: channels
    bool helperGridActive = true;            // Toggle: helperGrid
    bool helperCursorActive = true;            // Toggle: helperCursor
    bool helperBoxActive = true;            // Toggle: helperBox

    // Define controls rectangles
    Rectangle layoutRecs[26] = {
        (Rectangle){ anchorMain.x + 0, anchorMain.y + 0, 328, 40 },    // Panel: panelEmpty
        (Rectangle){ anchorMain.x + 16, anchorMain.y + 8, 24, 24 },    // Button: btnOpen
        (Rectangle){ anchorMain.x + 48, anchorMain.y + 8, 24, 24 },    // Button: btnExport
        (Rectangle){ anchorMain.x + 88, anchorMain.y + 8, 24, 24 },    // Toggle: showInfoWindow
        (Rectangle){ anchorMain.x + 120, anchorMain.y + 8, 24, 24 },    // Toggle: showEditWindow
        (Rectangle){ anchorMain.x + 160, anchorMain.y + 8, 72, 24 },    // Button: btnHelp
        (Rectangle){ anchorMain.x + 240, anchorMain.y + 8, 72, 24 },    // Button: btnAbout
        (Rectangle){ anchorZoom.x + 0, anchorZoom.y + 0, 392, 40 },    // Panel: panelBack
        (Rectangle){ anchorZoom.x + 16, anchorZoom.y + 8, 24, 24 },    // Button: center
        (Rectangle){ anchorZoom.x + 88, anchorZoom.y + 16, 150, 12 },    // SliderBar: zoom
        (Rectangle){ anchorZoom.x + 264, anchorZoom.y + 8, 72, 24 },    // Label: lblScaleFilter
        (Rectangle){ anchorZoom.x + 336, anchorZoom.y + 8, 24, 24 },    // ToggleGroup: scaleFilter
        (Rectangle){ anchorChannels.x + 0, anchorChannels.y + 0, 200, 40 },    // Panel: panelChannels
        (Rectangle){ anchorBack.x + 0, anchorBack.y + 0, 160, 40 },    // Panel: panelZoom
        (Rectangle){ anchorBack.x + 16, anchorBack.y + 8, 32, 24 },    // Label: lblBack
        (Rectangle){ anchorBack.x + 48, anchorBack.y + 8, 24, 24 },    // ToggleGroup: background
        (Rectangle){ anchorChannels.x + 64, anchorChannels.y + 8, 24, 24 },    // ToggleGroup: channels
        (Rectangle){ anchorChannels.x + 8, anchorChannels.y + 8, 56, 24 },    // Label: lblChannels
        (Rectangle){ anchorHelpers.x + 0, anchorHelpers.y + 0, 152, 40 },    // Panel: panelHelpers
        (Rectangle){ anchorHelpers.x + 8, anchorHelpers.y + 8, 56, 24 },    // Label: lblHelpers
        (Rectangle){ anchorHelpers.x + 56, anchorHelpers.y + 8, 24, 24 },    // Toggle: helperGrid
        (Rectangle){ anchorHelpers.x + 88, anchorHelpers.y + 8, 24, 24 },    // Toggle: helperCursor
        (Rectangle){ anchorHelpers.x + 120, anchorHelpers.y + 8, 24, 24 },    // Toggle: helperBox
        (Rectangle){ anchorHelpers.x + 152, anchorHelpers.y + 0, 16, 40 },    // Panel: panelMain
        (Rectangle){ anchorFullscreen.x + 0, anchorFullscreen.y + 0, 40, 40 },    // Panel: visualization
        (Rectangle){ anchorFullscreen.x + 8, anchorFullscreen.y + 8, 24, 24 },    // Button: fullScreen
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
            GuiPanel(layoutRecs[0], "");
            if (GuiButton(layoutRecs[1], btnOpenText)) BtnOpen(); 
            if (GuiButton(layoutRecs[2], btnExportText)) BtnExport(); 
            GuiToggle(layoutRecs[3], showInfoWindowText, &showInfoWindowActive);
            GuiToggle(layoutRecs[4], showEditWindowText, &showEditWindowActive);
            if (GuiButton(layoutRecs[5], btnHelpText)) BtnHelp(); 
            if (GuiButton(layoutRecs[6], btnAboutText)) BtnAbout(); 
            GuiPanel(layoutRecs[7], "");
            if (GuiButton(layoutRecs[8], centerText)) Center(); 
            GuiSliderBar(layoutRecs[9], zoomText, NULL, &zoomValue, 0, 100);
            GuiLabel(layoutRecs[10], lblScaleFilterText);
            GuiToggleGroup(layoutRecs[11], scaleFilterText, &scaleFilterActive);
            GuiPanel(layoutRecs[12], "");
            GuiPanel(layoutRecs[13], "");
            GuiLabel(layoutRecs[14], lblBackText);
            GuiToggleGroup(layoutRecs[15], backgroundText, &backgroundActive);
            GuiToggleGroup(layoutRecs[16], channelsText, &channelsActive);
            GuiLabel(layoutRecs[17], lblChannelsText);
            GuiPanel(layoutRecs[18], "");
            GuiLabel(layoutRecs[19], lblHelpersText);
            GuiToggle(layoutRecs[20], helperGridText, &helperGridActive);
            GuiToggle(layoutRecs[21], helperCursorText, &helperCursorActive);
            GuiToggle(layoutRecs[22], helperBoxText, &helperBoxActive);
            GuiPanel(layoutRecs[23], "");
            GuiPanel(layoutRecs[24], "");
            if (GuiButton(layoutRecs[25], fullScreenText)) FullScreen(); 
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
// Button: btnOpen logic
static void BtnOpen()
{
    // TODO: Implement control logic
}
// Button: btnExport logic
static void BtnExport()
{
    // TODO: Implement control logic
}
// Button: btnHelp logic
static void BtnHelp()
{
    // TODO: Implement control logic
}
// Button: btnAbout logic
static void BtnAbout()
{
    // TODO: Implement control logic
}
// Button: center logic
static void Center()
{
    // TODO: Implement control logic
}
// Button: fullScreen logic
static void FullScreen()
{
    // TODO: Implement control logic
}


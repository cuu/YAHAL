/* -------------------------------------------------------------------------------- */
/* -- µGUI - Generic GUI module (C)Achim Döbler, 2015                            -- */
/* -------------------------------------------------------------------------------- */
// µGUI is a generic GUI module for embedded systems.
// This is a free software that is open for education, research and commercial
// developments under license policy of following terms.
//
//  Copyright (C) 2015, Achim Döbler, all rights reserved.
//  URL: http://www.embeddedlightning.com/
//
// * The µGUI module is a free software and there is NO WARRANTY.
// * No restriction on use. You can use, modify and redistribute it for
//   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
// * Redistributions of source code must retain the above copyright notice.
//
/* -------------------------------------------------------------------------------- */
/* -- REVISION HISTORY                                                           -- */
/* -------------------------------------------------------------------------------- */
//  Mar 18, 2015  V0.3  Driver support added.
//                      Window and object support added.
//                      Touch support added.
//                      Fixed some minor bugs.
//
//  Oct 20, 2014  V0.2  Function UG_DrawRoundFrame() added.
//                      Function UG_FillRoundFrame() added.
//                      Function UG_DrawArc() added.
//                      Fixed some minor bugs.
//
//  Oct 11, 2014  V0.1  First release.
/* -------------------------------------------------------------------------------- */
#include <stdint.h>
#include "uGUI_colors.h"
#include "lcd_interface.h"

#ifndef __UGUI_H_
#define __UGUI_H_

/* -------------------------------------------------------------------------------- */
/* -- TYPEDEFS                                                                   -- */
/* -------------------------------------------------------------------------------- */

typedef int8_t UG_RESULT;
typedef uint32_t UG_COLOR;

/* -------------------------------------------------------------------------------- */
/* -- DEFINES                                                                    -- */
/* -------------------------------------------------------------------------------- */

/* Alignments */
#define ALIGN_H_LEFT                                  (1<<0)
#define ALIGN_H_CENTER                                (1<<1)
#define ALIGN_H_RIGHT                                 (1<<2)
#define ALIGN_V_TOP                                   (1<<3)
#define ALIGN_V_CENTER                                (1<<4)
#define ALIGN_V_BOTTOM                                (1<<5)
#define ALIGN_BOTTOM_RIGHT                            (ALIGN_V_BOTTOM|ALIGN_H_RIGHT)
#define ALIGN_BOTTOM_CENTER                           (ALIGN_V_BOTTOM|ALIGN_H_CENTER)
#define ALIGN_BOTTOM_LEFT                             (ALIGN_V_BOTTOM|ALIGN_H_LEFT)
#define ALIGN_CENTER_RIGHT                            (ALIGN_V_CENTER|ALIGN_H_RIGHT)
#define ALIGN_CENTER                                  (ALIGN_V_CENTER|ALIGN_H_CENTER)
#define ALIGN_CENTER_LEFT                             (ALIGN_V_CENTER|ALIGN_H_LEFT)
#define ALIGN_TOP_RIGHT                               (ALIGN_V_TOP|ALIGN_H_RIGHT)
#define ALIGN_TOP_CENTER                              (ALIGN_V_TOP|ALIGN_H_CENTER)
#define ALIGN_TOP_LEFT                                (ALIGN_V_TOP|ALIGN_H_LEFT)

/* Default IDs */
#define OBJ_ID_0                                      0
#define OBJ_ID_1                                      1
#define OBJ_ID_2                                      2
#define OBJ_ID_3                                      3
#define OBJ_ID_4                                      4
#define OBJ_ID_5                                      5
#define OBJ_ID_6                                      6
#define OBJ_ID_7                                      7
#define OBJ_ID_8                                      8
#define OBJ_ID_9                                      9
#define OBJ_ID_10                                     10
#define OBJ_ID_11                                     11
#define OBJ_ID_12                                     12
#define OBJ_ID_13                                     13
#define OBJ_ID_14                                     14
#define OBJ_ID_15                                     15
#define OBJ_ID_16                                     16
#define OBJ_ID_17                                     17
#define OBJ_ID_18                                     18
#define OBJ_ID_19                                     19

/* -------------------------------------------------------------------------------- */
/* -- FUNCTION RESULTS                                                           -- */
/* -------------------------------------------------------------------------------- */
#define UG_RESULT_FAIL                               -1
#define UG_RESULT_OK                                  0

/* -------------------------------------------------------------------------------- */
/* -- BITMAP                                                                     -- */
/* -------------------------------------------------------------------------------- */

#define BMP_BPP_1                                     (1<<0)
#define BMP_BPP_2                                     (1<<1)
#define BMP_BPP_4                                     (1<<2)
#define BMP_BPP_8                                     (1<<3)
#define BMP_BPP_16                                    (1<<4)
#define BMP_BPP_32                                    (1<<5)
#define BMP_RGB888                                    (1<<0)
#define BMP_RGB565                                    (1<<1)
#define BMP_RGB555                                    (1<<2)

/* -------------------------------------------------------------------------------- */
/* -- MESSAGE                                                                    -- */
/* -------------------------------------------------------------------------------- */

/* Message types */
#define MSG_TYPE_NONE                                 0
#define MSG_TYPE_WINDOW                               1
#define MSG_TYPE_OBJECT                               2

/* -------------------------------------------------------------------------------- */
/* -- TOUCH                                                                      -- */
/* -------------------------------------------------------------------------------- */
/* Touch structure */

#define TOUCH_STATE_PRESSED                           1
#define TOUCH_STATE_RELEASED                          0

/* -------------------------------------------------------------------------------- */
/* -- OBJECTS                                                                    -- */
/* -------------------------------------------------------------------------------- */

/* Currently supported objects */
#define OBJ_TYPE_NONE                                 0
#define OBJ_TYPE_BUTTON                               1
#define OBJ_TYPE_TEXTBOX                              2
#define OBJ_TYPE_IMAGE                                3

/* Standard object events */
#define OBJ_EVENT_NONE                                0
#define OBJ_EVENT_CLICKED                             1

/* Object states */
#define OBJ_STATE_FREE                                (1<<0)
#define OBJ_STATE_VALID                               (1<<1)
#define OBJ_STATE_BUSY                                (1<<2)
#define OBJ_STATE_VISIBLE                             (1<<3)
#define OBJ_STATE_ENABLE                              (1<<4)
#define OBJ_STATE_UPDATE                              (1<<5)
#define OBJ_STATE_REDRAW                              (1<<6)
#define OBJ_STATE_TOUCH_ENABLE                        (1<<7)
#define OBJ_STATE_INIT                                (OBJ_STATE_FREE | OBJ_STATE_VALID)

/* Object touch states */
#define OBJ_TOUCH_STATE_CHANGED                       (1<<0)
#define OBJ_TOUCH_STATE_PRESSED_ON_OBJECT             (1<<1)
#define OBJ_TOUCH_STATE_PRESSED_OUTSIDE_OBJECT        (1<<2)
#define OBJ_TOUCH_STATE_RELEASED_ON_OBJECT            (1<<3)
#define OBJ_TOUCH_STATE_RELEASED_OUTSIDE_OBJECT       (1<<4)
#define OBJ_TOUCH_STATE_IS_PRESSED_ON_OBJECT          (1<<5)
#define OBJ_TOUCH_STATE_IS_PRESSED                    (1<<6)
#define OBJ_TOUCH_STATE_CLICK_ON_OBJECT               (1<<7)
#define OBJ_TOUCH_STATE_INIT                          0

/* -------------------------------------------------------------------------------- */
/* -- WINDOW                                                                     -- */
/* -------------------------------------------------------------------------------- */

/* Window states */
#define WND_STATE_FREE                                (1<<0)
#define WND_STATE_VALID                               (1<<1)
#define WND_STATE_BUSY                                (1<<2)
#define WND_STATE_VISIBLE                             (1<<3)
#define WND_STATE_ENABLE                              (1<<4)
#define WND_STATE_UPDATE                              (1<<5)
#define WND_STATE_REDRAW_TITLE                        (1<<6)

/* Window styles */
#define WND_STYLE_2D                                  (0<<0)
#define WND_STYLE_3D                                  (1<<0)
#define WND_STYLE_HIDE_TITLE                          (0<<1)
#define WND_STYLE_SHOW_TITLE                          (1<<1)

/* -------------------------------------------------------------------------------- */
/* -- BUTTON OBJECT                                                              -- */
/* -------------------------------------------------------------------------------- */

/* Default button IDs */
#define BTN_ID_0                                      OBJ_ID_0
#define BTN_ID_1                                      OBJ_ID_1
#define BTN_ID_2                                      OBJ_ID_2
#define BTN_ID_3                                      OBJ_ID_3
#define BTN_ID_4                                      OBJ_ID_4
#define BTN_ID_5                                      OBJ_ID_5
#define BTN_ID_6                                      OBJ_ID_6
#define BTN_ID_7                                      OBJ_ID_7
#define BTN_ID_8                                      OBJ_ID_8
#define BTN_ID_9                                      OBJ_ID_9
#define BTN_ID_10                                     OBJ_ID_10
#define BTN_ID_11                                     OBJ_ID_11
#define BTN_ID_12                                     OBJ_ID_12
#define BTN_ID_13                                     OBJ_ID_13
#define BTN_ID_14                                     OBJ_ID_14
#define BTN_ID_15                                     OBJ_ID_15
#define BTN_ID_16                                     OBJ_ID_16
#define BTN_ID_17                                     OBJ_ID_17
#define BTN_ID_18                                     OBJ_ID_18
#define BTN_ID_19                                     OBJ_ID_19

/* Button states */
#define BTN_STATE_RELEASED                            (0<<0)
#define BTN_STATE_PRESSED                             (1<<0)
#define BTN_STATE_ALWAYS_REDRAW                       (1<<1)

/* Button style */
#define BTN_STYLE_2D                                  (0<<0)
#define BTN_STYLE_3D                                  (1<<0)
#define BTN_STYLE_TOGGLE_COLORS                       (1<<1)
#define BTN_STYLE_USE_ALTERNATE_COLORS                (1<<2)

/* Button events */
#define BTN_EVENT_CLICKED                             OBJ_EVENT_CLICKED

/* -------------------------------------------------------------------------------- */
/* -- TEXTBOX OBJECT                                                             -- */
/* -------------------------------------------------------------------------------- */

/* Default textbox IDs */
#define TXB_ID_0                                      OBJ_ID_0
#define TXB_ID_1                                      OBJ_ID_1
#define TXB_ID_2                                      OBJ_ID_2
#define TXB_ID_3                                      OBJ_ID_3
#define TXB_ID_4                                      OBJ_ID_4
#define TXB_ID_5                                      OBJ_ID_5
#define TXB_ID_6                                      OBJ_ID_6
#define TXB_ID_7                                      OBJ_ID_7
#define TXB_ID_8                                      OBJ_ID_8
#define TXB_ID_9                                      OBJ_ID_9
#define TXB_ID_10                                     OBJ_ID_10
#define TXB_ID_11                                     OBJ_ID_11
#define TXB_ID_12                                     OBJ_ID_12
#define TXB_ID_13                                     OBJ_ID_13
#define TXB_ID_14                                     OBJ_ID_14
#define TXB_ID_15                                     OBJ_ID_15
#define TXB_ID_16                                     OBJ_ID_16
#define TXB_ID_17                                     OBJ_ID_17
#define TXB_ID_18                                     OBJ_ID_18
#define TXB_ID_19                                     OBJ_ID_19

/* -------------------------------------------------------------------------------- */
/* -- IMAGE OBJECT                                                               -- */
/* -------------------------------------------------------------------------------- */

/* Default image IDs */
#define IMG_ID_0                                      OBJ_ID_0
#define IMG_ID_1                                      OBJ_ID_1
#define IMG_ID_2                                      OBJ_ID_2
#define IMG_ID_3                                      OBJ_ID_3
#define IMG_ID_4                                      OBJ_ID_4
#define IMG_ID_5                                      OBJ_ID_5
#define IMG_ID_6                                      OBJ_ID_6
#define IMG_ID_7                                      OBJ_ID_7
#define IMG_ID_8                                      OBJ_ID_8
#define IMG_ID_9                                      OBJ_ID_9
#define IMG_ID_10                                     OBJ_ID_10
#define IMG_ID_11                                     OBJ_ID_11
#define IMG_ID_12                                     OBJ_ID_12
#define IMG_ID_13                                     OBJ_ID_13
#define IMG_ID_14                                     OBJ_ID_14
#define IMG_ID_15                                     OBJ_ID_15
#define IMG_ID_16                                     OBJ_ID_16
#define IMG_ID_17                                     OBJ_ID_17
#define IMG_ID_18                                     OBJ_ID_18
#define IMG_ID_19                                     OBJ_ID_19

/* Image types */
#define IMG_TYPE_BMP                                  (1<<0)

#define UG_SATUS_WAIT_FOR_UPDATE                      (1<<0)

class uGUI
{
public:

    struct WINDOW;

    /* Area structure */
    struct AREA
    {
        int16_t xs;
        int16_t ys;
        int16_t xe;
        int16_t ye;
    };

    /* Object structure */
    struct OBJECT
    {
        uint8_t state;                              /* object state                               */
        uint8_t touch_state;                        /* object touch state                         */
        void (*update)(uGUI *, WINDOW *, OBJECT*);  /* pointer to object-specific update function */
        AREA a_abs;                                 /* absolute area of the object                */
        AREA a_rel;                                 /* relative area of the object                */
        uint8_t type;                               /* object type                                */
        uint8_t id;                                 /* object ID                                  */
        uint8_t event;                              /* object-specific events                     */
        void* data;                                 /* pointer to object-specific data            */
    };

    struct FONT
    {
        unsigned char* p;
        int16_t char_width;
        int16_t char_height;
    };

    /* Text structure */
    struct TEXT
    {
        char* str;
        const FONT* font;
        AREA a;
        UG_COLOR fc;
        UG_COLOR bc;
        uint8_t align;
        int16_t h_space;
        int16_t v_space;
    };

    struct BMP
    {
        const void* p;
        uint16_t width;
        uint16_t height;
        uint8_t bpp;
        uint8_t colors;
    };

    /* Message structure */
    struct MESSAGE
    {
        uint8_t type;
        uint8_t id;
        uint8_t sub_id;
        uint8_t event;
        void* src;
    };

    /* Button structure */
    struct BUTTON
    {
        uint8_t state;
        uint8_t style;
        UG_COLOR fc;
        UG_COLOR bc;
        UG_COLOR afc;
        UG_COLOR abc;
        const FONT* font;
        char* str;
    };

    /* Textbox structure */
    struct TEXTBOX
    {
        char* str;
        const FONT* font;
        uint8_t style;
        UG_COLOR fc;
        UG_COLOR bc;
        uint8_t align;
        int8_t h_space;
        int8_t v_space;
    };

    /* Title structure */
    struct TITLE
    {
        char* str;
        const FONT* font;
        int8_t h_space;
        int8_t v_space;
        uint8_t align;
        UG_COLOR fc;
        UG_COLOR bc;
        UG_COLOR ifc;
        UG_COLOR ibc;
        uint8_t height;
    };

    /* Window structure */
    struct WINDOW
    {
        uint8_t objcnt;
        OBJECT* objlst;
        uint8_t state;
        UG_COLOR fc;
        UG_COLOR bc;
        int16_t xs;
        int16_t ys;
        int16_t xe;
        int16_t ye;
        uint8_t style;
        TITLE title;
        void (*cb)(MESSAGE*);
    };

    /* Image structure */
    struct IMAGE
    {
        void* img;
        uint8_t type;
    };

    uGUI(lcd_interface & lcd);

    /* -------------------------------------------------------------------------------- */
    /* -- PROTOTYPES                                                                 -- */
    /* -------------------------------------------------------------------------------- */
    /* Classic functions */
    void    FontSelect(const FONT* font);
    void    FillScreen(UG_COLOR c);
    void    FillFrame(int16_t x1, int16_t y1, int16_t x2, int16_t y2, UG_COLOR c);
    void    FillRoundFrame(int16_t x1, int16_t y1, int16_t x2, int16_t y2,
                        int16_t r, UG_COLOR c);
    void    DrawMesh(int16_t x1, int16_t y1, int16_t x2, int16_t y2, UG_COLOR c);
    void    DrawFrame(int16_t x1, int16_t y1, int16_t x2, int16_t y2, UG_COLOR c);
    void    DrawRoundFrame(int16_t x1, int16_t y1, int16_t x2, int16_t y2,
                        int16_t r, UG_COLOR c);
    void    DrawPixel(int16_t x0, int16_t y0, UG_COLOR c);
    void    DrawCircle(int16_t x0, int16_t y0, int16_t r, UG_COLOR c);
    void    FillCircle(int16_t x0, int16_t y0, int16_t r, UG_COLOR c);
    void    DrawArc(int16_t x0, int16_t y0, int16_t r, uint8_t s, UG_COLOR c);
    void    DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, UG_COLOR c);
    void    PutString(int16_t x, int16_t y, char* str);
    void    PutChar(char chr, int16_t x, int16_t y, UG_COLOR fc, UG_COLOR bc);
    void    ConsolePutString(char* str);
    void    ConsoleSetArea(int16_t xs, int16_t ys, int16_t xe, int16_t ye);
    void    ConsoleSetForecolor(UG_COLOR c);
    void    ConsoleSetBackcolor(UG_COLOR c);
    void    SetForecolor(UG_COLOR c);
    void    SetBackcolor(UG_COLOR c);
    int16_t GetXDim(void);
    int16_t GetYDim(void);
    void    FontSetHSpace(uint16_t s);
    void    FontSetVSpace(uint16_t s);

    /* Miscellaneous functions */
    void    WaitForUpdate(void);
    void    Update(void);
    void    DrawBMP(int16_t xp, int16_t yp, BMP* bmp);
    void    TouchUpdate(int16_t xp, int16_t yp, uint8_t state);

    /* Window functions */
    UG_RESULT   WindowCreate(WINDOW* wnd, OBJECT* objlst, uint8_t objcnt,
                           void (*cb)(MESSAGE*));
    UG_RESULT   WindowDelete(WINDOW* wnd);
    UG_RESULT   WindowShow(WINDOW* wnd);
    UG_RESULT   WindowHide(WINDOW* wnd);
    UG_RESULT   WindowResize(WINDOW* wnd, int16_t xs, int16_t ys, int16_t xe,
                           int16_t ye);
    UG_RESULT   WindowAlert(WINDOW* wnd);
    UG_RESULT   WindowSetForeColor(WINDOW* wnd, UG_COLOR fc);
    UG_RESULT   WindowSetBackColor(WINDOW* wnd, UG_COLOR bc);
    UG_RESULT   WindowSetTitleTextColor(WINDOW* wnd, UG_COLOR c);
    UG_RESULT   WindowSetTitleColor(WINDOW* wnd, UG_COLOR c);
    UG_RESULT   WindowSetTitleInactiveTextColor(WINDOW* wnd, UG_COLOR c);
    UG_RESULT   WindowSetTitleInactiveColor(WINDOW* wnd, UG_COLOR c);
    UG_RESULT   WindowSetTitleText(WINDOW* wnd, char* str);
    UG_RESULT   WindowSetTitleTextFont(WINDOW* wnd, const FONT* font);
    UG_RESULT   WindowSetTitleTextHSpace(WINDOW* wnd, int8_t hs);
    UG_RESULT   WindowSetTitleTextVSpace(WINDOW* wnd, int8_t vs);
    UG_RESULT   WindowSetTitleTextAlignment(WINDOW* wnd, uint8_t align);
    UG_RESULT   WindowSetTitleHeight(WINDOW* wnd, uint8_t height);
    UG_RESULT   WindowSetXStart(WINDOW* wnd, int16_t xs);
    UG_RESULT   WindowSetYStart(WINDOW* wnd, int16_t ys);
    UG_RESULT   WindowSetXEnd(WINDOW* wnd, int16_t xe);
    UG_RESULT   WindowSetYEnd(WINDOW* wnd, int16_t ye);
    UG_RESULT   WindowSetStyle(WINDOW* wnd, uint8_t style);
    UG_COLOR    WindowGetForeColor(WINDOW* wnd);
    UG_COLOR    WindowGetBackColor(WINDOW* wnd);
    UG_COLOR    WindowGetTitleTextColor(WINDOW* wnd);
    UG_COLOR    WindowGetTitleColor(WINDOW* wnd);
    UG_COLOR    WindowGetTitleInactiveTextColor(WINDOW* wnd);
    UG_COLOR    WindowGetTitleInactiveColor(WINDOW* wnd);
    char *      WindowGetTitleText(WINDOW* wnd);
    FONT *      WindowGetTitleTextFont(WINDOW* wnd);
    int8_t      WindowGetTitleTextHSpace(WINDOW* wnd);
    int8_t      WindowGetTitleTextVSpace(WINDOW* wnd);
    uint8_t     WindowGetTitleTextAlignment(WINDOW* wnd);
    uint8_t     WindowGetTitleHeight(WINDOW* wnd);
    int16_t     WindowGetXStart(WINDOW* wnd);
    int16_t     WindowGetYStart(WINDOW* wnd);
    int16_t     WindowGetXEnd(WINDOW* wnd);
    int16_t     WindowGetYEnd(WINDOW* wnd);
    uint8_t     WindowGetStyle(WINDOW* wnd);
    UG_RESULT   WindowGetArea(WINDOW* wnd, AREA* a);
    int16_t     WindowGetInnerWidth(WINDOW* wnd);
    int16_t     WindowGetOuterWidth(WINDOW* wnd);
    int16_t     WindowGetInnerHeight(WINDOW* wnd);
    int16_t     WindowGetOuterHeight(WINDOW* wnd);

    /* Button functions */
    UG_RESULT   ButtonCreate(WINDOW* wnd, BUTTON* btn, uint8_t id, int16_t xs,
                           int16_t ys, int16_t xe, int16_t ye);
    UG_RESULT   ButtonDelete(WINDOW* wnd, uint8_t id);
    UG_RESULT   ButtonShow(WINDOW* wnd, uint8_t id);
    UG_RESULT   ButtonHide(WINDOW* wnd, uint8_t id);
    UG_RESULT   ButtonSetForeColor(WINDOW* wnd, uint8_t id, UG_COLOR fc);
    UG_RESULT   ButtonSetBackColor(WINDOW* wnd, uint8_t id, UG_COLOR bc);
    UG_RESULT   ButtonSetAlternateForeColor(WINDOW* wnd, uint8_t id,
                                          UG_COLOR afc);
    UG_RESULT   ButtonSetAlternateBackColor(WINDOW* wnd, uint8_t id,
                                          UG_COLOR abc);
    UG_RESULT   ButtonSetText(WINDOW* wnd, uint8_t id, char* str);
    UG_RESULT   ButtonSetFont(WINDOW* wnd, uint8_t id, const FONT* font);
    UG_RESULT   ButtonSetStyle(WINDOW* wnd, uint8_t id, uint8_t style);
    UG_COLOR    ButtonGetForeColor(WINDOW* wnd, uint8_t id);
    UG_COLOR    ButtonGetBackColor(WINDOW* wnd, uint8_t id);
    UG_COLOR    ButtonGetAlternateForeColor(WINDOW* wnd, uint8_t id);
    UG_COLOR    ButtonGetAlternateBackColor(WINDOW* wnd, uint8_t id);
    char *      ButtonGetText(WINDOW* wnd, uint8_t id);
    FONT *      ButtonGetFont(WINDOW* wnd, uint8_t id);
    uint8_t     ButtonGetStyle(WINDOW* wnd, uint8_t id);

    /* Textbox functions */
    UG_RESULT   TextboxCreate(WINDOW* wnd, TEXTBOX* txb, uint8_t id, int16_t xs,
                            int16_t ys, int16_t xe, int16_t ye);
    UG_RESULT   TextboxDelete(WINDOW* wnd, uint8_t id);
    UG_RESULT   TextboxShow(WINDOW* wnd, uint8_t id);
    UG_RESULT   TextboxHide(WINDOW* wnd, uint8_t id);
    UG_RESULT   TextboxSetForeColor(WINDOW* wnd, uint8_t id, UG_COLOR fc);
    UG_RESULT   TextboxSetBackColor(WINDOW* wnd, uint8_t id, UG_COLOR bc);
    UG_RESULT   TextboxSetText(WINDOW* wnd, uint8_t id, char* str);
    UG_RESULT   TextboxSetFont(WINDOW* wnd, uint8_t id, const FONT* font);
    UG_RESULT   TextboxSetHSpace(WINDOW* wnd, uint8_t id, int8_t hs);
    UG_RESULT   TextboxSetVSpace(WINDOW* wnd, uint8_t id, int8_t vs);
    UG_RESULT   TextboxSetAlignment(WINDOW* wnd, uint8_t id, uint8_t align);
    UG_COLOR    TextboxGetForeColor(WINDOW* wnd, uint8_t id);
    UG_COLOR    TextboxGetBackColor(WINDOW* wnd, uint8_t id);
    char *      TextboxGetText(WINDOW* wnd, uint8_t id);
    FONT *      TextboxGetFont(WINDOW* wnd, uint8_t id);
    int8_t      TextboxGetHSpace(WINDOW* wnd, uint8_t id);
    int8_t      TextboxGetVSpace(WINDOW* wnd, uint8_t id);
    uint8_t     TextboxGetAlignment(WINDOW* wnd, uint8_t id);

    /* Image functions */
    UG_RESULT   ImageCreate(WINDOW* wnd, IMAGE* img, uint8_t id, int16_t xs,
                          int16_t ys, int16_t xe, int16_t ye);
    UG_RESULT   ImageDelete(WINDOW* wnd, uint8_t id);
    UG_RESULT   ImageShow(WINDOW* wnd, uint8_t id);
    UG_RESULT   ImageHide(WINDOW* wnd, uint8_t id);
    UG_RESULT   ImageSetBMP(WINDOW* wnd, uint8_t id, const BMP* bmp);

private:

    UG_RESULT   _WindowDrawTitle(WINDOW* wnd);
    void        _WindowUpdate(WINDOW* wnd);
    UG_RESULT   _WindowClear(WINDOW* wnd);

    static void _TextboxUpdate(uGUI *gui, uGUI::WINDOW* wnd, uGUI::OBJECT* obj);
    static void _ButtonUpdate(uGUI *gui, uGUI::WINDOW* wnd, uGUI::OBJECT* obj);
    static void _ImageUpdate(uGUI *gui, uGUI::WINDOW* wnd, uGUI::OBJECT* obj);

    void        _HandleEvents(WINDOW* wnd);
    void        _DrawObjectFrame(int16_t xs, int16_t ys, int16_t xe, int16_t ye,
                          UG_COLOR* p);
    void        _UpdateObjects(WINDOW* wnd);
    void        _ProcessTouchData(WINDOW* wnd);
    UG_RESULT   _DeleteObject(WINDOW* wnd, uint8_t type, uint8_t id);
    OBJECT *    _SearchObject(WINDOW* wnd, uint8_t type, uint8_t id);
    OBJECT *    _GetFreeObject(WINDOW* wnd);
    void        _PutText(TEXT* txt);

    struct _CONSOLE
    {
        int16_t x_pos;
        int16_t y_pos;
        int16_t x_start;
        int16_t y_start;
        int16_t x_end;
        int16_t y_end;
        UG_COLOR fore_color;
        UG_COLOR back_color;
    };

    struct _FONT
    {
        unsigned char* p;
        int16_t char_width;
        int16_t char_height;
        int8_t char_h_space;
        int8_t char_v_space;
    };

    struct _TOUCH
    {
        uint8_t state;
        int16_t xp;
        int16_t yp;
    };

    lcd_interface & _lcd;
    int16_t _x_dim;
    int16_t _y_dim;
    _TOUCH _touch;
    WINDOW * _next_window;
    WINDOW * _active_window;
    WINDOW * _last_window;
    _CONSOLE _console;
    _FONT _font;
    UG_COLOR _fore_color;
    UG_COLOR _back_color;
    UG_COLOR _desktop_color;
    uint8_t _state;
};

#endif

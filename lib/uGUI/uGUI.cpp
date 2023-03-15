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

#include "uGUI.h"
#include "pixel_stream_rgb565.h"

uGUI::uGUI(lcd_interface & lcd) :
        _lcd(lcd)
{
    _x_dim = _lcd.getSizeX();
    _y_dim = _lcd.getSizeY();
    _console.x_start = 4;
    _console.y_start = 4;
    _console.x_end = _x_dim - _console.x_start - 1;
    _console.y_end = _y_dim - _console.x_start - 1;
    _console.x_pos = _console.x_end;
    _console.y_pos = _console.y_end;
    _font.char_h_space = 1;
    _font.char_v_space = 1;
    _font.p = nullptr;
    _desktop_color = 0x5E8BEf;
    _fore_color = C_WHITE;
    _back_color = C_BLACK;
    _next_window = nullptr;
    _active_window = nullptr;
    _last_window = nullptr;
    _state = 0;
}

void uGUI::FontSelect(const FONT* f)
{
    _font.p = f->p;
    _font.char_width = f->char_width;
    _font.char_height = f->char_height;
}

void uGUI::FillScreen(UG_COLOR c)
{
    FillFrame(0, 0, _x_dim - 1, _y_dim - 1, c);
}

void uGUI::FillFrame(int16_t x1, int16_t y1, int16_t x2, int16_t y2, UG_COLOR c)
{
    int16_t n;
    /* swap coordinates if necessary */
    if (x2 < x1)
    {
        n = x2;
        x2 = x1;
        x1 = n;
    }
    if (y2 < y1)
    {
        n = y2;
        y2 = y1;
        y1 = n;
    }

    _lcd.fillArea(x1, y1, x2, y2, c);
}

void uGUI::FillRoundFrame(int16_t x1, int16_t y1, int16_t x2, int16_t y2,
                          int16_t r, UG_COLOR c)
{
    int16_t x, y, xd;
    /* swap coordinates if necessary */
    if (x2 < x1)
    {
        x = x2;
        x2 = x1;
        x1 = x;
    }
    if (y2 < y1)
    {
        y = y2;
        y2 = y1;
        y1 = y;
    }

    if (r <= 0)
        return;

    xd = 3 - (r << 1);
    x = 0;
    y = r;

    FillFrame(x1 + r, y1, x2 - r, y2, c);

    while (x <= y)
    {
        if (y > 0)
        {
            DrawLine(x2 + x - r, y1 - y + r, x2 + x - r, y + y2 - r, c);
            DrawLine(x1 - x + r, y1 - y + r, x1 - x + r, y + y2 - r, c);
        }
        if (x > 0)
        {
            DrawLine(x1 - y + r, y1 - x + r, x1 - y + r, x + y2 - r, c);
            DrawLine(x2 + y - r, y1 - x + r, x2 + y - r, x + y2 - r, c);
        }
        if (xd < 0)
        {
            xd += (x << 2) + 6;
        }
        else
        {
            xd += ((x - y) << 2) + 10;
            y--;
        }
        x++;
    }
}

void uGUI::DrawMesh(int16_t x1, int16_t y1, int16_t x2, int16_t y2, UG_COLOR c)
{
    int16_t n, m;

    if (x2 < x1)
    {
        n = x2;
        x2 = x1;
        x1 = n;
    }
    if (y2 < y1)
    {
        n = y2;
        y2 = y1;
        y1 = n;
    }

    for (m = y1; m <= y2; m += 2)
    {
        for (n = x1; n <= x2; n += 2)
        {
            _lcd.drawPixel(n, m, c);
        }
    }
}

void uGUI::DrawFrame(int16_t x1, int16_t y1, int16_t x2, int16_t y2, UG_COLOR c)
{
    DrawLine(x1, y1, x2, y1, c);
    DrawLine(x1, y2, x2, y2, c);
    DrawLine(x1, y1, x1, y2, c);
    DrawLine(x2, y1, x2, y2, c);
}

void uGUI::DrawRoundFrame(int16_t x1, int16_t y1, int16_t x2, int16_t y2,
                          int16_t r, UG_COLOR c)
{
    int16_t n;
    if (x2 < x1)
    {
        n = x2;
        x2 = x1;
        x1 = n;
    }
    if (y2 < y1)
    {
        n = y2;
        y2 = y1;
        y1 = n;
    }

    if (r > x2)
        return;
    if (r > y2)
        return;

    DrawLine(x1 + r, y1, x2 - r, y1, c);
    DrawLine(x1 + r, y2, x2 - r, y2, c);
    DrawLine(x1, y1 + r, x1, y2 - r, c);
    DrawLine(x2, y1 + r, x2, y2 - r, c);
    DrawArc(x1 + r, y1 + r, r, 0x0C, c);
    DrawArc(x2 - r, y1 + r, r, 0x03, c);
    DrawArc(x1 + r, y2 - r, r, 0x30, c);
    DrawArc(x2 - r, y2 - r, r, 0xC0, c);
}

void uGUI::DrawPixel(int16_t x, int16_t y, UG_COLOR c)
{
    _lcd.drawPixel(x, y, c);
}

void uGUI::DrawCircle(int16_t x0, int16_t y0, int16_t r, UG_COLOR c)
{
    int16_t x, y, xd, yd, e;

    if (x0 < 0)
        return;
    if (y0 < 0)
        return;
    if (r <= 0)
        return;

    xd = 1 - (r << 1);
    yd = 0;
    e = 0;
    x = r;
    y = 0;

    while (x >= y)
    {
        _lcd.drawPixel(x0 - x, y0 + y, c);
        _lcd.drawPixel(x0 - x, y0 - y, c);
        _lcd.drawPixel(x0 + x, y0 + y, c);
        _lcd.drawPixel(x0 + x, y0 - y, c);
        _lcd.drawPixel(x0 - y, y0 + x, c);
        _lcd.drawPixel(x0 - y, y0 - x, c);
        _lcd.drawPixel(x0 + y, y0 + x, c);
        _lcd.drawPixel(x0 + y, y0 - x, c);

        y++;
        e += yd;
        yd += 2;
        if (((e << 1) + xd) > 0)
        {
            x--;
            e += xd;
            xd += 2;
        }
    }
}

void uGUI::FillCircle(int16_t x0, int16_t y0, int16_t r, UG_COLOR c)
{
    int16_t x, y, xd;

    if (x0 < 0)
        return;
    if (y0 < 0)
        return;
    if (r <= 0)
        return;

    xd = 3 - (r << 1);
    x = 0;
    y = r;

    while (x <= y)
    {
        if (y > 0)
        {
            DrawLine(x0 - x, y0 - y, x0 - x, y0 + y, c);
            DrawLine(x0 + x, y0 - y, x0 + x, y0 + y, c);
        }
        if (x > 0)
        {
            DrawLine(x0 - y, y0 - x, x0 - y, y0 + x, c);
            DrawLine(x0 + y, y0 - x, x0 + y, y0 + x, c);
        }
        if (xd < 0)
        {
            xd += (x << 2) + 6;
        }
        else
        {
            xd += ((x - y) << 2) + 10;
            y--;
        }
        x++;
    }
    DrawCircle(x0, y0, r, c);
}

void uGUI::DrawArc(int16_t x0, int16_t y0, int16_t r, uint8_t s, UG_COLOR c)
{
    int16_t x, y, xd, yd, e;

    if (x0 < 0)
        return;
    if (y0 < 0)
        return;
    if (r <= 0)
        return;

    xd = 1 - (r << 1);
    yd = 0;
    e = 0;
    x = r;
    y = 0;

    while (x >= y)
    {
        // Q1
        if (s & 0x01)
            _lcd.drawPixel(x0 + x, y0 - y, c);
        if (s & 0x02)
            _lcd.drawPixel(x0 + y, y0 - x, c);

        // Q2
        if (s & 0x04)
            _lcd.drawPixel(x0 - y, y0 - x, c);
        if (s & 0x08)
            _lcd.drawPixel(x0 - x, y0 - y, c);

        // Q3
        if (s & 0x10)
            _lcd.drawPixel(x0 - x, y0 + y, c);
        if (s & 0x20)
            _lcd.drawPixel(x0 - y, y0 + x, c);

        // Q4
        if (s & 0x40)
            _lcd.drawPixel(x0 + y, y0 + x, c);
        if (s & 0x80)
            _lcd.drawPixel(x0 + x, y0 + y, c);

        y++;
        e += yd;
        yd += 2;
        if (((e << 1) + xd) > 0)
        {
            x--;
            e += xd;
            xd += 2;
        }
    }
}

void uGUI::DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, UG_COLOR c)
{
    int16_t n, dx, dy, sgndx, sgndy, dxabs, dyabs, x, y, drawx, drawy;

    /* check if horizontal line has to be drawn */
    if (y1 == y2)
    {
        /* swap coordinates if necessary */
        if (x2 < x1)
        {
            n = x2;
            x2 = x1;
            x1 = n;
        }
        _lcd.drawHLine(x1, y1, x2, c);
        return;
    }

    /* check if vertical line has to be drawn */
    if (x1 == x2)
    {
        /* swap coordinates if necessary */
        if (y2 < y1)
        {
            n = y2;
            y2 = y1;
            y1 = n;
        }
        _lcd.drawVLine(x1, y1, y2, c);
        return;
    }

    dx = x2 - x1;
    dy = y2 - y1;
    dxabs = (dx > 0) ? dx : -dx;
    dyabs = (dy > 0) ? dy : -dy;
    sgndx = (dx > 0) ? 1 : -1;
    sgndy = (dy > 0) ? 1 : -1;
    x = dyabs >> 1;
    y = dxabs >> 1;
    drawx = x1;
    drawy = y1;

    _lcd.drawPixel(drawx, drawy, c);

    if (dxabs >= dyabs)
    {
        for (n = 0; n < dxabs; n++)
        {
            y += dyabs;
            if (y >= dxabs)
            {
                y -= dxabs;
                drawy += sgndy;
            }
            drawx += sgndx;
            _lcd.drawPixel(drawx, drawy, c);
        }
    }
    else
    {
        for (n = 0; n < dyabs; n++)
        {
            x += dxabs;
            if (x >= dyabs)
            {
                x -= dyabs;
                drawx += sgndx;
            }
            drawy += sgndy;
            _lcd.drawPixel(drawx, drawy, c);
        }
    }
}

void uGUI::PutChar(const char chr, int16_t x, int16_t y, UG_COLOR fc, UG_COLOR bc, bool opaque)
{
    uint16_t i, j, k, xo, yo, c, bn;
    uint8_t b, bt;
    unsigned char* p;

    bt = (uint8_t) chr;

    switch (bt)
    {
    case 0xB6:
        bt = 0x94;
        break; // ö
    case 0x96:
        bt = 0x99;
        break; // Ö
    case 0xBC:
        bt = 0x81;
        break; // ü
    case 0x9C:
        bt = 0x9A;
        break; // Ü
    case 0xA4:
        bt = 0x84;
        break; // ä
    case 0x84:
        bt = 0x8E;
        break; // Ä
    case 0xB5:
        bt = 0xE6;
        break; // µ
    case 0xB0:
        bt = 0xF8;
        break; // °
    }

    yo = y;
    bn = _font.char_width;
    if (!bn)
        return;
    bn >>= 3;
    if (_font.char_width % 8)
        bn++;
    p = _font.p;
    p += bt * _font.char_height * bn;

    for (j = 0; j < _font.char_height; j++)
    {
        xo = x;
        c = _font.char_width;
        for (i = 0; i < bn; i++)
        {
            b = *p++;
            for (k = 0; (k < 8) && c; k++)
            {
                if (b & 0x01)
                {
                    _lcd.drawPixel(xo, yo, fc);
                }
                else
                {
                    if (opaque) _lcd.drawPixel(xo, yo, bc);
                }
                b >>= 1;
                xo++;
                c--;
            }
        }
        yo++;
    }
}

void uGUI::PutString(int16_t x, int16_t y, const char* str, bool opaque)
{
    int16_t xp, yp;
    char chr;

    xp = x;
    yp = y;

    while (*str != 0)
    {
        chr = *str;
        if (chr == '\n')
        {
            xp = _x_dim;
            str++;
            continue;
        }
        // skip UTF8 prefix chars
        if ((chr == 0xC2) || (chr == 0xC3))
        {
            str++;
            continue;
        }

        if (xp + _font.char_width > _x_dim - 1)
        {
            xp = x;
            yp += _font.char_height + _font.char_v_space;
        }

        PutChar(chr, xp, yp, _fore_color, _back_color, opaque);

        xp += _font.char_width + _font.char_h_space;
        str++;
    }
}

void uGUI::ConsolePutString(char* str)
{
    char chr;

    while (*str != 0)
    {
        chr = *str;
        if (chr == '\n')
        {
            _console.x_pos = _x_dim;
            str++;
            continue;
        }

        _console.x_pos += _font.char_width + _font.char_h_space;

        if (_console.x_pos + _font.char_width > _console.x_end)
        {
            _console.x_pos = _console.x_start;
            _console.y_pos += _font.char_height + _font.char_v_space;
        }
        if (_console.y_pos + _font.char_height > _console.y_end)
        {
            _console.x_pos = _console.x_start;
            _console.y_pos = _console.y_start;
            FillFrame(_console.x_start, _console.y_start, _console.x_end,
                      _console.y_end, _console.back_color);
        }

        PutChar(chr, _console.x_pos, _console.y_pos, _console.fore_color,
                _console.back_color);
        str++;
    }
}

void uGUI::ConsoleSetArea(int16_t xs, int16_t ys, int16_t xe, int16_t ye)
{
    _console.x_start = xs;
    _console.y_start = ys;
    _console.x_end = xe;
    _console.y_end = ye;
}

void uGUI::ConsoleSetForecolor(UG_COLOR c)
{
    _console.fore_color = c;
}

void uGUI::ConsoleSetBackcolor(UG_COLOR c)
{
    _console.back_color = c;
}

void uGUI::SetForecolor(UG_COLOR c)
{
    _fore_color = c;
}

void uGUI::SetBackcolor(UG_COLOR c)
{
    _back_color = c;
}

int16_t uGUI::GetXDim(void)
{
    return _x_dim;
}

int16_t uGUI::GetYDim(void)
{
    return _y_dim;
}

void uGUI::FontSetHSpace(uint16_t s)
{
    _font.char_h_space = s;
}

void uGUI::FontSetVSpace(uint16_t s)
{
    _font.char_v_space = s;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const UG_COLOR pal_window[] = {
    /* Frame 0 */
    0x646464,
    0x646464,
    0x646464,
    0x646464,
    /* Frame 1 */
    0xFFFFFF,
    0xFFFFFF,
    0x696969,
    0x696969,
    /* Frame 2 */
    0xE3E3E3,
    0xE3E3E3,
    0xA0A0A0,
    0xA0A0A0, };

const UG_COLOR pal_button_pressed[] = {
    /* Frame 0 */
    0x646464,
    0x646464,
    0x646464,
    0x646464,
    /* Frame 1 */
    0xA0A0A0,
    0xA0A0A0,
    0xA0A0A0,
    0xA0A0A0,
    /* Frame 2 */
    0xF0F0F0,
    0xF0F0F0,
    0xF0F0F0,
    0xF0F0F0, };

const UG_COLOR pal_button_released[] = {
    /* Frame 0 */
    0x646464,
    0x646464,
    0x646464,
    0x646464,
    /* Frame 1 */
    0xFFFFFF,
    0xFFFFFF,
    0x696969,
    0x696969,
    /* Frame 2 */
    0xE3E3E3,
    0xE3E3E3,
    0xA0A0A0,
    0xA0A0A0, };
/* -------------------------------------------------------------------------------- */
/* -- INTERNAL FUNCTIONS                                                         -- */
/* -------------------------------------------------------------------------------- */
void uGUI::_PutText(TEXT* txt)
{
    uint16_t sl, rc;
    int16_t xp, yp;
    int16_t xs = txt->a.xs;
    int16_t ys = txt->a.ys;
    int16_t xe = txt->a.xe;
    int16_t ye = txt->a.ye;
    uint8_t align = txt->align;
    int16_t char_width = txt->font->char_width;
    int16_t char_height = txt->font->char_height;
    int16_t char_h_space = txt->h_space;
    int16_t char_v_space = txt->v_space;
    uint16_t i, j, k, xo, yo, cw, bn;
    uint8_t b, bt;

    unsigned char* p;

    char* str = txt->str;
    char* c = str;

    if (txt->font->p == nullptr)
        return;
    if (str == nullptr)
        return;
    if ((ye - ys) < txt->font->char_height)
        return;

    rc = 1;
    c = str;
    while (*c != 0)
    {
        if (*c == '\n')
            rc++;
        c++;
    }

    yp = 0;
    if (align & (ALIGN_V_CENTER | ALIGN_V_BOTTOM))
    {
        yp = ye - ys + 1;
        yp -= char_height * rc;
        yp -= char_v_space * (rc - 1);
        if (yp < 0)
            return;
    }
    if (align & ALIGN_V_CENTER)
        yp >>= 1;
    yp += ys;

    while (1)
    {
        sl = 0;
        c = str;
        while ((*c != 0) && (*c != '\n'))
        {
            c++;
            sl++;
        }

        xp = xe - xs + 1;
        xp -= char_width * sl;
        xp -= char_h_space * (sl - 1);
        if (xp < 0)
            return;

        if (align & ALIGN_H_LEFT)
            xp = 0;
        else if (align & ALIGN_H_CENTER)
            xp >>= 1;
        xp += xs;

        while ((*str != '\n'))
        {
            if (*str == 0)
                return;
            /*----------------------------------*/
            /* Draw one char                    */
            /*----------------------------------*/
            bt = (uint8_t) *str;
            switch (bt)
            {
                case 0xB6:
                    bt = 0x94;
                    break; // ö
                case 0x96:
                    bt = 0x99;
                    break; // Ö
                case 0xBC:
                    bt = 0x81;
                    break; // ü
                case 0x9C:
                    bt = 0x9A;
                    break; // Ü
                case 0xA4:
                    bt = 0x84;
                    break; // ä
                case 0x84:
                    bt = 0x8E;
                    break; // Ä
                case 0xB5:
                    bt = 0xE6;
                    break; // µ
                case 0xB0:
                    bt = 0xF8;
                    break; // °
            }
            yo = yp;
            bn = char_width;
            bn >>= 3;
            if (char_width % 8)
                bn++;
            p = txt->font->p;
            p += bt * char_height * bn;
            for (j = 0; j < char_height; j++)
            {
                xo = xp;
                cw = char_width;
                for (i = 0; i < bn; i++)
                {
                    b = *p++;
                    for (k = 0; (k < 8) && cw; k++)
                    {
                        if (b & 0x01)
                        {
                            _lcd.drawPixel(xo, yo, txt->fc);
                        }
                        else
                        {
                            _lcd.drawPixel(xo, yo, txt->bc);
                        }
                        b >>= 1;
                        xo++;
                        cw--;
                    }
                }
                yo++;
            }
            /*----------------------------------*/
            xp += char_width + char_h_space;
            str++;
        }
        str++;
        yp += char_height + char_v_space;
    }
}

uGUI::OBJECT * uGUI::_GetFreeObject(WINDOW* wnd)
{
    uint8_t i;
    OBJECT* obj = (OBJECT*) wnd->objlst;

    for (i = 0; i < wnd->objcnt; i++)
    {
        obj = (OBJECT*) (&wnd->objlst[i]);
        if ((obj->state & OBJ_STATE_FREE) && (obj->state & OBJ_STATE_VALID))
        {
            /* Free object found! */
            return obj;
        }
    }
    return nullptr;
}

uGUI::OBJECT * uGUI::_SearchObject(WINDOW* wnd, uint8_t type, uint8_t id)
{
    uint8_t i;
    OBJECT* obj = (OBJECT*) wnd->objlst;

    for (i = 0; i < wnd->objcnt; i++)
    {
        obj = (OBJECT*) (&wnd->objlst[i]);
        if (!(obj->state & OBJ_STATE_FREE) && (obj->state & OBJ_STATE_VALID))
        {
            if ((obj->type == type) && (obj->id == id))
            {
                /* Requested object found! */
                return obj;
            }
        }
    }
    return nullptr;
}

UG_RESULT uGUI::_DeleteObject(WINDOW* wnd, uint8_t type, uint8_t id)
{
    OBJECT* obj = nullptr;

    obj = _SearchObject(wnd, type, id);

    /* Object found? */
    if (obj != nullptr)
    {
        /* We dont't want to delete a visible or busy object! */
        if ((obj->state & OBJ_STATE_VISIBLE) || (obj->state & OBJ_STATE_UPDATE))
            return UG_RESULT_FAIL;
        obj->state = OBJ_STATE_INIT;
        obj->data = nullptr;
        obj->event = 0;
        obj->id = 0;
        obj->touch_state = 0;
        obj->type = 0;
        obj->update = nullptr;
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

void uGUI::_ProcessTouchData(WINDOW* wnd)
{
    int16_t xp, yp;
    uint16_t i, objcnt;
    OBJECT* obj;
    uint8_t objstate;
    uint8_t objtouch;
    uint8_t tchstate;

    xp = _touch.xp;
    yp = _touch.yp;
    tchstate = _touch.state;

    objcnt = wnd->objcnt;
    for (i = 0; i < objcnt; i++)
    {
        obj = (OBJECT*) &wnd->objlst[i];
        objstate = obj->state;
        objtouch = obj->touch_state;
        if (!(objstate & OBJ_STATE_FREE) && (objstate & OBJ_STATE_VALID)
                && (objstate & OBJ_STATE_VISIBLE)
                && !(objstate & OBJ_STATE_REDRAW))
        {
            /* Process touch data */
            if ((tchstate) && xp != -1)
            {
                if (!(objtouch & OBJ_TOUCH_STATE_IS_PRESSED))
                {
                    objtouch |= OBJ_TOUCH_STATE_PRESSED_OUTSIDE_OBJECT
                            | OBJ_TOUCH_STATE_CHANGED;
                    objtouch &= ~(OBJ_TOUCH_STATE_RELEASED_ON_OBJECT
                            | OBJ_TOUCH_STATE_RELEASED_OUTSIDE_OBJECT
                            | OBJ_TOUCH_STATE_CLICK_ON_OBJECT);
                }
                objtouch &= ~OBJ_TOUCH_STATE_IS_PRESSED_ON_OBJECT;
                if (xp >= obj->a_abs.xs)
                {
                    if (xp <= obj->a_abs.xe)
                    {
                        if (yp >= obj->a_abs.ys)
                        {
                            if (yp <= obj->a_abs.ye)
                            {
                                objtouch |=
                                OBJ_TOUCH_STATE_IS_PRESSED_ON_OBJECT;
                                if (!(objtouch & OBJ_TOUCH_STATE_IS_PRESSED))
                                {
                                    objtouch &=
                                            ~OBJ_TOUCH_STATE_PRESSED_OUTSIDE_OBJECT;
                                    objtouch |=
                                    OBJ_TOUCH_STATE_PRESSED_ON_OBJECT;
                                }
                            }
                        }
                    }
                }
                objtouch |= OBJ_TOUCH_STATE_IS_PRESSED;
            }
            else if (objtouch & OBJ_TOUCH_STATE_IS_PRESSED)
            {
                if (objtouch & OBJ_TOUCH_STATE_IS_PRESSED_ON_OBJECT)
                {
                    if (objtouch & OBJ_TOUCH_STATE_PRESSED_ON_OBJECT)
                        objtouch |= OBJ_TOUCH_STATE_CLICK_ON_OBJECT;
                    objtouch |= OBJ_TOUCH_STATE_RELEASED_ON_OBJECT;
                }
                else
                {
                    objtouch |= OBJ_TOUCH_STATE_RELEASED_OUTSIDE_OBJECT;
                }
                if (objtouch & OBJ_TOUCH_STATE_IS_PRESSED)
                {
                    objtouch |= OBJ_TOUCH_STATE_CHANGED;
                }
                objtouch &= ~(OBJ_TOUCH_STATE_PRESSED_OUTSIDE_OBJECT
                        | OBJ_TOUCH_STATE_PRESSED_ON_OBJECT
                        | OBJ_TOUCH_STATE_IS_PRESSED);
            }
        }
        obj->touch_state = objtouch;
    }
}

void uGUI::_UpdateObjects(WINDOW* wnd)
{
    uint16_t i, objcnt;
    OBJECT* obj;
    uint8_t objstate;
    uint8_t objtouch;

    /* Check each object, if it needs to be updated? */
    objcnt = wnd->objcnt;
    for (i = 0; i < objcnt; i++)
    {
        obj = (OBJECT*) &wnd->objlst[i];
        objstate = obj->state;
        objtouch = obj->touch_state;
        if (!(objstate & OBJ_STATE_FREE) && (objstate & OBJ_STATE_VALID))
        {
            if (objstate & OBJ_STATE_UPDATE)
            {
                (obj->update)(this, wnd, obj);
            }
            if ((objstate & OBJ_STATE_VISIBLE)
                    && (objstate & OBJ_STATE_TOUCH_ENABLE))
            {
                if ((objtouch
                        & (OBJ_TOUCH_STATE_CHANGED | OBJ_TOUCH_STATE_IS_PRESSED)))
                {
                    (obj->update)(this, wnd, obj);
                }
            }
        }
    }
}

void uGUI::_HandleEvents(WINDOW* wnd)
{
    uint16_t i, objcnt;
    OBJECT* obj;
    uint8_t objstate;
    static MESSAGE msg;
    msg.src = nullptr;

    /* Handle window-related events */
    //ToDo
    /* Handle object-related events */
    msg.type = MSG_TYPE_OBJECT;
    objcnt = wnd->objcnt;
    for (i = 0; i < objcnt; i++)
    {
        obj = (OBJECT*) &wnd->objlst[i];
        objstate = obj->state;
        if (!(objstate & OBJ_STATE_FREE) && (objstate & OBJ_STATE_VALID))
        {
            if (obj->event != OBJ_EVENT_NONE)
            {
                msg.src = &obj;
                msg.id = obj->type;
                msg.sub_id = obj->id;

                wnd->cb(&msg);

                obj->event = OBJ_EVENT_NONE;
            }
        }
    }
}

void uGUI::_DrawObjectFrame(int16_t xs, int16_t ys, int16_t xe, int16_t ye,
                            UG_COLOR* p)
{
    // Frame 0
    DrawLine(xs, ys, xe - 1, ys, *p++);
    DrawLine(xs, ys + 1, xs, ye - 1, *p++);
    DrawLine(xs, ye, xe, ye, *p++);
    DrawLine(xe, ys, xe, ye - 1, *p++);
    // Frame 1
    DrawLine(xs + 1, ys + 1, xe - 2, ys + 1, *p++);
    DrawLine(xs + 1, ys + 2, xs + 1, ye - 2, *p++);
    DrawLine(xs + 1, ye - 1, xe - 1, ye - 1, *p++);
    DrawLine(xe - 1, ys + 1, xe - 1, ye - 2, *p++);
    // Frame 2
    DrawLine(xs + 2, ys + 2, xe - 3, ys + 2, *p++);
    DrawLine(xs + 2, ys + 3, xs + 2, ye - 3, *p++);
    DrawLine(xs + 2, ye - 2, xe - 2, ye - 2, *p++);
    DrawLine(xe - 2, ys + 2, xe - 2, ye - 3, *p);
}

/* -------------------------------------------------------------------------------- */
/* -- MISCELLANEOUS FUNCTIONS                                                    -- */
/* -------------------------------------------------------------------------------- */
void uGUI::Update(void)
{
    WINDOW* wnd;

    /* Is somebody waiting for this update? */
    if (_state & UG_SATUS_WAIT_FOR_UPDATE)
        _state &= ~UG_SATUS_WAIT_FOR_UPDATE;

    /* Keep track of the windows */
    if (_next_window != _active_window)
    {
        if (_next_window != nullptr)
        {
            _last_window = _active_window;
            _active_window = _next_window;

            /* Do we need to draw an inactive title? */
            if ((_last_window->style & WND_STYLE_SHOW_TITLE)
                    && (_last_window->state & WND_STATE_VISIBLE))
            {
                /* Do both windows differ in size */
                if ((_last_window->xs != _active_window->xs)
                        || (_last_window->xe != _active_window->xe)
                        || (_last_window->ys != _active_window->ys)
                        || (_last_window->ye != _active_window->ye))
                {
                    /* Redraw title of the last window */
                    _WindowDrawTitle(_last_window);
                }
            }
            _active_window->state &= ~WND_STATE_REDRAW_TITLE;
            _active_window->state |= WND_STATE_UPDATE | WND_STATE_VISIBLE;
        }
    }

    /* Is there an active window */
    if (_active_window != nullptr)
    {
        wnd = _active_window;

        /* Does the window need to be updated? */
        if (wnd->state & WND_STATE_UPDATE)
        {
            /* Do it! */
            _WindowUpdate(wnd);
        }

        /* Is the window visible? */
        if (wnd->state & WND_STATE_VISIBLE)
        {
            _ProcessTouchData(wnd);
            _UpdateObjects(wnd);
            _HandleEvents(wnd);
        }
    }
}

void uGUI::WaitForUpdate(void)
{
    _state |= UG_SATUS_WAIT_FOR_UPDATE;
    while (_state & UG_SATUS_WAIT_FOR_UPDATE)
    {
    };
}

void uGUI::DrawBMP(int16_t xp, int16_t yp, BMP* bmp)
{
    if (bmp->p == nullptr)
        return;

    /* Only support 16 BPP so far */
    if ((bmp->bpp != BMP_BPP_16) || (bmp->colors != BMP_RGB565))
        return;

    pixel_stream_rgb565 ps((uint16_t*) bmp->p, bmp->height * bmp->width);
    _lcd.drawArea(xp, yp, xp + bmp->width - 1, yp + bmp->height - 1, ps);
}

void uGUI::TouchUpdate(int16_t xp, int16_t yp, uint8_t state)
{
    _touch.xp = xp;
    _touch.yp = yp;
    _touch.state = state;
}

/* -------------------------------------------------------------------------------- */
/* -- WINDOW FUNCTIONS                                                           -- */
/* -------------------------------------------------------------------------------- */
UG_RESULT uGUI::WindowCreate(WINDOW* wnd, OBJECT* objlst, uint8_t objcnt,
                             void (*cb)(MESSAGE*))
{
    uint8_t i;
    OBJECT* obj = nullptr;

    if ((wnd == nullptr) || (objlst == nullptr) || (objcnt == 0))
        return UG_RESULT_FAIL;

    /* Initialize all objects of the window */
    for (i = 0; i < objcnt; i++)
    {
        obj = (OBJECT*) &objlst[i];
        obj->state = OBJ_STATE_INIT;
        obj->data = nullptr;
    }

    /* Initialize window */
    wnd->objcnt = objcnt;
    wnd->objlst = objlst;
    wnd->state = WND_STATE_VALID;
    wnd->fc = 0x000000;
    wnd->bc = 0xF0F0F0;
    wnd->xs = 0;
    wnd->ys = 0;
    wnd->xe = GetXDim() - 1;
    wnd->ye = GetYDim() - 1;
    wnd->cb = cb;
    wnd->style = WND_STYLE_3D | WND_STYLE_SHOW_TITLE;

    /* Initialize window title-bar */
    wnd->title.str = nullptr;
    wnd->title.font = nullptr;
    wnd->title.h_space = 2;
    wnd->title.v_space = 2;
    wnd->title.align = ALIGN_CENTER_LEFT;
    wnd->title.fc = C_WHITE;
    wnd->title.bc = C_BLUE;
    wnd->title.ifc = C_WHITE;
    wnd->title.ibc = C_GRAY;
    wnd->title.height = 15;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::WindowDelete(WINDOW* wnd)
{
    if (wnd == _active_window)
        return UG_RESULT_FAIL;

    /* Only delete valid windows */
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        wnd->state = 0;
        wnd->cb = nullptr;
        wnd->objcnt = 0;
        wnd->objlst = nullptr;
        wnd->xs = 0;
        wnd->ys = 0;
        wnd->xe = 0;
        wnd->ye = 0;
        wnd->style = 0;
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

UG_RESULT uGUI::WindowShow(WINDOW* wnd)
{
    if (wnd != nullptr)
    {
        /* Force an update, even if this is the active window! */
        wnd->state |= WND_STATE_VISIBLE | WND_STATE_UPDATE;
        wnd->state &= ~WND_STATE_REDRAW_TITLE;
        _next_window = wnd;
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

UG_RESULT uGUI::WindowHide(WINDOW* wnd)
{
    if (wnd != nullptr)
    {
        if (wnd == _active_window)
        {
            /* Is there an old window which just lost the focus? */
            if ((_last_window != nullptr)
                    && (_last_window->state & WND_STATE_VISIBLE))
            {
                if ((_last_window->xs > wnd->xs) || (_last_window->ys > wnd->ys)
                        || (_last_window->xe < wnd->xe)
                        || (_last_window->ye < wnd->ye))
                {
                    _WindowClear(wnd);
                }
                _next_window = _last_window;
            }
            else
            {
                _active_window->state &= ~WND_STATE_VISIBLE;
                _active_window->state |= WND_STATE_UPDATE;
            }
        }
        else
        {
            /* If the old window is visible, clear it! */
            _WindowClear(wnd);
        }
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

UG_RESULT uGUI::WindowResize(WINDOW* wnd, int16_t xs, int16_t ys, int16_t xe,
                             int16_t ye)
{
    int16_t pos;
    int16_t xmax, ymax;

    xmax = GetXDim() - 1;
    ymax = GetYDim() - 1;

    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        /* Do some checks... */
        if ((xs < 0) || (ys < 0))
            return UG_RESULT_FAIL;
        if ((xe > xmax) || (ye > ymax))
            return UG_RESULT_FAIL;
        pos = xe - xs;
        if (pos < 10)
            return UG_RESULT_FAIL;
        pos = ye - ys;
        if (pos < 10)
            return UG_RESULT_FAIL;

        /* ... and if everything is OK move the window! */
        wnd->xs = xs;
        wnd->ys = ys;
        wnd->xe = xe;
        wnd->ye = ye;

        if ((wnd->state & WND_STATE_VISIBLE) && (_active_window == wnd))
        {
            if (wnd->ys)
                FillFrame(0, 0, xmax, wnd->ys - 1, _desktop_color);
            pos = wnd->ye + 1;
            if (!(pos > ymax))
                FillFrame(0, pos, xmax, ymax, _desktop_color);
            if (wnd->xs)
                FillFrame(0, wnd->ys, wnd->xs - 1, wnd->ye, _desktop_color);
            pos = wnd->xe + 1;
            if (!(pos > xmax))
                FillFrame(pos, wnd->ys, xmax, wnd->ye, _desktop_color);

            wnd->state &= ~WND_STATE_REDRAW_TITLE;
            wnd->state |= WND_STATE_UPDATE;
        }
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

UG_RESULT uGUI::WindowAlert(WINDOW* wnd)
{
    UG_COLOR c;
    c = WindowGetTitleTextColor(wnd);
    if (WindowSetTitleTextColor(wnd, WindowGetTitleColor(wnd)) == UG_RESULT_FAIL)
        return UG_RESULT_FAIL;
    if (WindowSetTitleColor(wnd, c) == UG_RESULT_FAIL)
        return UG_RESULT_FAIL;
    return UG_RESULT_OK;
}

UG_RESULT uGUI::WindowSetForeColor(WINDOW* wnd, UG_COLOR fc)
{
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        wnd->fc = fc;
        wnd->state |= WND_STATE_UPDATE;
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

UG_RESULT uGUI::WindowSetBackColor(WINDOW* wnd, UG_COLOR bc)
{
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        wnd->bc = bc;
        wnd->state |= WND_STATE_UPDATE;
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

UG_RESULT uGUI::WindowSetTitleTextColor(WINDOW* wnd, UG_COLOR c)
{
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        wnd->title.fc = c;
        wnd->state |= WND_STATE_UPDATE | WND_STATE_REDRAW_TITLE;
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

UG_RESULT uGUI::WindowSetTitleColor(WINDOW* wnd, UG_COLOR c)
{
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        wnd->title.bc = c;
        wnd->state |= WND_STATE_UPDATE | WND_STATE_REDRAW_TITLE;
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

UG_RESULT uGUI::WindowSetTitleInactiveTextColor(WINDOW* wnd, UG_COLOR c)
{
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        wnd->title.ifc = c;
        wnd->state |= WND_STATE_UPDATE | WND_STATE_REDRAW_TITLE;
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

UG_RESULT uGUI::WindowSetTitleInactiveColor(WINDOW* wnd, UG_COLOR c)
{
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        wnd->title.ibc = c;
        wnd->state |= WND_STATE_UPDATE | WND_STATE_REDRAW_TITLE;
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

UG_RESULT uGUI::WindowSetTitleText(WINDOW* wnd, char* str)
{
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        wnd->title.str = str;
        wnd->state |= WND_STATE_UPDATE | WND_STATE_REDRAW_TITLE;
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

UG_RESULT uGUI::WindowSetTitleTextFont(WINDOW* wnd, const FONT* font)
{
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        wnd->state |= WND_STATE_UPDATE | WND_STATE_REDRAW_TITLE;
        wnd->title.font = font;
        if (wnd->title.height <= (font->char_height + 1))
        {
            wnd->title.height = font->char_height + 2;
            wnd->state &= ~WND_STATE_REDRAW_TITLE;
        }
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

UG_RESULT uGUI::WindowSetTitleTextHSpace(WINDOW* wnd, int8_t hs)
{
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        wnd->title.h_space = hs;
        wnd->state |= WND_STATE_UPDATE | WND_STATE_REDRAW_TITLE;
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

UG_RESULT uGUI::WindowSetTitleTextVSpace(WINDOW* wnd, int8_t vs)
{
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        wnd->title.v_space = vs;
        wnd->state |= WND_STATE_UPDATE | WND_STATE_REDRAW_TITLE;
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

UG_RESULT uGUI::WindowSetTitleTextAlignment(WINDOW* wnd, uint8_t align)
{
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        wnd->title.align = align;
        wnd->state |= WND_STATE_UPDATE | WND_STATE_REDRAW_TITLE;
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

UG_RESULT uGUI::WindowSetTitleHeight(WINDOW* wnd, uint8_t height)
{
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        wnd->title.height = height;
        wnd->state &= ~WND_STATE_REDRAW_TITLE;
        wnd->state |= WND_STATE_UPDATE;
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

UG_RESULT uGUI::WindowSetXStart(WINDOW* wnd, int16_t xs)
{
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        wnd->xs = xs;
        if (WindowResize(wnd, wnd->xs, wnd->ys, wnd->xe,
                         wnd->ye) == UG_RESULT_FAIL)
            return UG_RESULT_FAIL;
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

UG_RESULT uGUI::WindowSetYStart(WINDOW* wnd, int16_t ys)
{
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        wnd->ys = ys;
        if (WindowResize(wnd, wnd->xs, wnd->ys, wnd->xe,
                         wnd->ye) == UG_RESULT_FAIL)
            return UG_RESULT_FAIL;
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

UG_RESULT uGUI::WindowSetXEnd(WINDOW* wnd, int16_t xe)
{
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        wnd->xe = xe;
        if (WindowResize(wnd, wnd->xs, wnd->ys, wnd->xe,
                         wnd->ye) == UG_RESULT_FAIL)
            return UG_RESULT_FAIL;
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

UG_RESULT uGUI::WindowSetYEnd(WINDOW* wnd, int16_t ye)
{
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        wnd->ye = ye;
        if (WindowResize(wnd, wnd->xs, wnd->ys, wnd->xe,
                         wnd->ye) == UG_RESULT_FAIL)
            return UG_RESULT_FAIL;
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

UG_RESULT uGUI::WindowSetStyle(WINDOW* wnd, uint8_t style)
{
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        /* 3D or 2D? */
        if (style & WND_STYLE_3D)
        {
            wnd->style |= WND_STYLE_3D;
        }
        else
        {
            wnd->style &= ~WND_STYLE_3D;
        }
        /* Show title-bar? */
        if (style & WND_STYLE_SHOW_TITLE)
        {
            wnd->style |= WND_STYLE_SHOW_TITLE;
        }
        else
        {
            wnd->style &= ~WND_STYLE_SHOW_TITLE;
        }
        wnd->state |= WND_STATE_UPDATE;
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

UG_COLOR uGUI::WindowGetForeColor(WINDOW* wnd)
{
    UG_COLOR c = C_BLACK;
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        c = wnd->fc;
    }
    return c;
}

UG_COLOR uGUI::WindowGetBackColor(WINDOW* wnd)
{
    UG_COLOR c = C_BLACK;
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        c = wnd->bc;
    }
    return c;
}

UG_COLOR uGUI::WindowGetTitleTextColor(WINDOW* wnd)
{
    UG_COLOR c = C_BLACK;
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        c = wnd->title.fc;
    }
    return c;
}

UG_COLOR uGUI::WindowGetTitleColor(WINDOW* wnd)
{
    UG_COLOR c = C_BLACK;
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        c = wnd->title.bc;
    }
    return c;
}

UG_COLOR uGUI::WindowGetTitleInactiveTextColor(WINDOW* wnd)
{
    UG_COLOR c = C_BLACK;
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        c = wnd->title.ifc;
    }
    return c;
}

UG_COLOR uGUI::WindowGetTitleInactiveColor(WINDOW* wnd)
{
    UG_COLOR c = C_BLACK;
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        c = wnd->title.ibc;
    }
    return c;
}

char* uGUI::WindowGetTitleText(WINDOW* wnd)
{
    char* str = nullptr;
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        str = wnd->title.str;
    }
    return str;
}

uGUI::FONT* uGUI::WindowGetTitleTextFont(WINDOW* wnd)
{
    FONT* f = nullptr;
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        f = (FONT*) wnd->title.font;
    }
    return f;
}

int8_t uGUI::WindowGetTitleTextHSpace(WINDOW* wnd)
{
    int8_t hs = 0;
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        hs = wnd->title.h_space;
    }
    return hs;
}

int8_t uGUI::WindowGetTitleTextVSpace(WINDOW* wnd)
{
    int8_t vs = 0;
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        vs = wnd->title.v_space;
    }
    return vs;
}

uint8_t uGUI::WindowGetTitleTextAlignment(WINDOW* wnd)
{
    uint8_t align = 0;
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        align = wnd->title.align;
    }
    return align;
}

uint8_t uGUI::WindowGetTitleHeight(WINDOW* wnd)
{
    uint8_t h = 0;
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        h = wnd->title.height;
    }
    return h;
}

int16_t uGUI::WindowGetXStart(WINDOW* wnd)
{
    int16_t xs = -1;
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        xs = wnd->xs;
    }
    return xs;
}

int16_t uGUI::WindowGetYStart(WINDOW* wnd)
{
    int16_t ys = -1;
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        ys = wnd->ys;
    }
    return ys;
}

int16_t uGUI::WindowGetXEnd(WINDOW* wnd)
{
    int16_t xe = -1;
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        xe = wnd->xe;
    }
    return xe;
}

int16_t uGUI::WindowGetYEnd(WINDOW* wnd)
{
    int16_t ye = -1;
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        ye = wnd->ye;
    }
    return ye;
}

uint8_t uGUI::WindowGetStyle(WINDOW* wnd)
{
    uint8_t style = 0;
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        style = wnd->style;
    }
    return style;
}

UG_RESULT uGUI::WindowGetArea(WINDOW* wnd, AREA* a)
{
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        a->xs = wnd->xs;
        a->ys = wnd->ys;
        a->xe = wnd->xe;
        a->ye = wnd->ye;
        if (wnd->style & WND_STYLE_3D)
        {
            a->xs += 3;
            a->ys += 3;
            a->xe -= 3;
            a->ye -= 3;
        }
        if (wnd->style & WND_STYLE_SHOW_TITLE)
        {
            a->ys += wnd->title.height + 1;
        }
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

int16_t uGUI::WindowGetInnerWidth(WINDOW* wnd)
{
    int16_t w = 0;
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        w = wnd->xe - wnd->xs;

        /* 3D style? */
        if (wnd->style & WND_STYLE_3D)
            w -= 6;

        if (w < 0)
            w = 0;
    }
    return w;
}

int16_t uGUI::WindowGetOuterWidth(WINDOW* wnd)
{
    int16_t w = 0;
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        w = wnd->xe - wnd->xs;

        if (w < 0)
            w = 0;
    }
    return w;
}

int16_t uGUI::WindowGetInnerHeight(WINDOW* wnd)
{
    int16_t h = 0;
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        h = wnd->ye - wnd->ys;

        /* 3D style? */
        if (wnd->style & WND_STYLE_3D)
            h -= 6;

        /* Is the title active */
        if (wnd->style & WND_STYLE_SHOW_TITLE)
            h -= wnd->title.height;

        if (h < 0)
            h = 0;
    }
    return h;
}

int16_t uGUI::WindowGetOuterHeight(WINDOW* wnd)
{
    int16_t h = 0;
    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        h = wnd->ye - wnd->ys;

        if (h < 0)
            h = 0;
    }
    return h;
}

UG_RESULT uGUI::_WindowDrawTitle(WINDOW* wnd)
{
    TEXT txt;
    int16_t xs, ys, xe, ye;

    if ((wnd != nullptr) && (wnd->state & WND_STATE_VALID))
    {
        xs = wnd->xs;
        ys = wnd->ys;
        xe = wnd->xe;
        ye = wnd->ye;

        /* 3D style? */
        if (wnd->style & WND_STYLE_3D)
        {
            xs += 3;
            ys += 3;
            xe -= 3;
            ye -= 3;
        }

        /* Is the window active or inactive? */
        if (wnd == _active_window)
        {
            txt.bc = wnd->title.bc;
            txt.fc = wnd->title.fc;
        }
        else
        {
            txt.bc = wnd->title.ibc;
            txt.fc = wnd->title.ifc;
        }

        /* Draw title */
        FillFrame(xs, ys, xe, ys + wnd->title.height - 1, txt.bc);

        /* Draw title text */
        txt.str = wnd->title.str;
        txt.font = wnd->title.font;
        txt.a.xs = xs + 3;
        txt.a.ys = ys;
        txt.a.xe = xe;
        txt.a.ye = ys + wnd->title.height - 1;
        txt.align = wnd->title.align;
        txt.h_space = wnd->title.h_space;
        txt.v_space = wnd->title.v_space;
        _PutText(&txt);

        /* Draw line */
        DrawLine(xs, ys + wnd->title.height, xe, ys + wnd->title.height,
                 pal_window[11]);
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

void uGUI::_WindowUpdate(WINDOW* wnd)
{
    uint16_t i, objcnt;
    OBJECT* obj;
    int16_t xs, ys, xe, ye;

    xs = wnd->xs;
    ys = wnd->ys;
    xe = wnd->xe;
    ye = wnd->ye;

    wnd->state &= ~WND_STATE_UPDATE;
    /* Is the window visible? */
    if (wnd->state & WND_STATE_VISIBLE)
    {
        /* 3D style? */
        if ((wnd->style & WND_STYLE_3D)
                && !(wnd->state & WND_STATE_REDRAW_TITLE))
        {
            _DrawObjectFrame(xs, ys, xe, ye, (UG_COLOR*) pal_window);
            xs += 3;
            ys += 3;
            xe -= 3;
            ye -= 3;
        }
        /* Show title bar? */
        if (wnd->style & WND_STYLE_SHOW_TITLE)
        {
            _WindowDrawTitle(wnd);
            ys += wnd->title.height + 1;
            if (wnd->state & WND_STATE_REDRAW_TITLE)
            {
                wnd->state &= ~WND_STATE_REDRAW_TITLE;
                return;
            }
        }
        /* Draw window area? */
        FillFrame(xs, ys, xe, ye, wnd->bc);

        /* Force each object to be updated! */
        objcnt = wnd->objcnt;
        for (i = 0; i < objcnt; i++)
        {
            obj = (OBJECT*) &wnd->objlst[i];
            if (!(obj->state & OBJ_STATE_FREE) && (obj->state & OBJ_STATE_VALID)
                    && (obj->state & OBJ_STATE_VISIBLE))
                obj->state |= (OBJ_STATE_UPDATE | OBJ_STATE_REDRAW);
        }
    }
    else
    {
        FillFrame(wnd->xs, wnd->xs, wnd->xe, wnd->ye, _desktop_color);
    }
}

UG_RESULT uGUI::_WindowClear(WINDOW* wnd)
{
    if (wnd != nullptr)
    {
        if (wnd->state & WND_STATE_VISIBLE)
        {
            wnd->state &= ~WND_STATE_VISIBLE;
            FillFrame(wnd->xs, wnd->ys, wnd->xe, wnd->ye, _desktop_color);

            if (wnd != _active_window)
            {
                /* If the current window is visible, update it! */
                if (_active_window->state & WND_STATE_VISIBLE)
                {
                    _active_window->state &= ~WND_STATE_REDRAW_TITLE;
                    _active_window->state |= WND_STATE_UPDATE;
                }
            }
        }
        return UG_RESULT_OK;
    }
    return UG_RESULT_FAIL;
}

/* -------------------------------------------------------------------------------- */
/* -- BUTTON FUNCTIONS                                                           -- */
/* -------------------------------------------------------------------------------- */
UG_RESULT uGUI::ButtonCreate(WINDOW* wnd, BUTTON* btn, uint8_t id, int16_t xs,
                             int16_t ys, int16_t xe, int16_t ye)
{
    OBJECT* obj;

    obj = _GetFreeObject(wnd);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    /* Initialize object-specific parameters */
    btn->state = BTN_STATE_RELEASED;
    btn->bc = wnd->bc;
    btn->fc = wnd->fc;
    btn->abc = wnd->bc;
    btn->afc = wnd->fc;
    btn->style = BTN_STYLE_3D;
    btn->font = nullptr;
    btn->str = (char *) "-";

    /* Initialize standard object parameters */
    obj->update = uGUI::_ButtonUpdate;
    obj->touch_state = OBJ_TOUCH_STATE_INIT;
    obj->type = OBJ_TYPE_BUTTON;
    obj->event = OBJ_EVENT_NONE;
    obj->a_rel.xs = xs;
    obj->a_rel.ys = ys;
    obj->a_rel.xe = xe;
    obj->a_rel.ye = ye;
    obj->a_abs.xs = -1;
    obj->a_abs.ys = -1;
    obj->a_abs.xe = -1;
    obj->a_abs.ye = -1;
    obj->id = id;
    obj->state |= OBJ_STATE_VISIBLE | OBJ_STATE_REDRAW | OBJ_STATE_VALID
            | OBJ_STATE_TOUCH_ENABLE;
    obj->data = (void*) btn;

    /* Update function: Do your thing! */
    obj->state &= ~OBJ_STATE_FREE;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::ButtonDelete(WINDOW* wnd, uint8_t id)
{
    return _DeleteObject(wnd, OBJ_TYPE_BUTTON, id);
}

UG_RESULT uGUI::ButtonShow(WINDOW* wnd, uint8_t id)
{
    OBJECT* obj = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_BUTTON, id);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    obj->state |= OBJ_STATE_VISIBLE;
    obj->state |= OBJ_STATE_UPDATE | OBJ_STATE_REDRAW;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::ButtonHide(WINDOW* wnd, uint8_t id)
{
    OBJECT* obj = nullptr;
    BUTTON* btn = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_BUTTON, id);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    btn = (BUTTON*) (obj->data);

    btn->state &= ~BTN_STATE_PRESSED;
    obj->touch_state = OBJ_TOUCH_STATE_INIT;
    obj->event = OBJ_EVENT_NONE;
    obj->state &= ~OBJ_STATE_VISIBLE;
    obj->state |= OBJ_STATE_UPDATE;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::ButtonSetForeColor(WINDOW* wnd, uint8_t id, UG_COLOR fc)
{
    OBJECT* obj = nullptr;
    BUTTON* btn = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_BUTTON, id);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    btn = (BUTTON*) (obj->data);
    btn->fc = fc;
    obj->state |= OBJ_STATE_UPDATE | OBJ_STATE_REDRAW;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::ButtonSetBackColor(WINDOW* wnd, uint8_t id, UG_COLOR bc)
{
    OBJECT* obj = nullptr;
    BUTTON* btn = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_BUTTON, id);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    btn = (BUTTON*) (obj->data);
    btn->bc = bc;
    obj->state |= OBJ_STATE_UPDATE | OBJ_STATE_REDRAW;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::ButtonSetAlternateForeColor(WINDOW* wnd, uint8_t id,
                                            UG_COLOR afc)
{
    OBJECT* obj = nullptr;
    BUTTON* btn = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_BUTTON, id);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    btn = (BUTTON*) (obj->data);
    btn->afc = afc;
    obj->state |= OBJ_STATE_UPDATE | OBJ_STATE_REDRAW;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::ButtonSetAlternateBackColor(WINDOW* wnd, uint8_t id,
                                            UG_COLOR abc)
{
    OBJECT* obj = nullptr;
    BUTTON* btn = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_BUTTON, id);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    btn = (BUTTON*) (obj->data);
    btn->abc = abc;
    obj->state |= OBJ_STATE_UPDATE | OBJ_STATE_REDRAW;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::ButtonSetText(WINDOW* wnd, uint8_t id, char* str)
{
    OBJECT* obj = nullptr;
    BUTTON* btn = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_BUTTON, id);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    btn = (BUTTON*) (obj->data);
    btn->str = str;
    obj->state |= OBJ_STATE_UPDATE | OBJ_STATE_REDRAW;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::ButtonSetFont(WINDOW* wnd, uint8_t id, const FONT* font)
{
    OBJECT* obj = nullptr;
    BUTTON* btn = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_BUTTON, id);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    btn = (BUTTON*) (obj->data);
    btn->font = font;
    obj->state |= OBJ_STATE_UPDATE | OBJ_STATE_REDRAW;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::ButtonSetStyle(WINDOW* wnd, uint8_t id, uint8_t style)
{
    OBJECT* obj = nullptr;
    BUTTON* btn = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_BUTTON, id);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    btn = (BUTTON*) (obj->data);

    /* Select color scheme */
    btn->style &= ~(BTN_STYLE_USE_ALTERNATE_COLORS | BTN_STYLE_TOGGLE_COLORS);
    btn->state |= BTN_STATE_ALWAYS_REDRAW;
    if (style & BTN_STYLE_TOGGLE_COLORS)
    {
        btn->style |= BTN_STYLE_TOGGLE_COLORS;
    }
    else if (style & BTN_STYLE_USE_ALTERNATE_COLORS)
    {
        btn->style |= BTN_STYLE_USE_ALTERNATE_COLORS;
    }
    else
    {
        btn->state &= ~BTN_STATE_ALWAYS_REDRAW;
    }

    /* 3D or 2D */
    if (style & BTN_STYLE_3D)
    {
        btn->style |= BTN_STYLE_3D;
    }
    else
    {
        btn->style &= ~BTN_STYLE_3D;
    }
    obj->state |= OBJ_STATE_UPDATE | OBJ_STATE_REDRAW;

    return UG_RESULT_OK;
}

UG_COLOR uGUI::ButtonGetForeColor(WINDOW* wnd, uint8_t id)
{
    OBJECT* obj = nullptr;
    BUTTON* btn = nullptr;
    UG_COLOR c = C_BLACK;

    obj = _SearchObject(wnd, OBJ_TYPE_BUTTON, id);
    if (obj != nullptr)
    {
        btn = (BUTTON*) (obj->data);
        c = btn->fc;
    }
    return c;
}

UG_COLOR uGUI::ButtonGetBackColor(WINDOW* wnd, uint8_t id)
{
    OBJECT* obj = nullptr;
    BUTTON* btn = nullptr;
    UG_COLOR c = C_BLACK;

    obj = _SearchObject(wnd, OBJ_TYPE_BUTTON, id);
    if (obj != nullptr)
    {
        btn = (BUTTON*) (obj->data);
        c = btn->bc;
    }
    return c;
}

UG_COLOR uGUI::ButtonGetAlternateForeColor(WINDOW* wnd, uint8_t id)
{
    OBJECT* obj = nullptr;
    BUTTON* btn = nullptr;
    UG_COLOR c = C_BLACK;

    obj = _SearchObject(wnd, OBJ_TYPE_BUTTON, id);
    if (obj != nullptr)
    {
        btn = (BUTTON*) (obj->data);
        c = btn->afc;
    }
    return c;
}

UG_COLOR uGUI::ButtonGetAlternateBackColor(WINDOW* wnd, uint8_t id)
{
    OBJECT* obj = nullptr;
    BUTTON* btn = nullptr;
    UG_COLOR c = C_BLACK;

    obj = _SearchObject(wnd, OBJ_TYPE_BUTTON, id);
    if (obj != nullptr)
    {
        btn = (BUTTON*) (obj->data);
        c = btn->abc;
    }
    return c;
}

char* uGUI::ButtonGetText(WINDOW* wnd, uint8_t id)
{
    OBJECT* obj = nullptr;
    BUTTON* btn = nullptr;
    char* str = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_BUTTON, id);
    if (obj != nullptr)
    {
        btn = (BUTTON*) (obj->data);
        str = btn->str;
    }
    return str;
}

uGUI::FONT * uGUI::ButtonGetFont(WINDOW* wnd, uint8_t id)
{
    OBJECT* obj = nullptr;
    BUTTON* btn = nullptr;
    FONT* font = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_BUTTON, id);
    if (obj != nullptr)
    {
        btn = (BUTTON*) (obj->data);
        font = (FONT*) btn->font;
    }
    return font;
}

uint8_t uGUI::ButtonGetStyle(WINDOW* wnd, uint8_t id)
{
    OBJECT* obj = nullptr;
    BUTTON* btn = nullptr;
    uint8_t style = 0;

    obj = _SearchObject(wnd, OBJ_TYPE_BUTTON, id);
    if (obj != nullptr)
    {
        btn = (BUTTON*) (obj->data);
        style = btn->style;
    }
    return style;
}

void uGUI::_ButtonUpdate(uGUI * gui, WINDOW* wnd, OBJECT* obj)
{
    BUTTON* btn;
    AREA a;
    TEXT txt;
    uint8_t d;

    /* Get object-specific data */
    btn = (BUTTON*) (obj->data);

    /* -------------------------------------------------- */
    /* Object touch section                               */
    /* -------------------------------------------------- */
    if ((obj->touch_state & OBJ_TOUCH_STATE_CHANGED))
    {
        /* Handle 'click' event */
        if (obj->touch_state & OBJ_TOUCH_STATE_CLICK_ON_OBJECT)
        {
            obj->event = BTN_EVENT_CLICKED;
            obj->state |= OBJ_STATE_UPDATE;
        }
        /* Is the button pressed down? */
        if (obj->touch_state & OBJ_TOUCH_STATE_PRESSED_ON_OBJECT)
        {
            btn->state |= BTN_STATE_PRESSED;
            obj->state |= OBJ_STATE_UPDATE;
        }
        /* Can we release the button? */
        else if (btn->state & BTN_STATE_PRESSED)
        {
            btn->state &= ~BTN_STATE_PRESSED;
            obj->state |= OBJ_STATE_UPDATE;
        }
        obj->touch_state &= ~OBJ_TOUCH_STATE_CHANGED;
    }

    /* -------------------------------------------------- */
    /* Object update section                              */
    /* -------------------------------------------------- */
    if (obj->state & OBJ_STATE_UPDATE)
    {
        if (obj->state & OBJ_STATE_VISIBLE)
        {
            /* Full redraw necessary? */
            if ((obj->state & OBJ_STATE_REDRAW)
                    || (btn->state & BTN_STATE_ALWAYS_REDRAW))
            {
                gui->WindowGetArea(wnd, &a);
                obj->a_abs.xs = obj->a_rel.xs + a.xs;
                obj->a_abs.ys = obj->a_rel.ys + a.ys;
                obj->a_abs.xe = obj->a_rel.xe + a.xs;
                obj->a_abs.ye = obj->a_rel.ye + a.ys;
                if (obj->a_abs.ye >= wnd->ye)
                    return;
                if (obj->a_abs.xe >= wnd->xe)
                    return;

                /* 3D or 2D style? */
                d = (btn->style & BTN_STYLE_3D) ? 3 : 1;

                txt.bc = btn->bc;
                txt.fc = btn->fc;

                if (btn->state & BTN_STATE_PRESSED)
                {
                    /* "toggle" style? */
                    if (btn->style & BTN_STYLE_TOGGLE_COLORS)
                    {
                        /* Swap colors */
                        txt.bc = btn->fc;
                        txt.fc = btn->bc;
                    }
                    /* Use alternate colors? */
                    else if (btn->style & BTN_STYLE_USE_ALTERNATE_COLORS)
                    {
                        txt.bc = btn->abc;
                        txt.fc = btn->afc;
                    }
                }
                gui->FillFrame(obj->a_abs.xs + d, obj->a_abs.ys + d,
                               obj->a_abs.xe - d, obj->a_abs.ye - d, txt.bc);

                /* Draw button text */
                txt.a.xs = obj->a_abs.xs + d;
                txt.a.ys = obj->a_abs.ys + d;
                txt.a.xe = obj->a_abs.xe - d;
                txt.a.ye = obj->a_abs.ye - d;
                txt.align = ALIGN_CENTER;
                txt.font = btn->font;
                txt.h_space = 2;
                txt.v_space = 2;
                txt.str = btn->str;
                gui->_PutText(&txt);
                obj->state &= ~OBJ_STATE_REDRAW;
            }
            /* Draw button frame */
            if (btn->style & BTN_STYLE_3D)
            { /* 3D */
                gui->_DrawObjectFrame(
                        obj->a_abs.xs,
                        obj->a_abs.ys,
                        obj->a_abs.xe,
                        obj->a_abs.ye,
                        (btn->state & BTN_STATE_PRESSED) ?
                                (UG_COLOR*) pal_button_pressed :
                                (UG_COLOR*) pal_button_released);
            }
            else
            { /* 2D */
                gui->DrawFrame(
                        obj->a_abs.xs, obj->a_abs.ys, obj->a_abs.xe,
                        obj->a_abs.ye,
                        (btn->state & BTN_STATE_PRESSED) ? btn->abc : btn->afc);
            }
        }
        else
        {
            gui->FillFrame(obj->a_abs.xs, obj->a_abs.ys, obj->a_abs.xe,
                           obj->a_abs.ye, wnd->bc);
        }
        obj->state &= ~OBJ_STATE_UPDATE;
    }
}

/* -------------------------------------------------------------------------------- */
/* -- TEXTBOX FUNCTIONS                                                          -- */
/* -------------------------------------------------------------------------------- */
UG_RESULT uGUI::TextboxCreate(WINDOW* wnd, TEXTBOX* txb, uint8_t id, int16_t xs,
                              int16_t ys, int16_t xe, int16_t ye)
{
    OBJECT* obj;

    obj = _GetFreeObject(wnd);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    /* Initialize object-specific parameters */
    txb->str = nullptr;
    txb->font = nullptr;
    txb->style = 0; /* reserved */
    txb->fc = wnd->fc;
    txb->bc = wnd->bc;
    txb->align = ALIGN_CENTER;
    txb->h_space = 2;
    txb->v_space = 2;

    /* Initialize standard object parameters */
    obj->update = &uGUI::_TextboxUpdate;
    obj->touch_state = OBJ_TOUCH_STATE_INIT;
    obj->type = OBJ_TYPE_TEXTBOX;
    obj->event = OBJ_EVENT_NONE;
    obj->a_rel.xs = xs;
    obj->a_rel.ys = ys;
    obj->a_rel.xe = xe;
    obj->a_rel.ye = ye;
    obj->a_abs.xs = -1;
    obj->a_abs.ys = -1;
    obj->a_abs.xe = -1;
    obj->a_abs.ye = -1;
    obj->id = id;
    obj->state |= OBJ_STATE_VISIBLE | OBJ_STATE_REDRAW | OBJ_STATE_VALID;
    obj->data = (void*) txb;

    /* Update function: Do your thing! */
    obj->state &= ~OBJ_STATE_FREE;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::TextboxDelete(WINDOW* wnd, uint8_t id)
{
    return _DeleteObject(wnd, OBJ_TYPE_TEXTBOX, id);
}

UG_RESULT uGUI::TextboxShow(WINDOW* wnd, uint8_t id)
{
    OBJECT* obj = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_TEXTBOX, id);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    obj->state |= OBJ_STATE_VISIBLE;
    obj->state |= OBJ_STATE_UPDATE | OBJ_STATE_REDRAW;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::TextboxHide(WINDOW* wnd, uint8_t id)
{
    OBJECT* obj = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_TEXTBOX, id);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    obj->state &= ~OBJ_STATE_VISIBLE;
    obj->state |= OBJ_STATE_UPDATE;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::TextboxSetForeColor(WINDOW* wnd, uint8_t id, UG_COLOR fc)
{
    OBJECT* obj = nullptr;
    TEXTBOX* txb = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_TEXTBOX, id);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    txb = (TEXTBOX*) (obj->data);
    txb->fc = fc;
    obj->state |= OBJ_STATE_UPDATE | OBJ_STATE_REDRAW;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::TextboxSetBackColor(WINDOW* wnd, uint8_t id, UG_COLOR bc)
{
    OBJECT* obj = nullptr;
    TEXTBOX* txb = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_TEXTBOX, id);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    txb = (TEXTBOX*) (obj->data);
    txb->bc = bc;
    obj->state |= OBJ_STATE_UPDATE | OBJ_STATE_REDRAW;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::TextboxSetText(WINDOW* wnd, uint8_t id, char* str)
{
    OBJECT* obj = nullptr;
    TEXTBOX* txb = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_TEXTBOX, id);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    txb = (TEXTBOX*) (obj->data);
    txb->str = str;
    obj->state |= OBJ_STATE_UPDATE | OBJ_STATE_REDRAW;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::TextboxSetFont(WINDOW* wnd, uint8_t id, const FONT* font)
{
    OBJECT* obj = nullptr;
    TEXTBOX* txb = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_TEXTBOX, id);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    txb = (TEXTBOX*) (obj->data);
    txb->font = font;
    obj->state |= OBJ_STATE_UPDATE | OBJ_STATE_REDRAW;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::TextboxSetHSpace(WINDOW* wnd, uint8_t id, int8_t hs)
{
    OBJECT* obj = nullptr;
    TEXTBOX* txb = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_TEXTBOX, id);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    txb = (TEXTBOX*) (obj->data);
    txb->h_space = hs;
    obj->state |= OBJ_STATE_UPDATE | OBJ_STATE_REDRAW;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::TextboxSetVSpace(WINDOW* wnd, uint8_t id, int8_t vs)
{
    OBJECT* obj = nullptr;
    TEXTBOX* txb = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_TEXTBOX, id);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    txb = (TEXTBOX*) (obj->data);
    txb->v_space = vs;
    obj->state |= OBJ_STATE_UPDATE | OBJ_STATE_REDRAW;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::TextboxSetAlignment(WINDOW* wnd, uint8_t id, uint8_t align)
{
    OBJECT* obj = nullptr;
    TEXTBOX* txb = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_TEXTBOX, id);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    txb = (TEXTBOX*) (obj->data);
    txb->align = align;
    obj->state |= OBJ_STATE_UPDATE | OBJ_STATE_REDRAW;

    return UG_RESULT_OK;
}

UG_COLOR uGUI::TextboxGetForeColor(WINDOW* wnd, uint8_t id)
{
    OBJECT* obj = nullptr;
    TEXTBOX* txb = nullptr;
    UG_COLOR c = C_BLACK;

    obj = _SearchObject(wnd, OBJ_TYPE_TEXTBOX, id);
    if (obj != nullptr)
    {
        txb = (TEXTBOX*) (obj->data);
        c = txb->fc;
    }
    return c;
}

UG_COLOR uGUI::TextboxGetBackColor(WINDOW* wnd, uint8_t id)
{
    OBJECT* obj = nullptr;
    TEXTBOX* txb = nullptr;
    UG_COLOR c = C_BLACK;

    obj = _SearchObject(wnd, OBJ_TYPE_TEXTBOX, id);
    if (obj != nullptr)
    {
        txb = (TEXTBOX*) (obj->data);
        c = txb->bc;
    }
    return c;
}

char* uGUI::TextboxGetText(WINDOW* wnd, uint8_t id)
{
    OBJECT* obj = nullptr;
    TEXTBOX* txb = nullptr;
    char* str = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_TEXTBOX, id);
    if (obj != nullptr)
    {
        txb = (TEXTBOX*) (obj->data);
        str = txb->str;
    }
    return str;
}

uGUI::FONT* uGUI::TextboxGetFont(WINDOW* wnd, uint8_t id)
{
    OBJECT* obj = nullptr;
    TEXTBOX* txb = nullptr;
    FONT* font = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_TEXTBOX, id);
    if (obj != nullptr)
    {
        txb = (TEXTBOX*) (obj->data);
        font = (FONT*) txb->font;
    }
    return font;
}

int8_t uGUI::TextboxGetHSpace(WINDOW* wnd, uint8_t id)
{
    OBJECT* obj = nullptr;
    TEXTBOX* txb = nullptr;
    int8_t hs = 0;

    obj = _SearchObject(wnd, OBJ_TYPE_TEXTBOX, id);
    if (obj != nullptr)
    {
        txb = (TEXTBOX*) (obj->data);
        hs = txb->h_space;
    }
    return hs;
}

int8_t uGUI::TextboxGetVSpace(WINDOW* wnd, uint8_t id)
{
    OBJECT* obj = nullptr;
    TEXTBOX* txb = nullptr;
    int8_t vs = 0;

    obj = _SearchObject(wnd, OBJ_TYPE_TEXTBOX, id);
    if (obj != nullptr)
    {
        txb = (TEXTBOX*) (obj->data);
        vs = txb->v_space;
    }
    return vs;
}

uint8_t uGUI::TextboxGetAlignment(WINDOW* wnd, uint8_t id)
{
    OBJECT* obj = nullptr;
    TEXTBOX* txb = nullptr;
    uint8_t align = 0;

    obj = _SearchObject(wnd, OBJ_TYPE_TEXTBOX, id);
    if (obj != nullptr)
    {
        txb = (TEXTBOX*) (obj->data);
        align = txb->align;
    }
    return align;
}

void uGUI::_TextboxUpdate(uGUI *gui, WINDOW* wnd, OBJECT* obj)
{
    TEXTBOX* txb;
    AREA a;
    TEXT txt;

    /* Get object-specific data */
    txb = (TEXTBOX*) (obj->data);

    /* -------------------------------------------------- */
    /* Object touch section                               */
    /* -------------------------------------------------- */

    /* Textbox doesn't support touch */

    /* -------------------------------------------------- */
    /* Object update section                              */
    /* -------------------------------------------------- */
    if (obj->state & OBJ_STATE_UPDATE)
    {
        if (obj->state & OBJ_STATE_VISIBLE)
        {
            /* Full redraw necessary? */
            if (obj->state & OBJ_STATE_REDRAW)
            {
                gui->WindowGetArea(wnd, &a);
                obj->a_abs.xs = obj->a_rel.xs + a.xs;
                obj->a_abs.ys = obj->a_rel.ys + a.ys;
                obj->a_abs.xe = obj->a_rel.xe + a.xs;
                obj->a_abs.ye = obj->a_rel.ye + a.ys;
                if (obj->a_abs.ye >= wnd->ye)
                    return;
                if (obj->a_abs.xe >= wnd->xe)
                    return;

                txt.bc = txb->bc;
                txt.fc = txb->fc;

                gui->FillFrame(obj->a_abs.xs, obj->a_abs.ys, obj->a_abs.xe,
                               obj->a_abs.ye, txt.bc);

                /* Draw Textbox text */
                txt.a.xs = obj->a_abs.xs;
                txt.a.ys = obj->a_abs.ys;
                txt.a.xe = obj->a_abs.xe;
                txt.a.ye = obj->a_abs.ye;
                txt.align = txb->align;
                txt.font = txb->font;
                txt.h_space = txb->h_space;
                txt.v_space = txb->v_space;
                txt.str = txb->str;
                gui->_PutText(&txt);
                obj->state &= ~OBJ_STATE_REDRAW;
            }
        }
        else
        {
            gui->FillFrame(obj->a_abs.xs, obj->a_abs.ys, obj->a_abs.xe,
                           obj->a_abs.ye, wnd->bc);
        }
        obj->state &= ~OBJ_STATE_UPDATE;
    }
}

/* -------------------------------------------------------------------------------- */
/* -- IMAGE FUNCTIONS                                                            -- */
/* -------------------------------------------------------------------------------- */
UG_RESULT uGUI::ImageCreate(WINDOW* wnd, IMAGE* img, uint8_t id, int16_t xs,
                            int16_t ys, int16_t xe, int16_t ye)
{
    OBJECT* obj;

    obj = _GetFreeObject(wnd);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    /* Initialize object-specific parameters */
    img->img = nullptr;
    img->type = IMG_TYPE_BMP;

    /* Initialize standard object parameters */
    obj->update = uGUI::_ImageUpdate;
    obj->touch_state = OBJ_TOUCH_STATE_INIT;
    obj->type = OBJ_TYPE_IMAGE;
    obj->event = OBJ_EVENT_NONE;
    obj->a_rel.xs = xs;
    obj->a_rel.ys = ys;
    obj->a_rel.xe = xe;
    obj->a_rel.ye = ye;
    obj->a_abs.xs = -1;
    obj->a_abs.ys = -1;
    obj->a_abs.xe = -1;
    obj->a_abs.ye = -1;
    obj->id = id;
    obj->state |= OBJ_STATE_VISIBLE | OBJ_STATE_REDRAW | OBJ_STATE_VALID;
    obj->data = (void*) img;

    /* Update function: Do your thing! */
    obj->state &= ~OBJ_STATE_FREE;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::ImageDelete(WINDOW* wnd, uint8_t id)
{
    return _DeleteObject(wnd, OBJ_TYPE_IMAGE, id);
}

UG_RESULT uGUI::ImageShow(WINDOW* wnd, uint8_t id)
{
    OBJECT* obj = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_IMAGE, id);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    obj->state |= OBJ_STATE_VISIBLE;
    obj->state |= OBJ_STATE_UPDATE | OBJ_STATE_REDRAW;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::ImageHide(WINDOW* wnd, uint8_t id)
{
    OBJECT* obj = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_IMAGE, id);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    obj->state &= ~OBJ_STATE_VISIBLE;
    obj->state |= OBJ_STATE_UPDATE;

    return UG_RESULT_OK;
}

UG_RESULT uGUI::ImageSetBMP(WINDOW* wnd, uint8_t id, const BMP* bmp)
{
    OBJECT* obj = nullptr;
    IMAGE* img = nullptr;

    obj = _SearchObject(wnd, OBJ_TYPE_IMAGE, id);
    if (obj == nullptr)
        return UG_RESULT_FAIL;

    img = (IMAGE*) (obj->data);
    img->img = (void*) bmp;
    img->type = IMG_TYPE_BMP;
    obj->state |= OBJ_STATE_UPDATE | OBJ_STATE_REDRAW;

    return UG_RESULT_OK;
}

void uGUI::_ImageUpdate(uGUI * gui, WINDOW* wnd, OBJECT* obj)
{
    IMAGE* img;
    AREA a;

    /* Get object-specific data */
    img = (IMAGE*) (obj->data);

    /* -------------------------------------------------- */
    /* Object touch section                               */
    /* -------------------------------------------------- */

    /* Image doesn't support touch */

    /* -------------------------------------------------- */
    /* Object update section                              */
    /* -------------------------------------------------- */
    if (obj->state & OBJ_STATE_UPDATE)
    {
        if (obj->state & OBJ_STATE_VISIBLE)
        {
            /* Full redraw necessary? */
            if (obj->state & OBJ_STATE_REDRAW)
            {
                gui->WindowGetArea(wnd, &a);
                /* ToDo: more/better image features */
                obj->a_abs.xs = obj->a_rel.xs + a.xs;
                obj->a_abs.ys = obj->a_rel.ys + a.ys;
                obj->a_abs.xe = obj->a_rel.xs + ((BMP*) img->img)->width + a.xs;
                obj->a_abs.ye = obj->a_rel.ys + ((BMP*) img->img)->height
                        + a.ys;
                if (obj->a_abs.ye >= wnd->ye)
                    return;
                if (obj->a_abs.xe >= wnd->xe)
                    return;

                /* Draw Image */
                if ((img->img != nullptr) && (img->type & IMG_TYPE_BMP))
                {
                    gui->DrawBMP(obj->a_abs.xs, obj->a_abs.ys, (BMP*) img->img);
                }

                obj->state &= ~OBJ_STATE_REDRAW;
            }
        }
        else
        {
            gui->FillFrame(obj->a_abs.xs, obj->a_abs.ys, obj->a_abs.xe,
                           obj->a_abs.ye, wnd->bc);
        }
        obj->state &= ~OBJ_STATE_UPDATE;
    }
}


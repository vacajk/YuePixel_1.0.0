/*******************************************************
 * 函数名：showCharacter
 * 描述  ：显示单个字符
 * 参数  ：
 *        @char_x     字符左上角x坐标
 *        @char_y     字符左上角y坐标
 *        @c          字符编码
 *        @charfont   字体
 * 返回值：无
 **********************************************************/
void showCharacter(int char_x, int char_y, int c, int charfont)
{
    int i, x, y, characterSpace;
    unsigned char line;
    unsigned short ct;

    const unsigned char *cb = fontattribute[charfont].font_bitmap;
    const unsigned char *ci = fontattribute[charfont].font_index;
    int len = fontattribute[charfont].font_num;
    int lx = fontattribute[charfont].font_width;
    int ly = fontattribute[charfont].font_height;

    if (charfont == Cnfont8x8 && c > 0xFF) //中文字体中的非英文字体
        ct = cn_utf8_to_unicode(c);
    else
        ct = (unsigned short)c;

    for (i = 0; i < len; i++)
    {
        if (charfont == Cnfont8x8) //中文编码为8字节，不方便用放flash，内存充足，因此放内存中。
        {
            if (Cnfont_index[i] == ct)
            {
                characterSpace = i;
                break;
            }
        }
        else
        {
            if (pgm_read_byte(ci + i) == ct) // ci[i] == ct
            {
                characterSpace = i;
                break;
            }
        }
    }
    if (i == len)
        characterSpace = 1; //空白符

    for (y = 0; y < ly; y++)
    {
        // line = cb[ly * characterSpace + y];
        line = pgm_read_byte(cb + (ly * characterSpace + y));
        for (x = lx - 1; x >= 0; x--)
        {
            if (((line >> (7 - x)) & 0x01) == 0 && XYsafe(char_x + x, char_y + y) != (uint16_t)-1)
            {
                leds_font[XYsafe(char_x + x, char_y + y)] = CRGB(0, 0, 0);
            }
        }
    }

    for (y = 0; y < ly; y++)
    {
        for (x = 0; x < lx; x++)
        {
            if (XYsafe(char_x + x, char_y + y) != (uint16_t)-1 && leds_font[XYsafe(char_x + x, char_y + y)] != CRGB(0, 0, 0)) //顺序不能换
            {
                leds[XYsafe(char_x + x, char_y + y)] = leds_font[XYsafe(char_x + x, char_y + y)];
            }
        }
    }
}

/*******************************************************
 * 函数名：characterTest
 * 描述  ：字符显示测试
 * 参数  ：无
 * 返回值：无
 **********************************************************/
void characterTest()
{
    int i;
    Serial.println("Show Char");
    for (i = 0; i < 58; i++)
    {
        fill_solid(leds_font, 64, CRGB::Green);
        fill_solid(leds, 64, CRGB::Black);
        showCharacter(0, 0, 'A' + i, Pix5x7);
        FastLED.show();
        delay(500);
    }
}

/*******************************************************
 * 函数名：showStringSlip
 * 描述  ：滚动显示字符串
 * 参数  ：
 *        @char_x     字符串起始左上角x坐标
 *        @char_y     字符串起始左上角y坐标
 *        @str        字符串
 *        @len        字符串长度
 * 返回值：无
 **********************************************************/
void showStringSlip(int char_x, int char_y, char *str, int len)
{
    int j;

    if (count > (strslipconfig.strspeed/20))
    {
        if(wordshow_i == pix_l)
        {
            wordshow_i = 0;
        }
        cnstr_p = 0;
        switch (strslipconfig.bg_color_func)
        {
        case SolidColor:
            fill_solid(strslipconfig.bg_sc_var.leds, strslipconfig.bg_sc_var.numToFill, strslipconfig.bg_sc_var.color);
            break;
        case RainbowColor:
            fill_rainbow(strslipconfig.bg_rc_var.pFirstLED, strslipconfig.bg_rc_var.numToFill, strslipconfig.bg_rc_var.initialhue, strslipconfig.bg_rc_var.deltahue);
            break;
        case GradiantColor:
            fill_gradient_RGB(strslipconfig.bg_gc_var.leds, strslipconfig.bg_gc_var.startpos, strslipconfig.bg_gc_var.startcolor, strslipconfig.bg_gc_var.endpos, strslipconfig.bg_gc_var.endcolor);
            break;
        case PaletteColor:
            fill_palette(strslipconfig.bg_pc_var.L, strslipconfig.bg_pc_var.N, strslipconfig.bg_pc_var.startIndex, strslipconfig.bg_pc_var.incIndex, strslipconfig.bg_pc_var.pal, strslipconfig.bg_pc_var.brightness, strslipconfig.bg_pc_var.blendType);
            break;
        default:
            break;
        }
        for (j = 0; j < len_t; j++)
        {
            switch (strslipconfig.font_color_func)
            {
            case SolidColor:
                fill_solid(strslipconfig.font_sc_var.leds, strslipconfig.font_sc_var.numToFill, strslipconfig.font_sc_var.color);
                break;
            case RainbowColor:
                fill_rainbow(strslipconfig.font_rc_var.pFirstLED, strslipconfig.font_rc_var.numToFill, strslipconfig.font_rc_var.initialhue, strslipconfig.font_rc_var.deltahue);
                break;
            case GradiantColor:
                fill_gradient_RGB(strslipconfig.font_gc_var.leds, strslipconfig.font_gc_var.startpos, strslipconfig.font_gc_var.startcolor, strslipconfig.font_gc_var.endpos, strslipconfig.font_gc_var.endcolor);
                break;
            case PaletteColor:
                fill_palette(strslipconfig.font_pc_var.L, strslipconfig.font_pc_var.N, strslipconfig.font_pc_var.startIndex, strslipconfig.font_pc_var.incIndex, strslipconfig.font_pc_var.pal, strslipconfig.font_pc_var.brightness, strslipconfig.font_pc_var.blendType);
                break;
            default:
                break;
            }
            if (strslipconfig.cfont == Cnfont8x8)
            {
                if (cnstr_type[j] == 1)
                {
                    showCharacter(char_x - wordshow_i + cnstr_pos[j], char_y, (int)((str[cnstr_p] << 16) + (str[cnstr_p + 1] << 8) + str[cnstr_p + 2]), strslipconfig.cfont);
                    cnstr_p += 3; //一个中文字符3字节
                }
                else
                {
                    showCharacter(char_x - wordshow_i + cnstr_pos[j], char_y, (int)str[cnstr_p], strslipconfig.cfont);
                    cnstr_p += 1; //一个英文字符1字节
                }
            }
            else
                showCharacter(char_x - wordshow_i + j * strslipconfig.cspace, char_y, str[j], strslipconfig.cfont);
        }
        FastLED.show();
        wordshow_i++;
        count = 0;
    }
}

/*******************************************************
 * 函数名：strsliptest
 * 描述  ：滚动显示英文字符串测试
 * 参数  ：无
 * 返回值：无
 **********************************************************/
void strsliptest()
{
    //字符太多会出现bug
    char str[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ   "; //"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz   ";
    int i, j;
    for (i = 5; i >= 0; i--)
    {
        strslipconfig.cfont = i;
        strslipconfig.cspace = fontattribute[i].font_test_space;
        // for (j = 0; j < 4; j++)
        // {
        strslipconfig.font_color_func = SolidColor; // j
        setSlipStrLen(str, strlen(str));
        showStringSlip(8, 0, str, strlen(str));
        // }
    }
}

/*******************************************************
 * 函数名：cnstrsliptest
 * 描述  ：滚动显示中英文字符串测试
  * 参数  ：无
 * 返回值：无
 **********************************************************/
void cnstrsliptest()
{
    //字符太多会出现bug
    char str[] = "你好世界！Hellow world!    ";
    char *p;
    strslipconfig.cfont = Cnfont8x8;
    strslipconfig.cspace = fontattribute[Cnfont8x8].font_test_space;
    strslipconfig.font_color_func = PaletteColor; // SolidColor
    // strslipconfig.font_pc_var.pal = myRedWhiteBluePalette_p;
    setSlipStrLen(str, strlen(str));
    showStringSlip(8, 0, str, strlen(str));
}

/*******************************************************
 * 函数名：showStringTwinkle
 * 描述  ：闪动显示字符串
 * 参数  ：
 *        @char_x     字符左上角x坐标
 *        @char_y     字符左上角y坐标
 *        @str        字符串
 *        @len        字符串长度
 * 返回值：无
 **********************************************************/
void showStringTwinkle(int char_x, int char_y, char *str, int len)
{
    if (count > (strstwinkleconfig.twkspeed/20))
    {
        if(wordshow_i >= len_t)
        {
            wordshow_i = 0;
            cnstr_p = 0;
        }
        
        switch (strstwinkleconfig.bg_color_func)
        {
        case SolidColor:
            fill_solid(strstwinkleconfig.bg_sc_var.leds, strstwinkleconfig.bg_sc_var.numToFill, strstwinkleconfig.bg_sc_var.color);
            break;
        case RainbowColor:
            fill_rainbow(strstwinkleconfig.bg_rc_var.pFirstLED, strstwinkleconfig.bg_rc_var.numToFill, strstwinkleconfig.bg_rc_var.initialhue, strstwinkleconfig.bg_rc_var.deltahue);
            break;
        case GradiantColor:
            fill_gradient_RGB(strstwinkleconfig.bg_gc_var.leds, strstwinkleconfig.bg_gc_var.startpos, strstwinkleconfig.bg_gc_var.startcolor, strstwinkleconfig.bg_gc_var.endpos, strstwinkleconfig.bg_gc_var.endcolor);
            break;
        case PaletteColor:
            fill_palette(strstwinkleconfig.bg_pc_var.L, strstwinkleconfig.bg_pc_var.N, strstwinkleconfig.bg_pc_var.startIndex, strstwinkleconfig.bg_pc_var.incIndex, strstwinkleconfig.bg_pc_var.pal, strstwinkleconfig.bg_pc_var.brightness, strstwinkleconfig.bg_pc_var.blendType);
            break;
        default:
            break;
        }
        switch (strstwinkleconfig.font_color_func)
        {
        case SolidColor:
            fill_solid(strstwinkleconfig.font_sc_var.leds, strstwinkleconfig.font_sc_var.numToFill, strstwinkleconfig.font_sc_var.color);
            break;
        case RainbowColor:
            fill_rainbow(strstwinkleconfig.font_rc_var.pFirstLED, strstwinkleconfig.font_rc_var.numToFill, strstwinkleconfig.font_rc_var.initialhue, strstwinkleconfig.font_rc_var.deltahue);
            break;
        case GradiantColor:
            fill_gradient_RGB(strstwinkleconfig.font_gc_var.leds, strstwinkleconfig.font_gc_var.startpos, strstwinkleconfig.font_gc_var.startcolor, strstwinkleconfig.font_gc_var.endpos, strstwinkleconfig.font_gc_var.endcolor);
            break;
        case PaletteColor:
            fill_palette(strstwinkleconfig.font_pc_var.L, strstwinkleconfig.font_pc_var.N, strstwinkleconfig.font_pc_var.startIndex, strstwinkleconfig.font_pc_var.incIndex, strstwinkleconfig.font_pc_var.pal, strstwinkleconfig.font_pc_var.brightness, strstwinkleconfig.font_pc_var.blendType);
            break;
        default:
            break;
        }
        if (strstwinkleconfig.cfont == Cnfont8x8)
        {
            if (cnstr_type[wordshow_i] == 1)
            {
                showCharacter(char_x, char_y, (int)((str[cnstr_p] << 16) + (str[cnstr_p + 1] << 8) + str[cnstr_p + 2]), strstwinkleconfig.cfont);
                cnstr_p += 3;
            }
            else
            {
                showCharacter(char_x, char_y, (int)str[cnstr_p], strstwinkleconfig.cfont);
                cnstr_p += 1;
            }
        }
        else
        {
            showCharacter(char_x, char_y, str[wordshow_i], strstwinkleconfig.cfont);
        }
        FastLED.show();
        wordshow_i++;
        count = 0; 
    }
}

/*******************************************************
 * 函数名：strtwinkletest
 * 描述  ：闪动显示英文字符串测试
 * 参数  ：无
 * 返回值：无
 **********************************************************/
void strtwinkletest()
{
    char str[] = "0123456789"; //"!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"; //"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
    int i, j, x, y;
    for (i = 6; i >= 0; i--)
    {
        strstwinkleconfig.cfont = i; // i
        // for (j = 0; j < 4; j++)
        // {
        strstwinkleconfig.font_color_func = SolidColor; // j
        x = fontattribute[i].font_test_x;
        y = fontattribute[i].font_test_y;
        setTwinkleStrLen(str, strlen(str));
        showStringTwinkle(x, y, str, strlen(str));
        // }
    }
}

/*******************************************************
 * 函数名：cnstrtwinkletest
 * 描述  ：闪动显示中英文字符串测试
 * 参数  ：无
 * 返回值：无
 **********************************************************/
void cnstrtwinkletest()
{
    //字符太多会出现bug
    char str[] = "你好世界！Hellow world!";
    char *p;
    strstwinkleconfig.cfont = Cnfont8x8;
    strstwinkleconfig.twkspeed = 500;
    strstwinkleconfig.font_color_func = PaletteColor; // SolidColor
    strstwinkleconfig.font_pc_var.pal = myRedWhiteBluePalette_p;
    strstwinkleconfig.font_pc_var.incIndex = 1;
    setTwinkleStrLen(str, strlen(str));
    showStringTwinkle(0, 0, str, strlen(str));
}

/*******************************************************
 * 函数名：setSlipStrLen
 * 描述  ：获取用于滑动显示的字符串中的中英文及字符数信息
 * 参数  ：
 *        @str      字符串
 *        @len      字符串长度
 * 返回值：无
 **********************************************************/
void setSlipStrLen(char *str, int len)
{
    int i, j, cnstr_l=0;

    if (strslipconfig.cfont == Cnfont8x8)
    {
        for (i = 0, j = 0; (uint8_t)str[i] != 0 && j < 200; i++, j++)
        {
            if ((uint8_t)str[i] < 0xE0) //非中文
            {
                cnstr_type[j] = 0;
                cnstr_pos[j] = cnstr_l;
                /*  Cnfont8x8 字体中为不同字符配置不同间距，观感更好*/
                if (str[i] == '$' || str[i] == '@' || str[i] == 'M' || str[i] == 'W' || str[i] == 'm' || str[i] == 'w' || str[i] == 165)
                {
                    cnstr_l += 6;
                }
                else if (str[i] == '&' || (str[i] >= 'A' && str[i] <= 'H') || str[i] == 'K' || (str[i] >= 'N' && str[i] <= 'S') || str[i] == 'U' || str[i] == 'V' || str[i] == 'X' || str[i] == 'Y')
                {
                    cnstr_l += 5;
                }
                else if (str[i] == '0' || (str[i] >= '2' && str[i] <= '9') || str[i] == '?' || str[i] == 'J' || str[i] == 'L' || str[i] == 'T' || str[i] == 'Z' || (str[i] >= 'a' && str[i] <= 'e') || str[i] == 'g' || str[i] == 'h' || str[i] == 'j' || str[i] == 'k' || (str[i] >= 'n' && str[i] <= 's') || str[i] == 'u' || str[i] == 'v' || str[i] == 'x' || str[i] == 'y' || str[i] == 'z')
                {
                    cnstr_l += 4;
                }
                else if (str[i] == ',' || str[i] == '1' || str[i] == 'f' || str[i] == 'l' || str[i] == 't')
                {
                    cnstr_l += 3;
                }
                else if (str[i] == '!' || str[i] == '.' || str[i] == 'I' || str[i] == 'i' || str[i] == ' ')
                {
                    cnstr_l += 2;
                }
                else
                {
                    cnstr_l += 8;
                }
            }
            else //中文
            {
                cnstr_type[j] = 1;
                cnstr_pos[j] = cnstr_l;
                cnstr_l += strslipconfig.cspace;
                i += 2;
            }
        }
        cnstr_type[j] = 2;
        cnstr_pos[j] = cnstr_l;
        pix_l = cnstr_l;
        len_t = j;
    }
    else
    {
        pix_l = len * strslipconfig.cspace;
        len_t = len;
    }
    cnstr_p = 0;
}

/*******************************************************
 * 函数名：setTwinkleStrLen
 * 描述  ：获取用于闪烁显示的字符串中的中英文及字符数信息
 * 参数  ：
 *        @str      字符串
 *        @len      字符串长度
 * 返回值：无
 **********************************************************/
void setTwinkleStrLen(char *str, int len)
{
    int i, j;
    if (strstwinkleconfig.cfont == Cnfont8x8)
    {
        for (i = 0, j = 0; (uint8_t)str[i] != 0 && j < 200; i++, j++)
        {
            if ((uint8_t)str[i] < 0xE0) //非中文
            {
                cnstr_type[j] = 0;
            }
            else //中文
            {
                cnstr_type[j] = 1;
                i += 2;
            }
        }
        cnstr_type[j] = 2;
        len_t = j;
    }
    else
    {
        len_t = len;
    }
    wordshow_i=0;  
}

/*******************************************************
 * 函数名：showWords
 * 描述  ：根据设置模式显示字符串
 * 参数  ：无
 * 返回值：无
 **********************************************************/
void showWords()
{
    switch (wordShowkMode)
    {
    case 1:
        showStringSlip(8, 0, message_str, strlen(message_str));
        break;
    case 2:
        showStringTwinkle(0, 0, message_str, strlen(message_str));
        break;
    default:
        break;
    }
}

/*******************************************************
 * 函数名：ShowIP
 * 描述  ：滑动显示当前设备IP
 * 参数  ：无
 * 返回值：无
 **********************************************************/
void ShowIP()
{
    char ip[25];
    strcpy(ip, (WiFi.localIP().toString()+"  ").c_str());//"182.168.1.1  ";   //此处为c++语法
    strslipconfig.cfont = Apple5x7;
    strslipconfig.cspace = fontattribute[Apple5x7].font_test_space;
    strslipconfig.font_color_func = SolidColor;
    showStringSlip_Old(8, 0, ip, strlen(ip));
}

/*******************************************************
 * 函数名：showStringSlip_Old
 * 描述  ：滚动显示字符串，非通过计数实现
 * 参数  ：
 *        @char_x     字符串起始左上角x坐标
 *        @char_y     字符串起始左上角y坐标
 *        @str        字符串
 *        @len        字符串长度
 * 返回值：无
 **********************************************************/
void showStringSlip_Old(int char_x, int char_y, char *str, int len)
{
    int i, j;
    int len_t, pix_l, cnstr_p, cnstr_l = 0;
    int cnstr_type[200], cnstr_pos[200]; 
    //cnstr_type：Cnfont8x8 字体字符串各字符中英文类型数组，0位英文，1位中文，2结束  cnstr_pos：Cnfont8x8 字体字符串中各字符偏移像素
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
    for (i = 0; i < pix_l; i++)
    {
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
                    showCharacter(char_x - i + cnstr_pos[j], char_y, (int)((str[cnstr_p] << 16) + (str[cnstr_p + 1] << 8) + str[cnstr_p + 2]), strslipconfig.cfont);
                    cnstr_p += 3;  //一个中文字符3字节
                }
                else
                {
                    showCharacter(char_x - i + cnstr_pos[j], char_y, (int)str[cnstr_p], strslipconfig.cfont);
                    cnstr_p += 1;   //一个英文字符1字节
                }
            }
            else
                showCharacter(char_x - i + j * strslipconfig.cspace, char_y, str[j], strslipconfig.cfont);
        }
        FastLED.show();
        delay(strslipconfig.strspeed);
    }
}

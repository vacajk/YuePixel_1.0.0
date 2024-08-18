/*******************************************************
* 函数名：DrawPic
* 描述  ：依据数组设置图片
* 参数  ：
*        @pic       图片数组
*        @BgCover   是否清除背景。 1：背景清除  0：背景不清除（黑色则显示原背景）
*        @pic_x     图片左上角x坐标值
*        @pic_y     图片左上角y坐标值
*        @pic_w     图片宽度
*        @pic_h     图片高度
* 返回值：无
**********************************************************/
void DrawPic(const unsigned char pic[], bool BgCover, int pic_x, int pic_y, int pic_w, int pic_h)
{
    int x, y;
    uint8_t r, g, b;
    // 覆盖不清屏
    for (y = 0; y < pic_h; y++)
    {
        for (x = 0; x < pic_w; x++)
        {
            // 适合颜色顺序为GBR
            r = pic[3 * (y * pic_w + x)];
            g = pic[3 * (y * pic_w + x) + 1];
            b = pic[3 * (y * pic_w + x) + 2];
            if (BgCover || r || g || b)
                leds[XYsafe(pic_x + x, pic_y + y)] = CRGB(r, g, b);
        }
    }
}

/*******************************************************
* 函数名：SetEmoji
* 描述  ：依据数组设置Emoji图片
* 参数  ：
*        @x  图片位于第x行 1~10
*        @y  图片位于第y列 1~10
* 返回值：无
**********************************************************/
void SetEmoji(int emoji_y, int emoji_x) // 1~10
{
    int i;
    if (emoji_y <= 5)
    {
        for (i = 0; i < 192; i++)
        {
            curremoji[i] = pgm_read_byte(gImage_emojis1+(192 * (10 * (emoji_y - 1) + (emoji_x - 1)) + i));
        }
    }
    else if (emoji_y <= 10)
    {
        for (i = 0; i < 192; i++)
        {
            curremoji[i] = pgm_read_byte(gImage_emojis2+(192 * (10 * (emoji_y - 6) + (emoji_x - 1)) + i));
        }
    }
    DrawPic(curremoji);
}

/*******************************************************
* 函数名：emojishowtest
* 描述  ：emoji显示测试函数
**********************************************************/
void emojishowtest()
{
    int i, j;
    for (i = 1; i <= 10; i++)
    {
        for (j = 1; j <= 10; j++)
        {
            SetEmoji(i, j);
            FastLED.show();
            delay(300);
        }
    }
}

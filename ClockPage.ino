/*******************************************************
 * 函数名：ClockPage1
 * 描述  ：渐亮渐暗显示时间
 * 参数  ：无
 * 返回值：无
 **********************************************************/
void ClockPage1()
{
    int h_1 = hour() / 10, h_2 = hour() % 10;
    int m_1 = minute() / 10, m_2 = minute() % 10;
    int brightness = 0; //模式1下的亮度

    if (count == 0)
    {
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        fill_solid(leds_font, NUM_LEDS, CRGB::Green);
        showCharacter(0, 1, h_1 + 48, Apple5x7);
        fill_solid(leds_font, NUM_LEDS, CRGB::Green);
        showCharacter(4, 1, h_2 + 48, Apple5x7);
    }

    if (count == 110)
    {
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        fill_solid(leds_font, NUM_LEDS, CRGB::Blue);
        showCharacter(0, 1, m_1 + 48, Apple5x7);
        fill_solid(leds_font, NUM_LEDS, CRGB::Blue);
        showCharacter(4, 1, m_2 + 48, Apple5x7);
    }

    if (count < 30) //最大亮度为120
    {
        brightness = count * 4;
    }
    else if (count < 80)
    {
        brightness = 120;
    }
    else if (count < 110)
    {
        brightness = 120 - (count - 80) * 4;
    }
    else if (count < 140)
    {
        brightness = (count - 110) * 4;
    }
    else if (count < 190)
    {
        brightness = 120;
    }
    else if (count < 220)
    {
        brightness = 120 - (count - 190) * 4;
    }
    else if (count < 320)
    {
        brightness = 0;
    }
    else
    {
        count = 0;
    }
    FastLED.setBrightness(brightness);
    FastLED.show();
}

/*******************************************************
 * 函数名：ClockPage2
 * 描述  ：左右移动显示时间
 * 参数  ：无
 * 返回值：无
 **********************************************************/
void ClockPage2()
{
    int h_1 = hour() / 10, h_2 = hour() % 10;
    int m_1 = minute() / 10, m_2 = minute() % 10;
    int x;

    if (count < 100)
    {
        x = 8;
    }
    else if (count < 145)
    {
        x = 8 - (count - 100) / 5;
    }
    else if (count < 245)
    {
        x = 0;
    }
    else if (count < 290)
    {
        x = (count - 245) / 5;
    }
    else
    {
        x = 8;
        count = 0;
    }

    fill_solid(leds, NUM_LEDS, CRGB::Black);
    fill_solid(leds_font, NUM_LEDS, CRGB::Green);
    showCharacter(x - 8, 1, h_1 + 48, Clock3x5);
    showCharacter(x - 5, 1, h_2 + 48, Clock3x5);
    showCharacter(x - 1, 1, ':', Clock3x5);
    fill_solid(leds_font, NUM_LEDS, CRGB::Blue);
    showCharacter(x, 1, ':', Clock3x5);
    fill_solid(leds_font, NUM_LEDS, CRGB::Blue);
    showCharacter(x + 2, 1, m_1 + 48, Clock3x5);
    showCharacter(x + 5, 1, m_2 + 48, Clock3x5);
    FastLED.show();
}

/*******************************************************
 * 函数名：ClockPage3
 * 描述  ：单屏幕显示时间，数字风格
 * 参数  ：无
 * 返回值：无
 **********************************************************/
void ClockPage3()
{
    int h_1, h_2, m_1, m_2;
    if (count > 50)
    {
        count = 0;
        h_1 = hour() / 10;
        h_2 = hour() % 10;
        m_1 = minute() / 10;
        m_2 = minute() % 10;
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        fill_solid(leds_font, NUM_LEDS, CRGB::Green);
        showCharacter(0, 0, h_1 + 48, Clock3x4);
        showCharacter(4, 0, h_2 + 48, Clock3x4);
        fill_solid(leds_font, NUM_LEDS, CRGB::Blue);
        showCharacter(0, 4, m_1 + 48, Clock3x4);
        showCharacter(4, 4, m_2 + 48, Clock3x4);
        FastLED.show();
    }
}

/*时钟风格显示时间表盘数组*/
uint8_t clockspace[12][5] =
    {
        // 时间 像素点1_x 像素点1_y 像素点2_x 像素点2_y
        {0, 3, 0, 4, 0},
        {1, 5, 0, 6, 0},
        {2, 7, 1, 7, 2},
        {3, 7, 3, 7, 4},
        {4, 7, 5, 7, 6},
        {5, 5, 7, 6, 7},
        {6, 3, 7, 4, 7},
        {7, 1, 7, 2, 7},
        {8, 0, 5, 0, 6},
        {9, 0, 3, 0, 4},
        {10, 0, 1, 0, 2},
        {11, 1, 0, 2, 0},
};

/*******************************************************
 * 函数名：ClockPage4
 * 描述  ：单屏幕显示时间,时钟风格
 * 参数  ：无
 * 返回值：无
 **********************************************************/
void ClockPage4()
{
    int h, m_1, m_2, i;

    if (count > 50)
    {
        count = 0;
        h = hour();
        m_1 = minute() / 10;
        m_2 = minute() % 10;

        fill_solid(leds, NUM_LEDS, CRGB::Black);
        fill_solid(leds_font, NUM_LEDS, CRGB::Blue);
        showCharacter(1, 2, m_1 + 48, Clock3x4);
        showCharacter(4, 2, m_2 + 48, Clock3x4);

        for (i = 0; i < 12; i++)
        {
            if (i == h % 12)
            {
                leds[XYsafe(clockspace[i][1], clockspace[i][2])] = CRGB::Green;
                leds[XYsafe(clockspace[i][3], clockspace[i][4])] = CRGB::Green;
            }
            else
            {
                leds[XYsafe(clockspace[i][1], clockspace[i][2])] = CRGB::White;
                leds[XYsafe(clockspace[i][3], clockspace[i][4])] = CRGB::White;
            }
        }
        FastLED.show();
    }
}

/*******************************************************
 * 函数名：showClock
 * 描述  ：根据设置模式显示时间
 * 参数  ：无
 * 返回值：无
 **********************************************************/
void showClock()
{
    switch (clockMode)
    {
    case 1:
        ClockPage1();
        break;
    case 2:
        ClockPage2();
        break;
    case 3:
        ClockPage3();
        break;
    case 4:
        ClockPage4();
        break;
    default:
        break;
    }
}

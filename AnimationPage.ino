/*******************************************************
 * 函数名：showAnimation
 * 描述  ：显示动态画面
 * 参数  ：无
 * 返回值：无
 **********************************************************/
void showAnimation()
{
  if(count>0&&aniMode==1)
  {
    uint8_t colorIndex = anm_colorIndex;
    for( int i = 0; i < NUM_LEDS; i++) {
      leds[i] = ColorFromPalette( anm_currentPalette, colorIndex, 255, anm_currentBlending);
      colorIndex += 3;   // 取色
    }
    FastLED.show();
    count=0;
    anm_colorIndex++;
  }
}

/*******************************************************
 * 函数名：SetupTotallyRandomPalette
 * 描述  ：使用完全随机的颜色填充调色板
 * 参数  ：无
 * 返回值：无
 **********************************************************/
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        anm_currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

/*******************************************************
 * 函数名：SetupBlackAndWhiteStripedPalette
 * 描述  ：设置黑白相间的调色板
 * 参数  ：无
 * 返回值：无
 **********************************************************/
void SetupBlackAndWhiteStripedPalette()
{
    // 设置所有16个调色板为黑色
    fill_solid( anm_currentPalette, 16, CRGB::Black);
    // 每隔4个设置为白色
    anm_currentPalette[0] = CRGB::White;
    anm_currentPalette[4] = CRGB::White;
    anm_currentPalette[8] = CRGB::White;
    anm_currentPalette[12] = CRGB::White;
    
}

/*******************************************************
 * 函数名：SetupPurpleAndGreenPalette
 * 描述  ：设置紫色和绿色条纹的调色板
 * 参数  ：无
 * 返回值：无
 **********************************************************/
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    anm_currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}

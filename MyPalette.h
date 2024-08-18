#ifndef __MYPALETTE_H__
#define __MYPALETTE_H__

/*自定义色盘配置文件*/
/*可以在此处自定义色盘，并在动态画面或文字显示中选择该色盘*/
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Green,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Green,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Green,
    CRGB::Green
};

#endif

/**********************************************************************
项目名称/Project          : 便携像素灯
作者/Author               : SMALL_DA
日期/Date（YYYYMMDD）     : 2022/8/18
-----------------------------------------------------------------------
V0.0.1  2022/8/18 项目创建 实现图片显示、屏幕旋转、wifiManager配网功能
V0.0.2  2022/8/19 实现apple4x6字符显示功能
v0.0.3  2022/8/23 添加Apple5x7,Apple6x10,Pix5x7字符字体，拓展字符显示功能,初步实现字符串显示功能
v0.0.4  2022/8/24 实现4种背景颜色、4种字体颜色的字符串流动显示、闪烁显示功能
        2022/8/25 添加Atari8x8、Undertale8x8、Blodnum8x8三种字符字体
v0.0.6  2022/8/27 添加中文字库
        2022/8/28 实现中文字符显示功能
v0.0.7  2022/8/29 完善中文字符显示功能，添加注释 
v0.0.8  2022/8/30 实现4种风格时钟显示，实现网路服务建立
v0.0.9  2022/8/31 编写配置主页、图片网页界面；修改数据存储方式，减少动态内存占用；实现WebSocketsServer获取设置数据功能；
                  实现网页选择图案显示功能
v0.1.0  2022/9/1 编写时钟界面；实现网页选择时钟模式功能
v0.9.0  2022/9/2 编写文字网页；实现文字显示功能
        2022/9/5 编写文字设置网页；实现文字显示配置功能
        2022/9/6 实现网页选择动画与亮度功能。
v1.0.0  2022/9/6 注释补充
***********************************************************************/
#include "Config.h"

void setup()
{
    Serial.begin(115200);
    wifiManager.autoConnect(MDNS_NAME);

    initNTP();

    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.addLeds<CHIPSET, LED_FONT_PIN, COLOR_ORDER>(leds_font, NUM_LEDS);
    FastLED.setBrightness(Brightness);

    WebServer_init();
    //SetRotation(2);   //设置页面旋转方向
    ShowIP();
    ticker.attach_ms(20, tickerCount);
    Serial.println("IP Show Over");
}

void loop()
{
    WebServer_run();
    showClock();
    showWords();
    showAnimation();

    /*****以下为测试用函数****/
    //characterTest();
    //emojishowtest();
    //cnstrsliptest();
    //cnstrtwinkletest();
    //strsliptest();
    //strtwinkletest();
}

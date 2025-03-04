#ifndef __CONFIG_H__
#define __CONFIG_H__

/*配置文件*/

#include <FastLED.h>
#include <WiFiManager.h>
#include <TimeLib.h>
#include <WiFiUdp.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <ESPmDNS.h>
#include <Ticker.h>
#include <ArduinoJson.h>
// #include <Hash.h>

#include "MyPalette.h"
#include "Image.h"
#include "Pixfont.h"
#include "Cnfont.h"

#define MDNS_NAME "YuePixel"

#define LED_PIN 11                            // GPIO4为信号引脚
#define LED_FONT_PIN 1                        // GPIO5（D2)为虚拟引脚，配置字体颜色使用
#define COLOR_ORDER GRB                       //色彩顺序
#define CHIPSET WS2812B                       //灯珠类型
#define MATRIXWIDTH 8                         //屏幕宽度
#define MATRIXHEIGHT 8                        //屏幕高度
#define NUM_LEDS (MATRIXWIDTH * MATRIXHEIGHT) //屏幕总像素

const uint8_t kMatrixWidth = MATRIXWIDTH; // 宽度和高度参数
const uint8_t kMatrixHeight = MATRIXHEIGHT;
const bool kMatrixSerpentineLayout = true; //像素布局参数(蛇形)
uint8_t Brightness = 5;
int RotationMode = 0;                      //旋转方向

WiFiManager wifiManager;
Ticker ticker;// 建立Ticker用于实现定时功能

CRGB leds_plus_safety_pixel[NUM_LEDS + 1];    //灯珠创建
CRGB *const leds(leds_plus_safety_pixel + 1);
CRGB leds_fonts_plus_safety_pixel[NUM_LEDS + 1]; //字体灯珠，存在但不显示
CRGB *const leds_font(leds_fonts_plus_safety_pixel + 1);

//****************************NTP配置****************************
#define LOCALPORT 8000              //侦听UDP数据包的本地端口
#define NTP_PACKET_SIZE 48          // NTP时间戳位于消息的前48个字节中
byte packetBuffer[NTP_PACKET_SIZE]; // 用于保存传入和传出数据包的缓冲区
// NTP服务器参数
char ntpServerName[128] = "ntp6.aliyun.com";  //NTP服务器名称
int timeZone = 8;        //显示为东八区
int timezone_offset = 8; //显示为东八区

//***************************定时器配置**************************
int count = 0;
//***************************网页配置****************************
char socketMessage[500] = { 'p', '1', '1' };
char settingMessage[500] = {0};
//***************************时钟界面配置************************
int clockMode = 0;  //时钟模式 0：不显示 1~4：对应风格
//***************************文字显示配置************************
int wordShowkMode = 0;  //0：不显示 1：滚动显示 2：闪烁显示
char* message_str;
int len_t, cnstr_p = 0;
int cnstr_type[200];    // cnstr_type：Cnfont8x8 字体字符串各字符中英文类型数组，0位英文，1位中文，2结束
int wordshow_i = 0;
//********滚动显示参数**********//
int pix_l;
int cnstr_pos[200]; //cnstr_pos：Cnfont8x8 字体字符串中各字符偏移像素
//****************************动画显示配置************************
int aniMode = 0;   //动画模式 0：不显示 1~10：对应风格
uint8_t anm_colorIndex = 0;
CRGBPalette16 anm_currentPalette;
TBlendType    anm_currentBlending;
int anm_style;

//**********************字体****************************
enum charfont
{
    Apple4x6,   //全
    Apple5x7,   //全
    Apple6x10,  //全 字体偏大
    Pix5x7,     //1~9 A~Z a~z
    Atari8x8,   //A~Z 0~9
    Undertale8x8, //全
    Blodnum8x8, //0~9
    Cnfont8x8,  //中英文
    Clock3x5,   //0~9 :
    Clock3x4,   //0~9
};

struct FontAttribute  //字体属性
{
    const unsigned char *font_bitmap;  //字体数组
    const unsigned char *font_index;  //字体编码数组
    int font_num;   //字体包含字符数
    int font_width; //字符宽度
    int font_height; //字符高度
    int font_test_x; //测试用：字符居中偏移
    int font_test_y; //测试用：字符居中偏移
    int font_test_space;  //相邻字符偏移像素
};

struct FontAttribute fontattribute[]=    //各字体属性设置
{
    {
        apple4x6_bitmap,
        apple_index,
        sizeof(apple_index) / sizeof(apple_index[0]),
        4,
        6,
        3,
        1,
        4,
    },
    {
        apple5x7_bitmap,
        apple_index,
        sizeof(apple_index) / sizeof(apple_index[0]),
        5,
        7,
        2,
        1,
        5,
    },
    {
        apple6x10_bitmap,
        apple6x10_index,
        sizeof(apple6x10_index) / sizeof(apple6x10_index[0]),
        6,
        10,
        2,
        -1,
        6,
    },
    {
        Pix5x7_bitmap,
        Pix5x7_index,
        sizeof(Pix5x7_index) / sizeof(Pix5x7_index[0]),
        5,
        7,
        2,
        1,
        6,
    },
    {
        Atari8x8_bitmap,
        Atari8x8_index,
        sizeof(Atari8x8_index) / sizeof(Atari8x8_index[0]),
        8,
        8,
        1,
        1,
        8,
    },
    {
        Undertale8x8_bitmap,
        Undertale8x8_index,
        sizeof(Undertale8x8_index) / sizeof(Undertale8x8_index[0]),
        8,
        8,
        1,
        1,
        8,
    },
    {
        Blodnum8x8_bitmap,
        Blodnum8x8_index,
        sizeof(Blodnum8x8_index) / sizeof(Blodnum8x8_index[0]),
        8,
        8,
        0,
        0,
        8,
    },
    {
        Cnfont_bitmap,
        (const unsigned char *)Cnfont_index,
        CNFONTLEN,
        8,
        8,
        0,
        0,
        8,
    },
    {
        Clock3x5_bitmap,
        Clock3x5_index,
        sizeof(Clock3x5_index) / sizeof(Clock3x5_index[0]),
        3,
        5,
        2,
        1,
        4,
    },
    {
        Clock3x4_bitmap,
        Clock3x4_index,
        sizeof(Clock3x4_index) / sizeof(Clock3x4_index[0]),
        3,
        4,
        2,
        2,
        4,
    },
};
//**********************字符串显示**********************
enum
{
    SolidColor,       //纯色
    RainbowColor,     //彩虹色
    GradiantColor,    //渐变色
    PaletteColor,     //色盘
};

struct SolidColorVar  //纯色填充函数参数
{
    struct CRGB *leds;  //led名称
    int numToFill;      //填充灯珠数量
    CRGB color;//const struct CRGB color;  //填充颜色
};

struct RainbowColorVar //渐变彩虹色填充函数参数
{
    struct CRGB *pFirstLED;  //led名称
    int numToFill;           //填充灯珠数量
    uint8_t initialhue;      //彩虹色的其实色调值，最大为255
    uint8_t deltahue;        //相邻灯珠的色调差，最大为255
};

struct GradiantColorVar  //渐变色填充函数参数
{
    CRGB *leds;       //led名称
    uint16_t startpos; //开始灯珠编号
    CRGB startcolor;   //开始灯珠颜色
    uint16_t endpos;   //结束灯珠编号
    CRGB endcolor;    //结束灯珠颜色
};

struct PaletteColorVar  //色盘颜色填充函数参数
{
    CRGB *L;              //led名称
    uint16_t N;           //灯珠数量
    uint8_t startIndex;   //起始颜色序号
    uint8_t incIndex;     //灯珠间颜色差
    CRGBPalette16 pal;   //palette色盘名
    uint8_t brightness;   //亮度
    TBlendType blendType; //色彩过渡方式  LINEARBLEND：线性渐变  NOBLEND：不渐变

    /*
    色板：
    CloudColors_p：云朵渐变
    LavaColors_p：火山渐变
    OceanColors_p：海洋渐变
    ForestColors_p：树林渐变
    RainbowColors_p：彩虹渐变
    RainbowStripeColors_p：彩带渐变
    PartyColors_p：派对渐变
    HeatColors_p：热浪渐变
    */
};

struct StrSlipConfig //滑动显示配置
{
    int font_color_func = SolidColor;                                            //字体颜色函数
    struct SolidColorVar font_sc_var = {leds_font, NUM_LEDS, CRGB::White}; //四种显示函数默认变量
    struct RainbowColorVar font_rc_var = {leds_font, NUM_LEDS, 30, 30};
    struct GradiantColorVar font_gc_var = {leds_font, 0, CRGB::Red, NUM_LEDS - 1, CRGB::Blue};
    struct PaletteColorVar font_pc_var = {leds_font, NUM_LEDS, 0, 3, (CRGBPalette16)RainbowColors_p , 255, LINEARBLEND};

    int bg_color_func = SolidColor;                                              //背景颜色函数
    struct SolidColorVar bg_sc_var = {leds, NUM_LEDS, CRGB::Black}; //四种显示函数默认变量
    struct RainbowColorVar bg_rc_var = {leds, NUM_LEDS, 10, 10};
    struct GradiantColorVar bg_gc_var = {leds, 0, CRGB::Yellow, NUM_LEDS - 1, CRGB::Green};
    struct PaletteColorVar bg_pc_var = {leds, NUM_LEDS, 0, 3, (CRGBPalette16)CloudColors_p, 255, LINEARBLEND};

    int strspeed = 80;  //滑动速度  ms/像素
    int cspace = 4;    //字符间隔（像素）
    int cfont = Apple4x6;     //字符字体
} strslipconfig; //滑动显示配置

struct StrTwinkleConfig //闪烁显示配置
{
    int font_color_func = SolidColor;                                    //字体颜色函数
    struct SolidColorVar font_sc_var = {leds_font, NUM_LEDS, CRGB::White}; //四种显示函数默认变量
    struct RainbowColorVar font_rc_var = {leds_font, NUM_LEDS, 30, 30};
    struct GradiantColorVar font_gc_var = {leds_font, 0, CRGB::Red, NUM_LEDS - 1, CRGB::Blue};
    struct PaletteColorVar font_pc_var = {leds_font, NUM_LEDS, 0, 3, (CRGBPalette16)RainbowColors_p , 255, LINEARBLEND};

    int bg_color_func = SolidColor;                                 //背景颜色函数
    struct SolidColorVar bg_sc_var = {leds, NUM_LEDS, CRGB::Black}; //四种显示函数默认变量
    struct RainbowColorVar bg_rc_var = {leds, NUM_LEDS, 10, 10};
    struct GradiantColorVar bg_gc_var = {leds, 0, CRGB::Yellow, NUM_LEDS - 1, CRGB::Green};
    struct PaletteColorVar bg_pc_var = {leds, NUM_LEDS, 0, 3, (CRGBPalette16)CloudColors_p, 255, LINEARBLEND};

    int twkspeed = 300;  //闪烁速度  ms/次
    int cfont = Apple4x6;     //字符字体
} strstwinkleconfig; //闪烁显示配置

//**********************函数声明************************
void initNTP();
void digitalClockDisplay();
void SetRotation(int dir);
void DrawPic(const unsigned char pic[], bool BgCover = true, int pic_x = 0, int pic_y = 0, int pic_w = MATRIXWIDTH, int pic_h = MATRIXHEIGHT);
void SetEmoji(int emoji_x, int emoji_y);
void emojishowtest();
void showCharacter(int char_x, int char_y, int c, int charfont = Apple4x6);
void characterTest();
void showStringSlip(int char_x, int char_y, char *str, int len);
void strsliptest();
void cnstrsliptest();
void showStringTwinkle(int char_x, int char_y, char *str, int len);
void strtwinkletest();
void cnstrtwinkletest();
void setSlipStrLen(char *str, int len);
void setTwinkleStrLen(char *str, int len);
void showWords();
void ClockPage1();
void ClockPage2();
void ClockPage3();
void ClockPage4();
void WebServer_init();
void WebServer_run();
void ShowIP();
void tickerCount();
void showClock();
void SetupPurpleAndGreenPalette();
void SetupTotallyRandomPalette();
void SetupBlackAndWhiteStripedPalette();
void showAnimation();

#endif

WiFiUDP Udp;

/*******************************************************
 * 函数名：getNtpTime
 * 描述  ：通过NTP获取时间
 * 参数  ：无
 * 返回值：获取的时间数据
 **********************************************************/
time_t getNtpTime() 
{
    IPAddress ntpServerIP; // NTP服务器的ip地址
    while (Udp.parsePacket() > 0)
        ; // 丢弃任何先前接收的数据包
    Serial.println("Transmit NTP Request");
    WiFi.hostByName(ntpServerName, ntpServerIP); //配置获取的NTP服务器
    sendNTPpacket(ntpServerIP);
    uint32_t beginWait = millis();
    while (millis() - beginWait < 1500)
    {
        int size = Udp.parsePacket();
        if (size >= NTP_PACKET_SIZE)
        {
            Serial.println("Receive NTP Response");
            Udp.read(packetBuffer, NTP_PACKET_SIZE); // 将数据包读入缓冲区
            unsigned long secsSince1900;
            // 将从位置40开始的4个字节转换为长整数
            secsSince1900 = (unsigned long)packetBuffer[40] << 24;
            secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
            secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
            secsSince1900 |= (unsigned long)packetBuffer[43];
            return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
        }
    }
    Serial.println("No NTP Response :-(");
    return 0; // 无法获取时间时返回0
}

/*******************************************************
 * 函数名：sendNTPpacket
 * 描述  ：向NTP服务器发送请求
 * 参数  ：
 *         @address    NTP服务器的ip地址
 * 返回值：无
 **********************************************************/
void sendNTPpacket(IPAddress &address)
{
    // 将缓冲区中的所有字节设置为0
    memset(packetBuffer, 0, NTP_PACKET_SIZE);
    // 初始化NTP请求所需的值
    packetBuffer[0] = 0b11100011; // LI, Version, Mode
    packetBuffer[1] = 0;          // Stratum, or type of clock
    packetBuffer[2] = 6;          // Polling Interval
    packetBuffer[3] = 0xEC;       // Peer Clock Precision
    // 8 bytes of zero for Root Delay & Root Dispersion
    packetBuffer[12] = 49;
    packetBuffer[13] = 0x4E;
    packetBuffer[14] = 49;
    packetBuffer[15] = 52;
    // 发送请求时间戳的数据包
    Udp.beginPacket(address, 123); // NTP请求发送到端口123
    Udp.write(packetBuffer, NTP_PACKET_SIZE);
    Udp.endPacket();
}

/*******************************************************
 * 函数名：initNTP
 * 描述  ：NTP初始化
 * 参数  ：无
 * 返回值：无
 **********************************************************/
void initNTP()
{
    // 登录成功，因此将UDP设置为本地端口
    Udp.begin(LOCALPORT);
    // 将时间提供程序设置为NTP
    setSyncProvider(getNtpTime); //同步时间
}

/*******************************************************
 * 函数名：digitalClockDisplay
 * 描述  ：时间打印，测试用
 * 参数  ：无
 * 返回值：无
 **********************************************************/
void digitalClockDisplay()
{
    Serial.print(hour());
    printDigits(minute());
    printDigits(second());
    Serial.print(" ");
    Serial.print(day());
    Serial.print(".");
    Serial.print(month());
    Serial.print(".");
    Serial.print(year());
    Serial.println();
}

/*******************************************************
 * 函数名：printDigits
 * 描述  ：数字时钟中实现打印冒号和前导0
 * 参数  ：
 *         @digits 数值
 * 返回值：无
 **********************************************************/
void printDigits(int digits)
{
    Serial.print(":");
    if (digits < 10)
        Serial.print('0');
    Serial.print(digits);
}

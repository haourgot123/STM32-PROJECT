#include "RTC.h"
#define RTC_ADDR 0x68<<1
uint8_t Decimal2BCD(uint8_t num)
{
	return (num/10)<<4|(num%10);
}
uint8_t BCD2Decimal(uint8_t num)
{
	return (num>>4)*10 + (num & 0x0F);
}
void RTC_WriteTime(RTC_Typedef *rtc)
{
	uint8_t buff[8];
	buff[0] = 0;
	buff[1] = Decimal2BCD(rtc->dt.second);
	buff[2] = Decimal2BCD(rtc->dt.min);
	buff[3] = Decimal2BCD(rtc->dt.hour);
	buff[4] = Decimal2BCD(rtc->dt.day);
	buff[5] = Decimal2BCD(rtc->dt.date);
	buff[6] = Decimal2BCD(rtc->dt.month);
	buff[7] = Decimal2BCD(rtc->dt.year);
	HAL_I2C_Master_Transmit(rtc->hi2c,RTC_ADDR,buff,8,100);
	
}
void RTC_ReadTime(RTC_Typedef *rtc)
{
	uint8_t buff[7];
	uint8_t add_reg = 0;
	HAL_I2C_Master_Transmit(rtc->hi2c,RTC_ADDR, &add_reg,1,100);
	HAL_I2C_Master_Receive(rtc->hi2c,RTC_ADDR,buff,7,100);
	rtc->dt.second = BCD2Decimal(buff[0]);
	rtc->dt.min = BCD2Decimal(buff[1]);
	rtc->dt.hour = BCD2Decimal(buff[2]);
	rtc->dt.day = BCD2Decimal(buff[3]);
	rtc->dt.date = BCD2Decimal(buff[4]);
	rtc->dt.month = BCD2Decimal(buff[5]);
	rtc->dt.year = BCD2Decimal(buff[6]);
	
}
void RTC_Init(RTC_Typedef *rtc,I2C_HandleTypeDef *hi2c)
{
	rtc->hi2c = hi2c;
}

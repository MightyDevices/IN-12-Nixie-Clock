/*
 * rtc.h
 *
 *  Created on: 24-02-2013
 *      Author: Tomek
 */

#ifndef STM32_RTC_H_
#define STM32_RTC_H_

#include <stm32l/stm32l.h>

/* registers base */
#define RTC_BASE							(0x40000000 + 0x2800)
/* registers */
#define RTC									((rtc_t *)RTC_BASE)

/* rtc */
typedef struct {
	reg32_t TR;
	reg32_t DR;
	reg32_t CR;
	reg32_t ISR;
	reg32_t PRER;
	reg32_t WUTR;
	reg32_t CALIBR;
	reg32_t ALRMAR;
	reg32_t ALRMBR;
	reg32_t WPR;
	reg32_t SSR;
	reg32_t SHIFTR;
	reg32_t TSTR;
	reg32_t TSDR;
	reg32_t TSSSR;
	reg32_t CALR;
	reg32_t TAFCR;
	reg32_t ALRMASSR;
	reg32_t ALRMBSSR;
	reg32_t RESERVED7;
	reg32_t BKP0R;
	reg32_t BKP1R;
	reg32_t BKP2R;
	reg32_t BKP3R;
	reg32_t BKP4R;
	reg32_t BKP5R;
	reg32_t BKP6R;
	reg32_t BKP7R;
	reg32_t BKP8R;
	reg32_t BKP9R;
	reg32_t BKP10R;
	reg32_t BKP11R;
	reg32_t BKP12R;
	reg32_t BKP13R;
	reg32_t BKP14R;
	reg32_t BKP15R;
	reg32_t BKP16R;
	reg32_t BKP17R;
	reg32_t BKP18R;
	reg32_t BKP19R;
	reg32_t BKP20R;
	reg32_t BKP21R;
	reg32_t BKP22R;
	reg32_t BKP23R;
	reg32_t BKP24R;
	reg32_t BKP25R;
	reg32_t BKP26R;
	reg32_t BKP27R;
	reg32_t BKP28R;
	reg32_t BKP29R;
	reg32_t BKP30R;
	reg32_t BKP31R;
} rtc_t;

/* RTC time register */
#define RTC_TR_PM                           (0x00400000)
#define RTC_TR_HT                           (0x00300000)
#define RTC_TR_HT_0                         (0x00100000)
#define RTC_TR_HT_1                         (0x00200000)
#define RTC_TR_HU                           (0x000F0000)
#define RTC_TR_HU_0                         (0x00010000)
#define RTC_TR_HU_1                         (0x00020000)
#define RTC_TR_HU_2                         (0x00040000)
#define RTC_TR_HU_3                         (0x00080000)
#define RTC_TR_MNT                          (0x00007000)
#define RTC_TR_MNT_0                        (0x00001000)
#define RTC_TR_MNT_1                        (0x00002000)
#define RTC_TR_MNT_2                        (0x00004000)
#define RTC_TR_MNU                          (0x00000F00)
#define RTC_TR_MNU_0                        (0x00000100)
#define RTC_TR_MNU_1                        (0x00000200)
#define RTC_TR_MNU_2                        (0x00000400)
#define RTC_TR_MNU_3                        (0x00000800)
#define RTC_TR_ST                           (0x00000070)
#define RTC_TR_ST_0                         (0x00000010)
#define RTC_TR_ST_1                         (0x00000020)
#define RTC_TR_ST_2                         (0x00000040)
#define RTC_TR_SU                           (0x0000000F)
#define RTC_TR_SU_0                         (0x00000001)
#define RTC_TR_SU_1                         (0x00000002)
#define RTC_TR_SU_2                         (0x00000004)
#define RTC_TR_SU_3                         (0x00000008)

/* RTC date register */
#define RTC_DR_YT                           (0x00F00000)
#define RTC_DR_YT_0                         (0x00100000)
#define RTC_DR_YT_1                         (0x00200000)
#define RTC_DR_YT_2                         (0x00400000)
#define RTC_DR_YT_3                         (0x00800000)
#define RTC_DR_YU                           (0x000F0000)
#define RTC_DR_YU_0                         (0x00010000)
#define RTC_DR_YU_1                         (0x00020000)
#define RTC_DR_YU_2                         (0x00040000)
#define RTC_DR_YU_3                         (0x00080000)
#define RTC_DR_WDU                          (0x0000E000)
#define RTC_DR_WDU_0                        (0x00002000)
#define RTC_DR_WDU_1                        (0x00004000)
#define RTC_DR_WDU_2                        (0x00008000)
#define RTC_DR_MT                           (0x00001000)
#define RTC_DR_MU                           (0x00000F00)
#define RTC_DR_MU_0                         (0x00000100)
#define RTC_DR_MU_1                         (0x00000200)
#define RTC_DR_MU_2                         (0x00000400)
#define RTC_DR_MU_3                         (0x00000800)
#define RTC_DR_DT                           (0x00000030)
#define RTC_DR_DT_0                         (0x00000010)
#define RTC_DR_DT_1                         (0x00000020)
#define RTC_DR_DU                           (0x0000000F)
#define RTC_DR_DU_0                         (0x00000001)
#define RTC_DR_DU_1                         (0x00000002)
#define RTC_DR_DU_2                         (0x00000004)
#define RTC_DR_DU_3                         (0x00000008)

/* RTC control register */
#define RTC_CR_COE                          (0x00800000)
#define RTC_CR_OSEL                         (0x00600000)
#define RTC_CR_OSEL_0                       (0x00200000)
#define RTC_CR_OSEL_1                       (0x00400000)
#define RTC_CR_POL                          (0x00100000)
#define RTC_CR_COSEL                        (0x00080000)
#define RTC_CR_BCK                          (0x00040000)
#define RTC_CR_SUB1H                        (0x00020000)
#define RTC_CR_ADD1H                        (0x00010000)
#define RTC_CR_TSIE                         (0x00008000)
#define RTC_CR_WUTIE                        (0x00004000)
#define RTC_CR_ALRBIE                       (0x00002000)
#define RTC_CR_ALRAIE                       (0x00001000)
#define RTC_CR_TSE                          (0x00000800)
#define RTC_CR_WUTE                         (0x00000400)
#define RTC_CR_ALRBE                        (0x00000200)
#define RTC_CR_ALRAE                        (0x00000100)
#define RTC_CR_DCE                          (0x00000080)
#define RTC_CR_FMT                          (0x00000040)
#define RTC_CR_BYPSHAD                      (0x00000020)
#define RTC_CR_REFCKON                      (0x00000010)
#define RTC_CR_TSEDGE                       (0x00000008)
#define RTC_CR_WUCKSEL                      (0x00000007)
#define RTC_CR_WUCKSEL_0                    (0x00000001)
#define RTC_CR_WUCKSEL_1                    (0x00000002)
#define RTC_CR_WUCKSEL_2                    (0x00000004)

/* RTC initialization and status register */
#define RTC_ISR_RECALPF                     (0x00010000)
#define RTC_ISR_TAMP3F                      (0x00008000)
#define RTC_ISR_TAMP2F                      (0x00004000)
#define RTC_ISR_TAMP1F                      (0x00002000)
#define RTC_ISR_TSOVF                       (0x00001000)
#define RTC_ISR_TSF                         (0x00000800)
#define RTC_ISR_WUTF                        (0x00000400)
#define RTC_ISR_ALRBF                       (0x00000200)
#define RTC_ISR_ALRAF                       (0x00000100)
#define RTC_ISR_INIT                        (0x00000080)
#define RTC_ISR_INITF                       (0x00000040)
#define RTC_ISR_RSF                         (0x00000020)
#define RTC_ISR_INITS                       (0x00000010)
#define RTC_ISR_SHPF                        (0x00000008)
#define RTC_ISR_WUTWF                       (0x00000004)
#define RTC_ISR_ALRBWF                      (0x00000002)
#define RTC_ISR_ALRAWF                      (0x00000001)

/* RTC prescaler register */
#define RTC_PRER_PREDIV_A                   (0x007F0000)
#define RTC_PRER_PREDIV_S                   (0x00007FFF)

/* RTC wakeup timer register */
#define RTC_WUTR_WUT                        (0x0000FFFF)

/* RTC calibration register */
#define RTC_CALIBR_DCS                      (0x00000080)
#define RTC_CALIBR_DC                       (0x0000001F)

/* RTC alarm A register */
#define RTC_ALRMAR_MSK4                     (0x80000000)
#define RTC_ALRMAR_WDSEL                    (0x40000000)
#define RTC_ALRMAR_DT                       (0x30000000)
#define RTC_ALRMAR_DT_0                     (0x10000000)
#define RTC_ALRMAR_DT_1                     (0x20000000)
#define RTC_ALRMAR_DU                       (0x0F000000)
#define RTC_ALRMAR_DU_0                     (0x01000000)
#define RTC_ALRMAR_DU_1                     (0x02000000)
#define RTC_ALRMAR_DU_2                     (0x04000000)
#define RTC_ALRMAR_DU_3                     (0x08000000)
#define RTC_ALRMAR_MSK3                     (0x00800000)
#define RTC_ALRMAR_PM                       (0x00400000)
#define RTC_ALRMAR_HT                       (0x00300000)
#define RTC_ALRMAR_HT_0                     (0x00100000)
#define RTC_ALRMAR_HT_1                     (0x00200000)
#define RTC_ALRMAR_HU                       (0x000F0000)
#define RTC_ALRMAR_HU_0                     (0x00010000)
#define RTC_ALRMAR_HU_1                     (0x00020000)
#define RTC_ALRMAR_HU_2                     (0x00040000)
#define RTC_ALRMAR_HU_3                     (0x00080000)
#define RTC_ALRMAR_MSK2                     (0x00008000)
#define RTC_ALRMAR_MNT                      (0x00007000)
#define RTC_ALRMAR_MNT_0                    (0x00001000)
#define RTC_ALRMAR_MNT_1                    (0x00002000)
#define RTC_ALRMAR_MNT_2                    (0x00004000)
#define RTC_ALRMAR_MNU                      (0x00000F00)
#define RTC_ALRMAR_MNU_0                    (0x00000100)
#define RTC_ALRMAR_MNU_1                    (0x00000200)
#define RTC_ALRMAR_MNU_2                    (0x00000400)
#define RTC_ALRMAR_MNU_3                    (0x00000800)
#define RTC_ALRMAR_MSK1                     (0x00000080)
#define RTC_ALRMAR_ST                       (0x00000070)
#define RTC_ALRMAR_ST_0                     (0x00000010)
#define RTC_ALRMAR_ST_1                     (0x00000020)
#define RTC_ALRMAR_ST_2                     (0x00000040)
#define RTC_ALRMAR_SU                       (0x0000000F)
#define RTC_ALRMAR_SU_0                     (0x00000001)
#define RTC_ALRMAR_SU_1                     (0x00000002)
#define RTC_ALRMAR_SU_2                     (0x00000004)
#define RTC_ALRMAR_SU_3                     (0x00000008)

/* RTC alarm B register */
#define RTC_ALRMBR_MSK4                     (0x80000000)
#define RTC_ALRMBR_WDSEL                    (0x40000000)
#define RTC_ALRMBR_DT                       (0x30000000)
#define RTC_ALRMBR_DT_0                     (0x10000000)
#define RTC_ALRMBR_DT_1                     (0x20000000)
#define RTC_ALRMBR_DU                       (0x0F000000)
#define RTC_ALRMBR_DU_0                     (0x01000000)
#define RTC_ALRMBR_DU_1                     (0x02000000)
#define RTC_ALRMBR_DU_2                     (0x04000000)
#define RTC_ALRMBR_DU_3                     (0x08000000)
#define RTC_ALRMBR_MSK3                     (0x00800000)
#define RTC_ALRMBR_PM                       (0x00400000)
#define RTC_ALRMBR_HT                       (0x00300000)
#define RTC_ALRMBR_HT_0                     (0x00100000)
#define RTC_ALRMBR_HT_1                     (0x00200000)
#define RTC_ALRMBR_HU                       (0x000F0000)
#define RTC_ALRMBR_HU_0                     (0x00010000)
#define RTC_ALRMBR_HU_1                     (0x00020000)
#define RTC_ALRMBR_HU_2                     (0x00040000)
#define RTC_ALRMBR_HU_3                     (0x00080000)
#define RTC_ALRMBR_MSK2                     (0x00008000)
#define RTC_ALRMBR_MNT                      (0x00007000)
#define RTC_ALRMBR_MNT_0                    (0x00001000)
#define RTC_ALRMBR_MNT_1                    (0x00002000)
#define RTC_ALRMBR_MNT_2                    (0x00004000)
#define RTC_ALRMBR_MNU                      (0x00000F00)
#define RTC_ALRMBR_MNU_0                    (0x00000100)
#define RTC_ALRMBR_MNU_1                    (0x00000200)
#define RTC_ALRMBR_MNU_2                    (0x00000400)
#define RTC_ALRMBR_MNU_3                    (0x00000800)
#define RTC_ALRMBR_MSK1                     (0x00000080)
#define RTC_ALRMBR_ST                       (0x00000070)
#define RTC_ALRMBR_ST_0                     (0x00000010)
#define RTC_ALRMBR_ST_1                     (0x00000020)
#define RTC_ALRMBR_ST_2                     (0x00000040)
#define RTC_ALRMBR_SU                       (0x0000000F)
#define RTC_ALRMBR_SU_0                     (0x00000001)
#define RTC_ALRMBR_SU_1                     (0x00000002)
#define RTC_ALRMBR_SU_2                     (0x00000004)
#define RTC_ALRMBR_SU_3                     (0x00000008)

/* RTC write protection register */
#define RTC_WPR_KEY                         (0x000000FF)

/* RTC sub second register */
#define RTC_SSR_SS                          (0x0000FFFF)

/* RTC shift control register  */
#define RTC_SHIFTR_SUBFS                    (0x00007FFF)
#define RTC_SHIFTR_ADD1S                    (0x80000000)

/* RTC time stamp time register */
#define RTC_TSTR_PM                         (0x00400000)
#define RTC_TSTR_HT                         (0x00300000)
#define RTC_TSTR_HT_0                       (0x00100000)
#define RTC_TSTR_HT_1                       (0x00200000)
#define RTC_TSTR_HU                         (0x000F0000)
#define RTC_TSTR_HU_0                       (0x00010000)
#define RTC_TSTR_HU_1                       (0x00020000)
#define RTC_TSTR_HU_2                       (0x00040000)
#define RTC_TSTR_HU_3                       (0x00080000)
#define RTC_TSTR_MNT                        (0x00007000)
#define RTC_TSTR_MNT_0                      (0x00001000)
#define RTC_TSTR_MNT_1                      (0x00002000)
#define RTC_TSTR_MNT_2                      (0x00004000)
#define RTC_TSTR_MNU                        (0x00000F00)
#define RTC_TSTR_MNU_0                      (0x00000100)
#define RTC_TSTR_MNU_1                      (0x00000200)
#define RTC_TSTR_MNU_2                      (0x00000400)
#define RTC_TSTR_MNU_3                      (0x00000800)
#define RTC_TSTR_ST                         (0x00000070)
#define RTC_TSTR_ST_0                       (0x00000010)
#define RTC_TSTR_ST_1                       (0x00000020)
#define RTC_TSTR_ST_2                       (0x00000040)
#define RTC_TSTR_SU                         (0x0000000F)
#define RTC_TSTR_SU_0                       (0x00000001)
#define RTC_TSTR_SU_1                       (0x00000002)
#define RTC_TSTR_SU_2                       (0x00000004)
#define RTC_TSTR_SU_3                       (0x00000008)

/* RTC time stamp date register */
#define RTC_TSDR_WDU                        (0x0000E000)
#define RTC_TSDR_WDU_0                      (0x00002000)
#define RTC_TSDR_WDU_1                      (0x00004000)
#define RTC_TSDR_WDU_2                      (0x00008000)
#define RTC_TSDR_MT                         (0x00001000)
#define RTC_TSDR_MU                         (0x00000F00)
#define RTC_TSDR_MU_0                       (0x00000100)
#define RTC_TSDR_MU_1                       (0x00000200)
#define RTC_TSDR_MU_2                       (0x00000400)
#define RTC_TSDR_MU_3                       (0x00000800)
#define RTC_TSDR_DT                         (0x00000030)
#define RTC_TSDR_DT_0                       (0x00000010)
#define RTC_TSDR_DT_1                       (0x00000020)
#define RTC_TSDR_DU                         (0x0000000F)
#define RTC_TSDR_DU_0                       (0x00000001)
#define RTC_TSDR_DU_1                       (0x00000002)
#define RTC_TSDR_DU_2                       (0x00000004)
#define RTC_TSDR_DU_3                       (0x00000008)

/* RTC timestamp sub second register */
#define RTC_TSSSR_SS                        (0x0000FFFF)

/* RTC calibration register */
#define RTC_CALR_CALP                       (0x00008000)
#define RTC_CALR_CALW8                      (0x00004000)
#define RTC_CALR_CALW16                     (0x00002000)
#define RTC_CALR_CALM                       (0x000001FF)
#define RTC_CALR_CALM_0                     (0x00000001)
#define RTC_CALR_CALM_1                     (0x00000002)
#define RTC_CALR_CALM_2                     (0x00000004)
#define RTC_CALR_CALM_3                     (0x00000008)
#define RTC_CALR_CALM_4                     (0x00000010)
#define RTC_CALR_CALM_5                     (0x00000020)
#define RTC_CALR_CALM_6                     (0x00000040)
#define RTC_CALR_CALM_7                     (0x00000080)
#define RTC_CALR_CALM_8                     (0x00000100)

/* RTC tamper and alternate function configuration register */
#define RTC_TAFCR_ALARMOUTTYPE              (0x00040000)
#define RTC_TAFCR_TAMPPUDIS                 (0x00008000)
#define RTC_TAFCR_TAMPPRCH                  (0x00006000)
#define RTC_TAFCR_TAMPPRCH_0                (0x00002000)
#define RTC_TAFCR_TAMPPRCH_1                (0x00004000)
#define RTC_TAFCR_TAMPFLT                   (0x00001800)
#define RTC_TAFCR_TAMPFLT_0                 (0x00000800)
#define RTC_TAFCR_TAMPFLT_1                 (0x00001000)
#define RTC_TAFCR_TAMPFREQ                  (0x00000700)
#define RTC_TAFCR_TAMPFREQ_0                (0x00000100)
#define RTC_TAFCR_TAMPFREQ_1                (0x00000200)
#define RTC_TAFCR_TAMPFREQ_2                (0x00000400)
#define RTC_TAFCR_TAMPTS                    (0x00000080)
#define RTC_TAFCR_TAMP3TRG                  (0x00000040)
#define RTC_TAFCR_TAMP3E                    (0x00000020)
#define RTC_TAFCR_TAMP2TRG                  (0x00000010)
#define RTC_TAFCR_TAMP2E                    (0x00000008)
#define RTC_TAFCR_TAMPIE                    (0x00000004)
#define RTC_TAFCR_TAMP1TRG                  (0x00000002)
#define RTC_TAFCR_TAMP1E                    (0x00000001)

/* RTC alarm A sub second register */
#define RTC_ALRMASSR_MASKSS                 (0x0F000000)
#define RTC_ALRMASSR_MASKSS_0               (0x01000000)
#define RTC_ALRMASSR_MASKSS_1               (0x02000000)
#define RTC_ALRMASSR_MASKSS_2               (0x04000000)
#define RTC_ALRMASSR_MASKSS_3               (0x08000000)
#define RTC_ALRMASSR_SS                     (0x00007FFF)

/* RTC alarm B sub second register */
#define RTC_ALRMBSSR_MASKSS                 (0x0F000000)
#define RTC_ALRMBSSR_MASKSS_0               (0x01000000)
#define RTC_ALRMBSSR_MASKSS_1               (0x02000000)
#define RTC_ALRMBSSR_MASKSS_2               (0x04000000)
#define RTC_ALRMBSSR_MASKSS_3               (0x08000000)
#define RTC_ALRMBSSR_SS                     (0x00007FFF)

/* init struct */
typedef struct {
	uint32_t hour_format;
	uint32_t asynch_prediv;
	uint32_t synch_prediv;
} rtc_init_t;

#define RTC_HOURFORMAT_24              		(0x00000000)
#define RTC_HOURFORMAT_12              		(0x00000040)

/* rtc time */
typedef struct {
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
	uint8_t h12_am_pm;
} RTC_TIME_t;

#define RTC_H12_AM                     		(0x00)
#define RTC_H12_PM                     		(0x40)

/* rtc date */
typedef struct {
	uint8_t week_day;
	uint8_t month;
	uint8_t day;
	uint8_t year;
} RTC_DATE_t;

#define RTC_MONTH_JANUARY              		(0x01)
#define RTC_MONTH_FEBRUARY             		(0x02)
#define RTC_MONTH_MARCH                		(0x03)
#define RTC_MONTH_APRIL                		(0x04)
#define RTC_MONTH_MAY                  		(0x05)
#define RTC_MONTH_JUNE                 		(0x06)
#define RTC_MONTH_JULY                 		(0x07)
#define RTC_MONTH_AUGUST               		(0x08)
#define RTC_MONTH_SEPTEMBER            		(0x09)
#define RTC_MONTH_OCTOBER              		(0x10)
#define RTC_MONTH_NOVEMBER             		(0x11)
#define RTC_MONTH_DECEMBER             		(0x12)

#define RTC_WEEKDAY_MONDAY            		(0x01)
#define RTC_WEEKDAY_TUESDAY            		(0x02)
#define RTC_WEEKDAY_WEDNESDAY          		(0x03)
#define RTC_WEEKDAY_THURSDAY           		(0x04)
#define RTC_WEEKDAY_FRIDAY             		(0x05)
#define RTC_WEEKDAY_SATURDAY           		(0x06)
#define RTC_WEEKDAY_SUNDAY             		(0x07)

/* alarm struct */
typedef struct {
	RTC_TIME_t time;
	uint32_t mask;
	uint32_t date_weekday_sel;
	uint8_t date_weekday;
} rtc_alarm_t;

#define RTC_ALARMDATEWEEKSEL_DATE      		(0x00000000)
#define RTC_ALARMDATEWEEKSEL_WEEKDAY   		(0x40000000)

#define RTC_ALARMMASK_NONE                	(0x00000000)
#define RTC_ALARMMASK_DATEWEEKDAY         	(0x80000000)
#define RTC_ALARMMASK_HOURS               	(0x00800000)
#define RTC_ALARMMASK_MINUTES             	(0x00008000)
#define RTC_ALARMMASK_SECONDS             	(0x00000080)
#define RTC_ALARMMASK_ALL                 	(0x80808080)

#define RTC_FORMAT_BIN                    	(0x00000000)
#define RTC_FORMAT_BCD                    	(0x00000001)

#define RTC_ALARM_A                       	(0x00000100)
#define RTC_ALARM_B                       	(0x00000200)

#define RTC_WAKEUPCLOCK_RTCCLK_DIV16        (0x00000000)
#define RTC_WAKEUPCLOCK_RTCCLK_DIV8         (0x00000001)
#define RTC_WAKEUPCLOCK_RTCCLK_DIV4         (0x00000002)
#define RTC_WAKEUPCLOCK_RTCCLK_DIV2         (0x00000003)
#define RTC_WAKEUPCLOCK_CK_SPRE_16B      	(0x00000004)
#define RTC_WAKEUPCLOCK_CK_SPRE_17B      	(0x00000006)

#define RTC_OUTPUT_DISABLE             		(0x00000000)
#define RTC_OUTPUT_ALARMA              		(0x00200000)
#define RTC_OUTPUT_ALARMB              		(0x00400000)
#define RTC_OUTPUT_WAKEUP              		(0x00600000)

#define RTC_OUTPUTPOLARITY_HIGH           	(0x00000000)
#define RTC_OUTPUTPOLARITY_LOW            	(0x00100000)

#define RTC_IT_TS                         	(0x00008000)
#define RTC_IT_WUT                        	(0x00004000)
#define RTC_IT_ALRB                       	(0x00002000)
#define RTC_IT_ALRA                       	(0x00001000)
#define RTC_IT_TAMP                       	(0x00000004)
#define RTC_IT_TAMP1                      	(0x00020000)
#define RTC_IT_TAMP2                      	(0x00040000)
#define RTC_IT_TAMP3                      	(0x00080000)

/* deinitialize rtc */
void RTC_DeInit(void);
/* initialize rtc */
void RTC_Init(rtc_init_t *init);
/* init struct */
void RTC_StructInit(rtc_init_t *init);
/* enter init mode */
void RTC_EnterInitMode(void);
/* exit init mode */
void RTC_ExitInitMode(void);
/* write protection */
void RTC_WriteProtectionCmd(int state);
/* wait for synchro */
void RTC_WaitForSynchro(void);
/* Set the specified RTC Alarm. */
void RTC_SetAlarm(uint32_t format, uint32_t alarm, rtc_alarm_t *init);
/* alarm struct init */
void RTC_AlarmStructInit(rtc_alarm_t *init);
/* enable/disable alarm */
void RTC_AlarmCmd(uint32_t alarm, int state);
/* wakeup clock config */
void RTC_WakeUpClockConfig(uint32_t clock);
/* set wakeup counter */
void RTC_SetWakeUpCounter(uint32_t counter);
/* get counter */
uint32_t RTC_GetWakeUpCounter(void);
/* Enables or Disables the RTC WakeUp timer.*/
void RTC_WakeUpCmd(int state);
/* configure interrupt */
void RTC_ITConfig(uint32_t it, int state);
/* get flag status */
uint32_t RTC_GetFlagStatus(void);
/* clear flag */
void RTC_ClearFlag(uint32_t flag);



#endif /* RTC_H_ */

#include "main.h"

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
static void MX_TIM2_Init(void);

/* USER CODE BEGIN PFP */
void Set_Seg(char);
void disp_timedate(void);
void bye(void);

char disp_num[4];
int disp_digit=0;
int sw1=0;
int sw2=0;
int sw3=0;
int sw_p=15;
int sw_p3=10;
int change_stat=0;
int disp_mode=0; /* mode=0  mm:ss  1 hh:mm  2:MM:DD 3:YYYY */
int blink;
int blink_p;
int onoff;
int i_sleep=0;
int i_sleep_max=20000;


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  int s1,s2;
  if (htim == &htim2)
  {
 	  HAL_GPIO_WritePin(GPIOA, DIG0_Pin|DIG1_Pin|DIG2_Pin|DIG3_Pin, GPIO_PIN_RESET);
 	    if (disp_digit<4){
 	    Set_Seg(disp_num[disp_digit]);
 	    }
    switch (disp_digit){
    case 3: /* case 0: */
    	HAL_GPIO_WritePin(GPIOA,DIG0_Pin, GPIO_PIN_SET);
    	break;
    case 2:/* case 1: */
    	HAL_GPIO_WritePin(GPIOA,DIG1_Pin, GPIO_PIN_SET);
    	break;
    case 1:/* case 2: */
    	HAL_GPIO_WritePin(GPIOA,DIG2_Pin, GPIO_PIN_SET);
    	break;
    case 0:/* case 3: */
    	HAL_GPIO_WritePin(GPIOA,DIG3_Pin, GPIO_PIN_SET);
    	break;
    case 4:
    	/* __disable_irq();*/
      	HAL_GPIO_WritePin(GPIOA, SEGA_Pin|SEGB_Pin|SEGD_Pin|SEGE_Pin|SEGF_Pin|SEGG_Pin, GPIO_PIN_RESET);
      	HAL_GPIO_WritePin(SEGC_GPIO_Port, SEGC_Pin, GPIO_PIN_RESET);

      	GPIO_InitStruct.Pin = SEGA_Pin|SEGB_Pin;
      	GPIO_InitStruct.Mode =  GPIO_MODE_INPUT;
      	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
      	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

      	HAL_GPIO_WritePin(GPIOA,DIG0_Pin, GPIO_PIN_SET);
      	s1=s2=0;
      	s1=HAL_GPIO_ReadPin(GPIOA,SEGA_Pin);
      	s2=HAL_GPIO_ReadPin(GPIOA,SEGB_Pin);
        if ((s1==1)&(s2==1)) {
        	sw3++;
        	i_sleep=0;
        	sw1=sw2=0;
        } else if (s1==1) {
        	sw1++;
           	i_sleep=0;
        	sw2=sw3=0;
        } else if (s2==1) {
        	sw2++;
           	i_sleep=0;
        	sw1=sw3=0;
        }

        HAL_GPIO_WritePin(GPIOA,DIG3_Pin, GPIO_PIN_RESET);

      	GPIO_InitStruct.Pin = SEGA_Pin|SEGB_Pin;
      	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
      	GPIO_InitStruct.Pull = GPIO_NOPULL;
      	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    	/* __enable_irq(); */

    	break;

    default:
       	break;
    }

    disp_digit++;
    if (disp_digit==5) disp_digit=0;

    i_sleep++;
  }
}

void Set_Seg(char num){
	  HAL_GPIO_WritePin(GPIOA, SEGA_Pin|SEGB_Pin|SEGD_Pin|SEGE_Pin|SEGF_Pin|SEGG_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(SEGC_GPIO_Port, SEGC_Pin, GPIO_PIN_RESET);

	  if (onoff==1){
		  switch(num) {
		  case '0':
			  HAL_GPIO_WritePin(GPIOA, SEGA_Pin|SEGB_Pin|SEGD_Pin|SEGE_Pin|SEGF_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(SEGC_GPIO_Port, SEGC_Pin, GPIO_PIN_SET);
			  break;
		  case '1':
			  /*HAL_GPIO_WritePin(GPIOA, SEGB_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(SEGC_GPIO_Port, SEGC_Pin, GPIO_PIN_SET);*/
			  HAL_GPIO_WritePin(GPIOA, SEGE_Pin|SEGF_Pin, GPIO_PIN_SET);
			  break;
		  case '2':
			  HAL_GPIO_WritePin(GPIOA, SEGA_Pin|SEGB_Pin|SEGD_Pin|SEGE_Pin|SEGG_Pin, GPIO_PIN_SET);
			  break;
		  case '3':
			  /*HAL_GPIO_WritePin(GPIOA, SEGA_Pin|SEGB_Pin|SEGD_Pin|SEGG_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(SEGC_GPIO_Port, SEGC_Pin, GPIO_PIN_SET);*/
			  HAL_GPIO_WritePin(GPIOA, SEGA_Pin|SEGD_Pin|SEGE_Pin|SEGF_Pin|SEGG_Pin, GPIO_PIN_SET);
			  break;
		  case '4':
			  /*HAL_GPIO_WritePin(GPIOA, SEGB_Pin|SEGF_Pin|SEGG_Pin, GPIO_PIN_SET);*/
			  HAL_GPIO_WritePin(GPIOA, SEGE_Pin|SEGF_Pin|SEGG_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(SEGC_GPIO_Port, SEGC_Pin, GPIO_PIN_SET);
			  break;
		  case '5':
			  HAL_GPIO_WritePin(GPIOA, SEGA_Pin|SEGD_Pin|SEGF_Pin|SEGG_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(SEGC_GPIO_Port, SEGC_Pin, GPIO_PIN_SET);
			  break;
		  case '6':
			  /*HAL_GPIO_WritePin(GPIOA, SEGA_Pin|SEGD_Pin|SEGE_Pin|SEGF_Pin|SEGG_Pin, GPIO_PIN_SET);*/
			  HAL_GPIO_WritePin(GPIOA, SEGA_Pin|SEGB_Pin|SEGD_Pin|SEGF_Pin|SEGG_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(SEGC_GPIO_Port, SEGC_Pin, GPIO_PIN_SET);
			  break;
		  case '7':
			  /*HAL_GPIO_WritePin(GPIOA, SEGA_Pin|SEGB_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(SEGC_GPIO_Port, SEGC_Pin, GPIO_PIN_SET);*/
			  HAL_GPIO_WritePin(GPIOA, SEGD_Pin|SEGE_Pin|SEGF_Pin, GPIO_PIN_SET);
			  break;
		  case '8':
			  HAL_GPIO_WritePin(GPIOA, SEGA_Pin|SEGB_Pin|SEGD_Pin|SEGE_Pin|SEGF_Pin|SEGG_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(SEGC_GPIO_Port, SEGC_Pin, GPIO_PIN_SET);
			  break;
		  case '9':
			  /*HAL_GPIO_WritePin(GPIOA, SEGA_Pin|SEGB_Pin|SEGD_Pin|SEGF_Pin|SEGG_Pin, GPIO_PIN_SET);*/
			  HAL_GPIO_WritePin(GPIOA, SEGA_Pin|SEGD_Pin|SEGE_Pin|SEGF_Pin|SEGG_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(SEGC_GPIO_Port, SEGC_Pin, GPIO_PIN_SET);
			  break;
		  case ':':
			  break;
		  case 'B':
			  HAL_GPIO_WritePin(GPIOA, SEGA_Pin|SEGB_Pin|SEGF_Pin|SEGG_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(SEGC_GPIO_Port, SEGC_Pin, GPIO_PIN_SET);
			  break;
		  case 'E':
			  HAL_GPIO_WritePin(GPIOA, SEGA_Pin|SEGB_Pin|SEGD_Pin|SEGG_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(SEGC_GPIO_Port, SEGC_Pin, GPIO_PIN_SET);
			  break;
		  case 'T':
			  HAL_GPIO_WritePin(GPIOA, SEGA_Pin|SEGB_Pin|SEGG_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(SEGC_GPIO_Port, SEGC_Pin, GPIO_PIN_SET);
			  break;
		  case 'Y':
			  /*HAL_GPIO_WritePin(GPIOA, SEGB_Pin|SEGD_Pin|SEGF_Pin|SEGG_Pin, GPIO_PIN_SET);*/
			  HAL_GPIO_WritePin(GPIOA, SEGA_Pin|SEGE_Pin|SEGF_Pin|SEGG_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(SEGC_GPIO_Port, SEGC_Pin, GPIO_PIN_SET);
			  break;
		  case 'o':
			  HAL_GPIO_WritePin(GPIOA, SEGA_Pin|SEGB_Pin|SEGF_Pin|SEGG_Pin, GPIO_PIN_SET);
			  break;
		  case 'O':
			  HAL_GPIO_WritePin(GPIOA, SEGD_Pin|SEGE_Pin|SEGG_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(SEGC_GPIO_Port, SEGC_Pin, GPIO_PIN_SET);
			  break;
		  case ' ':
			  break;
		  default:
			  break;
		  }
	  }

	  blink++;
	  if (blink_p>0){
		  if (blink>blink_p){
			  blink = 0;
			  onoff = 1 - onoff;
		  }
	  } else {
		  onoff = 1;
	  }
}


void disp_timedate(void)
{

    RTC_DateTypeDef date;
    RTC_TimeTypeDef time;

    uint8_t  mm,ss;

    HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BCD);

    switch (disp_mode){
    case 0:
        mm = time.Hours;
       	ss = time.Minutes;
    	break;
    case 1:
        mm = time.Minutes;
       	ss = time.Seconds;
    	break;
    case 2:
    	mm= date.Month;
    	if ((mm>>4)==0) mm=0b10100000 | (mm & 0x0f);
    	ss = date.Date;
    	if ((ss>>4)==0) ss=0b10100000 | (ss & 0x0f);
    	break;
    case 3:
    	mm=0b00100000;
    	ss=date.Year;
    	break;
    default:
    	mm=0;
    	ss=0;
    	break;
    }

   	disp_num[2] = '0' + (mm & 0x0f);
   	mm >>= 4;
   	disp_num[3] = '0' + mm ;

   	disp_num[0] = '0' + (ss & 0x0f);
   	ss >>= 4;
   	disp_num[1] = '0' + ss ;

}

void bye(void)
{
	char msg[10]={' ',' ',' ','B','Y','E',' ',' ',' ',' '};

    if (i_sleep>i_sleep_max) {
    	for (uint8_t i=0; i<7; i++){
    		for (uint8_t j=3; j>0; j--){
    			disp_num[j]=disp_num[j-1];
    		}
    		disp_num[0] = msg[i];
    		HAL_Delay(200);
    	}
  	HAL_Delay(1000);
    HAL_PWR_EnterSTANDBYMode();
    }
}

void time_correction()
{
	int8_t loop=0;
	int8_t s_hour, s_minute, s_second, s_month, s_date, s_year, sec_old;

	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef sDate = {0};

	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BCD);

	s_hour = (sTime.Hours & 0x0f) + 10* (sTime.Hours>>4);
	s_minute = (sTime.Minutes & 0x0f) + 10* (sTime.Minutes>>4);
	s_second = (sTime.Seconds & 0x0f) + 10* (sTime.Seconds>>4);
	s_month = (sDate.Month & 0x0f) + 10* (sDate.Month>>4);
	s_date = (sDate.Date & 0x0f) + 10* (sDate.Date>>4);
	s_year = (sDate.Year & 0x0f) + 10* (sDate.Year>>4);
	sec_old = s_second;

	while (loop==0){
		HAL_Delay(100);

		HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BCD);
		HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BCD);

		s_hour = (sTime.Hours & 0x0f) + 10* (sTime.Hours>>4);
		s_minute = (sTime.Minutes & 0x0f) + 10* (sTime.Minutes>>4);
		s_second = (sTime.Seconds & 0x0f) + 10* (sTime.Seconds>>4);
		s_month = (sDate.Month & 0x0f) + 10* (sDate.Month>>4);
		s_date = (sDate.Date & 0x0f) + 10* (sDate.Date>>4);
		s_year = (sDate.Year & 0x0f) + 10* (sDate.Year>>4);

		if (s_second != sec_old){
			HAL_Delay(1000);
			s_second += 1;
			if (s_second > 59){
				s_second = 0;
				s_minute += 1;
			}
			if (s_minute > 59){
				s_minute = 0;
				s_hour += 1;
			}
			if (s_hour > 23){
				s_hour = 0;
				s_date += 1;
			}

			sTime.Hours = s_hour;
			sTime.Minutes = s_minute;
			sTime.Seconds = s_second;
			HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
			sDate.WeekDay = RTC_WEEKDAY_WEDNESDAY;
			sDate.Month = s_month;
			sDate.Date = s_date;
			sDate.Year = s_year;
			HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
			loop=1;
		}
		sec_old = s_second;
	}
}


int main(void)
{

 RTC_TimeTypeDef sTime = {0};
 RTC_DateTypeDef sDate = {0};

 uint8_t set_mode, set_point, ss, date_max;
 int8_t s_hour, s_minute, s_month, s_date, s_year, inc;

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  MX_TIM2_Init();

  HAL_TIM_Base_Start_IT(&htim2);


  blink_p=200;
  blink=0;
  onoff=1;
  set_mode=0;

  while (1)
  {

	    while (set_mode==0){ /* time display mode */
	    	blink_p=0;
	    	if (sw3>sw_p3) {
	    		set_mode=1;
	    		set_point=0;
	    		sw3=0;

	    	    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BCD);
	    	    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BCD);

	    		s_hour = (sTime.Hours & 0x0f) + 10* (sTime.Hours>>4);
	    		s_minute = (sTime.Minutes & 0x0f) + 10* (sTime.Minutes>>4);
	    		s_month = (sDate.Month & 0x0f) + 10* (sDate.Month>>4);
	    		s_date = (sDate.Date & 0x0f) + 10* (sDate.Date>>4);
	    		s_year = (sDate.Year & 0x0f) + 10* (sDate.Year>>4);
	    	}
	    	if(sw1>sw_p) {
	    		disp_mode++;
	    		sw1 = 0;
	    	}
	    	if(sw2>sw_p){
	    		disp_mode++;
	    		sw2 = 0;
	    	}
	    	if(disp_mode>3) disp_mode=0;
	    	if(disp_mode<0) disp_mode=3;

	    	disp_timedate();
	    	HAL_Delay(100);

	    	bye();

	    }

	    while (set_mode==1){
	    	if (sw3>sw_p3) {
	    		set_point++;
	    		sw1 = sw2 = 0;
	    		sw3 = 0;
	    	} else if (sw1>sw_p) {
	    		inc = 1;
	    		sw1 = 0;
	    	} else if (sw2>sw_p) {
	    		inc = -1;
	    		sw2 = 0;
	    	} else inc = 0;

	    	blink_p = 200;

	    	switch (set_point){
	    	case 0: /* Year */
	    		s_year += inc;
	    		if (s_year > 99) s_year = 0;
	    		if (s_year < 0 ) s_year = 99;
	    		disp_num[3] = 'Y';
	    		disp_num[2] = ' ';
	    		ss = s_year;
	    		break;

	    	case 1: /* Month */
	    		s_month += inc;
	    		if (s_month > 12) s_month = 1;
	    		if (s_month < 1 ) s_month = 12;
	    		disp_num[3] = 'O';
	    		disp_num[2] = ' ';
	    		ss = s_month;
	    		break;

	    	case 2: /* Date */
		    	s_date += inc;
		    	switch (s_month){
		    	case 1:
		    	case 3:
		    	case 5:
		    	case 7:
		    	case 8:
		    	case 10:
		    	case 12:
		    		date_max = 31;
		    		break;
		    	case 4:
		    	case 6:
		    	case 9:
		    	case 11:
		    		date_max = 30;
		    		break;
		    	case 2:
		    		date_max = 29;
		    		break;
		    	}
		    	if (s_date > date_max) s_date = 1;
		    	if (s_date < 1) s_date = date_max;
		    	disp_num[3] = 'o';
	    		disp_num[2] = ' ';
	    		ss = s_date;
	    		break;

	    	case 3: /* Hour */
	    		s_hour += inc;
			    if (s_hour > 23) s_hour = 0;
			    if (s_hour < 0 ) s_hour = 23;
	    		disp_num[3] = ' ';
	    		disp_num[2] = 'O';
	    		ss = s_hour;
	    		break;

	    	case 4: /* Minute */
	    		s_minute += inc;
		    	if (s_minute > 59) s_minute = 0;
		    	if (s_minute < 0 ) s_minute = 59;
	    		disp_num[3] = ' ';
	    		disp_num[2] = 'o';
	    		ss = s_minute;
	    		break;

	    	case 5:
	    		set_mode = 0;
	    		/* RTC set */
	    		sTime.Hours = s_hour;
	    		sTime.Minutes = s_minute;
	    		sTime.Seconds = 0;
	    		HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	    	    sDate.WeekDay = RTC_WEEKDAY_WEDNESDAY;
	       	    sDate.Month = s_month;
	      	    sDate.Date = s_date;
	      	    sDate.Year = s_year;
	      	    HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

		    	blink_p=0;

	    		disp_num[3] = '5';
	    		disp_num[2] = 'E';
	    		disp_num[1] = 'T';
	    		disp_num[0] = ' ';
		    	HAL_Delay(600);
	      	    break;

	    	default:
	    		break;
	    	}

	    	if (set_mode == 1) {
	    		disp_num[0] = '0' + (ss % 10 );
	    		ss /= 10;
	    		if (ss==0) {
	    			disp_num[1] = ' ';
	    		} else {
	    			disp_num[1] = '0' + ss ;
	    		}
	    	}
	    	HAL_Delay(200);

	    	bye();

	    }
  }
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}


static void MX_RTC_Init(void)
{

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;

  if ((RCC->CSR & RCC_CSR_RTCEN)==0)
    {
       if(HAL_RTC_Init(&hrtc)!=HAL_OK)
       {
          Error_Handler();
        }
    }
    else//RTC初期化済の場合
    {
    	HAL_RTC_MspInit(&hrtc);

    }

  /* USER CODE BEGIN Check_RTC_BKUP */
#define MAGIC_NO 0x12a5

  if(HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR0) != MAGIC_NO)
  {
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    sTime.Hours = 22;
    sTime.Minutes = 11;
    sTime.Seconds = 0;
    if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
    {
      Error_Handler();
    }
    sDate.WeekDay = RTC_WEEKDAY_WEDNESDAY;
    sDate.Month = RTC_MONTH_JULY;
    sDate.Date = 4;
    sDate.Year = 24;
    if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
    {
      Error_Handler();
    }
    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR0, MAGIC_NO);
  }
  /* RTC calibration  CALP=1 CALM=378=0b101111010 +127.8 ppm */
  /*
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  RTC->CALR = RTC_CALR_CALP|RTC_CALR_CALM_1|RTC_CALR_CALM_3|RTC_CALR_CALM_4|
		       RTC_CALR_CALM_5|RTC_CALR_CALM_6|RTC_CALR_CALM_8 ;

  RTC->WPR = 0xFE;
  RTC->WPR = 0x64;
  */
  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date

  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
 */
  /** Enable the WakeUp
  */
  /*if (HAL_RTCEx_SetWakeUpTimer(&hrtc, 0, RTC_WAKEUPCLOCK_CK_SPRE_16BITS) != HAL_OK)
  {
    Error_Handler();
  }*/
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4196;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SEGB_Pin|SEGA_Pin|SEGG_Pin|SEGF_Pin
                          |DIG0_Pin|DIG1_Pin|DIG2_Pin|DIG3_Pin
                          |SEGE_Pin|SEGD_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SEGC_GPIO_Port, SEGC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : SEGB_Pin SEGA_Pin SEGG_Pin SEGF_Pin
                           DIG0_Pin DIG1_Pin DIG2_Pin DIG3_Pin
                           SEGE_Pin SEGD_Pin */
  GPIO_InitStruct.Pin = SEGB_Pin|SEGA_Pin|SEGG_Pin|SEGF_Pin
                          |DIG0_Pin|DIG1_Pin|DIG2_Pin|DIG3_Pin
                          |SEGE_Pin|SEGD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : SEGC_Pin */
  GPIO_InitStruct.Pin = SEGC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SEGC_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

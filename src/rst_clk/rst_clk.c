#include "rst_clk.h"
void RST_CLK_GetClocksFreq(RST_CLK_FreqTypeDef* RST_CLK_Clocks)
{
  uint32_t cpu_c1_freq, cpu_c2_freq, cpu_c3_freq;
  uint32_t adc_c1_freq, adc_c3_freq;
  uint32_t adciu_c1_freq, adciu_c3_freq;
  uint32_t hsi_c1_freq, hse_c1_freq;
  uint32_t per_c1_freq/*, per_c2_freq*/;
  uint32_t pll_mul;
  uint32_t temp;



  /* Compute CPU_CLK, ADC_CLK, ADCIU_CLK, RTCHSI, RTCHSE clocks frequencies */

  /* Compute CPU_CLK frequency */

  /* Determine CPU_C1 frequency */
  if( RST_CLK->CPU_CLOCK & (2 << RST_CLK_CPU_CLOCK_CPU_C1_SEL_Pos) ) {
    cpu_c1_freq = HSE_Value;
  }
  else {
    cpu_c1_freq = HSI_Value;
  }
  if( RST_CLK->CPU_CLOCK & (1 << RST_CLK_CPU_CLOCK_CPU_C1_SEL_Pos) ) {
    cpu_c1_freq /= 2;
  }

  /* Determine CPU_C2 frequency */
  cpu_c2_freq = cpu_c1_freq;

  /* Determine CPU PLL output frequency */
  pll_mul = ((RST_CLK->PLL_CONTROL >> RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos)
		  & (uint32_t) 0x0F) + 1;
  if (RST_CLK->CPU_CLOCK & (1 << RST_CLK_CPU_CLOCK_CPU_C2_SEL_Pos)) {
    cpu_c2_freq *= pll_mul;
  }

  /*Select CPU_CLK from HSI, CPU_C3, LSE, LSI cases */
  switch ((RST_CLK->CPU_CLOCK >> RST_CLK_CPU_CLOCK_HCLK_SEL_Pos)
      & (uint32_t) 0x03) {
    case 0:
      /* HSI */
      RST_CLK_Clocks->CPU_CLK_Frequency = HSI_Value;
      break;
    case 1:
      /* CPU_C3 */
      /* Determine CPU_C3 frequency */
      if ((RST_CLK->CPU_CLOCK >> RST_CLK_CPU_CLOCK_CPU_C3_SEL_Pos
          & (uint32_t) 0x08) == 0x00) {
        cpu_c3_freq = cpu_c2_freq;
      }
      else {
        cpu_c3_freq = cpu_c2_freq
            / (1
                << ((RST_CLK->CPU_CLOCK
                    >> RST_CLK_CPU_CLOCK_CPU_C3_SEL_Pos
                    & (uint32_t) 0x07) + 1));
      }
      RST_CLK_Clocks->CPU_CLK_Frequency = cpu_c3_freq;
      break;
    case 2:
      /* LSE */
      RST_CLK_Clocks->CPU_CLK_Frequency = LSE_Value;
      break;
    default: /* case 3 */
      /* LSI */
      RST_CLK_Clocks->CPU_CLK_Frequency = LSI_Value;
      break;
  }

  /* Compute RTCHSI_CLK frequency */
  temp = RST_CLK->RTC_CLOCK >> RST_CLK_RTC_CLOCK_HSI_SEL_Pos;
  if ((temp & 0x08U) == 0) {
    hsi_c1_freq = HSI_Value;
  }
  else {
    temp = 1 << ((temp & 0x07U) + 1);
    hsi_c1_freq = HSI_Value / temp;
  }
  RST_CLK_Clocks->RTCHSI_Frequency = hsi_c1_freq;

  /* Compute RTCHSE_CLK frequency */
  temp = RST_CLK->RTC_CLOCK >> RST_CLK_RTC_CLOCK_HSE_SEL_Pos;
  if ((temp & 0x08U) == 0) {
    hse_c1_freq = HSE_Value;
  }
  else {
    temp = 1 << ((temp & 0x07U) + 1);
    hse_c1_freq = HSE_Value / temp;
  }
  RST_CLK_Clocks->RTCHSE_Frequency = hse_c1_freq;

  /* Determine clock frequency per_c1 and per_c2 */
  if(RST_CLK->PER_CLOCK & 0x02)
	  per_c1_freq = LSE_Value;
  else
	  per_c1_freq = LSI_Value;

  if(RST_CLK->PER_CLOCK & 0x01)
	  per_c1_freq /= 2;

 
  /* Compute ADC_CLK frequency */

  /* Select ADC_C1 from cpu_c1, per_c1_freq, cpu_c2_freq, HSI_Value cases */
  switch ((RST_CLK->ADC_MCO_CLOCK >> RST_CLK_ADC_MCO_CLOCK_ADC_C1_SEL_Pos)
      & (uint32_t) 0x03) {
    case 0:
      /* ADC_C1 */
      adc_c1_freq = cpu_c1_freq;
      break;
    case 1:
      /* ADC_C1 */
      adc_c1_freq = per_c1_freq;
      break;
    case 2:
      /* ADC_C2 */
      adc_c1_freq = cpu_c2_freq;
      break;
    default: /* case 3 */
      /* ADC_C2 */
      adc_c1_freq = HSI_Value;
      break;
  }


  temp = RST_CLK->ADC_MCO_CLOCK >> RST_CLK_ADC_MCO_CLOCK_ADC_C3_SEL_Pos;
  if ((temp & 0x08U) == 0) {
    adc_c3_freq = adc_c1_freq;
  }
  else {
    temp = 1 << ((temp & 0x07U) + 1);
    adc_c3_freq = adc_c1_freq / temp;
  }

  RST_CLK_Clocks->ADC_CLK_Frequency = adc_c3_freq;

  /* Compute ADCIU_CLK frequency */

  /* Select ADCIU_C1 from cpu_c1, per_c1_freq, cpu_c2_freq, HSI_Value cases */
  switch ((RST_CLK->ADC_MCO_CLOCK >> RST_CLK_ADC_MCO_CLOCK_ADCIU_C1_SEL_Pos)
      & (uint32_t) 0x03) {
    case 0:
      /* ADCIU_C1 */
      adciu_c1_freq = cpu_c1_freq;
      break;
    case 1:
      /* ADCIU_C1 */
      adciu_c1_freq = per_c1_freq;
      break;
    case 2:
      /* ADCIU_C1 */
      adciu_c1_freq = cpu_c2_freq;
      break;
    default: /* case 3 */
      /* ADCIU_C1 */
      adciu_c1_freq = HSI_Value;
      break;
  }


  temp = RST_CLK->ADC_MCO_CLOCK >> RST_CLK_ADC_MCO_CLOCK_ADCIU_C3_SEL_Pos;
  if ((temp & 0x08U) == 0) {
    adciu_c3_freq = adciu_c1_freq;
  }
  else {
    temp = 1 << ((temp & 0x07U) + 1);
    adciu_c3_freq = adciu_c1_freq / temp;
  }

  RST_CLK_Clocks->ADCIU_CLK_Frequency = adciu_c3_freq;

}

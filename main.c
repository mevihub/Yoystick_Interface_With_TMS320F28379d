
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "F2837xD_device.h"
#include "F28x_Project.h"
#include "F2837xD_Examples.h"

#include "driverlib.h"
#include "device.h"

#define     EX_ADC_RESOLUTION       12

void gpio_init();
void ConfigADC(uint32_t ADC_BASE);
void initADC_SOC(void);

uint16_t Adc_Result_1,Adc_Result_2;

void main(void)
{


    Device_init();
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();


    ConfigADC(ADCA_BASE);
    initADC_SOC();
    gpio_init();
    EINT;
    ERTM;

    while(1)
       {

        // Convert, wait for completion, and store results
           ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER0);
            ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER2);

            while(ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1) == false)
                {

                }
            ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

            ////           // Store results
              Adc_Result_1= ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
              Adc_Result_2 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER2);


              if( (Adc_Result_1 <2000))
                        {
                            GpioDataRegs.GPCTOGGLE.bit.GPIO67=1;
                            DEVICE_DELAY_US(50000);
                        }

                        else if(Adc_Result_1>4000)
                        {
                            GpioDataRegs.GPDTOGGLE.bit.GPIO111 =1;
                            DEVICE_DELAY_US(50000);
                        }
                        else if( (Adc_Result_2 <2000))
                        {
                            GpioDataRegs.GPBTOGGLE.bit.GPIO60=1;
                            DEVICE_DELAY_US(50000);
                        }
                        else if(Adc_Result_2>4090)
                        {
                            GpioDataRegs.GPATOGGLE.bit.GPIO22=1;
                            DEVICE_DELAY_US(50000);
                        }

                        else {
                            GpioDataRegs.GPCSET.bit.GPIO67=1;
                            GpioDataRegs.GPDSET.bit.GPIO111=1;
                            GpioDataRegs.GPBSET.bit.GPIO60=1;
                            GpioDataRegs.GPASET.bit.GPIO22=1;
                            }


       }


}


void ConfigADC(uint32_t ADC_BASE)
{
    EALLOW;

    ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_4_0);

#if(EX_ADC_RESOLUTION == 12)
    {
        ADC_setMode(ADC_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
    }
#elif(EX_ADC_RESOLUTION == 16)
    {
      ADC_setMode(ADCA_BASE, ADC_RESOLUTION_16BIT, ADC_MODE_DIFFERENTIAL);
    }
#endif
    ADC_setInterruptPulseMode(ADC_BASE, ADC_PULSE_END_OF_CONV);
    ADC_enableConverter(ADC_BASE);
    DEVICE_DELAY_US(1000);
    EDIS;
}



void initADC_SOC(void)
{
#if(EX_ADC_RESOLUTION == 12)
    {
        ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 15);
        ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN2, 15);

    }
#elif(EX_ADC_RESOLUTION == 16)
    {
        ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0,64);
    }
#endif
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER2);

    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);

    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);


}


void gpio_init()
{
    EALLOW;


    // select gpio for led

    GpioCtrlRegs.GPCMUX1.bit.GPIO67=0;      // 0=GPIO,  1=EPWM1A,  2=Resv,  3=Resv
    GpioCtrlRegs.GPCDIR.bit.GPIO67=1;       // 1=OUTput,  0=INput
    GpioCtrlRegs.GPCPUD.bit.GPIO67=0;       // 0: Enables the Pull-Up. 1: Disables the Pull-Up.
    GpioCtrlRegs.GPCCSEL1.bit.GPIO67=0;     //xx00: CPU1 selected    xx01: CPU1.CLA1 selected
                                               //xx10: CPU2 selected xx11: CPU2.CLA1 selected
    GpioCtrlRegs.GPDMUX1.bit.GPIO111=0;      // 0=GPIO,  1=EPWM1A,  2=Resv,  3=Resv
    GpioCtrlRegs.GPDDIR.bit.GPIO111=1;       // 1=OUTput,  0=INput
    GpioCtrlRegs.GPDPUD.bit.GPIO111=0;       // 0: Enables the Pull-Up. 1: Disables the Pull-Up.
    GpioCtrlRegs.GPDCSEL2.bit.GPIO111=0;     //xx00: CPU1 selected    xx01: CPU1.CLA1 selected



    GpioCtrlRegs.GPBMUX2.bit.GPIO60=0;      // 0=GPIO,  1=EPWM1A,  2=Resv,  3=Resv
    GpioCtrlRegs.GPBDIR.bit.GPIO60=1;       // 1=OUTput,  0=INput
    GpioCtrlRegs.GPBPUD.bit.GPIO60=0;       // 0: Enables the Pull-Up. 1: Disables the Pull-Up.
    GpioCtrlRegs.GPBCSEL4.bit.GPIO60=0;     //xx00: CPU1 selected    xx01: CPU1.CLA1 selected

    GpioCtrlRegs.GPAMUX2.bit.GPIO22=0;      // 0=GPIO,  1=EPWM1A,  2=Resv,  3=Resv
    GpioCtrlRegs.GPADIR.bit.GPIO22=1;       // 1=OUTput,  0=INput
    GpioCtrlRegs.GPAPUD.bit.GPIO22=0;       // 0: Enables the Pull-Up. 1: Disables the Pull-Up.
    GpioCtrlRegs.GPACSEL3.bit.GPIO22=0;     //xx00: CPU1 selected    xx01: CPU1.CLA1 selected


    EDIS;
}

//
// End of File
//

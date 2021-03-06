//###########################################################################
//
// FILE:   dma.c
//
// TITLE:  C28x DMA driver.
//
//###########################################################################
// $Copyright:  $
//###########################################################################

#include "dma.h"

//*****************************************************************************
//
// DMA_configAddresses
//
//*****************************************************************************
void DMA_configAddresses(uint32_t base, const void *destAddr,
                         const void *srcAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(DMA_isBaseValid(base));

    EALLOW;

    //
    // Set up SOURCE address.
    //
    HWREG(base + DMA_O_SRC_BEG_ADDR_SHADOW) = (uint32_t)srcAddr;
    HWREG(base + DMA_O_SRC_ADDR_SHADOW)     = (uint32_t)srcAddr;

    //
    // Set up DESTINATION address.
    //
    HWREG(base + DMA_O_DST_BEG_ADDR_SHADOW) = (uint32_t)destAddr;
    HWREG(base + DMA_O_DST_ADDR_SHADOW)     = (uint32_t)destAddr;

    EDIS;
}

//*****************************************************************************
//
// DMA_configBurst
//
//*****************************************************************************
void DMA_configBurst(uint32_t base, uint16_t size, int16_t srcStep,
                     int16_t destStep)
{
    //
    // Check the arguments.
    //
    ASSERT(DMA_isBaseValid(base));
    ASSERT((size >= 1U) || (size <= 32U));

    EALLOW;

    //
    // Set up BURST registers.
    //
    HWREGH(base + DMA_O_BURST_SIZE)     = size - 1U;
    HWREGH(base + DMA_O_SRC_BURST_STEP) = srcStep;
    HWREGH(base + DMA_O_DST_BURST_STEP) = destStep;

    EDIS;
}

//*****************************************************************************
//
// DMA_configTransfer
//
//*****************************************************************************
void DMA_configTransfer(uint32_t base, uint32_t transferSize, int16_t srcStep,
                        int16_t destStep)
{
    //
    // Check the arguments.
    //
    ASSERT(DMA_isBaseValid(base));
    ASSERT(transferSize <= 0x10000);

    EALLOW;

    //
    // Set up TRANSFER registers.
    //
    HWREGH(base + DMA_O_TRANSFER_SIZE)     = (uint16_t)(transferSize - 1U);
    HWREGH(base + DMA_O_SRC_TRANSFER_STEP) = srcStep;
    HWREGH(base + DMA_O_DST_TRANSFER_STEP) = destStep;

    EDIS;
}

//*****************************************************************************
//
// DMA_configWrap
//
//*****************************************************************************
void DMA_configWrap(uint32_t base, uint32_t srcWrapSize, int16_t srcStep,
                    uint32_t destWrapSize, int16_t destStep)
{
    //
    // Check the arguments.
    //
    ASSERT(DMA_isBaseValid(base));
    ASSERT((srcWrapSize <= 0x10000) || (destWrapSize <= 0x10000));

    EALLOW;

    //
    // Set up WRAP registers.
    //
    HWREGH(base + DMA_O_SRC_WRAP_SIZE) = (uint16_t)(srcWrapSize - 1U);
    HWREGH(base + DMA_O_SRC_WRAP_STEP) = srcStep;

    HWREGH(base + DMA_O_DST_WRAP_SIZE) = (uint16_t)(destWrapSize - 1U);
    HWREGH(base + DMA_O_DST_WRAP_STEP) = destStep;

    EDIS;
}

//*****************************************************************************
//
// DMA_configMode
//
//*****************************************************************************
void DMA_configMode(uint32_t base, DMA_Trigger trigger, uint32_t config)
{
    //
    // Check the arguments.
    //
    ASSERT(DMA_isBaseValid(base));

    EALLOW;

    //
    // Set up trigger selection in the CMA/CLA trigger source selection
    // registers. These are considered part of system control.
    //
    switch(base)
    {
        case DMA_CH1_BASE:
            //
            // Channel 1
            //
            HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL1) =
                (HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL1) &
                 ~((uint32_t)SYSCTL_DMACHSRCSEL1_CH1_M)) |
                ((uint32_t)trigger << SYSCTL_DMACHSRCSEL1_CH1_S);

            //
            // Set peripheral interrupt select bits to the channel number.
            //
            HWREGH(DMA_CH1_BASE + DMA_O_MODE) =
               (HWREGH(DMA_CH1_BASE + DMA_O_MODE) & ~DMA_MODE_PERINTSEL_M) | 1U;
            break;

        case DMA_CH2_BASE:
            //
            // Channel 2
            //
            HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL1) =
                (HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL1) &
                 ~((uint32_t)SYSCTL_DMACHSRCSEL1_CH2_M)) |
                ((uint32_t)trigger << SYSCTL_DMACHSRCSEL1_CH2_S);

            //
            // Set peripheral interrupt select bits to the channel number.
            //
            HWREGH(DMA_CH2_BASE + DMA_O_MODE) =
               (HWREGH(DMA_CH2_BASE + DMA_O_MODE) & ~DMA_MODE_PERINTSEL_M) | 2U;
            break;

        case DMA_CH3_BASE:
            //
            // Channel 3
            //
            HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL1) =
                (HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL1) &
                 ~((uint32_t)SYSCTL_DMACHSRCSEL1_CH3_M)) |
                ((uint32_t)trigger << SYSCTL_DMACHSRCSEL1_CH3_S);

            //
            // Set peripheral interrupt select bits to the channel number.
            //
            HWREGH(DMA_CH3_BASE + DMA_O_MODE) =
               (HWREGH(DMA_CH3_BASE + DMA_O_MODE) & ~DMA_MODE_PERINTSEL_M) | 3U;
            break;

        case DMA_CH4_BASE:
            //
            // Channel 4
            //
            HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL1) =
                (HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL1) &
                 ~((uint32_t)SYSCTL_DMACHSRCSEL1_CH4_M)) |
                ((uint32_t)trigger << SYSCTL_DMACHSRCSEL1_CH4_S);

            //
            // Set peripheral interrupt select bits to the channel number.
            //
            HWREGH(DMA_CH4_BASE + DMA_O_MODE) =
               (HWREGH(DMA_CH4_BASE + DMA_O_MODE) & ~DMA_MODE_PERINTSEL_M) | 4U;
            break;

        case DMA_CH5_BASE:
            //
            // Channel 5
            //
            HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL2) =
                (HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL2) &
                 ~((uint32_t)SYSCTL_DMACHSRCSEL2_CH5_M)) |
                ((uint32_t)trigger << SYSCTL_DMACHSRCSEL2_CH5_S);

            //
            // Set peripheral interrupt select bits to the channel number.
            //
            HWREGH(DMA_CH5_BASE + DMA_O_MODE) =
               (HWREGH(DMA_CH5_BASE + DMA_O_MODE) & ~DMA_MODE_PERINTSEL_M) | 5U;
            break;

        case DMA_CH6_BASE:
            //
            // Channel 6
            //
            HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL2) =
                (HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL2) &
                 ~((uint32_t)SYSCTL_DMACHSRCSEL2_CH6_M)) |
                ((uint32_t)trigger << SYSCTL_DMACHSRCSEL2_CH6_S);

            //
            // Set peripheral interrupt select bits to the channel number.
            //
            HWREGH(DMA_CH6_BASE + DMA_O_MODE) =
               (HWREGH(DMA_CH6_BASE + DMA_O_MODE) & ~DMA_MODE_PERINTSEL_M) | 6U;
            break;

        default:
            //
            // Invalid base.
            //
            break;
    }

    //
    // Write the configuration to the mode register.
    //
    HWREGH(base + DMA_O_MODE) &= ~(DMA_MODE_DATASIZE | DMA_MODE_CONTINUOUS |
                                   DMA_MODE_ONESHOT);
    HWREGH(base + DMA_O_MODE) |= config;

    EDIS;
}


#include "initialize_leds.h"
#include <ti/devices/msp/msp.h>
#include "hw_interface.h"

#define POWER_STARTUP_DELAY (16)
void InitializeGPIO() {
    // 1. Reset GPIO port (the one(s) for pins that you will use)
    GPIOA->GPRCM.RSTCTL = (GPIO_RSTCTL_KEY_UNLOCK_W | GPIO_RSTCTL_RESETSTKYCLR_CLR | GPIO_RSTCTL_RESETASSERT_ASSERT);
    GPIOB->GPRCM.RSTCTL = (GPIO_RSTCTL_KEY_UNLOCK_W | GPIO_RSTCTL_RESETSTKYCLR_CLR | GPIO_RSTCTL_RESETASSERT_ASSERT);
    // 2. Enable power on LED GPIO port
    GPIOA->GPRCM.PWREN = (GPIO_PWREN_KEY_UNLOCK_W | GPIO_PWREN_ENABLE_ENABLE);
    GPIOB->GPRCM.PWREN = (GPIO_PWREN_KEY_UNLOCK_W | GPIO_PWREN_ENABLE_ENABLE);

    delay_cycles(POWER_STARTUP_DELAY); // delay to enable GPIO to turn on and reset

    /* Code to initialize specific GPIO PIN */
    // PA0 is red led gpio
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM1)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001));//init PA0 LED 12A
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM2)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa1 led 11b
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM3)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa28 led 11a
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM10)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa5 led 10b
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM11)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa6 led 10a
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM14)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa7 led 9b
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM19)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa8 led 9a
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM20)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa9 led 8b
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM21)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa10 led 8a
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM22)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa11 led 7b
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM34)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa12 led 7a
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM35)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa13 led 6b
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM36)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa14 led 6a
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM37)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa15 led 5b
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM38)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa16 led 5a
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM39)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa17 led 4b
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM40)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa18 led 4a
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM46)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa21 led 3b
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM47)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa22 led 3a
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM53)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa23 led 2b
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM54)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa24 led 2a
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM55)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa25 led 1b
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM59)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa26 led 1a
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM60)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //init pa27 led 12b

    IOMUX->SECCFG.PINCM[(IOMUX_PINCM25)] = (IOMUX_PINCM_PC_CONNECTED | //init PB8 button
                            IOMUX_PINCM_INENA_ENABLE |      // Enable input
                            IOMUX_PINCM_PIPU_ENABLE |       // Enable pull-up
                            ((uint32_t) 0x00000001)); 

    GPIOA->DOUT31_0 = (0xFFFFFFFF); //Turn off all LEDs by default with active low
                      
    GPIOA->DOESET31_0 = (1 << 0); // PA0
    GPIOA->DOESET31_0 = (1 << 1); // PA1
    GPIOA->DOESET31_0 = (1 << 28); // PA28
    GPIOA->DOESET31_0 = (1 << 5);  // PA5
    GPIOA->DOESET31_0 = (1 << 6);  // PA6
    GPIOA->DOESET31_0 = (1 << 7);  // PA7
    GPIOA->DOESET31_0 = (1 << 8);  // PA8
    GPIOA->DOESET31_0 = (1 << 9);  // PA9
    GPIOA->DOESET31_0 = (1 << 10); // PA10
    GPIOA->DOESET31_0 = (1 << 11); // PA11
    GPIOA->DOESET31_0 = (1 << 12); // PA12
    GPIOA->DOESET31_0 = (1 << 13); // PA13
    GPIOA->DOESET31_0 = (1 << 14); // PA14
    GPIOA->DOESET31_0 = (1 << 15); // PA15
    GPIOA->DOESET31_0 = (1 << 16); // PA16
    GPIOA->DOESET31_0 = (1 << 17); // PA17
    GPIOA->DOESET31_0 = (1 << 18); // PA18
    GPIOA->DOESET31_0 = (1 << 21); // PA21
    GPIOA->DOESET31_0 = (1 << 22); // PA22
    GPIOA->DOESET31_0 = (1 << 23); // PA23
    GPIOA->DOESET31_0 = (1 << 24); // PA24
    GPIOA->DOESET31_0 = (1 << 25); // PA25
    GPIOA->DOESET31_0 = (1 << 26); // PA26
    GPIOA->DOESET31_0 = (1 << 27); // PA27
    GPIOB->DOESET31_0 &= ~(1 << 8); // set the button to INPUT mode
}


// PIC18F45K50 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

#if defined(__18F45K50)
#pragma config PLLSEL   = PLL3X     // PLL Selection (3x clock multiplier)
#pragma config CFGPLLEN = OFF       // PLL Enable Configuration bit (PLL Disabled (firmware controlled))
#pragma config CPUDIV   = NOCLKDIV  // CPU System Clock Postscaler (CPU uses system clock (no divide))
#pragma config LS48MHZ  = SYS48X8   // Low Speed USB mode with 48 MHz system clock (System clock at 48 MHz, USB clock divider is set to 8)
#pragma config FOSC     = INTOSCIO  // Oscillator Selection (Internal oscillator)
#pragma config PCLKEN   = OFF       // Primary Oscillator Shutdown (Primary oscillator shutdown firmware controlled)
#pragma config FCMEN    = OFF       // Fail-Safe Clock Monitor (Fail-Safe Clock Monitor disabled)
#pragma config IESO     = OFF       // Internal/External Oscillator Switchover (Oscillator Switchover mode disabled)
#pragma config nPWRTEN  = OFF       // Power-up Timer Enable (Power up timer disabled)
#pragma config BOREN    = SBORDIS   // Brown-out Reset Enable (BOR enabled in hardware (SBOREN is ignored))
#pragma config BORV     = 190       // Brown-out Reset Voltage (BOR set to 1.9V nominal)
#pragma config nLPBOR   = ON        // Low-Power Brown-out Reset (Low-Power Brown-out Reset enabled)
#pragma config WDTEN    = OFF       // Watchdog Timer Enable bits (WDT controlled by firmware (SWDTEN enabled))
#pragma config WDTPS    = 32768     // Watchdog Timer Postscaler (1:32768)
#pragma config CCP2MX   = RC1       // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN   = OFF       // PORTB A/D Enable bit (PORTB<5:0> pins are configured as digital I/O on Reset)
#pragma config T3CMX    = RB5       // Timer3 Clock Input MUX bit (T3CKI function is on RC0)
#pragma config SDOMX    = RC7       // SDO Output MUX bit (SDO function is on RC7)
#pragma config MCLRE    = ON        // Master Clear Reset Pin Enable (MCLR pin enabled; RE3 input disabled)
#pragma config STVREN   = ON        // Stack Full/Underflow Reset (Stack full/underflow will cause Reset)
#pragma config LVP      = OFF       // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT    = ON        // Dedicated In-Circuit Debug/Programming Port Enable (ICPORT disabled)
#pragma config XINST    = OFF       // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled)
#pragma config CP0      = OFF       // Block 0 Code Protect (Block 0 is not code-protected)
#pragma config CP1      = OFF       // Block 1 Code Protect (Block 1 is not code-protected)
#pragma config CP2      = OFF       // Block 2 Code Protect (Block 2 is not code-protected)
#pragma config CP3      = OFF       // Block 3 Code Protect (Block 3 is not code-protected)
#pragma config CPB      = OFF       // Boot Block Code Protect (Boot block is not code-protected)
#pragma config CPD      = OFF       // Data EEPROM Code Protect (Data EEPROM is not code-protected)
#pragma config WRT0     = OFF       // Block 0 Write Protect (Block 0 (0800-1FFFh) is not write-protected)
#pragma config WRT1     = OFF       // Block 1 Write Protect (Block 1 (2000-3FFFh) is not write-protected)
#pragma config WRT2     = OFF       // Block 2 Write Protect (Block 2 (04000-5FFFh) is not write-protected)
#pragma config WRT3     = OFF       // Block 3 Write Protect (Block 3 (06000-7FFFh) is not write-protected)
#pragma config WRTC     = OFF       // Configuration Registers Write Protect (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB     = OFF       // Boot Block Write Protect (Boot block (0000-7FFh) is not write-protected)
#pragma config WRTD     = OFF       // Data EEPROM Write Protect (Data EEPROM is not write-protected)
#pragma config EBTR0    = OFF       // Block 0 Table Read Protect (Block 0 is not protected from table reads executed in other blocks)
#pragma config EBTR1    = OFF       // Block 1 Table Read Protect (Block 1 is not protected from table reads executed in other blocks)
#pragma config EBTR2    = OFF       // Block 2 Table Read Protect (Block 2 is not protected from table reads executed in other blocks)
#pragma config EBTR3    = OFF       // Block 3 Table Read Protect (Block 3 is not protected from table reads executed in other blocks)
#pragma config EBTRB    = OFF       // Boot Block Table Read Protect (Boot block is not protected from table reads executed in other blocks)
#endif

#if defined(__18F4550)
#pragma config PLLDIV   = 5       // (20 MHz input)
#pragma config CPUDIV   = OSC1_PLL2
#pragma config USBDIV   = 2       // Clock source from 96MHz PLL/2
#pragma config FOSC     = HSPLL_HS
#pragma config FCMEN    = OFF
#pragma config IESO     = OFF
#pragma config PWRT     = OFF
#pragma config BOR      = ON
#pragma config BORV     = 3
#pragma config VREGEN   = ON
#pragma config WDT      = OFF
#pragma config WDTPS    = 32768
#pragma config MCLRE    = ON		// make MCLR an input-pin
#pragma config LPT1OSC  = OFF
#pragma config PBADEN   = OFF
#pragma config CCP2MX   = OFF
#pragma config STVREN   = ON
#pragma config LVP      = OFF
#pragma config ICPRT    = ON       // Dedicated In-Circuit Debug/Programming
#pragma config XINST    = OFF       // Extended Instruction Set
#pragma config CP0      = OFF
#pragma config CP1      = OFF
#pragma config CP2      = OFF
#pragma config CP3      = OFF
#pragma config CPB      = OFF
#pragma config CPD      = OFF
#pragma config WRT0     = OFF
#pragma config WRT1     = OFF
#pragma config WRT2     = OFF
#pragma config WRT3     = OFF
#pragma config WRTB     = OFF       // Boot Block Write Protection
#pragma config WRTC     = OFF
#pragma config WRTD     = OFF
#pragma config EBTR0    = OFF
#pragma config EBTR1    = OFF
#pragma config EBTR2    = OFF
#pragma config EBTR3    = OFF
#pragma config EBTRB    = OFF

#endif
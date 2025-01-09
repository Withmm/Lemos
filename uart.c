#include "types.h"
#include "uart.h"

/* UART0 = 0x10000000L 
 * reg = offset of reg
 */
#define UART_REG(reg) ((volatile u8 *)(UART0 + reg))

#define UART_READ(reg) (*(UART_REG(reg)))
#define UART_WRITE(reg, v) (*(UART_REG(reg)) = (v))

/*
 * Reference
 * [1]: TECHNICAL DATA ON 16550, http://byterunner.com/16550.html
 */

/*
 * UART control registers map. see [1] "PROGRAMMING TABLE"
 * note some are reused by multiple functions
 * 0 (write mode): THR/DLL
 * 1 (write mode): IER/DLM
 */
#define RHR 0   // Receive Holding Register (read mode)
#define THR 0   // Transmit Holding Register (write mode)
#define DLL 0   // LSB of Divisor Latch (write mode)
#define IER 1   // Interrupt Enable Register (write mode)
#define DLM 1   // MSB of Divisor Latch (write mode)
#define FCR 2   // FIFO Control Register (write mode)
#define ISR 2   // Interrupt Status Register (read mode)
#define LCR 3   // Line Control Register
#define MCR 4   // Modem Control Register
#define LSR 5   // Line Status Register
#define MSR 6   // Modem Status Register
#define SPR 7   // ScratchPad Register

/*
 * POWER UP DEFAULTS
 * IER = 0: TX/RX holding register interrupts are both disabled
 * ISR = 1: no interrupt penting
 * LCR = 0
 * MCR = 0
 * LSR = 60 HEX
 * MSR = BITS 0-3 = 0, BITS 4-7 = inputs
 * FCR = 0
 * TX = High
 * OP1 = High
 * OP2 = High
 * RTS = High
 * DTR = High
 * RXRDY = High
 * TXRDY = Low
 * INT = Low
 */

/*
 * LINE STATUS REGISTER (LSR)
 * LSR BIT 0:
 * 0 = no data in receive holding register or FIFO.
 * 1 = data has been receive and saved in the receive holding register or FIFO.
 * ......
 * LSR BIT 5:
 * 0 = transmit holding register is full. 16550 will not accept any data for transmission.
 * 1 = transmitter hold register (or FIFO) is empty. CPU can load the next character.
 * ......
 */
#define LSR_RX_READY (1 << 0)
#define LSR_TX_IDLE  (1 << 5)

void
uart_init(void)
{
	/* disable interrupts */
	UART_WRITE(IER, 0x00);

	/* Setting baud rate */
	u8 lcr = UART_READ(LCR);
	UART_WRITE(LCR, lcr | (1 << 7));
	UART_WRITE(DLL, 0x03);
	UART_WRITE(DLM, 0x00);

	lcr = 0;
	UART_WRITE(LCR, lcr | (3 << 0));
}

int
uart_putc(char c)
{
	while ((UART_READ(LSR) & LSR_TX_IDLE) == 0)
		;
	return UART_WRITE(THR, c);
}

void 
uart_puts(const char *s)
{
	while (*s)
		uart_putc(*s++);
}

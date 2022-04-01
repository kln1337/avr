CC=avr-gcc
LD=avr-ld
OBJCOPY=avr-objcopy
MCU=m168
MCUL=atmega168
CFLAGS=-mmcu=${MCUL} -DF_CPU=16000000UL -Os -I.
PORT=/dev/ttyUSB0
TARGET=main
INCLUDE= -I.

all: main
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex
	avr-size --mcu=${MCUL} ${TARGET}.hex

main: ${TARGET}.c
	${CC} ${CFLAGS} -o ${TARGET}.bin ${TARGET}.c uart.c

flash: ${TARGET}.hex
	avrdude -q -e -D -v -V -c arduino -p${MCUL} -P ${PORT} -b 19200 -U flash:w:${TARGET}.hex
clean:
	rm -f *.bin *.o

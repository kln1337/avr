CC=avr-gcc
LD=avr-ld
OBJCOPY=avr-objcopy
MCU=m168
MCUL=atmega168
CFLAGS=-mmcu=${MCUL} -DF_CPU=16000000UL -Os
PORT=/dev/ttyUSB0
TARGET=main
INCLUDE= -I.

all: ${TARGET}.c
	${CC} ${CFLAGS} -c ${TARGET}.c -o ${TARGET}.bin
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex
	avr-size --mcu=${MCUL} -C --format=avr ${TARGET}.hex
# main: ${TARGET}.c uart
# 	${CC} ${INCLUDE} ${CFLAGS} -c ${TARGET}.c -o ${TARGET}.bin
# uart: uart.c
# 	${CC} ${INCLUDE} ${CFLAGS} -c uart.c -o uart.bin

flash: ${TARGET}.hex
	avrdude -q -e -D -v -V -c arduino -p${MCUL} -P ${PORT} -b 19200 -U flash:w:${TARGET}.hex
clean:
	rm -f *.bin *.o

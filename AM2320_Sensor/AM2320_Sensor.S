;------------------------
; Assembly Code
;------------------------
#define __SFR_OFFSET 0x00
#include "avr/io.h"
;------------------------
.global I2C_init
.global I2C_START
.global I2C_write
.global I2C_read
.global I2C_read_NACK
.global I2C_STOP
.global delay_2ms
;==============================================================
I2C_init:
;--------
    LDI   R21, 0
    STS   TWSR, R21       ;prescaler = 0
    LDI   R21, 72         ;division factor = 72
    STS   TWBR, R21       ;SCK freq = 100kHz
    LDI   R21, (1<<TWEN)
    STS   TWCR, R21       ;enable TWI
    RET   
;==============================================================
I2C_START:
;---------
    LDI   R21, (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)
    STS   TWCR, R21       ;transmit START condition
    ;----------------------------------------------------------
wt1:LDS   R21, TWCR
    SBRS  R21, TWINT      ;TWI interrupt = 1?
    RJMP  wt1             ;no, wait for end of transmission
    ;----------------------------------------------------------
    RET
;==============================================================
I2C_write:
;---------
    STS   TWDR, R24       ;receive byte via R24 & copy into TWDR
    LDI   R21, (1<<TWINT)|(1<<TWEN)
    STS   TWCR, R21       ;transmit SLA+W
    ;----------------------------------------------------------
wt2:LDS   R21, TWCR
    SBRS  R21, TWINT
    RJMP  wt2             ;wait for end of transmission
    ;----------------------------------------------------------
    RET
;==============================================================
I2C_STOP:
;--------
    LDI   R21, (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)
    STS   TWCR, R21       ;transmit STOP condition
    RET
;==============================================================
I2C_read:
;--------
    LDI   R21, (1<<TWINT)|(1<<TWEA)|(1<<TWEN)
    STS   TWCR, R21         ;enable TWI & ACK
    ;----------------------------------------------------------
wt3:LDS   R21, TWCR
    SBRS  R21, TWINT
    RJMP  wt3                ;wait for data byte to be read
    ;----------------------------------------------------------
    LDS   R27, TWDR         ;store received byte
    RET
;==============================================================
I2C_read_NACK:
;-------------
    LDI   R21, (1<<TWINT)|(1<<TWEN)
    STS   TWCR, R21         ;enable TWI & ACK
    ;----------------------------------------------------------
wt4:LDS   R21, TWCR
    SBRS  R21, TWINT
    RJMP  wt4               ;wait for data byte to be read
    ;----------------------------------------------------------
    LDS   R27, TWDR         ;store received byte
    RET
;==============================================================
delay_2ms:                  ;delay 2ms
;---------
    LDI   R20, 255
l1: LDI   R21, 42
l2: LDI   R22, 1
l3: DEC   R22
    BRNE  l3
    DEC   R21
    BRNE  l2
    DEC   R20
    BRNE  l1
    RET
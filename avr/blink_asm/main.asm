	;; LED blink atmega328p - SENAI 
	.include "m328Pdef.inc"
	
	.cseg
	.org 0
	ldi r20, 0x00
	ldi r21, 0x20
	out DDRB, r21
	jmp main
	
main:
	cli
	ldi r24, 100
	out PORTB, r20
	call delay
	out PORTB, r21
	ldi r24, 100
	call delay
	jmp main
	
delay:
	ldi   r31, 255
loop:
	sbiw    r30, 1
	brne    loop
	sbiw 	  r24, 1
	brne    delay
	ret

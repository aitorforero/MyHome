#ifndef _pin_magic_
#define _pin_magic_
// Pin usage:

// LCD Data Bit :   7   6   5   4   3   2   1   0
// Mega dig. pin:  29  28  27  26  25  24  23  22
// Mega port/pin: PA7 PA6 PA5 PA4 PA3 PA2 PA1 PA0

// Pixel read operations require a minimum 400 nS delay from RD_ACTIVE
// to polling the input pins. At 16 MHz, one machine cycle is 62.5 nS.
// This code burns 7 cycles (437.5 nS) doing nothing; the RJMPs are
// equivalent to two NOPs each, final NOP burns the 7th cycle, and the
// last line is a radioactive mutant emoticon.
#define DELAY7 \
asm volatile( \
"rjmp .+0" "\n\t" \
"rjmp .+0" "\n\t" \
"rjmp .+0" "\n\t" \
"nop" "\n" \
::);


  #define write8inline(d) {                          \
    PORTA = d; \
    WR_STROBE; }
    
  #define read8inline(result) {                       \
    RD_ACTIVE;                                        \
    DELAY7; \
    result = PINA; \
    RD_IDLE; }

 // // These set the PORT directions as required before the write and read
 // // operations.
  #define setWriteDirInline() { DDRA = 0xFF;}
  #define setReadDirInline() { DDRA = 0x00;}


// All of the functions are inlined on the Arduino Mega. When using the
// breakout board, the macro versions aren't appreciably larger than the
// function equivalents, and they're super simple and fast. When using
// the shield, the macros become pretty complicated...but this board has
// so much code space, the macros are used anyway. If you need to free
// up program space, some macros can be removed, at a minor cost in speed.
#define write8 write8inline
#define read8 read8inline
#define setWriteDir setWriteDirInline
#define setReadDir setReadDirInline
#define writeRegister8 writeRegister8inline
#define writeRegister16 writeRegister16inline
#define writeRegisterPair writeRegisterPairInline
// When using the TFT breakout board, control pins are configurable.
#define RD_ACTIVE *rdPort &= rdPinUnset
#define RD_IDLE *rdPort |= rdPinSet
#define WR_ACTIVE *wrPort &= wrPinUnset
#define WR_IDLE *wrPort |= wrPinSet
#define CD_COMMAND *cdPort &= cdPinUnset
#define CD_DATA *cdPort |= cdPinSet
#define CS_ACTIVE *csPort &= csPinUnset
#define CS_IDLE *csPort |= csPinSet
#endif
// Data read and write strobes, ~2 instructions and always inline
#define RD_STROBE { RD_ACTIVE; RD_IDLE; }
#define WR_STROBE { WR_ACTIVE; WR_IDLE; }
// These higher-level operations are usually functionalized,
// except on Mega where's there's gobs and gobs of program space.
// Set value of TFT register: 8-bit address, 8-bit value
#define writeRegister8inline(a, d) { \
CD_COMMAND; write8(a); CD_DATA; write8(d); }
// Set value of TFT register: 16-bit address, 16-bit value
// See notes at top about macro expansion, hence hi & lo temp vars
#define writeRegister16inline(a, d) { \
uint8_t hi, lo; \
hi = (a) >> 8; lo = (a); CD_COMMAND; write8(hi); write8(lo); \
hi = (d) >> 8; lo = (d); CD_DATA ; write8(hi); write8(lo); }
// Set value of 2 TFT registers: Two 8-bit addresses (hi & lo), 16-bit value
#define writeRegisterPairInline(aH, aL, d) { \
uint8_t hi = (d) >> 8, lo = (d); \
CD_COMMAND; write8(aH); CD_DATA; write8(hi); \
CD_COMMAND; write8(aL); CD_DATA; write8(lo); }



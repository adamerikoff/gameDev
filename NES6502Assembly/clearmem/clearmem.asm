;; ====================================================
;; iNES HEADER
;; ====================================================
.segment "HEADER"             ; Define a memory segment for the iNES file header
.byte $4E, $45, $53, $1A      ; 4 bytes identifying an iNES file: ASCII "NES" followed by 0x1A
.byte %00000000               ; Flags for PRG and CHR ROM sizes (placeholder for now)
.byte %00000000               ; Flags for mapper, mirroring, and battery (placeholder for now)
.byte $00                     ; Unused, reserved for future use
.byte $00                     ; Unused, reserved for future use
.byte $00                     ; Unused, reserved for future use
.byte $00, $00, $00, $00, $00 ; Padding to make up the 16-byte iNES header

;; ====================================================
;; CODE SEGMENT
;; ====================================================
.segment "CODE"               ; Define a memory segment for the code

RESET:                        ; Reset vector entry point
    sei                       ; Set Interrupt Disable flag (disable interrupts)
    cld                       ; Clear Decimal Mode flag
    ldx #$FF                  ; Load X register with 0xFF (initialize stack pointer)
    txs                       ; Transfer X to Stack Pointer (set stack pointer to top of stack)

    inx                       ; Load X register with 0xFF (initialize index for memory clearing loop)
    txa
ClearRAM:                      ; Loop to clear memory
    sta $0000,x                  ; Store 0 at memory location $0 + X (zeroing out memory)
    sta $0100,x                  ; Store 0 at memory location $0 + X (zeroing out memory)
    sta $0200,x                  ; Store 0 at memory location $0 + X (zeroing out memory)
    sta $0300,x                  ; Store 0 at memory location $0 + X (zeroing out memory)
    sta $0400,x                  ; Store 0 at memory location $0 + X (zeroing out memory)
    sta $0500,x                  ; Store 0 at memory location $0 + X (zeroing out memory)
    sta $0600,x                  ; Store 0 at memory location $0 + X (zeroing out memory)
    sta $0700,x                  ; Store 0 at memory location $0 + X (zeroing out memory)
    inx                       ; Decrement X register (move to the next memory location)
    bne ClearRAM               ; Branch if X is not zero (loop until X reaches 0)

LoopForever:
    jmp LoopForever

NMI:                          ; Non-Maskable Interrupt handler
    rti                       ; Return from Interrupt (placeholder for actual NMI logic)

IRQ:                          ; Interrupt Request handler
    rti                       ; Return from Interrupt (placeholder for actual IRQ logic)


;; ====================================================
;; VECTORS SEGMENT
;; ====================================================
.segment "VECTORS"            ; Define a memory segment for interrupt vectors
.word NMI
.word RESET
.word IRQ

.text
.arm
.global setDelay

setDelay:
    CMP R0, #10
    BGE salir
    MOV R0, #10
salir:
    MOV PC, LR
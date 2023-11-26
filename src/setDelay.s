.text
.arm
.global setDelay

// setDelay: Configura el retardo, limitándolo a un mínimo de 10.
// Parámetros: R0 - Valor de retardo a configurar
// Valor de retorno: R0 - Valor de retardo ajustado
setDelay:
    CMP R0, #10
    BGE salir
    MOV R0, #10
salir:
    MOV PC, LR
    
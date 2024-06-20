.globl compareVersion
.type compareVersion, @function

compareVersion:
    push %r12
    push %r13
    
    mov %rdi, %r12
    mov %rsi, %r13
    xor %r10, %r10
    xor %r11, %r11

tokenize_vers1:
    mov %r12, %rdi
    call myStrtok
    test %rax, %rax
    jz vers1_has_no_entry
    mov %r12, %rdi
    mov %rax, %r12
    call myAtoi
    mov %eax, %r10d
    jmp tokenize_vers2
vers1_has_no_entry:
    mov $0, %r10d
    mov %rax, %r12
tokenize_vers2:
    mov %r13, %rdi
    call myStrtok
    test %rax, %rax
    jz vers2_has_no_entry
    mov %r13, %rdi
    mov %rax, %r13
    call myAtoi
    mov %eax, %r11d
    jmp compare
vers2_has_no_entry: 
    mov $0, %r11d
    mov %rax, %r13
    
compare:
    test %r12, %r12
    jnz compare_value
    test %r13, %r13
    jz vers1_vers2_eq
compare_value:
    cmp %r11d, %r10d
    jl vers1_below
    jg vers1_above
    jmp tokenize_vers1
vers1_below:
    mov $-1, %rax
    jmp exit_compareVersion
vers1_above:
    mov $1, %rax
    jmp exit_compareVersion
vers1_vers2_eq:
    xor %rax, %rax
exit_compareVersion:
    pop %r13
    pop %r12
    ret
    
myStrtok:
    xor %rax, %rax
    test %rdi, %rdi
    jz exit_myStrtok
    cmpb $0, (%rdi)
    je exit_myStrtok
loopStrtok:
    cmpb $0, (%rdi)
    je exit_foundNull
    cmpb $46, (%rdi)
    je foundToken
    inc %rdi
    jmp loopStrtok
foundToken:
    movb $0, (%rdi)
    inc %rdi
exit_foundNull:
    mov %rdi, %rax
exit_myStrtok:
    ret
    
myAtoi:
    xor %rax, %rax
    xor %esi, %esi
    xor %rdx, %rdx
    mov $10, %ecx
    jmp consume_whitespace_entry
    
consume_whitespace_loop:
    lea 1(%rdi), %rdi
    
consume_whitespace_entry:
    cmpb $0, (%rdi)
    je exit
    cmpb $0x20, (%rdi)
    je consume_whitespace_loop
    cmpb $0x09, (%rdi)  
    je consume_whitespace_loop
    cmpb $0x0D, (%rdi)
    je consume_whitespace_loop
    cmpb $0x0A, (%rdi)  
    je consume_whitespace_loop
    
    // Check positive sign
    cmpb $43, (%rdi)
    je consume_digit
    
    // Check negative sign
    cmpb $45, (%rdi)
    jne consume_digit_skip
    mov $1, %esi
    
    // Get digit
consume_digit:
    lea 1(%rdi), %rdi
    cmpb $0, (%rdi)
    je exit
    
consume_digit_skip:
    
    //jo exit
    mov (%rdi), %r8b
    sub $48, %r8b
    js exit
    cmpb $10, %r8b
    ja exit
    movzx %r8b, %r8d
    imul %ecx
    jo exit_overflow
    add %r8d, %eax
    jo exit_overflow
    jmp consume_digit
    
exit_overflow:
    test %esi, %esi
    jnz neg_overflow
    mov $0x7FFFFFFF, %eax
    ret
neg_overflow:
    mov $0x80000000, %eax
    ret
exit:
    test %esi, %esi
    jz bye
    neg %eax
bye:
    ret
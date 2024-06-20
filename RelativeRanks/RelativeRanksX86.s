.text
.global findRelativeRanks
.type findRelativeRanks, @function
findRelativeRanks:
    xor %eax, %eax
    mov %rsi, (%rdx)
    push %rdi
    push %rsi
    mov %rsi, %rdi
    call malloc
    pop %rsi
    pop %rdi
    
    push %rbp
    shl $1, %rsi
    sub %rsi, %rsp
    mov %rsp, %rbp
    shr $1, %rsi
    mov %rsi, %rdx
    dec %rdx
findRelativeRanks_buildIndex:
    movw %dx, (%rbp, %rdx, 2)
    dec %rdx
    jnz findRelativeRanks_buildIndex
    movw $0, (%rbp) 

    push %rsi
    mov %rsi, %rcx
    dec %rcx
    mov %rbp, %rsi
    xor %rdx, %rdx
    call mergeSortASM
    pop %rsi


    push %rbx
    shl $1, %rsi
    sub %rsi, %rsp
    mov %rsp, %rbx
    shr $1, %rsi

    mov %rsi, %rdx
    xor %r8, %r8
    inc %r8
findRelativeRanks_loopRank:
    mov -2(%rbp, %rdx, 2), %cx
    movzx %cx, %rcx
    movw %r8w, (%rbx, %rcx, 2)
    inc %r8
    dec %rdx
    jnz findRelativeRanks_loopRank

    shl $1, %rsi
    add %rsi, %rsp
    pop %rbx
    add %rsi, %rsp
    pop %rbp
    ret
.global mergeSortASM
mergeSortASM:
    cmp %rdx, %rcx
    jne mergeSort_perform
    ret
mergeSort_perform:
    push %rdx
    push %rcx
    mov %rcx, %r8
    sub %rdx, %r8
    shr $1, %r8
    push %r8
    push %rcx
    mov %rdx, %rcx
    add %r8, %rcx
    push %rcx
    call mergeSortASM
    pop %rdx
    inc %rdx
    pop %rcx
    call mergeSortASM
    pop %r8
    pop %rcx
    pop %rdx

    push %rbx
    push %r12
    mov %rcx, %r9
    sub %rdx, %r9
    inc %r9

    mov %r9, %r10
    lea (%rsi, %rdx, 2), %rdx
    mov %rdx, %r12
    lea (%rdx, %r8, 2), %r8
    add $2, %r8
    mov %r8, %r11
    lea 2(%rsi, %rcx, 2), %rcx
mergeSort_loopMerge:

    cmp %r8, %rdx
    ja mergeSort_loopMerge_list2
    cmp %rcx, %r11
    je mergeSort_loopMerge_list1
    movw (%rdx), %ax
    movzx %ax, %rax
    mov (%rdi, %rax, 4), %eax
    movw (%r11), %bx
    movzx %bx, %rbx
    cmp (%rdi, %rbx, 4), %eax
    ja mergeSort_loopMerge_list2
mergeSort_loopMerge_list1:
    mov (%rdx), %ax
    add $2, %rdx
    jmp mergeSort_loopMerge_exit
mergeSort_loopMerge_list2:
    mov (%r11), %ax
    add $2, %r11
mergeSort_loopMerge_exit:
    push %ax
    dec %r10
    jnz mergeSort_loopMerge

    mov %r9, %r10
mergeSort_copyBack:
    pop %ax
    movw %ax, -2(%r12, %r10, 2)
    dec %r10
    jnz mergeSort_copyBack

    pop %r12
    pop %rbx
    ret


.data
scoreTemp:
.align 8
.zero 20000

rankTemp:
.align 8
.zero 20000
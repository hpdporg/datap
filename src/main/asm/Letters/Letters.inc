
section '.data' data readable writeable

	
	letterTerminator db 0

		
section '.text' code readable writeable executable ;align 16



letters:
namespace letters
letters.numAsLetters:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label numAsLetters.debugMsgSize qword at rbp-8 
	label numAsLetters.heapAddress qword at rbp-16
	label numAsLetters.linearAllocationSize qword at rbp-24
	label numAsLetters.num qword at rbp-32
	label numAsLetters.lettersLength qword at rbp-40
	label numAsLetters.numberNegative qword at rbp-48
	label numAsLetters.lettersBufferReverse qword at rbp-56
	label numAsLetters.lettersBufferForward qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [numAsLetters.num], rcx


	and rsp, -32
	push rbx 
	push rbp 
	push rdi 
	push rsi
	push rsp 
	push r12 
	push r13 
	push r14 
	push r15
	sub rsp, 8



	sub rsp, 8*4
	call [GetProcessHeap]
	mov [numAsLetters.heapAddress], rax
	add rsp, 8*4


	mov rcx, 0
	add rcx, ListItem.next
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, 200			; 200 bytes		
	mov rdx, 000001000b
	mov rcx, [numAsLetters.heapAddress]
	call [ HeapAlloc] 
	mov [numAsLetters.lettersBufferReverse], rax
	add rsp, 8*4

	sub rsp, 8*4
	mov r8, 200			; 200 bytes		
	mov rdx, 000001000b
	mov rcx, [numAsLetters.heapAddress]
	call [ HeapAlloc] 
	mov [numAsLetters.lettersBufferForward], rax
	add rsp, 8*4

	mov rax, 0
	mov [numAsLetters.lettersLength], rax
	mov [numAsLetters.numberNegative], rax

	mov rcx, [numAsLetters.num]


	cmp rcx, rax
	jns numAsLetters.notNegativeNum

	mov [numAsLetters.numberNegative], 1
	mov rcx, [numAsLetters.num]
	neg rcx
	mov [numAsLetters.num], rcx

	numAsLetters.notNegativeNum:


	mov rax, [numAsLetters.num]
	mov rdx, 0
	mov rbx, 10
	
	mov r9, [numAsLetters.lettersBufferReverse]
	mov rdi, r9
	cld


	numAsLetters.divideDigit:


	idiv rbx

	cmp al, 0
	je numAsLetters.terminateNumString

	add [numAsLetters.lettersLength], 1
	
	mov rbx, rax

	add dl, 48
	mov rax, rdx
	mov rcx, 1
	db 10101010b	;db 0xaa	;stosb

	mov rax, rbx
	mov rdx, 0
	mov rbx, 10
	jmp numAsLetters.divideDigit


	numAsLetters.terminateNumString:
	
	add [numAsLetters.lettersLength], 1

	add dl, 48
	mov rax, rdx
	mov rcx, 1
	db 10101010b	;db 0xaa	;stosb

	mov rax, 0
	mov rcx, 1
	db 10101010b	;db 0xaa	;stosb


	cmp [numAsLetters.numberNegative], 1
	jne numAsLetters.notNegativeLength

	add [numAsLetters.lettersLength], 1

	numAsLetters.notNegativeLength:

	mov rax, [numAsLetters.lettersLength]


	mov r9, [numAsLetters.lettersBufferReverse]
	mov r10, [numAsLetters.lettersBufferForward]
	mov rsi, r9
	mov r8, r10
	add r8, rax
	mov rdi, r8



	mov rax, 0

	numAsLetters.retrieveReverseNumString:

	std
	mov rcx, 1
	db 10101010b	;db 0xaa	;stosb

	mov rax, 0
	mov rcx, 1
	cld

	lodsb
	
	cmp rax, 0
	jne numAsLetters.retrieveReverseNumString


	cmp [numAsLetters.numberNegative], 1
	jne numAsLetters.noSign
	
	mov rax, 0
	mov al, 150
	mov rcx, 1
	std
	db 10101010b	;db 0xaa	;stosb


	numAsLetters.noSign:



	mov rax, [numAsLetters.lettersBufferForward]

	


	add rsp, 8	
	pop r15 
	pop r14 
	pop r13 
	pop r12 
	pop rsp 
	pop rsi 
	pop rdi 
	pop rbp 
	pop rbx

	mov rsp, rbp
	pop rbp

	retn 0




letters.letterLength:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*4);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label letterLength.letters qword at rbp-8 
	label letterLength.lettersLength qword at rbp-16
	label letterLength.linearAllocationSize qword at rbp-24
	label letterLength.num qword at rbp-32
	;label letterLength.lettersLength qword at rbp-40
	;label letterLength.numberNegative qword at rbp-48
	;label letterLength.lettersBufferReverse qword at rbp-56
	;label letterLength.lettersBufferForward qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [letterLength.letters], rcx



	and rsp, -32
	push rbx 
	push rbp 
	push rdi 
	push rsi
	push rsp 
	push r12 
	push r13 
	push r14 
	push r15
	sub rsp, 8


	mov rdx, [letterLength.letters]



	mov rax, 0
	mov rcx, 0
	not rcx
	cld
	mov rdi, rdx

	repne scasb

	
	not rcx
	dec rcx
	mov [letterLength.lettersLength], rcx


	mov rax, [letterLength.lettersLength]


	add rsp, 8	
	pop r15 
	pop r14 
	pop r13 
	pop r12 
	pop rsp 
	pop rsi 
	pop rdi 
	pop rbp 
	pop rbx

	mov rsp, rbp
	pop rbp

	retn 0


letters.appendLetters:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*7);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label appendLetters.letters qword at rbp-8 
	label appendLetters.lettersLength qword at rbp-16
	label appendLetters.linearAllocationSize qword at rbp-24
	label appendLetters.newLetters qword at rbp-32
	label appendLetters.newLettersLength qword at rbp-40
	label appendLetters.lettersLengthSum qword at rbp-48
	label appendLetters.appendedLetters qword at rbp-56
	;label appendLetters.lettersBufferForward qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [appendLetters.letters], rcx
	mov [appendLetters.newLetters], rdx


	and rsp, -32
	push rbx 
	push rbp 
	push rdi 
	push rsi
	push rsp 
	push r12 
	push r13 
	push r14 
	push r15
	sub rsp, 8


	
	sub rsp, 8*8
	mov rcx, [appendLetters.letters]	
	call letterLength
	add rsp, 8*8
	mov [appendLetters.lettersLength], rax

	sub rsp, 8*8
	mov rcx, [appendLetters.newLetters]	
	call letterLength
	add rsp, 8*8
	mov [appendLetters.newLettersLength], rax

	mov rax, [appendLetters.lettersLength]
	mov rcx, [appendLetters.newLettersLength]

	add rax, rcx
	mov [appendLetters.lettersLengthSum], rax

	mov rcx, [appendLetters.lettersLengthSum]
	add rcx, 1b							; Trailing 0
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;allocate rcx, appendLetters.appendedLetters

	mov rsi, [appendLetters.letters]
	mov rdi, [appendLetters.appendedLetters]
	cld
	mov rcx, [appendLetters.lettersLength]
	rep movsb

	mov rsi, [appendLetters.newLetters]
	mov rdi, [appendLetters.appendedLetters]
	add rdi, [appendLetters.lettersLength]
	cld
	mov rcx, [appendLetters.newLettersLength]
	rep movsb

	mov rsi, letterTerminator
	mov rdi, [appendLetters.appendedLetters]
	add rdi, [appendLetters.lettersLength]
	add rdi, [appendLetters.newLettersLength]
	mov rcx, 1
	cld
	rep movsb


	mov rax, [appendLetters.appendedLetters]

	add rsp, 8	
	pop r15 
	pop r14 
	pop r13 
	pop r12 
	pop rsp 
	pop rsi 
	pop rdi 
	pop rbp 
	pop rbx

	mov rsp, rbp
	pop rbp

	retn 0


end namespace


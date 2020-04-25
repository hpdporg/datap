


section '.data' data readable writeable align 16


	struc NumericParsing
		label .
		.opFlags dq 0			; Basic operation flags
		;.tranOpFlags dq 0		; Transcendental flags
	end struc



	; NUM_PARS_OP Flags
	; NUM_PARS_OP_MORE		1b			0	; +
	; NUM_PARS_OP_LESS		10b			1	; -
	; NUM_PARS_OP_DIV		100b			2	; /
	; NUM_PARS_OP_MUL		1000b			3	; *




	; Used with address offsets
	virtual at 0
		NumericParsing NumericParsing
	end virtual

	
	

section '.text' code readable writeable executable align 16


numericParsing:
namespace numericParsing
new:
namespace new
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*2);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16


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
	mov rcx, NumericParsing.opFlags
	call allocate.new
	mov [handleAllocatedMemory], rax
	add rsp, 8*8
	





	mov rax, [handleAllocatedMemory]


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




end namespace
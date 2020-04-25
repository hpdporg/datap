


section '.data' data readable writeable align 16


	struc NumExpRefVal
		label .
		.labelAlloc dq 0		; Ref or val from expression
		.val dq 0			; Actual value
		.flags dq 0			; NUM_EXP_REF_VAL flags
		.refFlags dq 0			; NUM_EXP_REF flags (optional)
		.refFilterFlags dq 0		; NUM_EXP_REF_FILT flags (optional)
	end struc



	; NUM_EXP_REF_VAL Flags
	; NUM_EXP_REF_VAL_REF		1b			0	; refName
	; NUM_EXP_REF_VAL_INTEGER	10b			1	; 8498
	; NUM_EXP_REF_VAL_FLOAT		100b			2	; 490.4499
	; NUM_EXP_REF_VAL_DATE		1000b			3	; 2020/03/09


	; NUM_EXP_REF Flags
	; NUM_EXP_REF_LOC	1b			0	; refName
	; NUM_EXP_REF_LIST	10b			1	; 8498
	; NUM_EXP_REF_FLOW	100b			2	; 490.4499

	; NUM_EXP_REF_FILT Flags
	; NUM_EXP_REF_FILT_NO_FILT	1b			0	; refName
	; NUM_EXP_REF_FILT_HAS_FILT	10b			1	; refName.member2




	; Used with address offsets
	virtual at 0
		NumExpRefVal NumExpRefVal
	end virtual

	
	

section '.text' code readable writeable executable align 16


numExpRefVal:
namespace numExpRefVal
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
	mov rcx, NumExpRefVal.refFilterFlags
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
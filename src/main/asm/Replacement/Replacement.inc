


section '.data' data readable writeable align 16




	;Flags
	;REPLACE_INSERT	REPLACE_BETWEEN




section '.text' code readable writeable executable align 16


replacement:
namespace replacement
replacement.lettersWithList:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label lettersWithList.heapAddress qword at rbp-8  
	label lettersWithList.handleAllocatedMemory qword at rbp-16
	label lettersWithList.matchFlow qword at rbp-24 
	label lettersWithList.list qword at rbp-32
	label lettersWithList.matchAddr qword at rbp-40
	label lettersWithList.letters qword at rbp-48
	label lettersWithList.flags qword at rbp-56
	label lettersWithList.letters qword at rbp-64
	label lettersWithList.matchingIndex qword at rbp-72
	label lettersWithList.matchResultsList qword at rbp-80
	label lettersWithList.startMatchFound qword at rbp-88
	label lettersWithList.matchFoundCount qword at rbp-96
	label lettersWithList.lettersLength qword at rbp-104
	label lettersWithList.matchingEnd qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [lettersWithList.flags], rcx
	mov [lettersWithList.letters], rdx
	mov [lettersWithList.list], r8
	mov [lettersWithList.matchResultsList], r9


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



	mov rbx, [lettersWithList.flags]
	bt r8, 0b					; REPLACE between
	jnc lettersWithList.replaceInsert		; Replace as insert at indices
	

	; Need lettersBetweenIndices

	sub rsp, 8*8
	call appendLetters
	add rsp, 8*8



	.replaceInsert:					; TO-DO



	mov rax, 0;[lettersWithList.list]


	lettersWithList.end:


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
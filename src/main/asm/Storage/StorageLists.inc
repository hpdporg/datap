


;section '.data' data readable writeable align 16



	

section '.text' code readable writeable executable align 16




namespace storage



storage.retrieveLettersList:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label retrieveLettersList.heapAddress qword at rbp-8  
	label retrieveLettersList.handleAllocatedMemory qword at rbp-16
	label retrieveLettersList.list qword at rbp-24 
	label retrieveLettersList.item qword at rbp-32
	label retrieveLettersList.recordAddr qword at rbp-40
	label retrieveLettersList.sizeretrieved qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [retrieveLettersList.recordAddr], rcx


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
	mov rcx, [retrieveLettersList.recordAddr]
	call retrieve
	add rsp, 8*8
	mov rbx, [retrieveLettersList.recordAddr]
	add rbx, Record.allocAddr
	



	mov rax, [retrieveLettersList.list]
	
	retrieveLettersList.end:


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
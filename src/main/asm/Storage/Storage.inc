


section '.data' data readable writeable align 16



	struc Record
		label .
		.allocAddr dq 0		; Binary or text allocation addr
		.allocSize dq 0		; Size of allocation (base 8)
		.name dq 0		; Record name with extension
		.location dq 0		; Path
		.handle dq 0
	end struc




	; Used with address offsets
	virtual at 0
		Record Record
	end virtual

	; ---- Structures
	;element Element


	

section '.text' code readable writeable executable align 16


; storage.defineFilePath
; storage.newFile

storage:
namespace storage
storage.new:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*2);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label new.heapAddress qword at rbp-8  
	label new.handleAllocatedMemory qword at rbp-16
	;virtual at rbp-64
	;	.list List
	;end virtual	



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
	mov [new.heapAddress], rax
	add rsp, 8*4
	

	mov rcx, 0
	add rcx, Record.handle
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [new.heapAddress]
	call [ HeapAlloc] 
	mov [new.handleAllocatedMemory], rax
	add rsp, 8*4


	mov rbx, [new.handleAllocatedMemory]
	add rbx, Record.allocAddr
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Record.allocSize
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Record.name
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Record.location
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Record.handle
	mov rax, 0
	mov [rbx], rax


	;lea rax, [new.list]
	;lea rcx, [new.list.indexedItemIndex]

	;sub rcx, rax
	;add rcx, 1000b

	;cld

	;lea rsi, [new.list]
	;mov rdi, [storage.new.handleAllocatedMemory]

	;rep movsb


	mov rax, [new.handleAllocatedMemory]


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

storage.retrieve:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*5);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label retrieve.heapAddress qword at rbp-8  
	label retrieve.handleAllocatedMemory qword at rbp-16
	label retrieve.list qword at rbp-24 
	label retrieve.item qword at rbp-32
	label retrieve.prevItem qword at rbp-40
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [retrieve.list], rcx
	mov [retrieve.item], rdx


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










	;mov rax, [retrieve.handleAllocatedMemory]


	retrieve.end:


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


storage.defineRecordPath:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*3);+(8*0)

	;mov rcx, [rbp+8]
	;mov rdx, [rbp+12]
	label defineRecordPath.recordAddr qword at rbp-8  
	label defineRecordPath.name qword at rbp-16
	label defineRecordPath.location qword at rbp-24
	;virtual at rbp-64
	;	.list List
	;end virtual	

	mov [defineRecordPath.recordAddr], rcx
	mov [defineRecordPath.name], rdx
	mov [defineRecordPath.location], r8

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

	mov rbx, [defineRecordPath.recordAddr]
	add rbx, Record.name
	mov rdx, [defineRecordPath.name]
	mov [rbx], rdx
	mov rbx, [defineRecordPath.recordAddr]
	add rbx, Record.location
	mov r8, [defineRecordPath.location]
	mov [rbx], r8	

	mov rax, [defineRecordPath.recordAddr]

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

storage.newFile:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*2);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label newFile.handleAddr qword at rbp-8  
	label newFile.fileNameAddr qword at rbp-16
	;virtual at rbp-64
	;	.list List
	;end virtual	

	mov [newFile.fileNameAddr], rcx

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
	mov qword [rsp+6*8], 0					;hTemplateFile
	mov qword [rsp+5*8], 128 				;dwFlagsandAttributes
	mov qword [rsp+4*8], 000000100b 			;dwCreationDisposition
	mov r9, 0 						;lpSecurityAttributes
	mov r8, 000000010b 					;dwShareMode
	mov rdx, 10100000000000000000000100000101b		;dwDesiredAccess
	;mov rcx, fileNameAddr
	call [CreateFile]
	add rsp, 8*8
	;mov handleAddr, rax

	;mov rcx, handleAddr
	sub rsp, 8*4
	call [SetEndOfFile]
	add rsp, 8*4


	mov rax, [newFile.handleAddr]

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


storage.writeFile:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*4);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label writeFile.handleAddr qword at rbp-8  
	label writeFile.entry qword at rbp-16
	label writeFile.size qword at rbp-24
	label writeFile.writtenAddr qword at rbp-32
	;virtual at rbp-64
	;	.list List
	;end virtual	

	mov [writeFile.handleAddr], rcx
	mov [writeFile.entry], rdx
	mov [writeFile.size], r8

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

	;mov rcx, handleAddr
	sub rsp, 8*4
	call [SetEndOfFile]
	add rsp, 8*4
	

	sub rsp, 8*8
	mov qword [rsp+4*8], 0
	;mov r9, writtenAddr
	;mov r8, size
	;mov rdx, entry
	;mov rcx, handleAddr
	call [WriteFile]
	add rsp, 8*8

	mov rax, [storage.writeFile.handleAddr]

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
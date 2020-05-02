


;section '.data' data readable writeable align 16



	

section '.text' code readable writeable executable align 16




namespace storage


retrieveList:
namespace retrieveList
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label listAddr qword at rbp-24 
	label item qword at rbp-32
	label recordAddr qword at rbp-40
	label sizeretrieved qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [recordAddr], rcx


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




	mov r11, [recordAddr]
	add r11, Record.jDelimiter
	mov rdx, [r11]
	mov rbx, [recordAddr]
	add rbx, Record.allocAddr
	mov rcx, [rbx]
	sub rsp, 8*8
	call matching.extractBetween
	add rsp, 8*8

	mov rbx, [recordAddr]
	add rbx, Record.allocAddr
	mov [rbx], rax	



	mov rax, [recordAddr]
	
	completed:


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


; TO-DO: Keep handle open until end
storeList:
namespace storeList
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*7);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label letterLength qword at rbp-24 
	label sizeWritten qword at rbp-32
	label recordAddr qword at rbp-40
	label lettersAlloc qword at rbp-48
	label listAlloc qword at rbp-56
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [recordAddr], rcx
	mov [listAlloc], rdx


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
	mov rcx, [listAlloc]
	call list.resetIndex
	add rsp, 8*8

	nextItem:
	mov rbx, [listAlloc]
	mov r8, rbx
	add r8, List.index
	add rbx, List.itemsCount
	mov rcx, [r8]
	mov rdx, [rbx]
	cmp rcx, rdx
	jnl endItems

	sub rsp, 8*8
	mov rcx, [listAlloc]
	call list.getNextItem
	add rsp, 8*8
	mov [lettersAlloc], rax

	sub rsp, 8*8
	mov rdx, [lettersAlloc]
	mov rcx, [recordAddr]
	call storeLetters
	add rsp, 8*8



	sub rsp, 8*8
	mov rbx, [recordAddr]
	add rbx, Record.jDelimiter
	mov rdx, [rbx]
	mov rcx, [recordAddr]
	call storeLetters
	add rsp, 8*8


	jmp nextItem
	endItems:




	mov rax, [recordAddr]


	completed:


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

; TO-DO: Keep handle open until end
restoreList:
namespace restoreList
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*7);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label letterLength qword at rbp-24 
	label sizeWritten qword at rbp-32
	label recordAddr qword at rbp-40
	label lettersAlloc qword at rbp-48
	label listAlloc qword at rbp-56
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [recordAddr], rcx
	mov [listAlloc], rdx


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
	mov rcx, [listAlloc]
	call list.resetIndex
	add rsp, 8*8

	mov rbx, [recordAddr]
	add rbx, Record.builtLocation
	mov rcx, [rbx]
	sub rsp, 8*4
	call [DeleteFile]
	add rsp, 8*4


	nextItem:
	mov rbx, [listAlloc]
	mov r8, rbx
	add r8, List.index
	add rbx, List.itemsCount
	mov rcx, [r8]
	mov rdx, [rbx]
	cmp rcx, rdx
	jnl endItems

	sub rsp, 8*8
	mov rcx, [listAlloc]
	call list.getNextItem
	add rsp, 8*8
	mov [lettersAlloc], rax


	sub rsp, 8*8
	mov rdx, [lettersAlloc]
	mov rcx, [recordAddr]
	call storeLetters
	add rsp, 8*8



	sub rsp, 8*8
	mov rbx, [recordAddr]
	add rbx, Record.jDelimiter
	mov rdx, [rbx]
	mov rcx, [recordAddr]
	call storeLetters
	add rsp, 8*8

	jmp nextItem
	endItems:




	mov rax, [recordAddr]


	completed:


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

; TO-DO: Keep handle open until end
; Stores a List into separate files
storeListLocations:
namespace storeListLocations
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label letterLength qword at rbp-24 
	label sizeWritten qword at rbp-32
	label recordAddr qword at rbp-40
	label lettersAlloc qword at rbp-48
	label listAlloc qword at rbp-56
	label locations qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [recordAddr], rcx
	mov [listAlloc], rdx
	mov [locations], r8


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
	mov rcx, [listAlloc]
	call list.resetIndex
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, [locations]
	call list.resetIndex
	add rsp, 8*8


	nextItem:
	mov rbx, [listAlloc]
	mov r8, rbx
	add r8, List.index
	add rbx, List.itemsCount
	mov rcx, [r8]
	mov rdx, [rbx]
	cmp rcx, rdx
	jnl endItems

	sub rsp, 8*8
	mov rcx, [locations]
	call list.getNextItem
	add rsp, 8*8
	mov rbx, [recordAddr]
	add rbx, Record.builtLocation
	mov [rbx], rax


	sub rsp, 8*8
	mov rcx, [listAlloc]
	call list.getNextItem
	add rsp, 8*8
	mov [lettersAlloc], rax

	sub rsp, 8*8
	mov rdx, [lettersAlloc]
	mov rcx, [recordAddr]
	call storeLetters
	add rsp, 8*8






	jmp nextItem
	endItems:




	mov rax, [recordAddr]


	completed:


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

; TO-DO: Keep handle open until end
restoreListLocations:
namespace restoreListLocations
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label letterLength qword at rbp-24 
	label sizeWritten qword at rbp-32
	label recordAddr qword at rbp-40
	label lettersAlloc qword at rbp-48
	label listAlloc qword at rbp-56
	label locations qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [recordAddr], rcx
	mov [listAlloc], rdx
	mov [locations], r8

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
	mov rcx, [listAlloc]
	call list.resetIndex
	add rsp, 8*8


	sub rsp, 8*8
	mov rcx, [locations]
	call list.resetIndex
	add rsp, 8*8



	nextItem:
	mov rbx, [listAlloc]
	mov r8, rbx
	add r8, List.index
	add rbx, List.itemsCount
	mov rcx, [r8]
	mov rdx, [rbx]
	cmp rcx, rdx
	jnl endItems

	sub rsp, 8*8
	mov rcx, [locations]
	call list.getNextItem
	add rsp, 8*8
	mov rbx, [recordAddr]
	add rbx, Record.builtLocation
	mov [rbx], rax


	mov rbx, [recordAddr]
	add rbx, Record.builtLocation
	mov rcx, [rbx]
	sub rsp, 8*4
	call [DeleteFile]
	add rsp, 8*4

	sub rsp, 8*8
	mov rcx, [listAlloc]
	call list.getNextItem
	add rsp, 8*8
	mov [lettersAlloc], rax


	sub rsp, 8*8
	mov rdx, [lettersAlloc]
	mov rcx, [recordAddr]
	call storeLetters
	add rsp, 8*8




	jmp nextItem
	endItems:




	mov rax, [recordAddr]


	completed:


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
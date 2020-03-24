
section '.data' data readable writeable

	

	letterTerminator db 0
	pathSepLetters db '\',0
	directoryContentsLetters db '\*',0
	currentDirLetter db '.',0
	containingDirLetters db '..',0
	newlineWinLetters db 13,10,0		; '\r\n',0
	tabLetters db 9,0			;'\t',0
		
section '.text' code readable writeable executable ;align 16



letters:
namespace letters
numAsLetters:
namespace numAsLetters
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label debugMsgSize qword at rbp-8 
	label heapAddress qword at rbp-16
	label linearAllocationSize qword at rbp-24
	label num qword at rbp-32
	label lettersLength qword at rbp-40
	label numberNegative qword at rbp-48
	label lettersBufferReverse qword at rbp-56
	label lettersBufferForward qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [num], rcx


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
	mov [heapAddress], rax
	add rsp, 8*4


	mov rcx, 0
	add rcx, ListItem.next
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, 200			; 200 bytes		
	mov rdx, 000001000b
	mov rcx, [heapAddress]
	call [ HeapAlloc] 
	mov [lettersBufferReverse], rax
	add rsp, 8*4

	sub rsp, 8*4
	mov r8, 200			; 200 bytes		
	mov rdx, 000001000b
	mov rcx, [heapAddress]
	call [ HeapAlloc] 
	mov [lettersBufferForward], rax
	add rsp, 8*4

	mov rax, 0
	mov [lettersLength], rax
	mov [numberNegative], rax

	mov rcx, [num]


	cmp rcx, rax
	jns notNegativeNum

	mov [numberNegative], 1
	mov rcx, [num]
	neg rcx
	mov [num], rcx

	notNegativeNum:


	mov rax, [num]
	mov rdx, 0
	mov rbx, 10
	
	mov r9, [lettersBufferReverse]
	mov rdi, r9
	cld


	divideDigit:


	idiv rbx

	cmp al, 0
	je terminateNumString

	add [lettersLength], 1
	
	mov rbx, rax

	add dl, 48
	mov rax, rdx
	mov rcx, 1
	db 10101010b	;db 0xaa	;stosb

	mov rax, rbx
	mov rdx, 0
	mov rbx, 10
	jmp divideDigit


	terminateNumString:
	
	add [lettersLength], 1

	add dl, 48
	mov rax, rdx
	mov rcx, 1
	db 10101010b	;db 0xaa	;stosb

	mov rax, 0
	mov rcx, 1
	db 10101010b	;db 0xaa	;stosb


	cmp [numberNegative], 1
	jne notNegativeLength

	add [lettersLength], 1

	notNegativeLength:

	mov rax, [lettersLength]


	mov r9, [lettersBufferReverse]
	mov r10, [lettersBufferForward]
	mov rsi, r9
	mov r8, r10
	add r8, rax
	mov rdi, r8



	mov rax, 0

	retrieveReverseNumString:

	std
	mov rcx, 1
	db 10101010b	;db 0xaa	;stosb

	mov rax, 0
	mov rcx, 1
	cld

	lodsb
	
	cmp rax, 0
	jne retrieveReverseNumString


	cmp [numberNegative], 1
	jne noSign
	
	mov rax, 0
	mov al, 150
	mov rcx, 1
	std
	db 10101010b	;db 0xaa	;stosb


	noSign:



	mov rax, [lettersBufferForward]

	


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


letterLength:
namespace letterLength
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*4);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label letters qword at rbp-8 
	label lettersLength qword at rbp-16
	label linearAllocationSize qword at rbp-24
	label num qword at rbp-32
	;label lettersLength qword at rbp-40
	;label numberNegative qword at rbp-48
	;label lettersBufferReverse qword at rbp-56
	;label lettersBufferForward qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [letters], rcx



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

	mov rcx, 0
	mov [lettersLength], rcx 		; Begin as 0

	mov rdx, [letters]

	mov rbx, [rdx]
	cmp bl, 0
	je completed			; Blank


	mov rax, 0
	mov rcx, 0
	not rcx
	cld
	mov rdi, rdx

	repne scasb

	
	not rcx
	dec rcx
	mov [lettersLength], rcx


	completed:
	mov rax, [lettersLength]


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

appendLetters:
namespace appendLetters
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*7);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label letters qword at rbp-8 
	label lettersLength qword at rbp-16
	label linearAllocationSize qword at rbp-24
	label newLetters qword at rbp-32
	label newLettersLength qword at rbp-40
	label lettersLengthSum qword at rbp-48
	label appendedLetters qword at rbp-56
	;label lettersBufferForward qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [letters], rcx
	mov [newLetters], rdx


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

	mov rcx, [letters]
	cmp rcx, 0					; Not appending on anything
	jne lettersNotZero

	mov rdx, [newLetters]
	mov [appendedLetters], rdx
	jmp completed


	lettersNotZero:

	
	sub rsp, 8*8
	mov rcx, [letters]	
	call letterLength
	add rsp, 8*8
	mov [lettersLength], rax

	sub rsp, 8*8
	mov rcx, [newLetters]	
	call letterLength
	add rsp, 8*8
	mov [newLettersLength], rax

	mov rax, [lettersLength]
	mov rcx, [newLettersLength]

	add rax, rcx
	mov [lettersLengthSum], rax

	mov rcx, [lettersLengthSum]
	add rcx, 1b							; Trailing 0
	sub rsp, 8*8
	call allocate.linear
	add rsp, 8*8
	mov [appendedLetters], rax
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;allocate rcx, appendedLetters

	mov rsi, [letters]
	mov rdi, [appendedLetters]
	cld
	mov rcx, [lettersLength]
	rep movsb

	mov rsi, [newLetters]
	mov rdi, [appendedLetters]
	add rdi, [lettersLength]
	cld
	mov rcx, [newLettersLength]
	rep movsb

	mov rsi, letterTerminator
	mov rdi, [appendedLetters]
	add rdi, [lettersLength]
	add rdi, [newLettersLength]
	mov rcx, 1
	cld
	rep movsb

	completed:

	mov rax, [appendedLetters]

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

; Expects StartIndex, EndIndex as next two Items in indicesList
; Will not resetIndex on indicesList in case there are more unrelated Items in List
betweenListsIndices:
namespace betweenListsIndices
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label letters qword at rbp-8 
	label lettersLength qword at rbp-16
	label linearAllocationSize qword at rbp-24
	label newLetters qword at rbp-32
	label newLettersLength qword at rbp-40
	label lettersLengthSum qword at rbp-48
	label indicesList qword at rbp-56
	label lettersBetween qword at rbp-64
	label startIndex qword at rbp-72
	label endIndex qword at rbp-80
	label betweenLength qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [letters], rcx
	mov [indicesList], rdx


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
	mov rcx, [letters]	
	call letterLength
	add rsp, 8*8
	mov [lettersLength], rax

	sub rsp, 8*8
	mov rcx, [indicesList]
	call list.getNextItem
	add rsp, 8*8	
	mov [startIndex], rax

	sub rsp, 8*8
	mov rcx, [indicesList]
	call list.getNextItem
	add rsp, 8*8	
	mov [endIndex], rax

	mov r8, [endIndex]
	mov r9, [startIndex]
	sub r8, r9
	add r8, 1b
	mov [betweenLength], r8


	mov rcx, [betweenLength]
	add rcx, 1b							; Trailing 0
	sub rsp, 8*8
	call allocate.linear
	add rsp, 8*8
	mov [lettersBetween], rax


	mov rsi, [letters]
	mov r9, [startIndex]
	add rsi, r9

	mov rdi, [lettersBetween]
	mov rcx, [betweenLength]
	cld
	rep movsb

	

	mov rsi, letterTerminator
	mov rdi, [lettersBetween]
	add rdi, [betweenLength]
	mov rcx, 1
	cld
	rep movsb



	mov rax, [lettersBetween]

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

; Expects StartIndex, EndIndex as params

betweenIndices:
namespace betweenIndices
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label letters qword at rbp-8 
	label lettersLength qword at rbp-16
	label linearAllocationSize qword at rbp-24
	label newLetters qword at rbp-32
	label newLettersLength qword at rbp-40
	label lettersLengthSum qword at rbp-48
	label indicesList qword at rbp-56
	label lettersBetween qword at rbp-64
	label startIndex qword at rbp-72
	label endIndex qword at rbp-80
	label betweenLength qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [letters], rcx
	mov [startIndex], rdx
	mov [endIndex], r8


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
	mov rcx, [letters]	
	call letterLength
	add rsp, 8*8
	mov [lettersLength], rax




	mov r8, [endIndex]
	mov r9, [startIndex]
	sub r8, r9
	add r8, 1b
	mov [betweenLength], r8


	mov rcx, [betweenLength]
	add rcx, 1b							; Trailing 0
	sub rsp, 8*8
	call allocate.linear
	add rsp, 8*8
	mov [lettersBetween], rax


	mov rsi, [letters]
	mov r9, [startIndex]
	add rsi, r9

	mov rdi, [lettersBetween]
	mov rcx, [betweenLength]
	cld
	rep movsb

	

	mov rsi, letterTerminator
	mov rdi, [lettersBetween]
	add rdi, [betweenLength]
	mov rcx, 1
	cld
	rep movsb



	mov rax, [lettersBetween]

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

copyLetters:
namespace copyLetters
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*7);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label letters qword at rbp-8 
	label lettersLength qword at rbp-16
	label linearAllocationSize qword at rbp-24
	label newLetters qword at rbp-32
	label newLettersLength qword at rbp-40
	label lettersLengthSum qword at rbp-48
	label appendedLetters qword at rbp-56
	;label lettersBufferForward qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [letters], rcx



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
	mov rcx, [letters]	
	call letterLength
	add rsp, 8*8
	mov [lettersLength], rax

	

	mov rcx, [lettersLength]
	add rcx, 1b							; Trailing 0
	sub rsp, 8*8
	call allocate.linear
	add rsp, 8*8
	mov [newLetters], rax
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;allocate rcx, newLetters

	mov rsi, [letters]
	mov rdi, [newLetters]
	cld
	mov rcx, [lettersLength]
	rep movsb



	mov rsi, letterTerminator
	mov rdi, [newLetters]
	add rdi, [lettersLength]
	mov rcx, 1
	cld
	rep movsb

	completed:

	mov rax, [newLetters]

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

appendZero:
namespace appendZero
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label debugMsgSize qword at rbp-8 
	label heapAddress qword at rbp-16
	label linearAllocationSize qword at rbp-24
	label num qword at rbp-32
	label lettersLength qword at rbp-40
	label numberNegative qword at rbp-48
	label letters qword at rbp-56
	label lettersBufferForward qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [letters], rcx
	mov [lettersLength], rdx

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
	mov [heapAddress], rax
	add rsp, 8*4


	mov rcx, 0
	add rcx, ListItem.next
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, [lettersLength]	; Length + 1 (zero)
	add r8, 1b
	mov rdx, 000001000b
	mov rcx, [heapAddress]
	call [ HeapAlloc] 
	mov [lettersBufferForward], rax
	add rsp, 8*4



	mov rsi, [letters]
	mov rcx, [lettersLength]
	
	mov rdi, [lettersBufferForward]
	cld
	rep movsb


	mov rsi, letterTerminator
	mov rdi, [lettersBufferForward]
	add rdi, [lettersLength]
	mov rcx, 1
	cld
	rep movsb




	mov rax, [lettersBufferForward]

	


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

listAsLetters:
namespace listAsLetters
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label debugMsgSize qword at rbp-8 
	label heapAddress qword at rbp-16
	label linearAllocationSize qword at rbp-24
	label lettersList qword at rbp-32
	label lettersLength qword at rbp-40
	label numberNegative qword at rbp-48
	label letters qword at rbp-56
	label nextLetters qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [lettersList], rcx

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

	mov rcx, 0
	mov [letters], 0		; Begin as 0


	sub rsp, 8*8
	mov rcx, [lettersList]
	call list.resetIndex
	add rsp, 8*8

	nextListItem:
	mov rbx, [lettersList]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl completed


	sub rsp, 8*8
	mov rcx, [lettersList]
	call list.getNextItem
	add rsp, 8*8
	mov [nextLetters], rax

	mov rcx, [letters]
	cmp rcx, 0
	jne notFirstLetters

	sub rsp, 8*8
	mov rcx, [nextLetters]
	call copyLetters				; allocate first, do not append
	add rsp, 8*8
	mov [letters], rax

	jmp nextListItem
	notFirstLetters:

	sub rsp, 8*8
	mov rcx, [nextLetters]
	call copyLetters				; allocate first, do not append
	add rsp, 8*8
	

	sub rsp, 8*8
	mov rdx,rax
	mov rcx, [letters]
	call appendLetters				; Append
	add rsp, 8*8
	mov [letters], rax


	jmp nextListItem
	completed:

	mov rax, [letters]

	


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


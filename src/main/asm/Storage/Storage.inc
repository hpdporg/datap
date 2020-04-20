


section '.data' data readable writeable align 16



	struc Record
		label .
		.allocAddr dq 0		; Binary or text allocation addr
		.allocSize dq 0		; Size of allocation (base 8)
		.name dq 0		; Record name with extension
		.location dq 0		; Path
		.builtLocation dq 0	; Built Path
		.handle dq 0
	end struc




	; Used with address offsets
	virtual at 0
		Record Record
	end virtual

	; ---- Structures
	;element Element

	debugRecName db 'DebugRec.txt',0

	

section '.text' code readable writeable executable align 16


; storage.defineFilePath
; storage.newFile

storage:
namespace storage
new:
namespace new
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*2);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
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
	mov [heapAddress], rax
	add rsp, 8*4
	

	mov rcx, 0
	add rcx, Record.handle
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [heapAddress]
	call [ HeapAlloc] 
	mov [handleAllocatedMemory], rax
	add rsp, 8*4


	mov rbx, [handleAllocatedMemory]
	add rbx, Record.allocAddr
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Record.allocSize
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Record.name
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Record.location
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Record.builtLocation
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Record.handle
	mov rax, 0
	mov [rbx], rax


	;lea rax, [list]
	;lea rcx, [list.indexedItemIndex]

	;sub rcx, rax
	;add rcx, 1000b

	;cld

	;lea rsi, [list]
	;mov rdi, [storage.handleAllocatedMemory]

	;rep movsb


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

retrieve:
namespace retrieve
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label list qword at rbp-24 
	label item qword at rbp-32
	label recordAddr qword at rbp-40
	label sizeRetrieved qword at rbp-48
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

	sub rsp, 8*8
	mov qword [rsp+6*8], 0					;hTemplateFile
	mov qword [rsp+5*8], 128 				;dwFlagsandAttributes
	mov qword [rsp+4*8], 000000100b 			;dwCreationDisposition
	mov r9, 0 						;lpSecurityAttributes
	mov r8, 000000010b 					;dwShareMode
	mov rdx, 10100000000000000000000100000101b		;dwDesiredAccess
	mov rbx, [recordAddr]
	add rbx, Record.builtLocation
	mov rcx, [rbx]
	call [CreateFile]
	add rsp, 8*8
	mov rbx, [recordAddr]
	add rbx, Record.handle
	mov [rbx], rax

	mov rbx, [recordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	sub rsp, 8*4
	call [SetEndOfFile]
	add rsp, 8*4


	sub rsp, 8*8
	mov rdx, 0				; File size high
	mov rbx, [recordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	call [GetFileSize]
	add rsp, 8*8
	mov rbx, [recordAddr]
	add rbx, Record.allocSize
	mov rcx, 0
	mov ecx, eax
	mov [rbx], rcx

	sub rsp, 8*4
	call [GetProcessHeap]
	mov [heapAddress], rax
	add rsp, 8*4
	

	sub rsp, 8*4
	mov rbx, [recordAddr]
	add rbx, Record.allocSize
	mov r8, [rbx]	
	mov rdx, 000001000b
	mov rcx, [heapAddress]
	call [ HeapAlloc] 
	mov rbx, [recordAddr]
	add rbx, Record.allocAddr
	mov [rbx], rax
	add rsp, 8*4



	sub rsp, 8*8
	mov r10, 0
	mov [rsp+4*8], r10
	lea r9, [sizeRetrieved]
	mov rbx, [recordAddr]
	add rbx, Record.allocSize
	mov r8, [rbx]
	mov rbx, [recordAddr]
	add rbx, Record.allocAddr
	mov rdx, [rbx]
	mov rbx, [recordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	call [ReadFile]
	add rsp, 8*8

	sub rsp, 8*8
	call [GetLastError]
	add rsp, 8*8
	mov r12, rax



	sub rsp, 8*8
	mov rdx, 0				; File size high
	mov rbx, [recordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	call [CloseHandle]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [recordAddr]
	add rbx, Record.allocSize
	mov rdx, [rbx]
	mov rbx, [recordAddr]
	add rbx, Record.allocAddr
	mov rcx, [rbx]
	call letters.appendZero
	add rsp, 8*8

	mov rbx, [recordAddr]
	add rbx, Record.allocAddr
	mov [rbx], rax

	mov rbx, [recordAddr]
	add rbx, Record.allocSize
	mov r8, [rbx]
	add r8, 1b
	mov [rbx], r8


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

storeLetters:
namespace storeLetters
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label letterLength qword at rbp-24 
	label sizeWritten qword at rbp-32
	label recordAddr qword at rbp-40
	label lettersAlloc qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [recordAddr], rcx
	mov [lettersAlloc], rdx


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
	mov rcx, [lettersAlloc]
	call letters.letterLength
	add rsp, 8*4
	mov [letterLength], rax


	sub rsp, 8*10
	mov qword [rsp+6*8], 0					;hTemplateFile
	mov qword [rsp+5*8], 128 				;dwFlagsandAttributes
	mov qword [rsp+4*8], 000000100b 			;dwCreationDisposition
	mov r9, 0 						;lpSecurityAttributes
	mov r8, 000000010b 					;dwShareMode
	mov rdx, 10100000000000000000000100000101b		;dwDesiredAccess
	mov rbx, [recordAddr]
	add rbx, Record.builtLocation
	mov rcx, [rbx]
	call [CreateFile]
	add rsp, 8*10
	mov rbx, [recordAddr]
	add rbx, Record.handle
	mov [rbx], rax

	mov rbx, [recordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	sub rsp, 8*4
	call [SetEndOfFile]
	add rsp, 8*4

	sub rsp, 8*8
	mov rdx, 0				; File size high
	mov rbx, [recordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	call [GetFileSize]
	add rsp, 8*8
	mov rbx, [recordAddr]
	add rbx, Record.allocSize
	mov rcx, 0
	mov ecx, eax
	mov [rbx], rcx

	sub rsp, 8*8
	mov qword [rsp+4*8], 0
	lea r9, [sizeWritten]
	mov r8, [letterLength]
	mov rdx, [lettersAlloc]
	mov rbx, [recordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	call [WriteFile]
	add rsp, 8*8


	mov rbx, [recordAddr]
	add rbx, Record.allocSize
	mov rcx, [rbx]
	mov rdx, [letterLength]
	add rcx, rdx
	mov [rbx], rcx

	

	sub rsp, 8*8
	mov rdx, 0				; File size high
	mov rbx, [recordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	call [CloseHandle]
	add rsp, 8*8




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

; Replaces contents

restoreLetters:
namespace restoreLetters
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label reheapAddress qword at rbp-8  
	label rehandleAllocatedMemory qword at rbp-16
	label reletterLength qword at rbp-24 
	label resizeWritten qword at rbp-32
	label rerecordAddr qword at rbp-40
	label reletters qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [rerecordAddr], rcx
	mov [reletters], rdx


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
	mov rcx, [reletters]
	call letters.letterLength
	add rsp, 8*4
	mov [reletterLength], rax


	mov rbx, [rerecordAddr]
	add rbx, Record.builtLocation
	mov rcx, [rbx]
	sub rsp, 8*4
	call [DeleteFile]
	add rsp, 8*4

	sub rsp, 8*8
	mov qword [rsp+6*8], 0					;hTemplateFile
	mov qword [rsp+5*8], 128 				;dwFlagsandAttributes
	mov qword [rsp+4*8], 000000100b 			;dwCreationDisposition
	mov r9, 0 						;lpSecurityAttributes
	mov r8, 000000010b 					;dwShareMode
	mov rdx, 10100000000000000000000100000101b		;dwDesiredAccess
	mov rbx, [rerecordAddr]
	add rbx, Record.builtLocation
	mov rcx, [rbx]
	call [CreateFile]
	add rsp, 8*8
	mov rbx, [rerecordAddr]
	add rbx, Record.handle
	mov [rbx], rax



	sub rsp, 8*8
	mov qword [rsp+4*8], 0
	lea r9, [resizeWritten]
	mov r8, [reletterLength]
	mov rdx, [reletters]
	mov rbx, [rerecordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	call [WriteFile]
	add rsp, 8*8


	mov rbx, [rerecordAddr]
	add rbx, Record.allocSize
	mov rcx, [rbx]
	mov rdx, [reletterLength]
	add rcx, rdx
	mov [rbx], rcx

	

	sub rsp, 8*8
	mov rdx, 0				; File size high
	mov rbx, [rerecordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	call [CloseHandle]
	add rsp, 8*8




	mov rax,0; [rerecordAddr]


	reend:


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

; Replaces file with allocation already in record
; No letters passed in
?restore:
namespace restore
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label letterLength qword at rbp-24 
	label sizeWritten qword at rbp-32
	label recordAddr qword at rbp-40
	label lettersAlloc qword at rbp-48
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


	sub rsp, 8*4
	mov rbx, [recordAddr]
	add rbx, Record.allocAddr
	mov rcx, [rbx]
	call letters.letterLength
	add rsp, 8*4
	mov [letterLength], rax
	mov rbx, [recordAddr]
	add rbx, Record.allocSize
	mov [rbx], rax


	mov rbx, [recordAddr]
	add rbx, Record.builtLocation
	mov rcx, [rbx]
	sub rsp, 8*4
	call [DeleteFile]
	add rsp, 8*4

	sub rsp, 8*8
	mov qword [rsp+6*8], 0					;hTemplateFile
	mov qword [rsp+5*8], 128 				;dwFlagsandAttributes
	mov qword [rsp+4*8], 000000100b 			;dwCreationDisposition
	mov r9, 0 						;lpSecurityAttributes
	mov r8, 000000010b 					;dwShareMode
	mov rdx, 10100000000000000000000100000101b		;dwDesiredAccess
	mov rbx, [recordAddr]
	add rbx, Record.builtLocation
	mov rcx, [rbx]
	call [CreateFile]
	add rsp, 8*8
	mov rbx, [recordAddr]
	add rbx, Record.handle
	mov [rbx], rax



	sub rsp, 8*8
	mov qword [rsp+4*8], 0
	lea r9, [sizeWritten]
	mov r8, [letterLength]
	mov rbx, [recordAddr]
	add rbx, Record.allocAddr
	mov rdx, [rbx]
	mov rbx, [recordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	call [WriteFile]
	add rsp, 8*8


	mov rbx, [recordAddr]
	add rbx, Record.allocSize
	mov rcx, [rbx]
	mov rdx, [letterLength]
	add rcx, rdx
	mov [rbx], rcx

	

	sub rsp, 8*8
	mov rdx, 0				; File size high
	mov rbx, [recordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	call [CloseHandle]
	add rsp, 8*8




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

defineRecordPath:
namespace defineRecordPath
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*3);+(8*0)

	;mov rcx, [rbp+8]
	;mov rdx, [rbp+12]
	label recordAddr qword at rbp-8  
	label name qword at rbp-16
	label location qword at rbp-24
	;virtual at rbp-64
	;	.list List
	;end virtual	

	mov [recordAddr], rcx
	mov [name], rdx
	mov [location], r8

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

	mov rbx, [recordAddr]
	add rbx, Record.name
	mov rdx, [name]
	mov [rbx], rdx
	mov rbx, [recordAddr]
	add rbx, Record.location
	mov r8, [location]
	mov [rbx], r8	


	sub rsp, 8*8
	mov rdx, pathSepLetters
	mov rcx, [location]
	call letters.appendLetters
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, [name]
	mov rcx, rax
	call letters.appendLetters
	add rsp, 8*8

	mov rbx, [recordAddr]
	add rbx, Record.builtLocation
	mov [rbx], rax


	mov rax, [recordAddr]

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

retrieveRecordNames:
namespace retrieveRecordNames
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*10);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label handle qword at rbp-24 
	label item qword at rbp-32
	label recordAddr qword at rbp-40
	label sizeRetrieved qword at rbp-48
	label w32FindData qword at rbp-56
	label locationContentsLetters qword at rbp-64
	label nextFileNameLetters qword at rbp-72
	label listAlloc qword at rbp-80
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

	;Sizes w32_find_Data
	;  DWORD    dwFileAttributes;		4
	;  FILETIME ftCreationTime;		8
	;  FILETIME ftLastAccessTime;		8
	;  FILETIME ftLastWriteTime;		8
	;  DWORD    nFileSizeHigh;		4
	;  DWORD    nFileSizeLow;		4
	;  DWORD    dwReserved0;		4
	;  DWORD    dwReserved1;		4
	;  CHAR     cFileName[MAX_PATH];	1



	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	mov [listAlloc], rax
	

	sub rsp, 8*8
	mov rdx, directoryContentsLetters
	mov rbx, [recordAddr]
	add rbx, Record.location
	mov rcx, [rbx]
	call letters.appendLetters
	add rsp, 8*8
	mov [locationContentsLetters], rax



	sub rsp, 8*8
	mov rcx, 8*20;64					; Size
	call allocate.linear
	add rsp, 8*8
	mov [w32FindData], rax




	sub rsp, 8*8
	mov rdx, [w32FindData]
	mov rcx,[locationContentsLetters]
	call [FindFirstFile]
	add rsp, 8*8
	mov [handle], rax
	mov r9, 0
	sub r9, 1b
	cmp rax, r9
	jne noError ; INVALID_HANDLE_VALUE

	;sub rsp, 8*8
	;call [GetLastError]
	;add rsp, 8*8
	;mov rax, rax
	

	noError:
	;jmp firstFile	; debug

	sub rsp, 8*8
	mov rdx, currentDirLetter
	mov r9, [w32FindData]
	add r9, 44
	mov rcx, r9
	call matching.lettersSameExact
	add rsp, 8*8
	cmp rax, 0
	jne nextFile

	sub rsp, 8*8
	mov rdx, containingDirLetters
	mov r9, [w32FindData]
	add r9, 44
	mov rcx, r9
	call matching.lettersSameExact
	add rsp, 8*8
	cmp rax, 0
	jne nextFile

	firstFile:
	mov r9, [w32FindData]
	add r9, 44
	mov rcx, r9
	sub rsp, 8*8
	call letters.copyLetters
	mov rdx, rax
	add rsp, 8*8



	sub rsp, 8*8
	;mov rdx, rax
	mov rcx, [listAlloc]
	call list.newLastItem
	add rsp, 8*8


	;mov r14, 0
	;mov [item], r14	;debug

	nextFile:

	;sub rsp, 8*8
	;mov rcx, 3892
	;call debugNumMsg
	;add rsp, 8*8
;jmp completed	;dbg just this line

	sub rsp, 8*8
	mov rdx, [w32FindData]
	mov rcx, [handle]
	call [FindNextFile]
	add rsp, 8*8
	mov r9, rax
	cmp r9, 0
	je endFiles



	;mov r14, [item]
	;add r14, 10b
	;mov [item], r14
	;cmp r14, 101b
	;jge end

	;jmp newLast	; debug

	sub rsp, 8*8
	mov rdx, currentDirLetter
	mov r9, [w32FindData]
	add r9, 44
	mov rcx, r9
	call matching.lettersSameExact				
	add rsp, 8*8
	cmp rax, 0
	jne nextFile

	sub rsp, 8*8
	mov rdx, containingDirLetters
	mov r9, [w32FindData]
	add r9, 44
	mov rcx, r9
	call matching.lettersSameExact
	add rsp, 8*8
	cmp rax, 0
	jne nextFile

	newLast:
	mov r9, [w32FindData]
	add r9, 44
	mov rcx, r9
	sub rsp, 8*8
	call letters.copyLetters
	mov rdx, rax
	add rsp, 8*8

	sub rsp, 8*8
	;mov rdx, rax
	mov rcx, [listAlloc]
	call list.newLastItem
	add rsp, 8*8

	;jmp completed	;dbg just this line

	jmp nextFile
	endFiles:


	sub rsp, 8*8
	mov rcx, [handle]
	;call [FindClose]
	add rsp, 8*8


	completed:




	mov rax, [listAlloc]


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

; Uses extension also
retrieveRecordNamesExtension:
namespace retrieveRecordNamesExtension
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label handle qword at rbp-24 
	label item qword at rbp-32
	label recordAddr qword at rbp-40
	label sizeRetrieved qword at rbp-48
	label w32FindData qword at rbp-56
	label locationContentsLetters qword at rbp-64
	label nextFileNameLetters qword at rbp-72
	label listAlloc qword at rbp-80
	label fileExtensionLetters qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [recordAddr], rcx
	mov [fileExtensionLetters], rdx

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

	;Sizes w32_find_Data
	;  DWORD    dwFileAttributes;		4
	;  FILETIME ftCreationTime;		8
	;  FILETIME ftLastAccessTime;		8
	;  FILETIME ftLastWriteTime;		8
	;  DWORD    nFileSizeHigh;		4
	;  DWORD    nFileSizeLow;		4
	;  DWORD    dwReserved0;		4
	;  DWORD    dwReserved1;		4
	;  CHAR     cFileName[MAX_PATH];	1



	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	mov [listAlloc], rax
	

	sub rsp, 8*8
	mov rdx, directoryContentsLetters
	mov rbx, [recordAddr]
	add rbx, Record.location
	mov rcx, [rbx]
	call letters.appendLetters
	add rsp, 8*8
	mov [locationContentsLetters], rax

	sub rsp, 8*8
	mov rdx, [fileExtensionLetters]
	mov rcx, [locationContentsLetters]
	call letters.appendLetters							; Only difference from retrieveRecordNames
	add rsp, 8*8
	mov [locationContentsLetters], rax


	sub rsp, 8*8
	mov rcx, 64
	call allocate.linear
	add rsp, 8*8
	mov [w32FindData], rax




	sub rsp, 8*8
	mov rdx, [w32FindData]
	mov rcx,[locationContentsLetters]
	call [FindFirstFile]
	add rsp, 8*8
	mov [handle], rax
	mov r9, 0
	sub r9, 1b
	cmp rax, r9
	jne noError ; INVALID_HANDLE_VALUE


	sub rsp, 8*8
	mov rcx, 64328
	;call debugNumMsg
	add rsp, 8*8

	;sub rsp, 8*8
	;call [GetLastError]
	;add rsp, 8*8
	;mov rax, rax
	

	noError:
	;jmp firstFile	; debug

	sub rsp, 8*8
	mov rdx, currentDirLetter
	mov r9, [w32FindData]
	add r9, 44
	mov rcx, r9
	call matching.lettersSameExact
	add rsp, 8*8
	cmp rax, 0
	jne nextFile


	sub rsp, 8*8
	mov rcx, 43228
	;call debugNumMsg
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, containingDirLetters
	mov r9, [w32FindData]
	add r9, 44
	mov rcx, r9
	call matching.lettersSameExact
	add rsp, 8*8
	cmp rax, 0
	jne nextFile


	sub rsp, 8*8
	mov rcx, 4828
	;call debugNumMsg
	add rsp, 8*8

	firstFile:
	mov r9, [w32FindData]
	add r9, 44
	mov rcx, r9
	sub rsp, 8*8
	call letters.copyLetters
	mov rdx, rax
	add rsp, 8*8

	sub rsp, 8*8
	;mov rdx, rax
	mov rcx, [listAlloc]
	call list.newLastItem
	add rsp, 8*8


	sub rsp, 8*8
	mov rcx, 2328
	;call debugNumMsg
	add rsp, 8*8


	;mov r14, 0
	;mov [item], r14	;debug

	nextFile:

	sub rsp, 8*8
	mov rdx, [w32FindData]
	mov rcx, [handle]
	call [FindNextFile]
	add rsp, 8*8
	mov r9, rax
	cmp r9, 0
	je endFiles



	;mov r14, [item]
	;add r14, 10b
	;mov [item], r14
	;cmp r14, 101b
	;jge completed

	;jmp newLast	; debug


	sub rsp, 8*8
	mov rcx, 88228
	;call debugNumMsg
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, currentDirLetter
	mov r9, [w32FindData]
	add r9, 44
	mov rcx, r9
	call matching.lettersSameExact				
	add rsp, 8*8
	cmp rax, 0
	jne nextFile

	sub rsp, 8*8
	mov rdx, containingDirLetters
	mov r9, [w32FindData]
	add r9, 44
	mov rcx, r9
	call matching.lettersSameExact
	add rsp, 8*8
	cmp rax, 0
	jne nextFile

	newLast:
	mov r9, [w32FindData]
	add r9, 44
	mov rcx, r9
	sub rsp, 8*8
	call letters.copyLetters
	mov rdx, rax
	add rsp, 8*8

	sub rsp, 8*8
	;mov rdx, rax
	mov rcx, [listAlloc]
	call list.newLastItem
	add rsp, 8*8



	jmp nextFile
	endFiles:


	sub rsp, 8*8
	mov rcx, 999228
	;call debugNumMsg
	add rsp, 8*8


	completed:


	sub rsp, 8*8
	mov rcx, 78728
	;call debugNumMsg
	add rsp, 8*8

	mov rax, [listAlloc]


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

removeRecord:
namespace removeRecord
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label listAlloc qword at rbp-24 
	label item qword at rbp-32
	label recordAddr qword at rbp-40
	label sizeRetrieved qword at rbp-48
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




	sub rsp, 8*8
	mov rdx, 0				; File size high
	mov rbx, [recordAddr]
	add rbx, Record.builtLocation
	mov rcx, [rbx]
	call [DeleteFile]
	add rsp, 8*8


	
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

debugNum:
namespace debugNum
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label listAlloc qword at rbp-24 
	label item qword at rbp-32
	label recordAddr qword at rbp-40
	label sizeRetrieved qword at rbp-48
	label num qword at rbp-56
	label lettersAlloc qword at rbp-64
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

	sub rsp, 8*8
	mov rcx, [num]
	call letters.numAsLetters
	add rsp, 8*8
	mov [lettersAlloc], rax


	sub rsp, 8*8
	call new
	add rsp, 8*8
	mov [recordAddr], rax

	mov rbx, [recordAddr]
	add rbx, Record.builtLocation
	mov rdx, debugRecName
	mov [rbx], rdx
	
	sub rsp, 8*8
	mov rdx, [lettersAlloc]
	mov rcx, [recordAddr]
	call storeLetters
	add rsp, 8*8


	
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

debugLetters:
namespace debugLetters
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label listAlloc qword at rbp-24 
	label item qword at rbp-32
	label recordAddr qword at rbp-40
	label sizeRetrieved qword at rbp-48
	label num qword at rbp-56
	label lettersAlloc qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [lettersAlloc], rcx

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
	call new
	add rsp, 8*8
	mov [recordAddr], rax

	mov rbx, [recordAddr]
	add rbx, Record.builtLocation
	mov rdx, debugRecName
	mov [rbx], rdx
	
	sub rsp, 8*8
	mov rdx, [lettersAlloc]
	mov rcx, [recordAddr]
	call storeLetters
	add rsp, 8*8


	
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

; Includes newline
debugNumMsg:
namespace debugNumMsg
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label listAlloc qword at rbp-24 
	label item qword at rbp-32
	label recordAddr qword at rbp-40
	label sizeRetrieved qword at rbp-48
	label num qword at rbp-56
	label lettersAlloc qword at rbp-64
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

	sub rsp, 8*8
	mov rcx, [num]
	call letters.numAsLetters
	add rsp, 8*8
	mov [lettersAlloc], rax

	sub rsp, 8*8
	mov rdx, newlineWinLetters
	mov rcx, [lettersAlloc]
	call letters.appendLetters
	add rsp, 8*8
	mov rdx, rax
	mov [lettersAlloc], rdx


	sub rsp, 8*8
	call new
	add rsp, 8*8
	mov [recordAddr], rax

	mov rbx, [recordAddr]
	add rbx, Record.builtLocation
	mov rdx, debugRecName
	mov [rbx], rdx
	
	sub rsp, 8*8
	mov rdx, [lettersAlloc]
	mov rcx, [recordAddr]
	call storeLetters
	add rsp, 8*8


	
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

; Includes newline
debugLettersMsg:
namespace debugLettersMsg
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label listAlloc qword at rbp-24 
	label item qword at rbp-32
	label recordAddr qword at rbp-40
	label sizeRetrieved qword at rbp-48
	label num qword at rbp-56
	label lettersAlloc qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [lettersAlloc], rcx

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
	mov rdx, newlineWinLetters
	mov rcx, [lettersAlloc]
	call letters.appendLetters
	add rsp, 8*8
	mov rdx, rax
	mov [lettersAlloc], rdx
	

	sub rsp, 8*8
	call new
	add rsp, 8*8
	mov [recordAddr], rax

	mov rbx, [recordAddr]
	add rbx, Record.builtLocation
	mov rdx, debugRecName
	mov [rbx], rdx
	
	sub rsp, 8*8
	mov rdx, [lettersAlloc]
	mov rcx, [recordAddr]
	call storeLetters
	add rsp, 8*8


	
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

newFile:
namespace newFile
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*2);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label handleAddr qword at rbp-8  
	label fileNameAddr qword at rbp-16
	;virtual at rbp-64
	;	.list List
	;end virtual	

	mov [fileNameAddr], rcx

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


	mov rax, [handleAddr]

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

writeFile:
namespace writeFile
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*4);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label handleAddr qword at rbp-8  
	label entry qword at rbp-16
	label size qword at rbp-24
	label writtenAddr qword at rbp-32
	;virtual at rbp-64
	;	.list List
	;end virtual	

	mov [handleAddr], rcx
	mov [entry], rdx
	mov [size], r8

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

	mov rax, [handleAddr]

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
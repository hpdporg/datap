


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
	add rbx, Record.builtLocation
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
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label retrieve.heapAddress qword at rbp-8  
	label retrieve.handleAllocatedMemory qword at rbp-16
	label retrieve.list qword at rbp-24 
	label retrieve.item qword at rbp-32
	label retrieve.recordAddr qword at rbp-40
	label retrieve.sizeRetrieved qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [retrieve.recordAddr], rcx


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
	mov rbx, [retrieve.recordAddr]
	add rbx, Record.builtLocation
	mov rcx, [rbx]
	call [CreateFile]
	add rsp, 8*8
	mov rbx, [retrieve.recordAddr]
	add rbx, Record.handle
	mov [rbx], rax

	mov rbx, [retrieve.recordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	sub rsp, 8*4
	call [SetEndOfFile]
	add rsp, 8*4


	sub rsp, 8*8
	mov rdx, 0				; File size high
	mov rbx, [retrieve.recordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	call [GetFileSize]
	add rsp, 8*8
	mov rbx, [retrieve.recordAddr]
	add rbx, Record.allocSize
	mov rcx, 0
	mov ecx, eax
	mov [rbx], rcx

	sub rsp, 8*4
	call [GetProcessHeap]
	mov [retrieve.heapAddress], rax
	add rsp, 8*4
	

	sub rsp, 8*4
	mov rbx, [retrieve.recordAddr]
	add rbx, Record.allocSize
	mov r8, [rbx]	
	mov rdx, 000001000b
	mov rcx, [retrieve.heapAddress]
	call [ HeapAlloc] 
	mov rbx, [retrieve.recordAddr]
	add rbx, Record.allocAddr
	mov [rbx], rax
	add rsp, 8*4



	sub rsp, 8*8
	mov r10, 0
	mov [rsp+4*8], r10
	lea r9, [retrieve.sizeRetrieved]
	mov rbx, [retrieve.recordAddr]
	add rbx, Record.allocSize
	mov r8, [rbx]
	mov rbx, [retrieve.recordAddr]
	add rbx, Record.allocAddr
	mov rdx, [rbx]
	mov rbx, [retrieve.recordAddr]
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
	mov rbx, [retrieve.recordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	call [CloseHandle]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [retrieve.recordAddr]
	add rbx, Record.allocSize
	mov rdx, [rbx]
	mov rbx, [retrieve.recordAddr]
	add rbx, Record.allocAddr
	mov rcx, [rbx]
	call letters.appendZero
	add rsp, 8*8

	mov rbx, [retrieve.recordAddr]
	add rbx, Record.allocAddr
	mov [rbx], rax

	mov rbx, [retrieve.recordAddr]
	add rbx, Record.allocSize
	mov r8, [rbx]
	add r8, 1b
	mov [rbx], r8


	mov rax, [retrieve.recordAddr]
	
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

storage.storeLetters:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label storeLetters.heapAddress qword at rbp-8  
	label storeLetters.handleAllocatedMemory qword at rbp-16
	label storeLetters.letterLength qword at rbp-24 
	label storeLetters.sizeWritten qword at rbp-32
	label storeLetters.recordAddr qword at rbp-40
	label storeLetters.letters qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [storeLetters.recordAddr], rcx
	mov [storeLetters.letters], rdx


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
	mov rcx, [storeLetters.letters]
	call letters.letterLength
	add rsp, 8*4
	mov [storeLetters.letterLength], rax


	sub rsp, 8*10
	mov qword [rsp+6*8], 0					;hTemplateFile
	mov qword [rsp+5*8], 128 				;dwFlagsandAttributes
	mov qword [rsp+4*8], 000000100b 			;dwCreationDisposition
	mov r9, 0 						;lpSecurityAttributes
	mov r8, 000000010b 					;dwShareMode
	mov rdx, 10100000000000000000000100000101b		;dwDesiredAccess
	mov rbx, [storeLetters.recordAddr]
	add rbx, Record.builtLocation
	mov rcx, [rbx]
	call [CreateFile]
	add rsp, 8*10
	mov rbx, [storeLetters.recordAddr]
	add rbx, Record.handle
	mov [rbx], rax

	mov rbx, [storeLetters.recordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	sub rsp, 8*4
	call [SetEndOfFile]
	add rsp, 8*4

	sub rsp, 8*8
	mov rdx, 0				; File size high
	mov rbx, [storeLetters.recordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	call [GetFileSize]
	add rsp, 8*8
	mov rbx, [storeLetters.recordAddr]
	add rbx, Record.allocSize
	mov rcx, 0
	mov ecx, eax
	mov [rbx], rcx

	sub rsp, 8*8
	mov qword [rsp+4*8], 0
	lea r9, [storeLetters.sizeWritten]
	mov r8, [storeLetters.letterLength]
	mov rdx, [storeLetters.letters]
	mov rbx, [storeLetters.recordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	call [WriteFile]
	add rsp, 8*8


	mov rbx, [storeLetters.recordAddr]
	add rbx, Record.allocSize
	mov rcx, [rbx]
	mov rdx, [storeLetters.letterLength]
	add rcx, rdx
	mov [rbx], rcx

	

	sub rsp, 8*8
	mov rdx, 0				; File size high
	mov rbx, [storeLetters.recordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	call [CloseHandle]
	add rsp, 8*8




	mov rax, [storeLetters.recordAddr]


	storeLetters.end:


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

; Replaces contents

storage.restoreLetters:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label restoreLetters.heapAddress qword at rbp-8  
	label restoreLetters.handleAllocatedMemory qword at rbp-16
	label restoreLetters.letterLength qword at rbp-24 
	label restoreLetters.sizeWritten qword at rbp-32
	label restoreLetters.recordAddr qword at rbp-40
	label restoreLetters.letters qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [restoreLetters.recordAddr], rcx
	mov [restoreLetters.letters], rdx


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
	mov rcx, [restoreLetters.letters]
	call letters.letterLength
	add rsp, 8*4
	mov [restoreLetters.letterLength], rax


	mov rbx, [restoreLetters.recordAddr]
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
	mov rbx, [restoreLetters.recordAddr]
	add rbx, Record.builtLocation
	mov rcx, [rbx]
	call [CreateFile]
	add rsp, 8*8
	mov rbx, [restoreLetters.recordAddr]
	add rbx, Record.handle
	mov [rbx], rax



	sub rsp, 8*8
	mov qword [rsp+4*8], 0
	lea r9, [restoreLetters.sizeWritten]
	mov r8, [restoreLetters.letterLength]
	mov rdx, [restoreLetters.letters]
	mov rbx, [restoreLetters.recordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	call [WriteFile]
	add rsp, 8*8


	mov rbx, [restoreLetters.recordAddr]
	add rbx, Record.allocSize
	mov rcx, [rbx]
	mov rdx, [restoreLetters.letterLength]
	add rcx, rdx
	mov [rbx], rcx

	

	sub rsp, 8*8
	mov rdx, 0				; File size high
	mov rbx, [restoreLetters.recordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	call [CloseHandle]
	add rsp, 8*8




	mov rax, [restoreLetters.recordAddr]


	restoreLetters.end:


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


; Replaces file with allocation already in record
; No letters passed in
storage.restore:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label restore.heapAddress qword at rbp-8  
	label restore.handleAllocatedMemory qword at rbp-16
	label restore.letterLength qword at rbp-24 
	label restore.sizeWritten qword at rbp-32
	label restore.recordAddr qword at rbp-40
	label restore.letters qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [restore.recordAddr], rcx
	

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
	mov rbx, [restore.recordAddr]
	add rbx, Record.allocAddr
	mov rcx, [rbx]
	call letters.letterLength
	add rsp, 8*4
	mov [restore.letterLength], rax
	mov rbx, [restore.recordAddr]
	add rbx, Record.allocSize
	mov [rbx], rax


	mov rbx, [restore.recordAddr]
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
	mov rbx, [restore.recordAddr]
	add rbx, Record.builtLocation
	mov rcx, [rbx]
	call [CreateFile]
	add rsp, 8*8
	mov rbx, [restore.recordAddr]
	add rbx, Record.handle
	mov [rbx], rax



	sub rsp, 8*8
	mov qword [rsp+4*8], 0
	lea r9, [restore.sizeWritten]
	mov r8, [restore.letterLength]
	mov rbx, [restore.recordAddr]
	add rbx, Record.allocAddr
	mov rdx, [rbx]
	mov rbx, [restore.recordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	call [WriteFile]
	add rsp, 8*8


	mov rbx, [restore.recordAddr]
	add rbx, Record.allocSize
	mov rcx, [rbx]
	mov rdx, [restore.letterLength]
	add rcx, rdx
	mov [rbx], rcx

	

	sub rsp, 8*8
	mov rdx, 0				; File size high
	mov rbx, [restore.recordAddr]
	add rbx, Record.handle
	mov rcx, [rbx]
	call [CloseHandle]
	add rsp, 8*8




	mov rax, [restore.recordAddr]


	restore.end:


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


	sub rsp, 8*8
	mov rdx, pathSepLetters
	mov rcx, [defineRecordPath.location]
	call letters.appendLetters
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, [defineRecordPath.name]
	mov rcx, rax
	call letters.appendLetters
	add rsp, 8*8

	mov rbx, [defineRecordPath.recordAddr]
	add rbx, Record.builtLocation
	mov [rbx], rax


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

storage.retrieveRecordNames:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*10);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label retrieveRecordNames.heapAddress qword at rbp-8  
	label retrieveRecordNames.handleAllocatedMemory qword at rbp-16
	label retrieveRecordNames.handle qword at rbp-24 
	label retrieveRecordNames.item qword at rbp-32
	label retrieveRecordNames.recordAddr qword at rbp-40
	label retrieveRecordNames.sizeRetrieved qword at rbp-48
	label retrieveRecordNames.w32FindData qword at rbp-56
	label retrieveRecordNames.locationContentsLetters qword at rbp-64
	label retrieveRecordNames.nextFileNameLetters qword at rbp-72
	label retrieveRecordNames.list qword at rbp-80
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [retrieveRecordNames.recordAddr], rcx


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
	mov [retrieveRecordNames.list], rax
	

	sub rsp, 8*8
	mov rdx, directoryContentsLetters
	mov rbx, [retrieveRecordNames.recordAddr]
	add rbx, Record.location
	mov rcx, [rbx]
	call letters.appendLetters
	add rsp, 8*8
	mov [retrieveRecordNames.locationContentsLetters], rax


	sub rsp, 8*8
	mov rcx, 64
	call allocate.linear
	add rsp, 8*8
	mov [retrieveRecordNames.w32FindData], rax




	sub rsp, 8*8
	mov rdx, [retrieveRecordNames.w32FindData]
	mov rcx,[retrieveRecordNames.locationContentsLetters]
	call [FindFirstFile]
	add rsp, 8*8
	mov [retrieveRecordNames.handle], rax
	mov r9, 0
	sub r9, 1b
	cmp rax, r9
	jne retrieveRecordNames.noError ; INVALID_HANDLE_VALUE

	;sub rsp, 8*8
	;call [GetLastError]
	;add rsp, 8*8
	;mov rax, rax
	

	.noError:
	;jmp retrieveRecordNames.firstFile	; debug

	sub rsp, 8*8
	mov rdx, currentDirLetter
	mov r9, [retrieveRecordNames.w32FindData]
	add r9, 44
	mov rcx, r9
	call matching.lettersSameExact
	add rsp, 8*8
	cmp rax, 0
	jne retrieveRecordNames.nextFile

	sub rsp, 8*8
	mov rdx, containingDirLetters
	mov r9, [retrieveRecordNames.w32FindData]
	add r9, 44
	mov rcx, r9
	call matching.lettersSameExact
	add rsp, 8*8
	cmp rax, 0
	jne retrieveRecordNames.nextFile

	.firstFile:
	mov r9, [retrieveRecordNames.w32FindData]
	add r9, 44
	mov rcx, r9
	sub rsp, 8*8
	call letters.copyLetters
	mov rdx, rax
	add rsp, 8*8

	sub rsp, 8*8
	;mov rdx, rax
	mov rcx, [retrieveRecordNames.list]
	call list.newLastItem
	add rsp, 8*8


	;mov r14, 0
	;mov [retrieveRecordNames.item], r14	;debug

	.nextFile:

	sub rsp, 8*8
	mov rdx, [retrieveRecordNames.w32FindData]
	mov rcx, [retrieveRecordNames.handle]
	call [FindNextFile]
	add rsp, 8*8
	mov r9, rax
	cmp r9, 0
	je retrieveRecordNames.endFiles



	;mov r14, [retrieveRecordNames.item]
	;add r14, 10b
	;mov [retrieveRecordNames.item], r14
	;cmp r14, 101b
	;jge retrieveRecordNames.end

	;jmp retrieveRecordNames.newLast	; debug

	sub rsp, 8*8
	mov rdx, currentDirLetter
	mov r9, [retrieveRecordNames.w32FindData]
	add r9, 44
	mov rcx, r9
	call matching.lettersSameExact				
	add rsp, 8*8
	cmp rax, 0
	jne retrieveRecordNames.nextFile

	sub rsp, 8*8
	mov rdx, containingDirLetters
	mov r9, [retrieveRecordNames.w32FindData]
	add r9, 44
	mov rcx, r9
	call matching.lettersSameExact
	add rsp, 8*8
	cmp rax, 0
	jne retrieveRecordNames.nextFile

	.newLast:
	mov r9, [retrieveRecordNames.w32FindData]
	add r9, 44
	mov rcx, r9
	sub rsp, 8*8
	call letters.copyLetters
	mov rdx, rax
	add rsp, 8*8

	sub rsp, 8*8
	;mov rdx, rax
	mov rcx, [retrieveRecordNames.list]
	call list.newLastItem
	add rsp, 8*8



	jmp retrieveRecordNames.nextFile
	.endFiles:




	retrieveRecordNames.end:

	mov rax, [retrieveRecordNames.list]


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

; Uses extension also
storage.retrieveRecordNamesExtension:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label retrieveRecordNamesExtension.heapAddress qword at rbp-8  
	label retrieveRecordNamesExtension.handleAllocatedMemory qword at rbp-16
	label retrieveRecordNamesExtension.handle qword at rbp-24 
	label retrieveRecordNamesExtension.item qword at rbp-32
	label retrieveRecordNamesExtension.recordAddr qword at rbp-40
	label retrieveRecordNamesExtension.sizeRetrieved qword at rbp-48
	label retrieveRecordNamesExtension.w32FindData qword at rbp-56
	label retrieveRecordNamesExtension.locationContentsLetters qword at rbp-64
	label retrieveRecordNamesExtension.nextFileNameLetters qword at rbp-72
	label retrieveRecordNamesExtension.list qword at rbp-80
	label retrieveRecordNamesExtension.fileExtensionLetters qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [retrieveRecordNamesExtension.recordAddr], rcx
	mov [retrieveRecordNamesExtension.fileExtensionLetters], rdx

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
	mov [retrieveRecordNamesExtension.list], rax
	

	sub rsp, 8*8
	mov rdx, directoryContentsLetters
	mov rbx, [retrieveRecordNamesExtension.recordAddr]
	add rbx, Record.location
	mov rcx, [rbx]
	call letters.appendLetters
	add rsp, 8*8
	mov [retrieveRecordNamesExtension.locationContentsLetters], rax

	sub rsp, 8*8
	mov rdx, [retrieveRecordNamesExtension.fileExtensionLetters]
	mov rcx, [retrieveRecordNamesExtension.locationContentsLetters]
	call letters.appendLetters							; Only difference from retrieveRecordNames
	add rsp, 8*8
	mov [retrieveRecordNamesExtension.locationContentsLetters], rax


	sub rsp, 8*8
	mov rcx, 64
	call allocate.linear
	add rsp, 8*8
	mov [retrieveRecordNamesExtension.w32FindData], rax




	sub rsp, 8*8
	mov rdx, [retrieveRecordNamesExtension.w32FindData]
	mov rcx,[retrieveRecordNamesExtension.locationContentsLetters]
	call [FindFirstFile]
	add rsp, 8*8
	mov [retrieveRecordNamesExtension.handle], rax
	mov r9, 0
	sub r9, 1b
	cmp rax, r9
	jne retrieveRecordNamesExtension.noError ; INVALID_HANDLE_VALUE


	sub rsp, 8*8
	mov rcx, 64328
	;call debugNumMsg
	add rsp, 8*8

	;sub rsp, 8*8
	;call [GetLastError]
	;add rsp, 8*8
	;mov rax, rax
	

	.noError:
	;jmp retrieveRecordNamesExtension.firstFile	; debug

	sub rsp, 8*8
	mov rdx, currentDirLetter
	mov r9, [retrieveRecordNamesExtension.w32FindData]
	add r9, 44
	mov rcx, r9
	call matching.lettersSameExact
	add rsp, 8*8
	cmp rax, 0
	jne retrieveRecordNamesExtension.nextFile


	sub rsp, 8*8
	mov rcx, 43228
	;call debugNumMsg
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, containingDirLetters
	mov r9, [retrieveRecordNamesExtension.w32FindData]
	add r9, 44
	mov rcx, r9
	call matching.lettersSameExact
	add rsp, 8*8
	cmp rax, 0
	jne retrieveRecordNamesExtension.nextFile


	sub rsp, 8*8
	mov rcx, 4828
	;call debugNumMsg
	add rsp, 8*8

	.firstFile:
	mov r9, [retrieveRecordNamesExtension.w32FindData]
	add r9, 44
	mov rcx, r9
	sub rsp, 8*8
	call letters.copyLetters
	mov rdx, rax
	add rsp, 8*8

	sub rsp, 8*8
	;mov rdx, rax
	mov rcx, [retrieveRecordNamesExtension.list]
	call list.newLastItem
	add rsp, 8*8


	sub rsp, 8*8
	mov rcx, 2328
	;call debugNumMsg
	add rsp, 8*8


	;mov r14, 0
	;mov [retrieveRecordNamesExtension.item], r14	;debug

	.nextFile:

	sub rsp, 8*8
	mov rdx, [retrieveRecordNamesExtension.w32FindData]
	mov rcx, [retrieveRecordNamesExtension.handle]
	call [FindNextFile]
	add rsp, 8*8
	mov r9, rax
	cmp r9, 0
	je retrieveRecordNamesExtension.endFiles



	;mov r14, [retrieveRecordNamesExtension.item]
	;add r14, 10b
	;mov [retrieveRecordNamesExtension.item], r14
	;cmp r14, 101b
	;jge retrieveRecordNamesExtension.end

	;jmp retrieveRecordNamesExtension.newLast	; debug


	sub rsp, 8*8
	mov rcx, 88228
	;call debugNumMsg
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, currentDirLetter
	mov r9, [retrieveRecordNamesExtension.w32FindData]
	add r9, 44
	mov rcx, r9
	call matching.lettersSameExact				
	add rsp, 8*8
	cmp rax, 0
	jne retrieveRecordNamesExtension.nextFile

	sub rsp, 8*8
	mov rdx, containingDirLetters
	mov r9, [retrieveRecordNamesExtension.w32FindData]
	add r9, 44
	mov rcx, r9
	call matching.lettersSameExact
	add rsp, 8*8
	cmp rax, 0
	jne retrieveRecordNamesExtension.nextFile

	.newLast:
	mov r9, [retrieveRecordNamesExtension.w32FindData]
	add r9, 44
	mov rcx, r9
	sub rsp, 8*8
	call letters.copyLetters
	mov rdx, rax
	add rsp, 8*8

	sub rsp, 8*8
	;mov rdx, rax
	mov rcx, [retrieveRecordNamesExtension.list]
	call list.newLastItem
	add rsp, 8*8



	jmp retrieveRecordNamesExtension.nextFile
	.endFiles:


	sub rsp, 8*8
	mov rcx, 999228
	;call debugNumMsg
	add rsp, 8*8


	retrieveRecordNamesExtension.end:


	sub rsp, 8*8
	mov rcx, 78728
	;call debugNumMsg
	add rsp, 8*8

	mov rax, [retrieveRecordNamesExtension.list]


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

storage.removeRecord:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label removeRecord.heapAddress qword at rbp-8  
	label removeRecord.handleAllocatedMemory qword at rbp-16
	label removeRecord.list qword at rbp-24 
	label removeRecord.item qword at rbp-32
	label removeRecord.recordAddr qword at rbp-40
	label removeRecord.sizeRetrieved qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [removeRecord.recordAddr], rcx


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
	mov rbx, [removeRecord.recordAddr]
	add rbx, Record.builtLocation
	mov rcx, [rbx]
	call [DeleteFile]
	add rsp, 8*8


	
	mov rax, [removeRecord.recordAddr]


	removeRecord.end:


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



storage.debugNum:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label debugNum.heapAddress qword at rbp-8  
	label debugNum.handleAllocatedMemory qword at rbp-16
	label debugNum.list qword at rbp-24 
	label debugNum.item qword at rbp-32
	label debugNum.recordAddr qword at rbp-40
	label debugNum.sizeRetrieved qword at rbp-48
	label debugNum.num qword at rbp-56
	label debugNum.letters qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [debugNum.num], rcx

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
	mov rcx, [debugNum.num]
	call letters.numAsLetters
	add rsp, 8*8
	mov [debugNum.letters], rax


	sub rsp, 8*8
	call new
	add rsp, 8*8
	mov [debugNum.recordAddr], rax

	mov rbx, [debugNum.recordAddr]
	add rbx, Record.builtLocation
	mov rdx, debugRecName
	mov [rbx], rdx
	
	sub rsp, 8*8
	mov rdx, [debugNum.letters]
	mov rcx, [debugNum.recordAddr]
	call storeLetters
	add rsp, 8*8


	
	mov rax, [debugNum.recordAddr]


	debugNum.end:


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


storage.debugLetters:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label debugLetters.heapAddress qword at rbp-8  
	label debugLetters.handleAllocatedMemory qword at rbp-16
	label debugLetters.list qword at rbp-24 
	label debugLetters.item qword at rbp-32
	label debugLetters.recordAddr qword at rbp-40
	label debugLetters.sizeRetrieved qword at rbp-48
	label debugLetters.num qword at rbp-56
	label debugLetters.letters qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [debugLetters.letters], rcx

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
	mov [debugLetters.recordAddr], rax

	mov rbx, [debugLetters.recordAddr]
	add rbx, Record.builtLocation
	mov rdx, debugRecName
	mov [rbx], rdx
	
	sub rsp, 8*8
	mov rdx, [debugLetters.letters]
	mov rcx, [debugLetters.recordAddr]
	call storeLetters
	add rsp, 8*8


	
	mov rax, [debugLetters.recordAddr]


	debugLetters.end:


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

; Includes newline
storage.debugNumMsg:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label debugNumMsg.heapAddress qword at rbp-8  
	label debugNumMsg.handleAllocatedMemory qword at rbp-16
	label debugNumMsg.list qword at rbp-24 
	label debugNumMsg.item qword at rbp-32
	label debugNumMsg.recordAddr qword at rbp-40
	label debugNumMsg.sizeRetrieved qword at rbp-48
	label debugNumMsg.num qword at rbp-56
	label debugNumMsg.letters qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [debugNumMsg.num], rcx

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
	mov rcx, [debugNumMsg.num]
	call letters.numAsLetters
	add rsp, 8*8
	mov [debugNumMsg.letters], rax

	sub rsp, 8*8
	mov rdx, newlineWinLetters
	mov rcx, [debugNumMsg.letters]
	call letters.appendLetters
	add rsp, 8*8
	mov rdx, rax
	mov [debugNumMsg.letters], rdx


	sub rsp, 8*8
	call new
	add rsp, 8*8
	mov [debugNumMsg.recordAddr], rax

	mov rbx, [debugNumMsg.recordAddr]
	add rbx, Record.builtLocation
	mov rdx, debugRecName
	mov [rbx], rdx
	
	sub rsp, 8*8
	mov rdx, [debugNumMsg.letters]
	mov rcx, [debugNumMsg.recordAddr]
	call storeLetters
	add rsp, 8*8


	
	mov rax, [debugNumMsg.recordAddr]


	debugNumMsg.end:


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

; Includes newline
storage.debugLettersMsg:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label debugLettersMsg.heapAddress qword at rbp-8  
	label debugLettersMsg.handleAllocatedMemory qword at rbp-16
	label debugLettersMsg.list qword at rbp-24 
	label debugLettersMsg.item qword at rbp-32
	label debugLettersMsg.recordAddr qword at rbp-40
	label debugLettersMsg.sizeRetrieved qword at rbp-48
	label debugLettersMsg.num qword at rbp-56
	label debugLettersMsg.letters qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [debugLettersMsg.letters], rcx

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
	mov rcx, [debugLettersMsg.letters]
	call letters.appendLetters
	add rsp, 8*8
	mov rdx, rax
	mov [debugLettersMsg.letters], rdx
	

	sub rsp, 8*8
	call new
	add rsp, 8*8
	mov [debugLettersMsg.recordAddr], rax

	mov rbx, [debugLettersMsg.recordAddr]
	add rbx, Record.builtLocation
	mov rdx, debugRecName
	mov [rbx], rdx
	
	sub rsp, 8*8
	mov rdx, [debugLettersMsg.letters]
	mov rcx, [debugLettersMsg.recordAddr]
	call storeLetters
	add rsp, 8*8


	
	mov rax, [debugLettersMsg.recordAddr]


	debugLettersMsg.end:


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
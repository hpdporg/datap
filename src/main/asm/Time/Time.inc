


section '.data' data readable writeable align 16



	struc Time
		label .
		.year dq 0	
		.month dq 0	
		.day dq 0	
		.hour dq 0
		.minute dq 0
		.second dq 0
		.ms dq 0
		.timestamp dq 0
	end struc



	; Used with address offsets
	virtual at 0
		Time Time
	end virtual

	; ---- Structures
	;time Time




	

section '.text' code readable writeable executable align 16


time:
namespace time
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
	add rcx, Time.timestamp
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [heapAddress]
	call [ HeapAlloc] 
	mov [handleAllocatedMemory], rax
	add rsp, 8*4



	mov rbx, [handleAllocatedMemory]
	add rbx, Time.year
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Time.month
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Time.day
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Time.hour
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Time.minute
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Time.second
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Time.ms
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Time.timestamp
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

getNow:
namespace getNow
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*3);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label timeAlloc	qword at rbp-24
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
	

;	typedef struct _SYSTEMTIME {		WORD = 16 bits
;  WORD wYear;
;  WORD wMonth;
;  WORD wDayOfWeek;
;  WORD wDay;
;  WORD wHour;
;  WORD wMinute;
;  WORD wSecond;
;  WORD wMilliseconds;
;} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;


	sub rsp, 8*4
	mov r8, 10000b			; 16 = 8*2	
	mov rdx, 000001000b
	mov rcx, [heapAddress]
	call [ HeapAlloc] 
	mov [handleAllocatedMemory], rax
	add rsp, 8*4


	sub rsp, 8*8
	call new
	add rsp, 8*8
	mov [timeAlloc], rax

	sub rsp, 8*8
	mov rcx, [handleAllocatedMemory]
	call [GetSystemTime]
	add rsp, 8*8



	mov rbx, [handleAllocatedMemory]
	add rbx, 0
	mov rax, [timeAlloc]
	add rax, Time.year
	mov rdx, 0
	mov dx, word [rbx]
	mov [rax], rdx




	;lea rax, [list]
	;lea rcx, [list.indexedItemIndex]

	;sub rcx, rax
	;add rcx, 1000b

	;cld

	;lea rsi, [list]
	;mov rdi, [storage.handleAllocatedMemory]

	;rep movsb

	completed:

	mov rax, [timeAlloc]


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
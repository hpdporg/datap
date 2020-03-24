
section '.data' data readable writeable


	struc Flow
		label .
		.lists dq 0
		.width dq 0				; Max width: List count
		.i dq 0					; List index
		.j dq 0					; List item index
		.length dq 0				; Max length: Greatest List item count.
		.paddingValue dq 0			; Defaults 0
	end struc	
	


	; Used with address offsets
	virtual at 0
		Flow Flow
	end virtual


	; ---- Structures
	;list List


	;newSVGMsg db 'New SVG',0
	
		
section '.text' code readable writeable executable ;align 16



flow:
namespace flow
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
	add rcx, Flow.paddingValue
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [heapAddress]
	call [ HeapAlloc] 
	mov [handleAllocatedMemory], rax
	add rsp, 8*4


	mov rbx, [handleAllocatedMemory]
	add rbx, Flow.lists
	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Flow.width
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Flow.i
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Flow.j
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Flow.length
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Flow.paddingValue
	mov rax, 0
	mov [rbx], rax
	mov rax, 0
	mov [rbx], rax


	;lea rax, [list]
	;lea rcx, [list.indexedItemIndex]

	;sub rcx, rax
	;add rcx, 1000b

	;cld

	;lea rsi, [list]
	;mov rdi, [list.handleAllocatedMemory]

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




; Called by flow.increaseWidth
; Increments Flow.width. Increases Flow.length if applicable
newLastList:
namespace newLastList
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label newList qword at rbp-24 
	label flow qword at rbp-32
	label prevItem qword at rbp-40
	label priorIndex qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [flow], rcx
	mov [newList], rdx


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
	mov rdx, [newList]
	mov rbx, [flow]
	add rbx, Flow.lists
	mov rcx, [rbx]
	call list.newLastItem
	add rsp, 8*8


;	struc Flow
;		label .
;		.lists dq 0
;		.width dq 0				; Max width: List count
;		.i dq 0					; List index
;		.j dq 0					; List item index
;		.length dq 0				; Max length: Greatest List item count.
;		.paddingValue dq 0			; Defaults 0
;	end struc	


	mov rbx, [flow]
	add rbx, Flow.width
	mov rcx, [rbx]
	add rcx, 1b
	mov [rbx], rcx					; Increment

	mov rdx, [newList]
	add rdx, List.itemsCount
	mov rcx, [rdx]
	mov rbx, [flow]
	add rbx, Flow.length
	mov r8, [rbx]

	cmp rcx, r8
	jle flowLengthNotIncreased
	
	mov [rbx], rcx					; Length increased when greater


	flowLengthNotIncreased:

	completed:

	mov rax, 0



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


; Builds new List, passes to Flow
; Calls flow.newLastList
; Takes Flow reference, length value as parameters
increaseWidth:
namespace increaseWidth
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label flowList qword at rbp-24 
	label flow qword at rbp-32
	label index qword at rbp-40
	label width qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [flow], rcx
	mov [width], rdx


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
	mov [index], rcx			; Begin as 0


	nextList:
	mov rcx, [index]
	mov rdx, [width]
	cmp rcx, rdx
	jnl increased


	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	sub rsp, 8*8
	mov rdx, rax
	mov rcx, [flow]
	call newLastList
	add rsp, 8*8


	mov rcx, [index]
	add rcx, 1b
	mov [index], rcx

	jmp nextList
	increased:





	completed:

	mov rax, 0



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

; Pass vals from List into Flow across
; New Flow row
; Missing vals at end will be padded with padding value
newLastIVals:
namespace newLastIVals
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label flowList qword at rbp-24 
	label flow qword at rbp-32
	label index qword at rbp-40
	label length qword at rbp-48
	label item qword at rbp-56
	label paddingValue qword at rbp-64
	label lists qword at rbp-72
	label nextFlowList qword at rbp-80
	label width qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [flow], rcx
	mov [flowList], rdx


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
	mov [index], rcx			; Begin as 0

	mov rbx, [flow]
	add rbx, Flow.width
	mov r11, [rbx]
	mov [width], r11

	mov rbx, [flow]
	add rbx, Flow.paddingValue
	mov r12, [rbx]
	mov [paddingValue], r12
	
	sub rsp, 8*8
	mov rcx, [flowList]
	call list.resetIndex
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [flow]
	add rbx, Flow.lists
	mov rcx, [rbx]
	mov [lists], rcx
	call list.resetIndex
	add rsp, 8*8

	nextVal:
	mov rcx, [index]
	mov rdx, [width]
	cmp rcx, rdx
	jnl endVals


	nextListVal:
	mov rcx, [index]
	mov rbx, [flowList]
	add rbx, List.itemsCount
	mov rdx, [rbx]
	cmp rcx, rdx
	jnl endListVals

	sub rsp, 8*8
	mov rcx, [flowList]
	call list.getNextItem
	add rsp, 8*8
	mov [item], rax

	jmp newItem

	endListVals:

	mov r12, [paddingValue]		; List not full width of flow, use padding value instead
	mov [item], r12


	newItem:

	sub rsp, 8*8
	mov rcx, [lists]
	call list.getNextItem
	add rsp, 8*8
	mov [nextFlowList], rax

	sub rsp, 8*8
	mov rdx, [item]
	mov rcx, [nextFlowList]
	call list.newLastItem
	add rsp, 8*8

	mov rbx, [nextFlowList]
	add rbx, List.itemsCount
	mov r13, [rbx]
	mov rbx, [flow]
	add rbx, Flow.length
	mov r14, [rbx]
	cmp r13, r14
	jle flowLengthNotIncreased		; Should only not increase when next Flow List is shorter than another. May not happen due to padding
	mov [rbx], r13

	flowLengthNotIncreased:

	mov rcx, [index]
	add rcx, 1b
	mov [index], rcx

	jmp nextVal
	endVals:





	completed:

	mov rax, 0



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

; Pass vals from List into Flow across. List index param will be used as numeric ascending value.
; New Flow row, row in List in ascending order
; Missing vals at end will be padded with padding value
newAscendingIVals:
namespace newAscendingIVals
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*13);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label flowList qword at rbp-24 
	label flow qword at rbp-32
	label index qword at rbp-40
	label length qword at rbp-48
	label item qword at rbp-56
	label paddingValue qword at rbp-64
	label lists qword at rbp-72
	label nextFlowList qword at rbp-80
	label ascendingListIndex qword at rbp-88
	label width qword at rbp-96
	label jIndex qword at rbp-104
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [flow], rcx
	mov [flowList], rdx
	mov [ascendingListIndex], r8


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
	mov [index], rcx			; Begin as 0

	mov rbx, [flow]
	add rbx, Flow.width
	mov r11, [rbx]
	mov [width], r11

	mov rbx, [flow]
	add rbx, Flow.paddingValue
	mov r12, [rbx]
	mov [paddingValue], r12
	

	mov rbx, [flow]
	add rbx, Flow.lists
	mov rcx, [rbx]
	mov [lists], rcx

	mov rbx, [flowList]
	add rbx, List.index
	mov rdx, [ascendingListIndex]
	mov [rbx], rdx
	mov r11, [lists]
	add r11, List.index
	mov [r11], rdx

	sub rsp, 8*8
	mov rcx, [lists]
	call list.getNextItem
	add rsp, 8*8
	mov [nextFlowList], rax

	sub rsp, 8*8
	mov rcx, [flowList]
	call list.getNextItem
	add rsp, 8*8
	mov [item], rax


	sub rsp, 8*8
	mov rdx, [item]
	mov rcx, [nextFlowList]
	call list.newAscendingItem
	add rsp, 8*8
	mov [jIndex], rax			; Cache, use this later




	sub rsp, 8*8
	mov rcx, [flowList]
	call list.resetIndex
	add rsp, 8*8



	sub rsp, 8*8
	mov rcx, [lists]
	call list.resetIndex
	add rsp, 8*8



	nextVal:
	mov rcx, [index]
	mov rdx, [width]
	cmp rcx, rdx
	jnl endVals





	nextListVal:
	mov rcx, [index]
	mov rbx, [flowList]
	add rbx, List.itemsCount
	mov rdx, [rbx]
	cmp rcx, rdx
	jnl endListVals




	sub rsp, 8*8
	mov rcx, [flowList]
	call list.getNextItem
	add rsp, 8*8
	mov [item], rax

	jmp newItem

	endListVals:

	mov r12, [paddingValue]		; List not full width of flow, use padding value instead
	mov [item], r12


	newItem:



	sub rsp, 8*8
	mov rcx, [lists]
	call list.getNextItem
	add rsp, 8*8
	mov [nextFlowList], rax

	mov r14, [index]
	mov r15, [ascendingListIndex]
	cmp r14, r15
	je increaseLengthOnly

	mov r9, [nextFlowList]
	add r9, List.index
	mov r8, [jIndex]
	mov [r9], r8


	sub rsp, 8*8
	mov rdx, [item]
	mov rcx, [nextFlowList]
	call list.newNextItem
	add rsp, 8*8

	increaseLengthOnly:



	mov rbx, [nextFlowList]
	add rbx, List.itemsCount
	mov r13, [rbx]
	mov rbx, [flow]
	add rbx, Flow.length
	mov r14, [rbx]
	cmp r13, r14
	jle flowLengthNotIncreased		; Should only not increase when next Flow List is shorter than another. May not happen due to padding
	mov [rbx], r13

	flowLengthNotIncreased:

	mov rcx, [index]
	add rcx, 1b
	mov [index], rcx

	jmp nextVal
	endVals:





	completed:




	mov rax, 0



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


; Finds item match, passes match index to Flow
; Also returns 0 when no match exists, 1 when exists
indexAsItemMatch:
namespace indexAsItemMatch
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*13);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label flowList qword at rbp-24 
	label flow qword at rbp-32
	label index qword at rbp-40
	label length qword at rbp-48
	label item qword at rbp-56
	label paddingValue qword at rbp-64
	label lists qword at rbp-72
	label nextFlowList qword at rbp-80
	label iListIndex qword at rbp-88
	label width qword at rbp-96
	label jIndex qword at rbp-104
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [flow], rcx
	mov [item], rdx
	mov [iListIndex], r8


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




	

	mov rbx, [flow]
	add rbx, Flow.lists
	mov rcx, [rbx]
	mov [lists], rcx


	mov r11, [lists]
	add r11, List.index
	mov rdx, [iListIndex]
	mov [r11], rdx

	sub rsp, 8*8
	mov rcx, [lists]
	call list.getNextItem
	add rsp, 8*8
	mov [nextFlowList], rax




	sub rsp, 8*8
	mov rcx, [nextFlowList]
	call list.resetIndex
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, [item]
	mov rcx, [nextFlowList]
	call list.getNextItemMatchIndex
	add rsp, 8*8
	mov [index], rax


	mov rbx, [flow]
	add rbx, Flow.j
	mov rax, [index]
	mov [rbx], rax



	mov rdx, 0						; Blank?
	mov rbx, [nextFlowList]
	add rbx, List.itemsCount
	mov r8, [rbx]
	cmp rdx, r8
	je endMatching

	mov rdx, [index]
	mov rbx, [nextFlowList]
	add rbx, List.itemsCount
	mov r8, [rbx]
	cmp rdx, r8
	je endMatching
	
	mov rax, 1

	jmp completed				; 0 when no match exists
	endMatching:

	mov rax, 0


	completed:

	mov rax, rax


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


; Get each i val at Flow's j index
; Should consider caching the j List in the Flow so heapfree is not necessary
getNextJVals:
namespace getNextJVals
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label flowList qword at rbp-24 
	label flow qword at rbp-32
	label index qword at rbp-40
	label length qword at rbp-48
	label item qword at rbp-56
	label paddingValue qword at rbp-64
	label lists qword at rbp-72
	label nextFlowList qword at rbp-80
	label iListIndex qword at rbp-88
	label width qword at rbp-96
	label jIndex qword at rbp-104
	label jVals qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [flow], rcx


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
	call list.new
	add rsp, 8*8
	mov [jVals], rax

	mov rbx, [flow]
	add rbx, Flow.lists
	mov r10, [rbx]
	mov [lists], r10

	mov rbx, [lists]
	add rbx, List.index
	mov r8, [flow]
	add r8, Flow.i
	mov rcx, [r8]
	mov [rbx], rcx







	mov rbx, [flow]
	mov r8, rbx
	add rbx, Flow.j
	mov rcx, [rbx]
	add r8, Flow.length
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endFlow



	nextVal:
	mov rbx, [flow]
	mov r8, rbx
	add rbx, Flow.i
	mov rcx, [rbx]
	add r8, Flow.width
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endVals


	sub rsp, 8*8
	mov rcx, [lists]
	call list.getNextItem
	add rsp, 8*8
	mov [nextFlowList], rax

	mov rbx, [nextFlowList]
	add rbx, List.index
	mov r11, [flow]
	add r11, Flow.j
	mov rcx, [r11]
	mov [rbx], rcx




	sub rsp, 8*8
	mov rcx, [nextFlowList]
	call list.getNextItem
	add rsp, 8*8
	mov [item], rax


	sub rsp, 8*8
	mov rdx, [item]
	mov rcx, [jVals]
	call list.newLastItem
	add rsp, 8*8


	mov rbx, [flow]
	add rbx, Flow.i
	mov rcx, [rbx]
	add rcx, 1b					; Increment
	mov [rbx], rcx

	jmp nextVal
	endVals:


	mov rbx, [flow]
	add rbx, Flow.j
	mov rcx, [rbx]
	add rcx, 1b					; Increment
	mov [rbx], rcx

	endFlow:


	completed:



	mov rax, [jVals]



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


; Flow i index as 0
; Takes Flow as param
resetI:
namespace resetI
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label flowList qword at rbp-24 
	label flow qword at rbp-32
	label index qword at rbp-40
	label length qword at rbp-48
	label item qword at rbp-56
	label paddingValue qword at rbp-64
	label lists qword at rbp-72
	label nextFlowList qword at rbp-80
	label iListIndex qword at rbp-88
	label width qword at rbp-96
	label jIndex qword at rbp-104
	label jVals qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [flow], rcx


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



	mov rbx, [flow]
	add rbx, Flow.i
	mov rcx, 0
	mov [rbx], rcx


	completed:

	mov rax, 0



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


; Flow i and j indices as 0
; Takes Flow as param
resetIJ:
namespace resetIJ
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label flowList qword at rbp-24 
	label flow qword at rbp-32
	label index qword at rbp-40
	label length qword at rbp-48
	label item qword at rbp-56
	label paddingValue qword at rbp-64
	label lists qword at rbp-72
	label nextFlowList qword at rbp-80
	label iListIndex qword at rbp-88
	label width qword at rbp-96
	label jIndex qword at rbp-104
	label jVals qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [flow], rcx


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



	mov rbx, [flow]
	mov rdx, rbx
	add rbx, Flow.i
	add rdx, Flow.j
	mov rcx, 0
	mov [rbx], rcx
	mov [rdx], rcx


	completed:

	mov rax, 0



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


; Gets val at i,j and increments i,j with wrapping
getNextItem:
namespace getNextItem
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label flowList qword at rbp-24 
	label flow qword at rbp-32
	label iIndex qword at rbp-40
	label length qword at rbp-48
	label item qword at rbp-56
	label paddingValue qword at rbp-64
	label lists qword at rbp-72
	label nextFlowList qword at rbp-80
	label iListIndex qword at rbp-88
	label width qword at rbp-96
	label jIndex qword at rbp-104
	label itemCompleted qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [flow], rcx


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
	mov [item], rcx			; Begin as 0
	mov [itemCompleted], rcx			; Begin as 0


	mov rbx, [flow]
	mov r9, rbx
	add rbx, Flow.i
	mov rcx, [rbx]
	mov [iIndex], rcx
	add r9, Flow.j
	mov rdx, [r9]
	mov [jIndex], rdx
	mov rbx, [flow]
	add rbx, Flow.lists
	mov r8, [rbx]
	mov [lists], r8
	mov r10, [flow]
	add r10, Flow.width
	mov r11, [r10]
	mov [width], r11
	mov rbx, [flow]
	add rbx, Flow.length
	mov rcx, [rbx]
	mov [length], rcx
	mov r10, [flow]
	add r10, Flow.paddingValue
	mov r11, [r10]
	mov [paddingValue], r11


	nextI:
	mov r11, [iIndex]
	mov r12, [width]
	cmp r11, r12
	jnl wrapI
	

	mov rbx, [lists]
	mov r10, rbx
	add r10, List.itemsCount
	mov rdx, [r10]
	add rbx, List.index
	mov r11, [iIndex]
	cmp r11, rdx
	jnl getPaddingVal
	mov [rbx], r11


	nextJ:
	mov rbx, [lists]
	add rbx, List.index
	mov r8, [iIndex]
	mov [rbx], r8
	
	sub rsp, 8*8
	mov rcx, [lists]
	call list.getNextItem
	add rsp, 8*8
	mov [nextFlowList], rax

	mov rbx, [nextFlowList]
	add rbx, List.itemsCount
	mov r15, [rbx]
	mov r13, [length]
	cmp r15, r13
	jnle getPaddingVal

	mov rbx, [nextFlowList]
	add rbx, List.index
	mov r11, [jIndex]
	mov [rbx], r11

	sub rsp, 8*8
	mov rcx, [nextFlowList]
	call list.getNextItem
	add rsp, 8*8
	mov [item], rax

	mov rdx, 1b
	mov [itemCompleted], rdx

	jmp incrementIJ

	getPaddingVal:
	mov r9, [paddingValue]
	mov [item], r9

	mov rdx, 1b
	mov [itemCompleted], rdx

	incrementIJ:

	mov r11, [iIndex]
	add r11, 1b
	mov [iIndex], r11
	mov rbx, [flow]
	add rbx, Flow.i
	mov [rbx], r11

	mov r11, [iIndex]
	mov r12, [width]
	cmp r11, r12
	jl completed					; Wrap I,J only when i greater than width

	wrapI:
	mov rcx, 0
	mov [iIndex], rcx			; Wrap I
	mov r10, [jIndex]
	add r10, 1b
	mov [jIndex], r10			; Wrap J
	mov rbx, [flow]
	mov r9, rbx
	add rbx, Flow.i
	add r9, Flow.j
	mov [rbx], rcx
	mov [r9], r10

	mov rdx, [itemCompleted]
	cmp rdx, 1b
	jne nextI


	completed:



	mov rax, [item]



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
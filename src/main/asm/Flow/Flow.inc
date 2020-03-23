
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
flow.new:
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
	add rcx, Flow.paddingValue
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [new.heapAddress]
	call [ HeapAlloc] 
	mov [new.handleAllocatedMemory], rax
	add rsp, 8*4


	mov rbx, [new.handleAllocatedMemory]
	add rbx, Flow.lists
	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Flow.width
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Flow.i
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Flow.j
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Flow.length
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Flow.paddingValue
	mov rax, 0
	mov [rbx], rax
	mov rax, 0
	mov [rbx], rax


	;lea rax, [new.list]
	;lea rcx, [new.list.indexedItemIndex]

	;sub rcx, rax
	;add rcx, 1000b

	;cld

	;lea rsi, [new.list]
	;mov rdi, [list.new.handleAllocatedMemory]

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





; Called by flow.increaseWidth
; Increments Flow.width. Increases Flow.length if applicable
flow.newLastList:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label newLastList.heapAddress qword at rbp-8  
	label newLastList.handleAllocatedMemory qword at rbp-16
	label newLastList.list qword at rbp-24 
	label newLastList.flow qword at rbp-32
	label newLastList.prevItem qword at rbp-40
	label newLastList.priorIndex qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [newLastList.flow], rcx
	mov [newLastList.list], rdx


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
	mov rdx, [newLastList.list]
	mov rbx, [newLastList.flow]
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


	mov rbx, [newLastList.flow]
	add rbx, Flow.width
	mov rcx, [rbx]
	add rcx, 1b
	mov [rbx], rcx					; Increment

	mov rdx, [newLastList.list]
	add rdx, List.itemsCount
	mov rcx, [rdx]
	mov rbx, [newLastList.flow]
	add rbx, Flow.length
	mov r8, [rbx]

	cmp rcx, r8
	jle newLastList.flowLengthNotIncreased
	
	mov [rbx], rcx					; Length increased when greater


	.flowLengthNotIncreased:

	.end:

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


; Builds new List, passes to Flow
; Calls flow.newLastList
; Takes Flow reference, length value as parameters
flow.increaseWidth:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label increaseWidth.heapAddress qword at rbp-8  
	label increaseWidth.handleAllocatedMemory qword at rbp-16
	label increaseWidth.list qword at rbp-24 
	label increaseWidth.flow qword at rbp-32
	label increaseWidth.index qword at rbp-40
	label increaseWidth.width qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [increaseWidth.flow], rcx
	mov [increaseWidth.width], rdx


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
	mov [increaseWidth.index], rcx			; Begin as 0


	.nextList:
	mov rcx, [increaseWidth.index]
	mov rdx, [increaseWidth.width]
	cmp rcx, rdx
	jnl increaseWidth.increased


	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	sub rsp, 8*8
	mov rdx, rax
	mov rcx, [increaseWidth.flow]
	call flow.newLastList
	add rsp, 8*8


	mov rcx, [increaseWidth.index]
	add rcx, 1b
	mov [increaseWidth.index], rcx

	jmp increaseWidth.nextList
	.increased:





	.end:

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

; Pass vals from List into Flow across
; New Flow row
; Missing vals at end will be padded with padding value
flow.newLastIVals:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label newLastIVals.heapAddress qword at rbp-8  
	label newLastIVals.handleAllocatedMemory qword at rbp-16
	label newLastIVals.list qword at rbp-24 
	label newLastIVals.flow qword at rbp-32
	label newLastIVals.index qword at rbp-40
	label newLastIVals.length qword at rbp-48
	label newLastIVals.item qword at rbp-56
	label newLastIVals.paddingValue qword at rbp-64
	label newLastIVals.lists qword at rbp-72
	label newLastIVals.nextFlowList qword at rbp-80
	label newLastIVals.width qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [newLastIVals.flow], rcx
	mov [newLastIVals.list], rdx


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
	mov [newLastIVals.index], rcx			; Begin as 0

	mov rbx, [newLastIVals.flow]
	add rbx, Flow.width
	mov r11, [rbx]
	mov [newLastIVals.width], r11

	mov rbx, [newLastIVals.flow]
	add rbx, Flow.paddingValue
	mov r12, [rbx]
	mov [newLastIVals.paddingValue], r12
	
	sub rsp, 8*8
	mov rcx, [newLastIVals.list]
	call list.resetIndex
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [newLastIVals.flow]
	add rbx, Flow.lists
	mov rcx, [rbx]
	mov [newLastIVals.lists], rcx
	call list.resetIndex
	add rsp, 8*8

	.nextVal:
	mov rcx, [newLastIVals.index]
	mov rdx, [newLastIVals.width]
	cmp rcx, rdx
	jnl newLastIVals.endVals


	.nextListVal:
	mov rcx, [newLastIVals.index]
	mov rbx, [newLastIVals.list]
	add rbx, List.itemsCount
	mov rdx, [rbx]
	cmp rcx, rdx
	jnl newLastIVals.endListVals

	sub rsp, 8*8
	mov rcx, [newLastIVals.list]
	call list.getNextItem
	add rsp, 8*8
	mov [newLastIVals.item], rax

	jmp newLastIVals.newItem

	.endListVals:

	mov r12, [newLastIVals.paddingValue]		; List not full width of flow, use padding value instead
	mov [newLastIVals.item], r12


	.newItem:

	sub rsp, 8*8
	mov rcx, [newLastIVals.lists]
	call list.getNextItem
	add rsp, 8*8
	mov [newLastIVals.nextFlowList], rax

	sub rsp, 8*8
	mov rdx, [newLastIVals.item]
	mov rcx, [newLastIVals.nextFlowList]
	call list.newLastItem
	add rsp, 8*8

	mov rbx, [newLastIVals.nextFlowList]
	add rbx, List.itemsCount
	mov r13, [rbx]
	mov rbx, [newLastIVals.flow]
	add rbx, Flow.length
	mov r14, [rbx]
	cmp r13, r14
	jle newLastIVals.flowLengthNotIncreased		; Should only not increase when next Flow List is shorter than another. May not happen due to padding
	mov [rbx], r13

	.flowLengthNotIncreased:

	mov rcx, [newLastIVals.index]
	add rcx, 1b
	mov [newLastIVals.index], rcx

	jmp newLastIVals.nextVal
	.endVals:





	.end:

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

; Pass vals from List into Flow across. List index param will be used as numeric ascending value.
; New Flow row, row in List in ascending order
; Missing vals at end will be padded with padding value
flow.newAscendingIVals:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*13);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label newAscendingIVals.heapAddress qword at rbp-8  
	label newAscendingIVals.handleAllocatedMemory qword at rbp-16
	label newAscendingIVals.list qword at rbp-24 
	label newAscendingIVals.flow qword at rbp-32
	label newAscendingIVals.index qword at rbp-40
	label newAscendingIVals.length qword at rbp-48
	label newAscendingIVals.item qword at rbp-56
	label newAscendingIVals.paddingValue qword at rbp-64
	label newAscendingIVals.lists qword at rbp-72
	label newAscendingIVals.nextFlowList qword at rbp-80
	label newAscendingIVals.ascendingListIndex qword at rbp-88
	label newAscendingIVals.width qword at rbp-96
	label newAscendingIVals.jIndex qword at rbp-104
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [newAscendingIVals.flow], rcx
	mov [newAscendingIVals.list], rdx
	mov [newAscendingIVals.ascendingListIndex], r8


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
	mov [newAscendingIVals.index], rcx			; Begin as 0

	mov rbx, [newAscendingIVals.flow]
	add rbx, Flow.width
	mov r11, [rbx]
	mov [newAscendingIVals.width], r11

	mov rbx, [newAscendingIVals.flow]
	add rbx, Flow.paddingValue
	mov r12, [rbx]
	mov [newAscendingIVals.paddingValue], r12
	

	mov rbx, [newAscendingIVals.flow]
	add rbx, Flow.lists
	mov rcx, [rbx]
	mov [newAscendingIVals.lists], rcx

	mov rbx, [newAscendingIVals.list]
	add rbx, List.index
	mov rdx, [newAscendingIVals.ascendingListIndex]
	mov [rbx], rdx
	mov r11, [newAscendingIVals.lists]
	add r11, List.index
	mov [r11], rdx

	sub rsp, 8*8
	mov rcx, [newAscendingIVals.lists]
	call list.getNextItem
	add rsp, 8*8
	mov [newAscendingIVals.nextFlowList], rax

	sub rsp, 8*8
	mov rcx, [newAscendingIVals.list]
	call list.getNextItem
	add rsp, 8*8
	mov [newAscendingIVals.item], rax


	sub rsp, 8*8
	mov rdx, [newAscendingIVals.item]
	mov rcx, [newAscendingIVals.nextFlowList]
	call list.newAscendingItem
	add rsp, 8*8
	mov [newAscendingIVals.jIndex], rax			; Cache, use this later




	sub rsp, 8*8
	mov rcx, [newAscendingIVals.list]
	call list.resetIndex
	add rsp, 8*8



	sub rsp, 8*8
	mov rcx, [newAscendingIVals.lists]
	call list.resetIndex
	add rsp, 8*8



	.nextVal:
	mov rcx, [newAscendingIVals.index]
	mov rdx, [newAscendingIVals.width]
	cmp rcx, rdx
	jnl newAscendingIVals.endVals





	.nextListVal:
	mov rcx, [newAscendingIVals.index]
	mov rbx, [newAscendingIVals.list]
	add rbx, List.itemsCount
	mov rdx, [rbx]
	cmp rcx, rdx
	jnl newAscendingIVals.endListVals




	sub rsp, 8*8
	mov rcx, [newAscendingIVals.list]
	call list.getNextItem
	add rsp, 8*8
	mov [newAscendingIVals.item], rax

	jmp newAscendingIVals.newItem

	.endListVals:

	mov r12, [newAscendingIVals.paddingValue]		; List not full width of flow, use padding value instead
	mov [newAscendingIVals.item], r12


	.newItem:



	sub rsp, 8*8
	mov rcx, [newAscendingIVals.lists]
	call list.getNextItem
	add rsp, 8*8
	mov [newAscendingIVals.nextFlowList], rax

	mov r14, [newAscendingIVals.index]
	mov r15, [newAscendingIVals.ascendingListIndex]
	cmp r14, r15
	je newAscendingIVals.increaseLengthOnly

	mov r9, [newAscendingIVals.nextFlowList]
	add r9, List.index
	mov r8, [newAscendingIVals.jIndex]
	mov [r9], r8


	sub rsp, 8*8
	mov rdx, [newAscendingIVals.item]
	mov rcx, [newAscendingIVals.nextFlowList]
	call list.newNextItem
	add rsp, 8*8

	.increaseLengthOnly:



	mov rbx, [newAscendingIVals.nextFlowList]
	add rbx, List.itemsCount
	mov r13, [rbx]
	mov rbx, [newAscendingIVals.flow]
	add rbx, Flow.length
	mov r14, [rbx]
	cmp r13, r14
	jle newAscendingIVals.flowLengthNotIncreased		; Should only not increase when next Flow List is shorter than another. May not happen due to padding
	mov [rbx], r13

	.flowLengthNotIncreased:

	mov rcx, [newAscendingIVals.index]
	add rcx, 1b
	mov [newAscendingIVals.index], rcx

	jmp newAscendingIVals.nextVal
	.endVals:





	.end:




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


; Finds item match, passes match index to Flow
; Also returns 0 when no match exists, 1 when exists
flow.indexAsItemMatch:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*13);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label indexAsItemMatch.heapAddress qword at rbp-8  
	label indexAsItemMatch.handleAllocatedMemory qword at rbp-16
	label indexAsItemMatch.list qword at rbp-24 
	label indexAsItemMatch.flow qword at rbp-32
	label indexAsItemMatch.index qword at rbp-40
	label indexAsItemMatch.length qword at rbp-48
	label indexAsItemMatch.item qword at rbp-56
	label indexAsItemMatch.paddingValue qword at rbp-64
	label indexAsItemMatch.lists qword at rbp-72
	label indexAsItemMatch.nextFlowList qword at rbp-80
	label indexAsItemMatch.iListIndex qword at rbp-88
	label indexAsItemMatch.width qword at rbp-96
	label indexAsItemMatch.jIndex qword at rbp-104
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [indexAsItemMatch.flow], rcx
	mov [indexAsItemMatch.item], rdx
	mov [indexAsItemMatch.iListIndex], r8


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




	

	mov rbx, [indexAsItemMatch.flow]
	add rbx, Flow.lists
	mov rcx, [rbx]
	mov [indexAsItemMatch.lists], rcx


	mov r11, [indexAsItemMatch.lists]
	add r11, List.index
	mov rdx, [indexAsItemMatch.iListIndex]
	mov [r11], rdx

	sub rsp, 8*8
	mov rcx, [indexAsItemMatch.lists]
	call list.getNextItem
	add rsp, 8*8
	mov [indexAsItemMatch.nextFlowList], rax




	sub rsp, 8*8
	mov rcx, [indexAsItemMatch.nextFlowList]
	call list.resetIndex
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, [indexAsItemMatch.item]
	mov rcx, [indexAsItemMatch.nextFlowList]
	call list.getNextItemMatchIndex
	add rsp, 8*8
	mov [indexAsItemMatch.index], rax


	mov rbx, [indexAsItemMatch.flow]
	add rbx, Flow.j
	mov rax, [indexAsItemMatch.index]
	mov [rbx], rax



	mov rdx, 0						; Blank?
	mov rbx, [indexAsItemMatch.nextFlowList]
	add rbx, List.itemsCount
	mov r8, [rbx]
	cmp rdx, r8
	je indexAsItemMatch.endMatching

	mov rdx, [indexAsItemMatch.index]
	mov rbx, [indexAsItemMatch.nextFlowList]
	add rbx, List.itemsCount
	mov r8, [rbx]
	cmp rdx, r8
	je indexAsItemMatch.endMatching
	
	mov rax, 1

	jmp indexAsItemMatch.end				; 0 when no match exists
	.endMatching:

	mov rax, 0


	.end:

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


; Get each i val at Flow's j index
; Should consider caching the j List in the Flow so heapfree is not necessary
flow.getNextJVals:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getNextJVals.heapAddress qword at rbp-8  
	label getNextJVals.handleAllocatedMemory qword at rbp-16
	label getNextJVals.list qword at rbp-24 
	label getNextJVals.flow qword at rbp-32
	label getNextJVals.index qword at rbp-40
	label getNextJVals.length qword at rbp-48
	label getNextJVals.item qword at rbp-56
	label getNextJVals.paddingValue qword at rbp-64
	label getNextJVals.lists qword at rbp-72
	label getNextJVals.nextFlowList qword at rbp-80
	label getNextJVals.iListIndex qword at rbp-88
	label getNextJVals.width qword at rbp-96
	label getNextJVals.jIndex qword at rbp-104
	label getNextJVals.jVals qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getNextJVals.flow], rcx


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
	mov [getNextJVals.jVals], rax

	mov rbx, [getNextJVals.flow]
	add rbx, Flow.lists
	mov r10, [rbx]
	mov [getNextJVals.lists], r10

	mov rbx, [getNextJVals.lists]
	add rbx, List.index
	mov r8, [getNextJVals.flow]
	add r8, Flow.i
	mov rcx, [r8]
	mov [rbx], rcx







	mov rbx, [getNextJVals.flow]
	mov r8, rbx
	add rbx, Flow.j
	mov rcx, [rbx]
	add r8, Flow.length
	mov rdx, [r8]
	cmp rcx, rdx
	jnl getNextJVals.endFlow



	.nextVal:
	mov rbx, [getNextJVals.flow]
	mov r8, rbx
	add rbx, Flow.i
	mov rcx, [rbx]
	add r8, Flow.width
	mov rdx, [r8]
	cmp rcx, rdx
	jnl getNextJVals.endVals


	sub rsp, 8*8
	mov rcx, [getNextJVals.lists]
	call list.getNextItem
	add rsp, 8*8
	mov [getNextJVals.nextFlowList], rax

	mov rbx, [getNextJVals.nextFlowList]
	add rbx, List.index
	mov r11, [getNextJVals.flow]
	add r11, Flow.j
	mov rcx, [r11]
	mov [rbx], rcx




	sub rsp, 8*8
	mov rcx, [getNextJVals.nextFlowList]
	call list.getNextItem
	add rsp, 8*8
	mov [getNextJVals.item], rax


	sub rsp, 8*8
	mov rdx, [getNextJVals.item]
	mov rcx, [getNextJVals.jVals]
	call list.newLastItem
	add rsp, 8*8


	mov rbx, [getNextJVals.flow]
	add rbx, Flow.i
	mov rcx, [rbx]
	add rcx, 1b					; Increment
	mov [rbx], rcx

	jmp getNextJVals.nextVal
	.endVals:


	mov rbx, [getNextJVals.flow]
	add rbx, Flow.j
	mov rcx, [rbx]
	add rcx, 1b					; Increment
	mov [rbx], rcx

	.endFlow:


	.end:



	mov rax, [getNextJVals.jVals]



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


; Flow i index as 0
; Takes Flow as param
flow.resetI:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label resetI.heapAddress qword at rbp-8  
	label resetI.handleAllocatedMemory qword at rbp-16
	label resetI.list qword at rbp-24 
	label resetI.flow qword at rbp-32
	label resetI.index qword at rbp-40
	label resetI.length qword at rbp-48
	label resetI.item qword at rbp-56
	label resetI.paddingValue qword at rbp-64
	label resetI.lists qword at rbp-72
	label resetI.nextFlowList qword at rbp-80
	label resetI.iListIndex qword at rbp-88
	label resetI.width qword at rbp-96
	label resetI.jIndex qword at rbp-104
	label resetI.jVals qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [resetI.flow], rcx


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



	mov rbx, [resetI.flow]
	add rbx, Flow.i
	mov rcx, 0
	mov [rbx], rcx


	.end:

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


; Flow i and j indices as 0
; Takes Flow as param
flow.resetIJ:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label resetIJ.heapAddress qword at rbp-8  
	label resetIJ.handleAllocatedMemory qword at rbp-16
	label resetIJ.list qword at rbp-24 
	label resetIJ.flow qword at rbp-32
	label resetIJ.index qword at rbp-40
	label resetIJ.length qword at rbp-48
	label resetIJ.item qword at rbp-56
	label resetIJ.paddingValue qword at rbp-64
	label resetIJ.lists qword at rbp-72
	label resetIJ.nextFlowList qword at rbp-80
	label resetIJ.iListIndex qword at rbp-88
	label resetIJ.width qword at rbp-96
	label resetIJ.jIndex qword at rbp-104
	label resetIJ.jVals qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [resetIJ.flow], rcx


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



	mov rbx, [resetIJ.flow]
	mov rdx, rbx
	add rbx, Flow.i
	add rdx, Flow.j
	mov rcx, 0
	mov [rbx], rcx
	mov [rdx], rcx


	.end:

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


; Gets val at i,j and increments i,j with wrapping
flow.getNextItem:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getNextItem.heapAddress qword at rbp-8  
	label getNextItem.handleAllocatedMemory qword at rbp-16
	label getNextItem.list qword at rbp-24 
	label getNextItem.flow qword at rbp-32
	label getNextItem.iIndex qword at rbp-40
	label getNextItem.length qword at rbp-48
	label getNextItem.item qword at rbp-56
	label getNextItem.paddingValue qword at rbp-64
	label getNextItem.lists qword at rbp-72
	label getNextItem.nextFlowList qword at rbp-80
	label getNextItem.iListIndex qword at rbp-88
	label getNextItem.width qword at rbp-96
	label getNextItem.jIndex qword at rbp-104
	label getNextItem.itemCompleted qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getNextItem.flow], rcx


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
	mov [getNextItem.item], rcx			; Begin as 0
	mov [getNextItem.itemCompleted], rcx			; Begin as 0


	mov rbx, [getNextItem.flow]
	mov r9, rbx
	add rbx, Flow.i
	mov rcx, [rbx]
	mov [getNextItem.iIndex], rcx
	add r9, Flow.j
	mov rdx, [r9]
	mov [getNextItem.jIndex], rdx
	mov rbx, [getNextItem.flow]
	add rbx, Flow.lists
	mov r8, [rbx]
	mov [getNextItem.lists], r8
	mov r10, [getNextItem.flow]
	add r10, Flow.width
	mov r11, [r10]
	mov [getNextItem.width], r11
	mov rbx, [getNextItem.flow]
	add rbx, Flow.length
	mov rcx, [rbx]
	mov [getNextItem.length], rcx
	mov r10, [getNextItem.flow]
	add r10, Flow.paddingValue
	mov r11, [r10]
	mov [getNextItem.paddingValue], r11


	.nextI:
	mov r11, [getNextItem.iIndex]
	mov r12, [getNextItem.width]
	cmp r11, r12
	jnl getNextItem.wrapI
	

	mov rbx, [getNextItem.lists]
	mov r10, rbx
	add r10, List.itemsCount
	mov rdx, [r10]
	add rbx, List.index
	mov r11, [getNextItem.iIndex]
	cmp r11, rdx
	jnl getNextItem.getPaddingVal
	mov [rbx], r11


	.nextJ:
	mov rbx, [getNextItem.lists]
	add rbx, List.index
	mov r8, [getNextItem.iIndex]
	mov [rbx], r8
	
	sub rsp, 8*8
	mov rcx, [getNextItem.lists]
	call list.getNextItem
	add rsp, 8*8
	mov [getNextItem.nextFlowList], rax

	mov rbx, [getNextItem.nextFlowList]
	add rbx, List.itemsCount
	mov r15, [rbx]
	mov r13, [getNextItem.length]
	cmp r15, r13
	jnle getNextItem.getPaddingVal

	mov rbx, [getNextItem.nextFlowList]
	add rbx, List.index
	mov r11, [getNextItem.jIndex]
	mov [rbx], r11

	sub rsp, 8*8
	mov rcx, [getNextItem.nextFlowList]
	call list.getNextItem
	add rsp, 8*8
	mov [getNextItem.item], rax

	mov rdx, 1b
	mov [getNextItem.itemCompleted], rdx

	jmp getNextItem.incrementIJ

	.getPaddingVal:
	mov r9, [getNextItem.paddingValue]
	mov [getNextItem.item], r9

	mov rdx, 1b
	mov [getNextItem.itemCompleted], rdx

	.incrementIJ:

	mov r11, [getNextItem.iIndex]
	add r11, 1b
	mov [getNextItem.iIndex], r11
	mov rbx, [getNextItem.flow]
	add rbx, Flow.i
	mov [rbx], r11

	mov r11, [getNextItem.iIndex]
	mov r12, [getNextItem.width]
	cmp r11, r12
	jl getNextItem.end					; Wrap I,J only when i greater than width

	.wrapI:
	mov rcx, 0
	mov [getNextItem.iIndex], rcx			; Wrap I
	mov r10, [getNextItem.jIndex]
	add r10, 1b
	mov [getNextItem.jIndex], r10			; Wrap J
	mov rbx, [getNextItem.flow]
	mov r9, rbx
	add rbx, Flow.i
	add r9, Flow.j
	mov [rbx], rcx
	mov [r9], r10

	mov rdx, [getNextItem.itemCompleted]
	cmp rdx, 1b
	jne getNextItem.nextI


	.end:



	mov rax, [getNextItem.item]



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
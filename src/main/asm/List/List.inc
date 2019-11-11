
section '.data' data readable writeable

	struc ListItem
		label .
		.item dq 0
		.previous dq 0
		.nesting dq 0
		.next dq 0
	end struc

	struc ItemMatch
		label .
		.item dq 0
		.index dq 0
		.nesting dq 0
	end struc

	struc List
		label .
		.firstItem dq 0
		.listSize dq 0
		.itemsCount dq 0
		.index dq 0
		.indexItem dq 0 			; Address of item at current index for faster item retrieval
		.indexedItemIndex dq 0			; Used to determine if index was set manually or actually equals indexed Item address
		.itemMatch dq 0				; Item matching
	end struc	
	


	; Used with address offsets
	virtual at 0
		ListItem ListItem
	end virtual

	; Used with address offsets
	virtual at 0
		ItemMatch ItemMatch
	end virtual


	; Used with address offsets
	virtual at 0
		List List
	end virtual


	; ---- Structures
	;list List


	;newSVGMsg db 'New SVG',0
	
		
section '.text' code readable writeable executable ;align 16



list:
namespace list
list.new:
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
	add rcx, List.itemMatch
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [new.heapAddress]
	call [ HeapAlloc] 
	mov [new.handleAllocatedMemory], rax
	add rsp, 8*4


	mov rbx, [new.handleAllocatedMemory]
	add rbx, List.firstItem
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, List.listSize
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, List.itemsCount
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, List.index
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, List.indexItem
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, List.indexedItemIndex
	mov rax, 0
	mov [rbx], rax
	sub rsp, 8*8
	call newItemMatch
	add rsp, 8*8
	mov rbx, [new.handleAllocatedMemory]
	add rbx, List.itemMatch
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


list.newItemMatch:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*2);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label newItemMatch.heapAddress qword at rbp-8  
	label newItemMatch.handleAllocatedMemory qword at rbp-16
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
	mov [newItemMatch.heapAddress], rax
	add rsp, 8*4
	

	mov rcx, 0
	add rcx, List.itemMatch
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [newItemMatch.heapAddress]
	call [ HeapAlloc] 
	mov [newItemMatch.handleAllocatedMemory], rax
	add rsp, 8*4


	mov rbx, [newItemMatch.handleAllocatedMemory]
	add rbx, ItemMatch.item
	mov rax, 0
	mov [rbx], rax
	mov rbx, [newItemMatch.handleAllocatedMemory]
	add rbx, ItemMatch.index
	mov rax, 0
	mov [rbx], rax
	mov rbx, [newItemMatch.handleAllocatedMemory]
	add rbx, ItemMatch.nesting
	mov rax, 0
	mov [rbx], rax


	;lea rax, [newItemMatch.list]
	;lea rcx, [newItemMatch.list.indexedItemIndex]

	;sub rcx, rax
	;add rcx, 1000b

	;cld

	;lea rsi, [newItemMatch.list]
	;mov rdi, [newItemMatch.handleAllocatedMemory]

	;rep movsb


	mov rax, [newItemMatch.handleAllocatedMemory]


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


list.newLastItem:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label newLastItem.heapAddress qword at rbp-8  
	label newLastItem.handleAllocatedMemory qword at rbp-16
	label newLastItem.list qword at rbp-24 
	label newLastItem.item qword at rbp-32
	label newLastItem.prevItem qword at rbp-40
	label newLastItem.priorIndex qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [newLastItem.list], rcx
	mov [newLastItem.item], rdx


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



	mov rbx, [newLastItem.list]
	add rbx, List.index
	mov r11, [rbx]
	mov [newLastItem.priorIndex], r11		; Restore later

	sub rsp, 8*4
	call [GetProcessHeap]
	mov [newLastItem.heapAddress], rax
	add rsp, 8*4


	mov rcx, 0
	add rcx, ListItem.next
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [newLastItem.heapAddress]
	call [ HeapAlloc] 
	mov [newLastItem.handleAllocatedMemory], rax
	add rsp, 8*4



	mov rbx, [newLastItem.handleAllocatedMemory]
	add rbx, ListItem.item
	mov rax, [newLastItem.item]
	mov [rbx], rax
	mov rbx, [newLastItem.handleAllocatedMemory]
	add rbx, ListItem.previous
	mov rax, 0
	mov [rbx], rax
	mov rbx, [newLastItem.handleAllocatedMemory]
	add rbx, ListItem.nesting
	mov rax, 0
	mov [rbx], rax
	mov rbx, [newLastItem.handleAllocatedMemory]
	add rbx, ListItem.next
	mov rax, 0
	mov [rbx], rax


	mov rbx, [newLastItem.list]
	add rbx, List.itemsCount
	mov rcx, [rbx]
	cmp rcx, 0
	jne newLastItem.firstItemExists
	
	mov rbx, [newLastItem.list]
	add rbx, List.firstItem
	mov rdx, [newLastItem.handleAllocatedMemory]
	mov [rbx], rdx						; Define first item

	mov rbx, [newLastItem.list]
	add rbx, List.indexItem
	mov rdx, [newLastItem.handleAllocatedMemory]
	mov [rbx], rdx						; Define index item

	
	jmp newLastItem.firstItem
	newLastItem.firstItemExists:



	mov rbx, [newLastItem.list]
	add rbx, List.indexItem
	mov rdx, [rbx]
	mov [newLastItem.prevItem], rdx


	mov rbx, [newLastItem.list]
	mov rdx, rbx
	add rbx, List.index
	mov r8, [rbx]
	add rdx, List.indexedItemIndex
	mov r9, [rdx]
	cmp r8, r9
	je newLastItem.nextItem				; Keep using prevItem when indices equal

	mov rbx, [newLastItem.list]			; Get first item when indexed is not cached and retrievable.
	add rbx, List.firstItem
	mov rdx, [rbx]
	mov [newLastItem.prevItem], rdx


	newLastItem.nextItem:
	mov rbx, [newLastItem.list]
	mov rdx, rbx
	add rbx, List.index
	mov rcx, [rbx]
	add rdx, List.itemsCount
	mov r8, [rdx]
	cmp rcx, r8
	jnl newLastItem.lastItemReached


	mov r9, [newLastItem.prevItem]
	add r9, ListItem.next
	mov r10, [r9]
	cmp r10, 0
	je newLastItem.lastItemReached

	mov [newLastItem.prevItem], r10
	mov rbx, [newLastItem.list]
	add rbx, List.index
	mov r11, [rbx]
	add r11, 1b
	mov [rbx], r11

	jmp newLastItem.nextItem
	newLastItem.lastItemReached:


	mov r9, [newLastItem.prevItem]
	mov r8, r9
	add r9, ListItem.next
	mov rdx, [newLastItem.handleAllocatedMemory]
	mov [r9], rdx					; New item as prior item's next
	add rdx, ListItem.previous
	mov [rdx], r8					; Prior item as item's previous


	newLastItem.firstItem:

	mov rbx, [newLastItem.list]
	add rbx, List.itemsCount
	mov r11, [rbx]
	add r11, 1b
	mov [rbx], r11					; Increment items count

	newLastItem.end:

	mov rbx, [newLastItem.list]
	add rbx, List.index
	mov r11, [newLastItem.priorIndex]		; Restore
	mov [rbx], r11
	

	mov rax, [newLastItem.handleAllocatedMemory]



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


list.getNextItem:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getNextItem.heapAddress qword at rbp-8  
	label getNextItem.handleAllocatedMemory qword at rbp-16
	label getNextItem.listAddress qword at rbp-24 
	label getNextItem.item qword at rbp-32
	label getNextItem.prevItem qword at rbp-40
	label getNextItem.prevItemIndex qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getNextItem.listAddress], rcx



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


	mov [getNextItem.listAddress], rcx


	mov rbx, [getNextItem.listAddress]
	
	;mov rcx, rbx;[rbx+List.index]
	mov r8, List.index
	add r8, rbx
	mov rcx, [r8]
	mov rax, 0
	cmp rcx, rax
	je getNextItem.retrieveFromFirstItem

	;mov rdx, [rbx+List.indexedItemIndex]
	mov rdx, List.indexedItemIndex
	add rdx, rbx
	mov rdx, [rdx]
	mov rax, 0

	cmp rdx, rax
	je getNextItem.retrieveFromFirstItem

	;cmp rcx, rax
	;jne retrieveFromFirstItem

	;mov rcx, [rbx+List.indexItem]
	mov rcx, List.indexItem
	add rcx, rbx
	mov rcx, [rcx]
	mov rax, 0

	cmp rcx, rax
	je getNextItem.retrieveFromFirstItem		


	;mov rdx, [rbx+List.indexedItemIndex]
	mov rdx, List.indexedItemIndex
	add rdx, rbx
	mov rdx, [rdx]
	;mov rcx, [rbx+List.index]
	mov rcx, List.index
	add rcx, rbx
	mov rcx, [rcx]
	cmp rcx, rdx

	jne getNextItem.retrieveFromFirstItem




	;jne retrieveFromFirstItem
	;mov rax, [rbx+List.index]
	mov rax, List.index
	add rax, rbx
	mov rax, [rax]
	add rax, 1
	mov rbx, [getNextItem.listAddress]
	mov r8, rbx
	add r8, List.indexedItemIndex
	mov qword [r8], rax
	sub rax, 1
	mov rbx, [getNextItem.listAddress]
	;mov rdx, [rbx+List.indexItem]
	mov rdx, List.indexItem
	add rdx, rbx
	mov rdx, [rdx]
	mov r9, rdx
	add r9, ListItem.next
	mov rcx, [r9]
	mov rbx, [getNextItem.listAddress]
	mov r9, rbx
	add r9, List.indexItem
	mov qword [r9], rcx	

	jmp getNextItem.itemReached

	.retrieveFromFirstItem:

	mov rbx, [getNextItem.listAddress]
	mov r9, rbx
	add r9, List.index
	mov rcx, [r9]
	mov rax, 0
	mov r9, rbx
	add r9, List.firstItem
	mov rdx, [r9]
	
	cmp rcx, rax
	je getNextItem.itemReached

	.itemNotReached:

	mov r9, rdx
	add r9, ListItem.next
	mov rbx, [r9]
	mov rdx, rbx
	add rax, 1
	
	cmp rax, rcx
	jne getNextItem.itemNotReached 


	.itemReached:

	add rax, 1
	mov rbx, [getNextItem.listAddress]
	mov r9, rbx
	add r9, List.index
	mov qword [r9], rax
	mov r10, rdx
	add r10, ListItem.item
	mov rax, [r10]
	



	;mov rcx, 0
	;mov [getNextItem.prevItemIndex], rcx		; Begin as 0

	;mov rbx, [getNextItem.list]
	;add rbx, List.indexItem
	;mov rdx, [rbx]
	;mov [getNextItem.prevItem], rdx


	;mov rbx, [getNextItem.list]
	;mov rdx, rbx
	;add rbx, List.index
	;mov r8, [rbx]
	;add rdx, List.indexedItemIndex
	;mov r9, [rdx]
	;cmp r8, r9
	;je getNextItem.atIndexedItem


	;mov rbx, [getNextItem.list]			; Start with first item when indexed is not cached and retrievable.
	;add rbx, List.firstItem
	;mov rdx, [rbx]
	;mov [getNextItem.prevItem], rdx

	;mov rbx, [getNextItem.list]
	;add rbx, List.index
	;mov rcx, [rbx]
	;cmp rcx, 0
	;jne getNextItem.nextItem

	;getNextItem.atIndexedItem:

	;mov rbx, [getNextItem.prevItem]
	;mov [getNextItem.item], rbx		

	;jmp getNextItem.lastItemReached

	;getNextItem.nextItem:
	;mov rbx, [getNextItem.list]
	;add rbx, List.index
	;mov rcx, [rbx]
	;mov rdx, [getNextItem.prevItemIndex]
	;cmp rcx, rdx
	;jne getNextItem.lastItemReached


	;mov r9, [getNextItem.prevItem]
	;add r9, ListItem.next
	;mov r10, [r9]
	;mov [getNextItem.item], r10

	;mov r11, [getNextItem.prevItemIndex]
	;add r11, 1b
	;mov [getNextItem.prevItemIndex], r11		; Increase prior item index
	
	;jmp getNextItem.nextItem

	;getNextItem.lastItemReached:


	;mov rbx, [getNextItem.list]			; Advance List index
	;add rbx, List.index
	;mov r11, [rbx]
	;add r11, 1b
	;mov [rbx], r11


	;mov r8, [getNextItem.list] 
	;add r8, List.itemsCount
	;mov r9, [r8]
	;cmp r11, r9
	;jnl getNextItem.maintainIndexedItem
		
	;mov r9, [getNextItem.item]
	;add r9, ListItem.next
	;mov r10, [r9]
	;mov r13, r10
	;mov rbx, [getNextItem.list]
	;mov rdx, rbx
	;add rbx, List.indexItem

	;jmp getNextItem.advanceOrMaintainIndexItem	

	;.maintainIndexedItem:				; Do not advance (Helpful when only one item so not cleared)

	;mov rbx, [getNextItem.list]			; Define index item, advance index item index
	;mov rdx, rbx
	;add rbx, List.indexItem
	;mov r13, [getNextItem.item]

	;.advanceOrMaintainIndexItem:
	;mov [rbx], r13
	;add rdx, List.indexedItemIndex
	;mov [rdx], r11

	;mov r12, [getNextItem.item]			; Get List Item's item
	;add r12, ListItem.item
	;mov rax, [r12]

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


; Gets Last Items diverged Item which is one nesting level higher
list.getLastDivergedItem:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getLastDivergedItem.heapAddress qword at rbp-8  
	label getLastDivergedItem.handleAllocatedMemory qword at rbp-16
	label getLastDivergedItem.listAddress qword at rbp-24 
	label getLastDivergedItem.item qword at rbp-32
	label getLastDivergedItem.prevItem qword at rbp-40
	label getLastDivergedItem.prevItemIndex qword at rbp-48
	label getLastDivergedItem.itemNesting qword at rbp-56
	label getLastDivergedItem.prevItemNesting qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getLastDivergedItem.listAddress], rcx




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
	mov [getLastDivergedItem.prevItemNesting], rcx		; Begin as 0
	mov [getLastDivergedItem.prevItem], rcx


	mov rbx, [getLastDivergedItem.listAddress]
	mov r8, rbx
	add rbx, List.itemsCount
	add r8, List.index
	mov rdx, [rbx]
	sub rdx, 1b
	mov [r8], rdx

	sub rsp, 8*8
	mov rcx, [getLastDivergedItem.listAddress]
	call getNextItemNesting
	add rsp, 8*8
	mov [getLastDivergedItem.itemNesting], rax



	mov rbx, [getLastDivergedItem.listAddress]
	mov r8, rbx
	add rbx, List.itemsCount
	add r8, List.index
	mov rdx, [rbx]
	sub rdx, 10b
	mov [r8], rdx

	.getPriorItem:
	mov rbx, [getLastDivergedItem.listAddress]
	add rbx, List.index
	mov rdx, [rbx]
	cmp rdx, 0
	jl getLastDivergedItem.end

	sub rsp, 8*8
	mov rcx, [getLastDivergedItem.listAddress]
	call getNextItemNesting
	add rsp, 8*8
	mov [getLastDivergedItem.prevItemNesting], rax

	sub rsp, 8*8
	mov rcx, [getLastDivergedItem.listAddress]
	call getNextItem
	add rsp, 8*8
	mov [getLastDivergedItem.prevItem], rax

	mov rbx, [getLastDivergedItem.prevItemNesting]
	mov rcx, [getLastDivergedItem.itemNesting]
	sub rcx, rbx
	mov r8, 1b
	cmp rcx, r8
	je getLastDivergedItem.end			; Must be 1 less

	mov rbx, [getLastDivergedItem.listAddress]
	add rbx, List.index
	mov rdx, [rbx]
	sub rdx, 10b
	mov [rbx], rdx					; Get prior index

	jmp getLastDivergedItem.getPriorItem
	.end:

	mov rax, [getLastDivergedItem.prevItem]

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

; Gets Last Items diverged Item nesting which is one nesting level higher
list.getLastDivergedItemNesting:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getLastDivergedItemNesting.heapAddress qword at rbp-8  
	label getLastDivergedItemNesting.handleAllocatedMemory qword at rbp-16
	label getLastDivergedItemNesting.listAddress qword at rbp-24 
	label getLastDivergedItemNesting.item qword at rbp-32
	label getLastDivergedItemNesting.prevItem qword at rbp-40
	label getLastDivergedItemNesting.prevItemIndex qword at rbp-48
	label getLastDivergedItemNesting.itemNesting qword at rbp-56
	label getLastDivergedItemNesting.prevItemNesting qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getLastDivergedItemNesting.listAddress], rcx



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
	mov [getLastDivergedItemNesting.prevItemNesting], rcx		; Begin as 0
	mov [getLastDivergedItemNesting.prevItem], rcx

	mov rbx, [getLastDivergedItemNesting.listAddress]
	mov r8, rbx
	add rbx, List.itemsCount
	add r8, List.index
	mov rdx, [rbx]
	sub rdx, 1b
	mov [r8], rdx

	sub rsp, 8*8
	mov rcx, [getLastDivergedItemNesting.listAddress]
	call getNextItemNesting
	add rsp, 8*8
	mov [getLastDivergedItemNesting.itemNesting], rax

	mov rbx, [getLastDivergedItemNesting.listAddress]
	mov r8, rbx
	add rbx, List.itemsCount
	add r8, List.index
	mov rdx, [rbx]
	sub rdx, 10b
	mov [r8], rdx

	.getPriorItem:
	mov rbx, [getLastDivergedItemNesting.listAddress]
	add rbx, List.index
	mov rdx, [rbx]
	cmp rdx, 0
	jl getLastDivergedItemNesting.end

	sub rsp, 8*8
	mov rcx, [getLastDivergedItemNesting.listAddress]
	call getNextItemNesting
	add rsp, 8*8
	mov [getLastDivergedItemNesting.prevItemNesting], rax

	sub rsp, 8*8
	mov rcx, [getLastDivergedItemNesting.listAddress]
	call getNextItem
	add rsp, 8*8
	mov [getLastDivergedItemNesting.prevItem], rax

	mov rbx, [getLastDivergedItemNesting.prevItemNesting]
	mov rcx, [getLastDivergedItemNesting.itemNesting]
	sub rcx, rbx
	mov r8, 1b
	cmp rcx, r8
	je getLastDivergedItemNesting.end			; Must be 1 less

	mov rbx, [getLastDivergedItemNesting.listAddress]
	add rbx, List.index
	mov rdx, [rbx]
	sub rdx, 10b
	mov [rbx], rdx					; Get prior index

	jmp getLastDivergedItemNesting.getPriorItem
	.end:

	mov rax, [getLastDivergedItemNesting.prevItemNesting]




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

; Gets Count of Items one level nested beneath index
list.getConvergedItemCount:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*9);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getConvergedItemCount.heapAddress qword at rbp-8  
	label getConvergedItemCount.handleAllocatedMemory qword at rbp-16
	label getConvergedItemCount.listAddress qword at rbp-24 
	label getConvergedItemCount.item qword at rbp-32
	label getConvergedItemCount.nextItem qword at rbp-40
	label getConvergedItemCount.prevItemIndex qword at rbp-48
	label getConvergedItemCount.itemNesting qword at rbp-56
	label getConvergedItemCount.nextItemNesting qword at rbp-64
	label getConvergedItemCount.convergedCount qword at rbp-72
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getConvergedItemCount.listAddress], rcx




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
	mov [getConvergedItemCount.nextItemNesting], rcx		; Begin as 0
	mov [getConvergedItemCount.nextItem], rcx
	mov [getConvergedItemCount.convergedCount], rcx


	sub rsp, 8*8
	mov rcx, [getConvergedItemCount.listAddress]
	call getNextItemNesting
	add rsp, 8*8
	mov [getConvergedItemCount.itemNesting], rax

	mov rbx, [getConvergedItemCount.listAddress]
	add rbx, List.index
	mov rdx, [rbx]
	add rdx, 1b
	mov [rbx], rdx


	.nextListItem:
	mov rbx, [getConvergedItemCount.listAddress]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov rcx, [rbx]
	mov r8, [rdx]
	cmp rcx, r8
	jnl getConvergedItemCount.end

	sub rsp, 8*8
	mov rcx, [getConvergedItemCount.listAddress]
	call getNextItemNesting
	add rsp, 8*8
	mov [getConvergedItemCount.nextItemNesting], rax

	sub rsp, 8*8
	mov rcx, [getConvergedItemCount.listAddress]
	call getNextItem
	add rsp, 8*8
	mov [getConvergedItemCount.nextItem], rax

	mov rbx, [getConvergedItemCount.nextItemNesting]
	mov rcx, [getConvergedItemCount.itemNesting]
	sub rbx, rcx
	mov r8, 1b
	mov r8, 0
	cmp rbx, r8
	jle getConvergedItemCount.end				; No more, diverged (nesting at a tangent or higher)
	mov r8, 1b
	cmp rbx, r8
	jne getConvergedItemCount.nextListItem			; Must be 1

	mov r9, [getConvergedItemCount.convergedCount]
	add r9, 1b
	mov [getConvergedItemCount.convergedCount], r9		; Increment

	jmp getConvergedItemCount.nextListItem
	.end:

	mov rax, [getConvergedItemCount.convergedCount]

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

; Gets Next Item at a determined nesting level
list.getNextTangentItem:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*9);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getNextTangentItem.heapAddress qword at rbp-8  
	label getNextTangentItem.handleAllocatedMemory qword at rbp-16
	label getNextTangentItem.listAddress qword at rbp-24 
	label getNextTangentItem.item qword at rbp-32
	label getNextTangentItem.nextItem qword at rbp-40
	label getNextTangentItem.prevItemIndex qword at rbp-48
	label getNextTangentItem.itemNesting qword at rbp-56
	label getNextTangentItem.nextItemNesting qword at rbp-64
	label getNextTangentItem.convergedCount qword at rbp-72
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getNextTangentItem.listAddress], rcx
	mov [getNextTangentItem.itemNesting], rdx




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
	mov [getNextTangentItem.nextItemNesting], rcx		; Begin as 0
	mov [getNextTangentItem.nextItem], rcx
	mov [getNextTangentItem.convergedCount], rcx





	.nextListItem:
	mov rbx, [getNextTangentItem.listAddress]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov rcx, [rbx]
	mov r8, [rdx]
	cmp rcx, r8
	jnl getNextTangentItem.end

	sub rsp, 8*8
	mov rcx, [getNextTangentItem.listAddress]
	call getNextItemNesting
	add rsp, 8*8
	mov [getNextTangentItem.nextItemNesting], rax

	sub rsp, 8*8
	mov rcx, [getNextTangentItem.listAddress]
	call getNextItem
	add rsp, 8*8
	mov [getNextTangentItem.nextItem], rax

	mov rbx, [getNextTangentItem.nextItemNesting]
	mov rcx, [getNextTangentItem.itemNesting]
	cmp rbx, rcx
	je getNextTangentItem.end	

	jmp getNextTangentItem.nextListItem
	.end:

	mov rax, [getNextTangentItem.nextItem]

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

; Does not advance List index
list.getNextItemNesting:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getNextItemNesting.heapAddress qword at rbp-8  
	label getNextItemNesting.handleAllocatedMemory qword at rbp-16
	label getNextItemNesting.listAddress qword at rbp-24 
	label getNextItemNesting.item qword at rbp-32
	label getNextItemNesting.prevItem qword at rbp-40
	label getNextItemNesting.prevItemIndex qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getNextItemNesting.listAddress], rcx



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



	mov [getNextItemNesting.listAddress], rcx


	mov rbx, [getNextItemNesting.listAddress]
	
	;mov rcx, rbx;[rbx+List.index]
	mov r8, List.index
	add r8, rbx
	mov rcx, [r8]
	mov rax, 0
	cmp rcx, rax
	je getNextItemNesting.retrieveFromFirstItem

	;mov rdx, [rbx+List.indexedItemIndex]
	mov rdx, List.indexedItemIndex
	add rdx, rbx
	mov rdx, [rdx]
	mov rax, 0

	cmp rdx, rax
	je getNextItemNesting.retrieveFromFirstItem

	;cmp rcx, rax
	;jne retrieveFromFirstItem

	;mov rcx, [rbx+List.indexItem]
	mov rcx, List.indexItem
	add rcx, rbx
	mov rcx, [rcx]
	mov rax, 0

	cmp rcx, rax
	je getNextItemNesting.retrieveFromFirstItem		


	;mov rdx, [rbx+List.indexedItemIndex]
	mov rdx, List.indexedItemIndex
	add rdx, rbx
	mov rdx, [rdx]
	;mov rcx, [rbx+List.index]
	mov rcx, List.index
	add rcx, rbx
	mov rcx, [rcx]
	cmp rcx, rdx

	jne getNextItemNesting.retrieveFromFirstItem




	;jne retrieveFromFirstItem
	;mov rax, [rbx+List.index]
	mov rax, List.index
	add rax, rbx
	mov rax, [rax]
	add rax, 1
	mov rbx, [getNextItemNesting.listAddress]
	mov r8, rbx
	add r8, List.indexedItemIndex
	mov qword [r8], rax
	sub rax, 1
	mov rbx, [getNextItemNesting.listAddress]
	;mov rdx, [rbx+List.indexItem]
	mov rdx, List.indexItem
	add rdx, rbx
	mov rdx, [rdx]
	mov r9, rdx
	add r9, ListItem.next
	mov rcx, [r9]
	mov rbx, [getNextItemNesting.listAddress]
	mov r9, rbx
	add r9, List.indexItem
	mov qword [r9], rcx	

	jmp getNextItemNesting.itemReached

	.retrieveFromFirstItem:

	mov rbx, [getNextItemNesting.listAddress]
	mov r9, rbx
	add r9, List.index
	mov rcx, [r9]
	mov rax, 0
	mov r9, rbx
	add r9, List.firstItem
	mov rdx, [r9]
	
	cmp rcx, rax
	je getNextItemNesting.itemReached

	.itemNotReached:

	mov r9, rdx
	add r9, ListItem.next
	mov rbx, [r9]
	mov rdx, rbx
	add rax, 1
	
	cmp rax, rcx
	jne getNextItemNesting.itemNotReached 


	.itemReached:

	;add rax, 1						; Do not advance index
	mov rbx, [getNextItemNesting.listAddress]
	mov r9, rbx
	add r9, List.index
	mov qword [r9], rax
	mov r10, rdx
	add r10, ListItem.nesting
	mov rax, [r10]
	



	;mov rcx, 0
	;mov [getNextItemNesting.prevItemIndex], rcx		; Begin as 0

	;mov rbx, [getNextItemNesting.list]
	;add rbx, List.indexItem
	;mov rdx, [rbx]
	;mov [getNextItemNesting.prevItem], rdx


	;mov rbx, [getNextItemNesting.list]
	;mov rdx, rbx
	;add rbx, List.index
	;mov r8, [rbx]
	;add rdx, List.indexedItemIndex
	;mov r9, [rdx]
	;cmp r8, r9
	;je getNextItemNesting.atIndexedItem


	;mov rbx, [getNextItemNesting.list]			; Start with first item when indexed is not cached and retrievable.
	;add rbx, List.firstItem
	;mov rdx, [rbx]
	;mov [getNextItemNesting.prevItem], rdx

	;mov rbx, [getNextItemNesting.list]
	;add rbx, List.index
	;mov rcx, [rbx]
	;cmp rcx, 0
	;jne getNextItemNesting.nextItem

	;getNextItemNesting.atIndexedItem:

	;mov rbx, [getNextItemNesting.prevItem]
	;mov [getNextItemNesting.item], rbx		

	;jmp getNextItemNesting.lastItemReached

	;getNextItemNesting.nextItem:
	;mov rbx, [getNextItemNesting.list]
	;add rbx, List.index
	;mov rcx, [rbx]
	;mov rdx, [getNextItemNesting.prevItemIndex]
	;cmp rcx, rdx
	;jne getNextItemNesting.lastItemReached


	;mov r9, [getNextItemNesting.prevItem]
	;add r9, ListItem.next
	;mov r10, [r9]
	;mov [getNextItemNesting.item], r10

	;mov r11, [getNextItemNesting.prevItemIndex]
	;add r11, 1b
	;mov [getNextItemNesting.prevItemIndex], r11		; Increase prior item index
	
	;jmp getNextItemNesting.nextItem

	;getNextItemNesting.lastItemReached:


	;mov rbx, [getNextItemNesting.list]			; Advance List index
	;add rbx, List.index
	;mov r11, [rbx]
	;add r11, 1b
	;mov [rbx], r11


	;mov r8, [getNextItemNesting.list] 
	;add r8, List.itemsCount
	;mov r9, [r8]
	;cmp r11, r9
	;jnl getNextItemNesting.maintainIndexedItem
		
	;mov r9, [getNextItemNesting.item]
	;add r9, ListItem.next
	;mov r10, [r9]
	;mov r13, r10
	;mov rbx, [getNextItemNesting.list]
	;mov rdx, rbx
	;add rbx, List.indexItem

	;jmp getNextItemNesting.advanceOrMaintainIndexItem	

	;.maintainIndexedItem:				; Do not advance (Helpful when only one item so not cleared)

	;mov rbx, [getNextItemNesting.list]			; Define index item, advance index item index
	;mov rdx, rbx
	;add rbx, List.indexItem
	;mov r13, [getNextItemNesting.item]

	;.advanceOrMaintainIndexItem:
	;mov [rbx], r13
	;add rdx, List.indexedItemIndex
	;mov [rdx], r11

	;mov r12, [getNextItemNesting.item]			; Get List Item's item
	;add r12, ListItem.item
	;mov rax, [r12]


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

list.nextItemNesting:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*7);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label nextItemNesting.heapAddress qword at rbp-8  
	label nextItemNesting.handleAllocatedMemory qword at rbp-16
	label nextItemNesting.listAddress qword at rbp-24 
	label nextItemNesting.item qword at rbp-32
	label nextItemNesting.prevItem qword at rbp-40
	label nextItemNesting.prevItemIndex qword at rbp-48
	label nextItemNesting.nesting qword at rbp-56
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [nextItemNesting.listAddress], rcx
	mov [nextItemNesting.nesting], rdx




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



	mov [nextItemNesting.listAddress], rcx


	mov rbx, [nextItemNesting.listAddress]
	
	;mov rcx, rbx;[rbx+List.index]
	mov r8, List.index
	add r8, rbx
	mov rcx, [r8]
	mov rax, 0
	cmp rcx, rax
	je nextItemNesting.retrieveFromFirstItem

	;mov rdx, [rbx+List.indexedItemIndex]
	mov rdx, List.indexedItemIndex
	add rdx, rbx
	mov rdx, [rdx]
	mov rax, 0

	cmp rdx, rax
	je nextItemNesting.retrieveFromFirstItem

	;cmp rcx, rax
	;jne retrieveFromFirstItem

	;mov rcx, [rbx+List.indexItem]
	mov rcx, List.indexItem
	add rcx, rbx
	mov rcx, [rcx]
	mov rax, 0

	cmp rcx, rax
	je nextItemNesting.retrieveFromFirstItem		


	;mov rdx, [rbx+List.indexedItemIndex]
	mov rdx, List.indexedItemIndex
	add rdx, rbx
	mov rdx, [rdx]
	;mov rcx, [rbx+List.index]
	mov rcx, List.index
	add rcx, rbx
	mov rcx, [rcx]
	cmp rcx, rdx

	jne nextItemNesting.retrieveFromFirstItem




	;jne retrieveFromFirstItem
	;mov rax, [rbx+List.index]
	mov rax, List.index
	add rax, rbx
	mov rax, [rax]
	add rax, 1
	mov rbx, [nextItemNesting.listAddress]
	mov r8, rbx
	add r8, List.indexedItemIndex
	mov qword [r8], rax
	sub rax, 1
	mov rbx, [nextItemNesting.listAddress]
	;mov rdx, [rbx+List.indexItem]
	mov rdx, List.indexItem
	add rdx, rbx
	mov rdx, [rdx]
	mov r9, rdx
	add r9, ListItem.next
	mov rcx, [r9]
	mov rbx, [nextItemNesting.listAddress]
	mov r9, rbx
	add r9, List.indexItem
	mov qword [r9], rcx	

	jmp nextItemNesting.itemReached

	.retrieveFromFirstItem:

	mov rbx, [nextItemNesting.listAddress]
	mov r9, rbx
	add r9, List.index
	mov rcx, [r9]
	mov rax, 0
	mov r9, rbx
	add r9, List.firstItem
	mov rdx, [r9]
	
	cmp rcx, rax
	je nextItemNesting.itemReached

	.itemNotReached:

	mov r9, rdx
	add r9, ListItem.next
	mov rbx, [r9]
	mov rdx, rbx
	add rax, 1
	
	cmp rax, rcx
	jne nextItemNesting.itemNotReached 


	.itemReached:

	;add rax, 1					; Do not advance
	mov rbx, [nextItemNesting.listAddress]
	mov r9, rbx
	add r9, List.index
	mov qword [r9], rax
	mov r10, rdx
	add r10, ListItem.nesting
	mov r13, [nextItemNesting.nesting]		; List Item's nesting
	mov [r10], r13
	


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

list.lastItemNesting:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*7);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label lastItemNesting.heapAddress qword at rbp-8  
	label lastItemNesting.handleAllocatedMemory qword at rbp-16
	label lastItemNesting.listAddress qword at rbp-24 
	label lastItemNesting.item qword at rbp-32
	label lastItemNesting.prevItem qword at rbp-40
	label lastItemNesting.prevItemIndex qword at rbp-48
	label lastItemNesting.nesting qword at rbp-56
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [lastItemNesting.listAddress], rcx
	mov [lastItemNesting.nesting], rdx




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



	mov [lastItemNesting.listAddress], rcx

	sub rsp, 8*8
	mov rcx, [lastItemNesting.listAddress]
	call resetIndex
	add rsp, 8*8


	mov rbx, [lastItemNesting.listAddress]
	mov rdx, rbx
	add rbx, List.itemsCount
	add rdx, List.index
	mov rcx, [rbx]
	sub rcx, 1b
	mov [rdx], rcx
	

	mov rbx, [lastItemNesting.listAddress]
	
	;mov rcx, rbx;[rbx+List.index]
	mov r8, List.index
	add r8, rbx
	mov rcx, [r8]
	mov rax, 0
	cmp rcx, rax
	je lastItemNesting.retrieveFromFirstItem

	;mov rdx, [rbx+List.indexedItemIndex]
	mov rdx, List.indexedItemIndex
	add rdx, rbx
	mov rdx, [rdx]
	mov rax, 0

	cmp rdx, rax
	je lastItemNesting.retrieveFromFirstItem

	;cmp rcx, rax
	;jne retrieveFromFirstItem

	;mov rcx, [rbx+List.indexItem]
	mov rcx, List.indexItem
	add rcx, rbx
	mov rcx, [rcx]
	mov rax, 0

	cmp rcx, rax
	je lastItemNesting.retrieveFromFirstItem		


	;mov rdx, [rbx+List.indexedItemIndex]
	mov rdx, List.indexedItemIndex
	add rdx, rbx
	mov rdx, [rdx]
	;mov rcx, [rbx+List.index]
	mov rcx, List.index
	add rcx, rbx
	mov rcx, [rcx]
	cmp rcx, rdx

	jne lastItemNesting.retrieveFromFirstItem




	;jne retrieveFromFirstItem
	;mov rax, [rbx+List.index]
	mov rax, List.index
	add rax, rbx
	mov rax, [rax]
	add rax, 1
	mov rbx, [lastItemNesting.listAddress]
	mov r8, rbx
	add r8, List.indexedItemIndex
	mov qword [r8], rax
	sub rax, 1
	mov rbx, [lastItemNesting.listAddress]
	;mov rdx, [rbx+List.indexItem]
	mov rdx, List.indexItem
	add rdx, rbx
	mov rdx, [rdx]
	mov r9, rdx
	add r9, ListItem.next
	mov rcx, [r9]
	mov rbx, [lastItemNesting.listAddress]
	mov r9, rbx
	add r9, List.indexItem
	mov qword [r9], rcx	

	jmp lastItemNesting.itemReached

	.retrieveFromFirstItem:

	mov rbx, [lastItemNesting.listAddress]
	mov r9, rbx
	add r9, List.index
	mov rcx, [r9]
	mov rax, 0
	mov r9, rbx
	add r9, List.firstItem
	mov rdx, [r9]
	
	cmp rcx, rax
	je lastItemNesting.itemReached

	.itemNotReached:

	mov r9, rdx
	add r9, ListItem.next
	mov rbx, [r9]
	mov rdx, rbx
	add rax, 1
	
	cmp rax, rcx
	jne lastItemNesting.itemNotReached 


	.itemReached:

	;add rax, 1					; Do not advance
	mov rbx, [lastItemNesting.listAddress]
	mov r9, rbx
	add r9, List.index
	mov qword [r9], rax
	mov r10, rdx
	add r10, ListItem.nesting
	mov r13, [lastItemNesting.nesting]		; List Item's nesting
	mov [r10], r13
	
	sub rsp, 8*8
	mov rcx, [lastItemNesting.listAddress]
	call resetIndex
	add rsp, 8*8


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

; New Item at index, not necessarily last index;
list.newNextItem:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*15);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label newNextItem.hHeap qword at rbp-8  
	label newNextItem.hAllocatedMemory qword at rbp-16
	label newNextItem.listAddress qword at rbp-24 
	label newNextItem.item qword at rbp-32
	label newNextItem.prevItem qword at rbp-40
	label newNextItem.prevItemIndex qword at rbp-48
	label newNextItem.newItemAddress qword at rbp-56
	label newNextItem.prevItemNext qword at rbp-64
	label newNextItem.nextItemPrev qword at rbp-72
	label newNextItem.newItemIndex qword at rbp-80
	label newNextItem.newListItem qword at rbp-88
	label newNextItem.itemSize qword at rbp-96
	label newNextItem.afterNewItemAddress qword at rbp-104
	label newNextItem.beforeNewItemAddress qword at rbp-112
	label newNextItem.beforeNewItemNesting qword at rbp-120
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [newNextItem.listAddress], rcx
	mov [newNextItem.newItemAddress], rdx



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


	mov rbx, [newNextItem.listAddress]
	mov r8, rbx
	add r8, List.itemsCount
	mov rcx, [r8]
	mov rax, 0


	cmp rcx, rax
	jne newNextItem.listNotBlank					; New First Item?

	mov rdx, [newNextItem.newItemAddress]
	mov rcx, [newNextItem.listAddress]
	sub rsp, 8*8
	call newLastItem
	add rsp, 8*8
	;add rsp, 16

	mov rbx, [newNextItem.listAddress]
	mov r8, rbx
	add r8, List.index
	mov qword [r8], 0 					; For chaining

	jmp newNextItem.newNextItemFailed

	.listNotBlank:						; Already checked blank
	mov rbx, [newNextItem.listAddress]
	mov r8, rbx
	add r8, List.itemsCount
	mov rcx, [r8]
	mov r9, rbx
	add r9, List.index	
	mov rax, [r9]

	cmp rcx, rax
	jne newNextItem.notLastItem					; New Last Item?

	mov rdx, [newNextItem.newItemAddress]
	mov rcx, [newNextItem.listAddress]
	sub rsp, 8*8
	call newLastItem
	add rsp, 8*8
	;add rsp, 16

	mov rbx, [newNextItem.listAddress]
	mov r8, rbx
	add r8, List.index
	mov qword [r8], 0 					; For chaining

	jmp newNextItem.newNextItemFailed

	.notLastItem:
	mov rbx, [newNextItem.listAddress]
	mov r9, rbx
	add r9, List.index
	mov rcx, [r9]
	mov [newNextItem.newItemIndex], rcx

	mov rcx, 0
	add rcx, ListItem.next
	add rcx, 1000b
	mov [newNextItem.itemSize], rcx		; Calculate item size

	sub rsp, 8*4
	call [GetProcessHeap]
	add rsp, 8*4
	cmp rax, 0
	je newNextItem.newNextItemFailed
	mov [newNextItem.hHeap], rax				; Get Heap

	; Reserve new item struc space
	sub rsp, 8*4	
	mov r8, [newNextItem.itemSize]
	mov rdx, 000001000b
	mov rcx, [newNextItem.hHeap]
	call [HeapAlloc] 
	add rsp, 8*4
	cmp rax, 0
	je newNextItem.newNextItemFailed
	mov [newNextItem.hAllocatedMemory], rax 		; New item allocated

	cmp rax, 0
	jne newNextItem.allocated


	; Error

	.allocated:


	mov rbx, [newNextItem.listAddress]
	
	mov r9, rbx
	add r9, List.index
	mov rcx, [r9]
	mov rax, 0

	mov r8, rbx
	add r8, List.firstItem
	mov rdx, [r8]
	
	cmp rcx, rax						; Index 0?
	je newNextItem.afterNewItemReached

	.afterNewItemNotReached:

	mov r10, rdx
	add r10, ListItem.next
	mov rbx, [r10]
	mov rdx, rbx
	add rax, 1
	
	cmp rax, rcx
	jne newNextItem.afterNewItemNotReached


	.afterNewItemReached:

	add rax, 1						; Destination Index?
	mov rbx, [newNextItem.listAddress]
	mov r8, rbx
	add r8, List.index
	mov qword [r8], rax				; After current item index?

	mov r9, rbx
	add r9, List.indexedItemIndex
	mov qword [r9], rax		;These may introduce problems
	mov r9, rbx
	add r9, List.indexItem
	mov qword [r9], rdx			;These may introduce problems	; First item or next?

	mov [newNextItem.afterNewItemAddress], rdx
	mov r8, rdx
	add r8, ListItem.previous
	mov rbx, [r8]

	mov rax, 0
	cmp rbx, rax
	jne newNextItem.notReplacingFirstItem

	mov [newNextItem.beforeNewItemAddress], rbx		; 0
	mov r8, rdx
	add r8, ListItem.nesting
	mov rax, [r8] 			; Use next's
	mov [newNextItem.beforeNewItemNesting], rax

	jmp newNextItem.firstReplaced

	.notReplacingFirstItem:

	mov [newNextItem.beforeNewItemAddress], rbx
	mov r8, rbx
	add r8, ListItem.nesting
	mov rdx, [r8]
	mov [newNextItem.beforeNewItemNesting], rdx

	.firstReplaced: 

	mov rdx, [newNextItem.beforeNewItemAddress]
	mov rbx, [newNextItem.afterNewItemAddress]

	mov r11, [newNextItem.hAllocatedMemory]
	add r11, ListItem.previous
	mov [r11], rdx
	mov r11, [newNextItem.hAllocatedMemory]
	add r11, ListItem.next
	mov [r11], rbx
	mov rbx, [newNextItem.beforeNewItemNesting]
	mov r11, [newNextItem.hAllocatedMemory]
	add r11, ListItem.nesting
	mov [r11], rbx
	mov rax, [newNextItem.newItemAddress]
	mov r11, [newNextItem.hAllocatedMemory]
	add r11, ListItem.item
	mov [r11], rax


	; Set following List Item addresses	
	mov rbx, [newNextItem.afterNewItemAddress]
	mov rdx, [newNextItem.hAllocatedMemory]
	mov r8, rbx
	add r8, ListItem.previous
	mov qword [r8], rdx

	mov rcx, [newNextItem.newItemIndex]
	cmp rcx, 0
	jne newNextItem.newNextItemNotFirstItem

	; Set list's first item
	mov rbx, [newNextItem.hAllocatedMemory]

	mov rax, [newNextItem.listAddress]	
	mov r8, rax
	add r8, List.firstItem
	mov qword [r8], rbx

	jmp newNextItem.increaseItemsCount

	.newNextItemNotFirstItem:
	mov rdx, [newNextItem.hAllocatedMemory]
	mov rbx, [newNextItem.beforeNewItemAddress]	
	mov r9, rbx
	add r9, ListItem.next
	mov qword [r9], rdx

	.increaseItemsCount:

	mov rbx, [newNextItem.listAddress]
	mov r9, rbx
	add r9, List.itemsCount
	mov rcx, [r9]


	add rcx, 1
	mov r8, rbx
	add r8, List.itemsCount
	mov qword [r8], rcx

	mov r9, rbx
	add r9, List.indexedItemIndex
	mov qword [r9], 0	;Until indexes are updated
	mov r9, rbx
	add r9, List.indexItem
	mov qword [r9], 0

	;Increment current List index

	;mov rbx, [newNextItem.listAddress]
	;mov rax, [rbx+List.index]
	;inc rax
	;mov [rbx+List.index], rax

	.newNextItemFailed:

	mov rax, [newNextItem.listAddress]









	;mov rcx, 0
	;mov [newNextItem.prevItemIndex], rcx		; Begin as 0
	;mov [newNextItem.prevItemNext], rcx


	;sub rsp, 8*4
	;call [GetProcessHeap]
	;mov [newNextItem.heapAddress], rax
	;add rsp, 8*4


	;mov rcx, 0
	;add rcx, ListItem.next
	;add rcx, 1000b

	;sub rsp, 8*4
	;mov r8, rcx		
	;mov rdx, 000001000b
	;mov rcx, [newNextItem.heapAddress]
	;call [ HeapAlloc] 
	;mov [newNextItem.handleAllocatedMemory], rax
	;add rsp, 8*4


	;mov rbx, [newNextItem.list]
	;add rbx, List.indexItem
	;mov rdx, [rbx]
	;mov [newNextItem.prevItem], rdx


	;mov rbx, [newNextItem.list]
	;mov rdx, rbx
	;add rbx, List.index
	;mov r8, [rbx]
	;add rdx, List.indexedItemIndex
	;mov r9, [rdx]
	;cmp r8, r9
	;je newNextItem.atIndexedItem

	;mov rbx, [newNextItem.list]			; Get first item when indexed is not cached and retrievable.
	;add rbx, List.firstItem
	;mov rdx, [rbx]
	;mov [newNextItem.prevItem], rdx

	;mov rbx, [newNextItem.list]
	;add rbx, List.index
	;mov rcx, [rbx]
	;cmp rcx, 0
	;jne newNextItem.nextItem

	;newNextItem.atIndexedItem:

	;mov rbx, [newNextItem.prevItem]
	;mov [newNextItem.item], rbx		

	;jmp newNextItem.indexReached

	;newNextItem.nextItem:
	;mov rbx, [newNextItem.list]
	;add rbx, List.index
	;mov rcx, [rbx]
	;mov rdx, [newNextItem.prevItemIndex]
	;cmp rcx, rdx
	;jne newNextItem.indexReached


	;mov r9, [newNextItem.prevItem]
	;add r9, ListItem.next
	;mov r10, [r9]
	;mov [newNextItem.item], r10

	;mov r11, [newNextItem.prevItemIndex]
	;add r11, 1b
	;mov [newNextItem.prevItemIndex], r11		; Increase prior item index
	
	;jmp newNextItem.nextItem

	;newNextItem.indexReached:


	;mov rbx, [newNextItem.item]
	;add rbx, ListItem.next
	;mov rdx, [rbx]
	;cmp rdx, 0
	;je newNextItem.noNextItem

	;mov [newNextItem.prevItemNext], rdx	
	;add rdx, ListItem.previous
	;mov [newNextItem.nextItemPrev], rdx		; Cache index. May remove this.
	;mov rax, [newNextItem.handleAllocatedMemory]
	;mov [rdx], rax

	;newNextItem.noNextItem:


	;mov rbx, [newNextItem.list]			; Advance List index
	;add rbx, List.index
	;mov r11, [rbx]
	;add r11, 1b
	;mov [rbx], r11





	;mov rbx, [newNextItem.handleAllocatedMemory]
	;add rbx, ListItem.item
	;mov rax, [newNextItem.newItem]
	;mov [rbx], rax
	;mov rbx, [newNextItem.handleAllocatedMemory]
	;add rbx, ListItem.previous
	;mov rax, [newNextItem.item]
	;mov [rbx], rax
	;mov rbx, [newNextItem.handleAllocatedMemory]
	;add rbx, ListItem.nesting
	;mov rax, 0
	;mov [rbx], rax
	;mov rbx, [newNextItem.handleAllocatedMemory]
	;add rbx, ListItem.next
	;mov rax, [newNextItem.prevItemNext]
	;mov [rbx], rax





	;mov rbx, [newNextItem.list]			; Increase items count
	;add rbx, List.itemsCount
	;mov r11, [rbx]
	;add r11, 1b
	;mov [rbx], r11


	;mov rbx, [newNextItem.list]			; Advance index item, index item index
	;mov rdx, rbx
	;add rbx, List.indexItem
	;mov r13, [newNextItem.handleAllocatedMemory]
	;mov [rbx], r13
	;add rdx, List.indexedItemIndex
	;mov [rdx], r11


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

list.getPriorItem:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*7);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getPriorItem.heapAddress qword at rbp-8  
	label getPriorItem.handleAllocatedMemory qword at rbp-16
	label getPriorItem.list qword at rbp-24 
	label getPriorItem.item qword at rbp-32
	label getPriorItem.prevItem qword at rbp-40
	label getPriorItem.prevItemIndex qword at rbp-48
	label getPriorItem.listItemMatch qword at rbp-56
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getPriorItem.list], rcx



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
	mov [getPriorItem.prevItemIndex], rcx		; Begin as 0

	mov rbx, [getPriorItem.list]
	add rbx, List.indexItem
	mov rdx, [rbx]
	mov [getPriorItem.prevItem], rdx


	mov rbx, [getPriorItem.list]
	mov rdx, rbx
	add rbx, List.index
	mov r8, [rbx]
	add rdx, List.indexedItemIndex
	mov r9, [rdx]
	cmp r8, r9
	je getPriorItem.atIndexedItem

	mov rbx, [getPriorItem.list]			; Get first item when indexed is not cached and retrievable.
	add rbx, List.firstItem
	mov rdx, [rbx]
	mov [getPriorItem.prevItem], rdx

	mov rbx, [getPriorItem.list]
	add rbx, List.index
	mov rcx, [rbx]
	cmp rcx, 0
	jne getPriorItem.nextItem

	getPriorItem.atIndexedItem:

	mov rbx, [getPriorItem.prevItem]
	mov [getPriorItem.item], rbx		

	jmp getPriorItem.lastItemReached

	getPriorItem.nextItem:
	mov rbx, [getPriorItem.list]
	add rbx, List.index
	mov rcx, [rbx]
	mov rdx, [getPriorItem.prevItemIndex]
	cmp rcx, rdx
	jne getPriorItem.lastItemReached


	mov r9, [getPriorItem.prevItem]
	add r9, ListItem.next
	mov r10, [r9]
	mov [getPriorItem.item], r10

	mov r11, [getPriorItem.prevItemIndex]
	add r11, 1b
	mov [getPriorItem.prevItemIndex], r11		; Increase prior item index
	
	jmp getPriorItem.nextItem

	getPriorItem.lastItemReached:

	mov r13, [getPriorItem.item]
	add r13, ListItem.previous
	mov rax, [r13]
	mov [getPriorItem.item], rax	
	cmp rax, 0
	je getPriorItem.end



	mov rbx, [getPriorItem.list]			; Decrease List index
	add rbx, List.index
	mov r11, [rbx]
	sub r11, 1b
	mov [rbx], r11

	mov rbx, [getPriorItem.list]			; Cache index item, index item index
	mov rdx, rbx
	add rbx, List.indexItem
	mov r13, [getPriorItem.item]
	mov [rbx], r13
	add rdx, List.indexedItemIndex
	mov [rdx], r11


	getPriorItem.end:

	mov r12, [getPriorItem.item]	
	cmp r12, 0
	je getPriorItem.noMatch

	mov rbx, [getPriorItem.list]
	mov rdx, rbx
	add rdx, List.itemMatch			
	mov rcx, [rdx]
	mov [getPriorItem.listItemMatch], rcx	
	mov r11, rcx
	add r11, ItemMatch.item
	mov r12, [getPriorItem.item]
	add r12, ListItem.item
	mov rax, [r12]
	mov [r11], rax
	mov rdx, rbx
	add rdx, List.index
	mov r11, rcx
	add r11, ItemMatch.index
	mov r13, [rdx]
	sub r13, 1b
	mov [r11], r13
	mov r11, rcx
	add r11, ItemMatch.nesting
	mov r12, [getPriorItem.item]	
	add r12, ListItem.nesting
	mov r13, [r12]
	mov [r11], r13

	mov r12, [getPriorItem.item]			; Get List Item's item
	add r12, ListItem.item
	mov rax, [r12]

	getPriorItem.noMatch:

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




list.getNextItemMatch:

	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getNextItemMatch.heapAddress qword at rbp-8  
	label getNextItemMatch.handleAllocatedMemory qword at rbp-16
	label getNextItemMatch.list qword at rbp-24 
	label getNextItemMatch.item qword at rbp-32
	label getNextItemMatch.prevItem qword at rbp-40
	label getNextItemMatch.prevItemIndex qword at rbp-48
	label getNextItemMatch.itemMatch qword at rbp-56
	label getNextItemMatch.listItemMatch qword at rbp-64

	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getNextItemMatch.list], rcx
	mov [getNextItemMatch.itemMatch], rdx



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
	mov [getNextItemMatch.prevItemIndex], rcx		; Begin as 0

	mov rbx, [getNextItemMatch.list]
	add rbx, List.indexItem
	mov rdx, [rbx]
	mov [getNextItemMatch.prevItem], rdx


	mov rbx, [getNextItemMatch.list]
	mov rdx, rbx
	add rbx, List.index
	mov r8, [rbx]
	add rdx, List.indexedItemIndex
	mov r9, [rdx]
	cmp r8, r9
	je getNextItemMatch.atIndexedItem

	mov rbx, [getNextItemMatch.list]			; Get first item when indexed is not cached and retrievable.
	add rbx, List.firstItem
	mov rdx, [rbx]
	mov [getNextItemMatch.prevItem], rdx

	mov rbx, [getNextItemMatch.list]
	add rbx, List.index
	mov rcx, [rbx]
	cmp rcx, 0
	jne getNextItemMatch.nextItem

	.atIndexedItem:

	mov rbx, [getNextItemMatch.prevItem]
	mov [getNextItemMatch.item], rbx		

	jmp getNextItemMatch.lastItemReached

	.nextItem:
	mov rbx, [getNextItemMatch.list]
	add rbx, List.index
	mov rcx, [rbx]
	mov rdx, [getNextItemMatch.prevItemIndex]
	cmp rcx, rdx
	jne getNextItemMatch.lastItemReached


	mov r9, [getNextItemMatch.prevItem]
	add r9, ListItem.next
	mov r10, [r9]
	mov [getNextItemMatch.item], r10

	mov r11, [getNextItemMatch.prevItemIndex]
	add r11, 1b
	mov [getNextItemMatch.prevItemIndex], r11		; Increase prior item index
	
	jmp getNextItemMatch.nextItem

	.lastItemReached:


	mov rbx, [getNextItemMatch.list]			; Advance List index
	add rbx, List.index
	mov r11, [rbx]
	add r11, 1b
	mov [rbx], r11

	mov rbx, [getNextItemMatch.list]			; Advance index item, index item index
	mov rdx, rbx
	add rbx, List.indexItem
	mov r13, [getNextItemMatch.item]
	mov [rbx], r13
	add rdx, List.indexedItemIndex
	mov [rdx], r11

	mov r12, [getNextItemMatch.item]			; Get List Item's item
	add r12, ListItem.item
	mov rax, [r12]
	mov r13, [getNextItemMatch.itemMatch]
	cmp rax, r13
	jne getNextItemMatch.nextItem

	mov r12, [getNextItemMatch.item]	
	cmp r12, 0
	je getNextItemMatch.noMatch

	mov rbx, [getNextItemMatch.list]
	mov rdx, rbx
	add rdx, List.itemMatch			
	mov rcx, [rdx]
	mov [getNextItemMatch.listItemMatch], rcx	
	mov r11, rcx
	add r11, ItemMatch.item
	mov r13, [getNextItemMatch.itemMatch]
	mov [r11], r13
	mov rdx, rbx
	add rdx, List.index
	mov r11, rcx
	add r11, ItemMatch.index
	mov r13, [rdx]
	sub r13, 1b
	mov [r11], r13
	mov r11, rcx
	add r11, ItemMatch.nesting
	mov r12, [getNextItemMatch.item]	
	add r12, ListItem.nesting
	mov r13, [r12]
	mov [r11], r13



	.noMatch:

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


; Components within next match. 
; Assumes match is an address and component value at loc is returned.
list.getNextItemMatchComp:

	push rbp 
	mov rbp, rsp 
	sub rsp, (8*9);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getNextItemMatchComp.heapAddress qword at rbp-8  
	label getNextItemMatchComp.handleAllocatedMemory qword at rbp-16
	label getNextItemMatchComp.list qword at rbp-24 
	label getNextItemMatchComp.item qword at rbp-32
	label getNextItemMatchComp.prevItem qword at rbp-40
	label getNextItemMatchComp.prevItemIndex qword at rbp-48
	label getNextItemMatchComp.itemMatch qword at rbp-56
	label getNextItemMatchComp.listItemMatch qword at rbp-64
	label getNextItemMatchComp.comp qword at rbp-72

	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getNextItemMatchComp.list], rcx
	mov [getNextItemMatchComp.itemMatch], rdx
	mov [getNextItemMatchComp.comp], r8



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
	mov [getNextItemMatchComp.prevItemIndex], rcx		; Begin as 0

	mov rbx, [getNextItemMatchComp.list]
	add rbx, List.indexItem
	mov rdx, [rbx]
	mov [getNextItemMatchComp.prevItem], rdx


	mov rbx, [getNextItemMatchComp.list]
	mov rdx, rbx
	add rbx, List.index
	mov r8, [rbx]
	add rdx, List.indexedItemIndex
	mov r9, [rdx]
	cmp r8, r9
	je getNextItemMatchComp.atIndexedItem

	mov rbx, [getNextItemMatchComp.list]			; Get first item when indexed is not cached and retrievable.
	add rbx, List.firstItem
	mov rdx, [rbx]
	mov [getNextItemMatchComp.prevItem], rdx

	mov rbx, [getNextItemMatchComp.list]
	add rbx, List.index
	mov rcx, [rbx]
	cmp rcx, 0
	jne getNextItemMatchComp.nextItem

	.atIndexedItem:

	mov rbx, [getNextItemMatchComp.prevItem]
	mov [getNextItemMatchComp.item], rbx		

	jmp getNextItemMatchComp.lastItemReached

	.nextItem:
	mov rbx, [getNextItemMatchComp.list]
	add rbx, List.index
	mov rcx, [rbx]
	mov rdx, [getNextItemMatchComp.prevItemIndex]
	cmp rcx, rdx
	jne getNextItemMatchComp.lastItemReached


	mov r9, [getNextItemMatchComp.prevItem]
	add r9, ListItem.next
	mov r10, [r9]
	mov [getNextItemMatchComp.item], r10

	mov r11, [getNextItemMatchComp.prevItemIndex]
	add r11, 1b
	mov [getNextItemMatchComp.prevItemIndex], r11		; Increase prior item index
	
	jmp getNextItemMatchComp.nextItem

	.lastItemReached:


	mov rbx, [getNextItemMatchComp.list]			; Advance List index
	add rbx, List.index
	mov r11, [rbx]
	add r11, 1b
	mov [rbx], r11

	mov rbx, [getNextItemMatchComp.list]			; Advance index item, index item index
	mov rdx, rbx
	add rbx, List.indexItem
	mov r13, [getNextItemMatchComp.item]
	mov [rbx], r13
	add rdx, List.indexedItemIndex
	mov [rdx], r11

	mov r12, [getNextItemMatchComp.item]			; Get List Item's item
	add r12, ListItem.item
	mov rax, [r12]
	mov r13, [getNextItemMatchComp.itemMatch]
	cmp rax, r13
	jne getNextItemMatchComp.nextItem

	mov r12, [getNextItemMatchComp.item]	
	cmp r12, 0
	je getNextItemMatchComp.noMatch

	mov rbx, [getNextItemMatchComp.list]
	mov rdx, rbx
	add rdx, List.itemMatch			
	mov rcx, [rdx]
	mov [getNextItemMatchComp.listItemMatch], rcx	
	mov r11, rcx
	add r11, ItemMatch.item
	mov r13, [getNextItemMatchComp.itemMatch]
	mov [r11], r13
	mov rdx, rbx
	add rdx, List.index
	mov r11, rcx
	add r11, ItemMatch.index
	mov r13, [rdx]
	sub r13, 1b
	mov [r11], r13
	mov r11, rcx
	add r11, ItemMatch.nesting
	mov r12, [getNextItemMatchComp.item]	
	add r12, ListItem.nesting
	mov r13, [r12]
	mov [r11], r13


	mov r8, rax
	add r8, [getNextItemMatchComp.comp]
	mov rax, [r8]

	.noMatch:

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


list.resetIndex:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*5);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label resetIndex.heapAddress qword at rbp-8  
	label resetIndex.handleAllocatedMemory qword at rbp-16
	label resetIndex.list qword at rbp-24 
	label resetIndex.item qword at rbp-32
	label resetIndex.prevItem qword at rbp-40
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [resetIndex.list], rcx



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





	mov rbx, [resetIndex.list]
	mov rdx, rbx
	add rdx, List.index
	mov rcx, 0
	mov [rdx], rcx
	mov rdx, rbx
	add rdx, List.indexedItemIndex
	mov rcx, 0
	mov [rdx], rcx
	mov rdx, rbx
	add rdx, List.firstItem
	mov rcx, 0
	mov r10, [rdx]
	mov r8, rbx
	add r8, List.indexItem
	mov [r8], r10
	



	mov rax,0

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
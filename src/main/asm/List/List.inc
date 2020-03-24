
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
	add rcx, List.itemMatch
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [heapAddress]
	call [ HeapAlloc] 
	mov [handleAllocatedMemory], rax
	add rsp, 8*4


	mov rbx, [handleAllocatedMemory]
	add rbx, List.firstItem
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, List.listSize
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, List.itemsCount
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, List.index
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, List.indexItem
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, List.indexedItemIndex
	mov rax, 0
	mov [rbx], rax
	sub rsp, 8*8
	call newItemMatch
	add rsp, 8*8
	mov rbx, [handleAllocatedMemory]
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

newItemMatch:
namespace newItemMatch
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
	add rcx, List.itemMatch
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [heapAddress]
	call [ HeapAlloc] 
	mov [handleAllocatedMemory], rax
	add rsp, 8*4


	mov rbx, [handleAllocatedMemory]
	add rbx, ItemMatch.item
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, ItemMatch.index
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, ItemMatch.nesting
	mov rax, 0
	mov [rbx], rax


	;lea rax, [list]
	;lea rcx, [list.indexedItemIndex]

	;sub rcx, rax
	;add rcx, 1000b

	;cld

	;lea rsi, [list]
	;mov rdi, [handleAllocatedMemory]

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


newLastItem:
namespace newLastItem
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label list qword at rbp-24 
	label item qword at rbp-32
	label prevItem qword at rbp-40
	label priorIndex qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [list], rcx
	mov [item], rdx


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



	mov rbx, [list]
	add rbx, List.index
	mov r11, [rbx]
	mov [priorIndex], r11		; Restore later

	sub rsp, 8*4
	call [GetProcessHeap]
	mov [heapAddress], rax
	add rsp, 8*4


	mov rcx, 0
	add rcx, ListItem.next
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [heapAddress]
	call [ HeapAlloc] 
	mov [handleAllocatedMemory], rax
	add rsp, 8*4



	mov rbx, [handleAllocatedMemory]
	add rbx, ListItem.item
	mov rax, [item]
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, ListItem.previous
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, ListItem.nesting
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, ListItem.next
	mov rax, 0
	mov [rbx], rax


	mov rbx, [list]
	add rbx, List.itemsCount
	mov rcx, [rbx]
	cmp rcx, 0
	jne firstItemExists
	
	mov rbx, [list]
	add rbx, List.firstItem
	mov rdx, [handleAllocatedMemory]
	mov [rbx], rdx						; Define first item

	mov rbx, [list]
	add rbx, List.indexItem
	mov rdx, [handleAllocatedMemory]
	mov [rbx], rdx						; Define index item

	
	jmp firstItem
	firstItemExists:



	mov rbx, [list]
	add rbx, List.indexItem
	mov rdx, [rbx]
	mov [prevItem], rdx


	mov rbx, [list]
	mov rdx, rbx
	add rbx, List.index
	mov r8, [rbx]
	add rdx, List.indexedItemIndex
	mov r9, [rdx]
	cmp r8, r9
	je nextItem				; Keep using prevItem when indices equal

	mov rbx, [list]			; Get first item when indexed is not cached and retrievable.
	add rbx, List.firstItem
	mov rdx, [rbx]
	mov [prevItem], rdx


	nextItem:
	mov rbx, [list]
	mov rdx, rbx
	add rbx, List.index
	mov rcx, [rbx]
	add rdx, List.itemsCount
	mov r8, [rdx]
	cmp rcx, r8
	jnl lastItemReached


	mov r9, [prevItem]
	add r9, ListItem.next
	mov r10, [r9]
	cmp r10, 0
	je lastItemReached

	mov [prevItem], r10
	mov rbx, [list]
	add rbx, List.index
	mov r11, [rbx]
	add r11, 1b
	mov [rbx], r11

	jmp nextItem
	lastItemReached:


	mov r9, [prevItem]
	mov r8, r9
	add r9, ListItem.next
	mov rdx, [handleAllocatedMemory]
	mov [r9], rdx					; New item as prior item's next
	add rdx, ListItem.previous
	mov [rdx], r8					; Prior item as item's previous


	firstItem:


	mov rbx, [list]
	add rbx, List.itemsCount
	mov r11, [rbx]
	add r11, 1b
	mov [rbx], r11					; Increment items count

	completed:

	mov rbx, [list]
	add rbx, List.index
	mov r11, [priorIndex]		; Restore
	mov [rbx], r11
	

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

getNextItem:
namespace getNextItem
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label listAddress qword at rbp-24 
	label item qword at rbp-32
	label prevItem qword at rbp-40
	label prevItemIndex qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [listAddress], rcx



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


	mov [listAddress], rcx


	mov rbx, [listAddress]
	
	;mov rcx, rbx;[rbx+List.index]
	mov r8, List.index
	add r8, rbx
	mov rcx, [r8]
	mov rax, 0
	cmp rcx, rax
	je retrieveFromFirstItem

	;mov rdx, [rbx+List.indexedItemIndex]
	mov rdx, List.indexedItemIndex
	add rdx, rbx
	mov rdx, [rdx]
	mov rax, 0

	cmp rdx, rax
	je retrieveFromFirstItem

	;cmp rcx, rax
	;jne retrieveFromFirstItem

	;mov rcx, [rbx+List.indexItem]
	mov rcx, List.indexItem
	add rcx, rbx
	mov rcx, [rcx]
	mov rax, 0

	cmp rcx, rax
	je retrieveFromFirstItem		


	;mov rdx, [rbx+List.indexedItemIndex]
	mov rdx, List.indexedItemIndex
	add rdx, rbx
	mov rdx, [rdx]
	;mov rcx, [rbx+List.index]
	mov rcx, List.index
	add rcx, rbx
	mov rcx, [rcx]
	cmp rcx, rdx

	jne retrieveFromFirstItem




	;jne retrieveFromFirstItem
	;mov rax, [rbx+List.index]
	mov rax, List.index
	add rax, rbx
	mov rax, [rax]
	add rax, 1
	mov rbx, [listAddress]
	mov r8, rbx
	add r8, List.indexedItemIndex
	mov qword [r8], rax
	sub rax, 1
	mov rbx, [listAddress]
	;mov rdx, [rbx+List.indexItem]
	mov rdx, List.indexItem
	add rdx, rbx
	mov rdx, [rdx]
	mov r9, rdx
	add r9, ListItem.next
	mov rcx, [r9]
	mov rbx, [listAddress]
	mov r9, rbx
	add r9, List.indexItem
	mov qword [r9], rcx	

	jmp itemReached

	retrieveFromFirstItem:

	mov rbx, [listAddress]
	mov r9, rbx
	add r9, List.index
	mov rcx, [r9]
	mov rax, 0
	mov r9, rbx
	add r9, List.firstItem
	mov rdx, [r9]
	
	cmp rcx, rax
	je itemReached

	itemNotReached:

	mov r9, rdx
	add r9, ListItem.next
	mov rbx, [r9]
	mov rdx, rbx
	add rax, 1
	
	cmp rax, rcx
	jne itemNotReached 


	itemReached:

	add rax, 1
	mov rbx, [listAddress]
	mov r9, rbx
	add r9, List.index
	mov qword [r9], rax
	mov r10, rdx
	add r10, ListItem.item
	mov rax, [r10]
	



	;mov rcx, 0
	;mov [prevItemIndex], rcx		; Begin as 0

	;mov rbx, [list]
	;add rbx, List.indexItem
	;mov rdx, [rbx]
	;mov [prevItem], rdx


	;mov rbx, [list]
	;mov rdx, rbx
	;add rbx, List.index
	;mov r8, [rbx]
	;add rdx, List.indexedItemIndex
	;mov r9, [rdx]
	;cmp r8, r9
	;je atIndexedItem


	;mov rbx, [list]			; Start with first item when indexed is not cached and retrievable.
	;add rbx, List.firstItem
	;mov rdx, [rbx]
	;mov [prevItem], rdx

	;mov rbx, [list]
	;add rbx, List.index
	;mov rcx, [rbx]
	;cmp rcx, 0
	;jne nextItem

	;atIndexedItem:

	;mov rbx, [prevItem]
	;mov [item], rbx		

	;jmp lastItemReached

	;nextItem:
	;mov rbx, [list]
	;add rbx, List.index
	;mov rcx, [rbx]
	;mov rdx, [prevItemIndex]
	;cmp rcx, rdx
	;jne lastItemReached


	;mov r9, [prevItem]
	;add r9, ListItem.next
	;mov r10, [r9]
	;mov [item], r10

	;mov r11, [prevItemIndex]
	;add r11, 1b
	;mov [prevItemIndex], r11		; Increase prior item index
	
	;jmp nextItem

	;lastItemReached:


	;mov rbx, [list]			; Advance List index
	;add rbx, List.index
	;mov r11, [rbx]
	;add r11, 1b
	;mov [rbx], r11


	;mov r8, [list] 
	;add r8, List.itemsCount
	;mov r9, [r8]
	;cmp r11, r9
	;jnl maintainIndexedItem
		
	;mov r9, [item]
	;add r9, ListItem.next
	;mov r10, [r9]
	;mov r13, r10
	;mov rbx, [list]
	;mov rdx, rbx
	;add rbx, List.indexItem

	;jmp advanceOrMaintainIndexItem	

	;.maintainIndexedItem:				; Do not advance (Helpful when only one item so not cleared)

	;mov rbx, [list]			; Define index item, advance index item index
	;mov rdx, rbx
	;add rbx, List.indexItem
	;mov r13, [item]

	;.advanceOrMaintainIndexItem:
	;mov [rbx], r13
	;add rdx, List.indexedItemIndex
	;mov [rdx], r11

	;mov r12, [item]			; Get List Item's item
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
end namespace


; Gets Last Items diverged Item which is one nesting level higher
getLastDivergedItem:
namespace getLastDivergedItem
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label listAddress qword at rbp-24 
	label item qword at rbp-32
	label prevItem qword at rbp-40
	label prevItemIndex qword at rbp-48
	label itemNesting qword at rbp-56
	label prevItemNesting qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [listAddress], rcx




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
	mov [prevItemNesting], rcx		; Begin as 0
	mov [prevItem], rcx


	mov rbx, [listAddress]
	mov r8, rbx
	add rbx, List.itemsCount
	add r8, List.index
	mov rdx, [rbx]
	sub rdx, 1b
	mov [r8], rdx

	sub rsp, 8*8
	mov rcx, [listAddress]
	call getNextItemNesting
	add rsp, 8*8
	mov [itemNesting], rax



	mov rbx, [listAddress]
	mov r8, rbx
	add rbx, List.itemsCount
	add r8, List.index
	mov rdx, [rbx]
	sub rdx, 10b
	mov [r8], rdx

	getPriorItem:
	mov rbx, [listAddress]
	add rbx, List.index
	mov rdx, [rbx]
	cmp rdx, 0
	jl completed

	sub rsp, 8*8
	mov rcx, [listAddress]
	call getNextItemNesting
	add rsp, 8*8
	mov [prevItemNesting], rax

	sub rsp, 8*8
	mov rcx, [listAddress]
	call getNextItem
	add rsp, 8*8
	mov [prevItem], rax

	mov rbx, [prevItemNesting]
	mov rcx, [itemNesting]
	sub rcx, rbx
	mov r8, 1b
	cmp rcx, r8
	je completed			; Must be 1 less

	mov rbx, [listAddress]
	add rbx, List.index
	mov rdx, [rbx]
	sub rdx, 10b
	mov [rbx], rdx					; Get prior index

	jmp getPriorItem
	completed:

	mov rax, [prevItem]

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

; Gets Last Items diverged Item nesting which is one nesting level higher
getLastDivergedItemNesting:
namespace getLastDivergedItemNesting
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label listAddress qword at rbp-24 
	label item qword at rbp-32
	label prevItem qword at rbp-40
	label prevItemIndex qword at rbp-48
	label itemNesting qword at rbp-56
	label prevItemNesting qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [listAddress], rcx



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
	mov [prevItemNesting], rcx		; Begin as 0
	mov [prevItem], rcx

	mov rbx, [listAddress]
	mov r8, rbx
	add rbx, List.itemsCount
	add r8, List.index
	mov rdx, [rbx]
	sub rdx, 1b
	mov [r8], rdx

	sub rsp, 8*8
	mov rcx, [listAddress]
	call getNextItemNesting
	add rsp, 8*8
	mov [itemNesting], rax

	mov rbx, [listAddress]
	mov r8, rbx
	add rbx, List.itemsCount
	add r8, List.index
	mov rdx, [rbx]
	sub rdx, 10b
	mov [r8], rdx

	getPriorItem:
	mov rbx, [listAddress]
	add rbx, List.index
	mov rdx, [rbx]
	cmp rdx, 0
	jl completed

	sub rsp, 8*8
	mov rcx, [listAddress]
	call getNextItemNesting
	add rsp, 8*8
	mov [prevItemNesting], rax

	sub rsp, 8*8
	mov rcx, [listAddress]
	call getNextItem
	add rsp, 8*8
	mov [prevItem], rax

	mov rbx, [prevItemNesting]
	mov rcx, [itemNesting]
	sub rcx, rbx
	mov r8, 1b
	cmp rcx, r8
	je completed			; Must be 1 less

	mov rbx, [listAddress]
	add rbx, List.index
	mov rdx, [rbx]
	sub rdx, 10b
	mov [rbx], rdx					; Get prior index

	jmp getPriorItem
	completed:

	mov rax, [prevItemNesting]




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

; Gets Count of Items one level nested beneath index
getConvergedItemCount:
namespace getConvergedItemCount
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*9);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label listAddress qword at rbp-24 
	label item qword at rbp-32
	label nextItem qword at rbp-40
	label prevItemIndex qword at rbp-48
	label itemNesting qword at rbp-56
	label nextItemNesting qword at rbp-64
	label convergedCount qword at rbp-72
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [listAddress], rcx




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
	mov [nextItemNesting], rcx		; Begin as 0
	mov [nextItem], rcx
	mov [convergedCount], rcx


	sub rsp, 8*8
	mov rcx, [listAddress]
	call getNextItemNesting
	add rsp, 8*8
	mov [itemNesting], rax

	mov rbx, [listAddress]
	add rbx, List.index
	mov rdx, [rbx]
	add rdx, 1b
	mov [rbx], rdx


	nextListItem:
	mov rbx, [listAddress]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov rcx, [rbx]
	mov r8, [rdx]
	cmp rcx, r8
	jnl completed

	sub rsp, 8*8
	mov rcx, [listAddress]
	call getNextItemNesting
	add rsp, 8*8
	mov [nextItemNesting], rax

	sub rsp, 8*8
	mov rcx, [listAddress]
	call getNextItem
	add rsp, 8*8
	mov [nextItem], rax

	mov rbx, [nextItemNesting]
	mov rcx, [itemNesting]
	sub rbx, rcx
	mov r8, 1b
	mov r8, 0
	cmp rbx, r8
	jle completed				; No more, diverged (nesting at a tangent or higher)
	mov r8, 1b
	cmp rbx, r8
	jne nextListItem			; Must be 1

	mov r9, [convergedCount]
	add r9, 1b
	mov [convergedCount], r9		; Increment

	jmp nextListItem
	completed:

	mov rax, [convergedCount]

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

; Gets Next Item at a determined nesting level
getNextTangentItem:
namespace getNextTangentItem
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*9);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label listAddress qword at rbp-24 
	label item qword at rbp-32
	label nextItem qword at rbp-40
	label prevItemIndex qword at rbp-48
	label itemNesting qword at rbp-56
	label nextItemNesting qword at rbp-64
	label convergedCount qword at rbp-72
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [listAddress], rcx
	mov [itemNesting], rdx




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
	mov [nextItemNesting], rcx		; Begin as 0
	mov [nextItem], rcx
	mov [convergedCount], rcx





	nextListItem:
	mov rbx, [listAddress]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov rcx, [rbx]
	mov r8, [rdx]
	cmp rcx, r8
	jnl completed

	sub rsp, 8*8
	mov rcx, [listAddress]
	call getNextItemNesting
	add rsp, 8*8
	mov [nextItemNesting], rax

	sub rsp, 8*8
	mov rcx, [listAddress]
	call getNextItem
	add rsp, 8*8
	mov [nextItem], rax

	mov rbx, [nextItemNesting]
	mov rcx, [itemNesting]
	cmp rbx, rcx
	je completed	

	jmp nextListItem
	completed:

	mov rax, [nextItem]

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

; Does not advance List index
getNextItemNesting:
namespace getNextItemNesting
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label listAddress qword at rbp-24 
	label item qword at rbp-32
	label prevItem qword at rbp-40
	label prevItemIndex qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [listAddress], rcx



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



	mov [listAddress], rcx


	mov rbx, [listAddress]
	
	;mov rcx, rbx;[rbx+List.index]
	mov r8, List.index
	add r8, rbx
	mov rcx, [r8]
	mov rax, 0
	cmp rcx, rax
	je retrieveFromFirstItem

	;mov rdx, [rbx+List.indexedItemIndex]
	mov rdx, List.indexedItemIndex
	add rdx, rbx
	mov rdx, [rdx]
	mov rax, 0

	cmp rdx, rax
	je retrieveFromFirstItem

	;cmp rcx, rax
	;jne retrieveFromFirstItem

	;mov rcx, [rbx+List.indexItem]
	mov rcx, List.indexItem
	add rcx, rbx
	mov rcx, [rcx]
	mov rax, 0

	cmp rcx, rax
	je retrieveFromFirstItem		


	;mov rdx, [rbx+List.indexedItemIndex]
	mov rdx, List.indexedItemIndex
	add rdx, rbx
	mov rdx, [rdx]
	;mov rcx, [rbx+List.index]
	mov rcx, List.index
	add rcx, rbx
	mov rcx, [rcx]
	cmp rcx, rdx

	jne retrieveFromFirstItem




	;jne retrieveFromFirstItem
	;mov rax, [rbx+List.index]
	mov rax, List.index
	add rax, rbx
	mov rax, [rax]
	add rax, 1
	mov rbx, [listAddress]
	mov r8, rbx
	add r8, List.indexedItemIndex
	mov qword [r8], rax
	sub rax, 1
	mov rbx, [listAddress]
	;mov rdx, [rbx+List.indexItem]
	mov rdx, List.indexItem
	add rdx, rbx
	mov rdx, [rdx]
	mov r9, rdx
	add r9, ListItem.next
	mov rcx, [r9]
	mov rbx, [listAddress]
	mov r9, rbx
	add r9, List.indexItem
	mov qword [r9], rcx	

	jmp itemReached

	retrieveFromFirstItem:

	mov rbx, [listAddress]
	mov r9, rbx
	add r9, List.index
	mov rcx, [r9]
	mov rax, 0
	mov r9, rbx
	add r9, List.firstItem
	mov rdx, [r9]
	
	cmp rcx, rax
	je itemReached

	itemNotReached:

	mov r9, rdx
	add r9, ListItem.next
	mov rbx, [r9]
	mov rdx, rbx
	add rax, 1
	
	cmp rax, rcx
	jne itemNotReached 


	itemReached:

	;add rax, 1						; Do not advance index
	mov rbx, [listAddress]
	mov r9, rbx
	add r9, List.index
	mov qword [r9], rax
	mov r10, rdx
	add r10, ListItem.nesting
	mov rax, [r10]
	



	;mov rcx, 0
	;mov [prevItemIndex], rcx		; Begin as 0

	;mov rbx, [list]
	;add rbx, List.indexItem
	;mov rdx, [rbx]
	;mov [prevItem], rdx


	;mov rbx, [list]
	;mov rdx, rbx
	;add rbx, List.index
	;mov r8, [rbx]
	;add rdx, List.indexedItemIndex
	;mov r9, [rdx]
	;cmp r8, r9
	;je atIndexedItem


	;mov rbx, [list]			; Start with first item when indexed is not cached and retrievable.
	;add rbx, List.firstItem
	;mov rdx, [rbx]
	;mov [prevItem], rdx

	;mov rbx, [list]
	;add rbx, List.index
	;mov rcx, [rbx]
	;cmp rcx, 0
	;jne nextItem

	;atIndexedItem:

	;mov rbx, [prevItem]
	;mov [item], rbx		

	;jmp lastItemReached

	;nextItem:
	;mov rbx, [list]
	;add rbx, List.index
	;mov rcx, [rbx]
	;mov rdx, [prevItemIndex]
	;cmp rcx, rdx
	;jne lastItemReached


	;mov r9, [prevItem]
	;add r9, ListItem.next
	;mov r10, [r9]
	;mov [item], r10

	;mov r11, [prevItemIndex]
	;add r11, 1b
	;mov [prevItemIndex], r11		; Increase prior item index
	
	;jmp nextItem

	;lastItemReached:


	;mov rbx, [list]			; Advance List index
	;add rbx, List.index
	;mov r11, [rbx]
	;add r11, 1b
	;mov [rbx], r11


	;mov r8, [list] 
	;add r8, List.itemsCount
	;mov r9, [r8]
	;cmp r11, r9
	;jnl maintainIndexedItem
		
	;mov r9, [item]
	;add r9, ListItem.next
	;mov r10, [r9]
	;mov r13, r10
	;mov rbx, [list]
	;mov rdx, rbx
	;add rbx, List.indexItem

	;jmp advanceOrMaintainIndexItem	

	;.maintainIndexedItem:				; Do not advance (Helpful when only one item so not cleared)

	;mov rbx, [list]			; Define index item, advance index item index
	;mov rdx, rbx
	;add rbx, List.indexItem
	;mov r13, [item]

	;.advanceOrMaintainIndexItem:
	;mov [rbx], r13
	;add rdx, List.indexedItemIndex
	;mov [rdx], r11

	;mov r12, [item]			; Get List Item's item
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
end namespace

nextItemNesting:
namespace nextItemNesting
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*7);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label listAddress qword at rbp-24 
	label item qword at rbp-32
	label prevItem qword at rbp-40
	label prevItemIndex qword at rbp-48
	label nesting qword at rbp-56
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [listAddress], rcx
	mov [nesting], rdx




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



	mov [listAddress], rcx


	mov rbx, [listAddress]
	
	;mov rcx, rbx;[rbx+List.index]
	mov r8, List.index
	add r8, rbx
	mov rcx, [r8]
	mov rax, 0
	cmp rcx, rax
	je retrieveFromFirstItem

	;mov rdx, [rbx+List.indexedItemIndex]
	mov rdx, List.indexedItemIndex
	add rdx, rbx
	mov rdx, [rdx]
	mov rax, 0

	cmp rdx, rax
	je retrieveFromFirstItem

	;cmp rcx, rax
	;jne retrieveFromFirstItem

	;mov rcx, [rbx+List.indexItem]
	mov rcx, List.indexItem
	add rcx, rbx
	mov rcx, [rcx]
	mov rax, 0

	cmp rcx, rax
	je retrieveFromFirstItem		


	;mov rdx, [rbx+List.indexedItemIndex]
	mov rdx, List.indexedItemIndex
	add rdx, rbx
	mov rdx, [rdx]
	;mov rcx, [rbx+List.index]
	mov rcx, List.index
	add rcx, rbx
	mov rcx, [rcx]
	cmp rcx, rdx

	jne retrieveFromFirstItem




	;jne retrieveFromFirstItem
	;mov rax, [rbx+List.index]
	mov rax, List.index
	add rax, rbx
	mov rax, [rax]
	add rax, 1
	mov rbx, [listAddress]
	mov r8, rbx
	add r8, List.indexedItemIndex
	mov qword [r8], rax
	sub rax, 1
	mov rbx, [listAddress]
	;mov rdx, [rbx+List.indexItem]
	mov rdx, List.indexItem
	add rdx, rbx
	mov rdx, [rdx]
	mov r9, rdx
	add r9, ListItem.next
	mov rcx, [r9]
	mov rbx, [listAddress]
	mov r9, rbx
	add r9, List.indexItem
	mov qword [r9], rcx	

	jmp itemReached

	retrieveFromFirstItem:

	mov rbx, [listAddress]
	mov r9, rbx
	add r9, List.index
	mov rcx, [r9]
	mov rax, 0
	mov r9, rbx
	add r9, List.firstItem
	mov rdx, [r9]
	
	cmp rcx, rax
	je itemReached

	itemNotReached:

	mov r9, rdx
	add r9, ListItem.next
	mov rbx, [r9]
	mov rdx, rbx
	add rax, 1
	
	cmp rax, rcx
	jne itemNotReached 


	itemReached:

	;add rax, 1					; Do not advance
	mov rbx, [listAddress]
	mov r9, rbx
	add r9, List.index
	mov qword [r9], rax
	mov r10, rdx
	add r10, ListItem.nesting
	mov r13, [nesting]		; List Item's nesting
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
end namespace

lastItemNesting:
namespace lastItemNesting
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*7);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label listAddress qword at rbp-24 
	label item qword at rbp-32
	label prevItem qword at rbp-40
	label prevItemIndex qword at rbp-48
	label nesting qword at rbp-56
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [listAddress], rcx
	mov [nesting], rdx




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



	mov [listAddress], rcx

	sub rsp, 8*8
	mov rcx, [listAddress]
	call resetIndex
	add rsp, 8*8


	mov rbx, [listAddress]
	mov rdx, rbx
	add rbx, List.itemsCount
	add rdx, List.index
	mov rcx, [rbx]
	sub rcx, 1b
	mov [rdx], rcx
	

	mov rbx, [listAddress]
	
	;mov rcx, rbx;[rbx+List.index]
	mov r8, List.index
	add r8, rbx
	mov rcx, [r8]
	mov rax, 0
	cmp rcx, rax
	je retrieveFromFirstItem

	;mov rdx, [rbx+List.indexedItemIndex]
	mov rdx, List.indexedItemIndex
	add rdx, rbx
	mov rdx, [rdx]
	mov rax, 0

	cmp rdx, rax
	je retrieveFromFirstItem

	;cmp rcx, rax
	;jne retrieveFromFirstItem

	;mov rcx, [rbx+List.indexItem]
	mov rcx, List.indexItem
	add rcx, rbx
	mov rcx, [rcx]
	mov rax, 0

	cmp rcx, rax
	je retrieveFromFirstItem		


	;mov rdx, [rbx+List.indexedItemIndex]
	mov rdx, List.indexedItemIndex
	add rdx, rbx
	mov rdx, [rdx]
	;mov rcx, [rbx+List.index]
	mov rcx, List.index
	add rcx, rbx
	mov rcx, [rcx]
	cmp rcx, rdx

	jne retrieveFromFirstItem




	;jne retrieveFromFirstItem
	;mov rax, [rbx+List.index]
	mov rax, List.index
	add rax, rbx
	mov rax, [rax]
	add rax, 1
	mov rbx, [listAddress]
	mov r8, rbx
	add r8, List.indexedItemIndex
	mov qword [r8], rax
	sub rax, 1
	mov rbx, [listAddress]
	;mov rdx, [rbx+List.indexItem]
	mov rdx, List.indexItem
	add rdx, rbx
	mov rdx, [rdx]
	mov r9, rdx
	add r9, ListItem.next
	mov rcx, [r9]
	mov rbx, [listAddress]
	mov r9, rbx
	add r9, List.indexItem
	mov qword [r9], rcx	

	jmp itemReached

	retrieveFromFirstItem:

	mov rbx, [listAddress]
	mov r9, rbx
	add r9, List.index
	mov rcx, [r9]
	mov rax, 0
	mov r9, rbx
	add r9, List.firstItem
	mov rdx, [r9]
	
	cmp rcx, rax
	je itemReached

	itemNotReached:

	mov r9, rdx
	add r9, ListItem.next
	mov rbx, [r9]
	mov rdx, rbx
	add rax, 1
	
	cmp rax, rcx
	jne itemNotReached 


	itemReached:

	;add rax, 1					; Do not advance
	mov rbx, [listAddress]
	mov r9, rbx
	add r9, List.index
	mov qword [r9], rax
	mov r10, rdx
	add r10, ListItem.nesting
	mov r13, [nesting]		; List Item's nesting
	mov [r10], r13
	
	sub rsp, 8*8
	mov rcx, [listAddress]
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
end namespace


; New Item at index, not necessarily last index;
newNextItem:
namespace newNextItem
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*15);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label hHeap qword at rbp-8  
	label hAllocatedMemory qword at rbp-16
	label listAddress qword at rbp-24 
	label item qword at rbp-32
	label prevItem qword at rbp-40
	label prevItemIndex qword at rbp-48
	label newItemAddress qword at rbp-56
	label prevItemNext qword at rbp-64
	label nextItemPrev qword at rbp-72
	label newItemIndex qword at rbp-80
	label newListItem qword at rbp-88
	label itemSize qword at rbp-96
	label afterNewItemAddress qword at rbp-104
	label beforeNewItemAddress qword at rbp-112
	label beforeNewItemNesting qword at rbp-120
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [listAddress], rcx
	mov [newItemAddress], rdx



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


	mov rbx, [listAddress]
	mov r8, rbx
	add r8, List.itemsCount
	mov rcx, [r8]
	mov rax, 0


	cmp rcx, rax
	jne listNotBlank					; New First Item?

	mov rdx, [newItemAddress]
	mov rcx, [listAddress]
	sub rsp, 8*8
	call newLastItem
	add rsp, 8*8
	;add rsp, 16

	mov rbx, [listAddress]
	mov r8, rbx
	add r8, List.index
	mov qword [r8], 0 					; For chaining

	jmp newNextItemFailed

	listNotBlank:						; Already checked blank
	mov rbx, [listAddress]
	mov r8, rbx
	add r8, List.itemsCount
	mov rcx, [r8]
	mov r9, rbx
	add r9, List.index	
	mov rax, [r9]

	cmp rcx, rax
	jne notLastItem					; New Last Item?

	mov rdx, [newItemAddress]
	mov rcx, [listAddress]
	sub rsp, 8*8
	call newLastItem
	add rsp, 8*8
	;add rsp, 16

	mov rbx, [listAddress]
	mov r8, rbx
	add r8, List.index
	mov qword [r8], 0 					; For chaining

	jmp newNextItemFailed

	notLastItem:
	mov rbx, [listAddress]
	mov r9, rbx
	add r9, List.index
	mov rcx, [r9]
	mov [newItemIndex], rcx

	mov rcx, 0
	add rcx, ListItem.next
	add rcx, 1000b
	mov [itemSize], rcx		; Calculate item size

	sub rsp, 8*4
	call [GetProcessHeap]
	add rsp, 8*4
	cmp rax, 0
	je newNextItemFailed
	mov [hHeap], rax				; Get Heap

	; Reserve new item struc space
	sub rsp, 8*4	
	mov r8, [itemSize]
	mov rdx, 000001000b
	mov rcx, [hHeap]
	call [HeapAlloc] 
	add rsp, 8*4
	cmp rax, 0
	je newNextItemFailed
	mov [hAllocatedMemory], rax 		; New item allocated

	cmp rax, 0
	jne allocated


	; Error

	allocated:


	mov rbx, [listAddress]
	
	mov r9, rbx
	add r9, List.index
	mov rcx, [r9]
	mov rax, 0

	mov r8, rbx
	add r8, List.firstItem
	mov rdx, [r8]
	
	cmp rcx, rax						; Index 0?
	je afterNewItemReached

	afterNewItemNotReached:

	mov r10, rdx
	add r10, ListItem.next
	mov rbx, [r10]
	mov rdx, rbx
	add rax, 1
	
	cmp rax, rcx
	jne afterNewItemNotReached


	afterNewItemReached:

	add rax, 1						; Destination Index?
	mov rbx, [listAddress]
	mov r8, rbx
	add r8, List.index
	mov qword [r8], rax				; After current item index?

	mov r9, rbx
	add r9, List.indexedItemIndex
	mov qword [r9], rax		;These may introduce problems
	mov r9, rbx
	add r9, List.indexItem
	mov qword [r9], rdx			;These may introduce problems	; First item or next?

	mov [afterNewItemAddress], rdx
	mov r8, rdx
	add r8, ListItem.previous
	mov rbx, [r8]

	mov rax, 0
	cmp rbx, rax
	jne notReplacingFirstItem

	mov [beforeNewItemAddress], rbx		; 0
	mov r8, rdx
	add r8, ListItem.nesting
	mov rax, [r8] 			; Use next's
	mov [beforeNewItemNesting], rax

	jmp firstReplaced

	notReplacingFirstItem:

	mov [beforeNewItemAddress], rbx
	mov r8, rbx
	add r8, ListItem.nesting
	mov rdx, [r8]
	mov [beforeNewItemNesting], rdx

	firstReplaced: 

	mov rdx, [beforeNewItemAddress]
	mov rbx, [afterNewItemAddress]

	mov r11, [hAllocatedMemory]
	add r11, ListItem.previous
	mov [r11], rdx
	mov r11, [hAllocatedMemory]
	add r11, ListItem.next
	mov [r11], rbx
	mov rbx, [beforeNewItemNesting]
	mov r11, [hAllocatedMemory]
	add r11, ListItem.nesting
	mov [r11], rbx
	mov rax, [newItemAddress]
	mov r11, [hAllocatedMemory]
	add r11, ListItem.item
	mov [r11], rax


	; Set following List Item addresses	
	mov rbx, [afterNewItemAddress]
	mov rdx, [hAllocatedMemory]
	mov r8, rbx
	add r8, ListItem.previous
	mov qword [r8], rdx

	mov rcx, [newItemIndex]
	cmp rcx, 0
	jne newNextItemNotFirstItem

	; Set list's first item
	mov rbx, [hAllocatedMemory]

	mov rax, [listAddress]	
	mov r8, rax
	add r8, List.firstItem
	mov qword [r8], rbx

	jmp increaseItemsCount

	newNextItemNotFirstItem:
	mov rdx, [hAllocatedMemory]
	mov rbx, [beforeNewItemAddress]	
	mov r9, rbx
	add r9, ListItem.next
	mov qword [r9], rdx

	increaseItemsCount:

	mov rbx, [listAddress]
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

	;mov rbx, [listAddress]
	;mov rax, [rbx+List.index]
	;inc rax
	;mov [rbx+List.index], rax

	newNextItemFailed:

	mov rax, [listAddress]









	;mov rcx, 0
	;mov [prevItemIndex], rcx		; Begin as 0
	;mov [prevItemNext], rcx


	;sub rsp, 8*4
	;call [GetProcessHeap]
	;mov [heapAddress], rax
	;add rsp, 8*4


	;mov rcx, 0
	;add rcx, ListItem.next
	;add rcx, 1000b

	;sub rsp, 8*4
	;mov r8, rcx		
	;mov rdx, 000001000b
	;mov rcx, [heapAddress]
	;call [ HeapAlloc] 
	;mov [handleAllocatedMemory], rax
	;add rsp, 8*4


	;mov rbx, [list]
	;add rbx, List.indexItem
	;mov rdx, [rbx]
	;mov [prevItem], rdx


	;mov rbx, [list]
	;mov rdx, rbx
	;add rbx, List.index
	;mov r8, [rbx]
	;add rdx, List.indexedItemIndex
	;mov r9, [rdx]
	;cmp r8, r9
	;je atIndexedItem

	;mov rbx, [list]			; Get first item when indexed is not cached and retrievable.
	;add rbx, List.firstItem
	;mov rdx, [rbx]
	;mov [prevItem], rdx

	;mov rbx, [list]
	;add rbx, List.index
	;mov rcx, [rbx]
	;cmp rcx, 0
	;jne nextItem

	;atIndexedItem:

	;mov rbx, [prevItem]
	;mov [item], rbx		

	;jmp indexReached

	;nextItem:
	;mov rbx, [list]
	;add rbx, List.index
	;mov rcx, [rbx]
	;mov rdx, [prevItemIndex]
	;cmp rcx, rdx
	;jne indexReached


	;mov r9, [prevItem]
	;add r9, ListItem.next
	;mov r10, [r9]
	;mov [item], r10

	;mov r11, [prevItemIndex]
	;add r11, 1b
	;mov [prevItemIndex], r11		; Increase prior item index
	
	;jmp nextItem

	;indexReached:


	;mov rbx, [item]
	;add rbx, ListItem.next
	;mov rdx, [rbx]
	;cmp rdx, 0
	;je noNextItem

	;mov [prevItemNext], rdx	
	;add rdx, ListItem.previous
	;mov [nextItemPrev], rdx		; Cache index. May remove this.
	;mov rax, [handleAllocatedMemory]
	;mov [rdx], rax

	;noNextItem:


	;mov rbx, [list]			; Advance List index
	;add rbx, List.index
	;mov r11, [rbx]
	;add r11, 1b
	;mov [rbx], r11





	;mov rbx, [handleAllocatedMemory]
	;add rbx, ListItem.item
	;mov rax, [newItem]
	;mov [rbx], rax
	;mov rbx, [handleAllocatedMemory]
	;add rbx, ListItem.previous
	;mov rax, [item]
	;mov [rbx], rax
	;mov rbx, [handleAllocatedMemory]
	;add rbx, ListItem.nesting
	;mov rax, 0
	;mov [rbx], rax
	;mov rbx, [handleAllocatedMemory]
	;add rbx, ListItem.next
	;mov rax, [prevItemNext]
	;mov [rbx], rax





	;mov rbx, [list]			; Increase items count
	;add rbx, List.itemsCount
	;mov r11, [rbx]
	;add r11, 1b
	;mov [rbx], r11


	;mov rbx, [list]			; Advance index item, index item index
	;mov rdx, rbx
	;add rbx, List.indexItem
	;mov r13, [handleAllocatedMemory]
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
end namespace

getPriorItem:
namespace getPriorItem
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*7);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label list qword at rbp-24 
	label item qword at rbp-32
	label prevItem qword at rbp-40
	label prevItemIndex qword at rbp-48
	label listItemMatch qword at rbp-56
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [list], rcx



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
	mov [prevItemIndex], rcx		; Begin as 0

	mov rbx, [list]
	add rbx, List.indexItem
	mov rdx, [rbx]
	mov [prevItem], rdx


	mov rbx, [list]
	mov rdx, rbx
	add rbx, List.index
	mov r8, [rbx]
	add rdx, List.indexedItemIndex
	mov r9, [rdx]
	cmp r8, r9
	je atIndexedItem

	mov rbx, [list]			; Get first item when indexed is not cached and retrievable.
	add rbx, List.firstItem
	mov rdx, [rbx]
	mov [prevItem], rdx

	mov rbx, [list]
	add rbx, List.index
	mov rcx, [rbx]
	cmp rcx, 0
	jne nextItem

	atIndexedItem:

	mov rbx, [prevItem]
	mov [item], rbx		

	jmp lastItemReached

	nextItem:
	mov rbx, [list]
	add rbx, List.index
	mov rcx, [rbx]
	mov rdx, [prevItemIndex]
	cmp rcx, rdx
	jne lastItemReached


	mov r9, [prevItem]
	add r9, ListItem.next
	mov r10, [r9]
	mov [item], r10

	mov r11, [prevItemIndex]
	add r11, 1b
	mov [prevItemIndex], r11		; Increase prior item index
	
	jmp nextItem

	lastItemReached:

	mov r13, [item]
	add r13, ListItem.previous
	mov rax, [r13]
	mov [item], rax	
	cmp rax, 0
	je completed



	mov rbx, [list]			; Decrease List index
	add rbx, List.index
	mov r11, [rbx]
	sub r11, 1b
	mov [rbx], r11

	mov rbx, [list]			; Cache index item, index item index
	mov rdx, rbx
	add rbx, List.indexItem
	mov r13, [item]
	mov [rbx], r13
	add rdx, List.indexedItemIndex
	mov [rdx], r11


	completed:

	mov r12, [item]	
	cmp r12, 0
	je noMatch

	mov rbx, [list]
	mov rdx, rbx
	add rdx, List.itemMatch			
	mov rcx, [rdx]
	mov [listItemMatch], rcx	
	mov r11, rcx
	add r11, ItemMatch.item
	mov r12, [item]
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
	mov r12, [item]	
	add r12, ListItem.nesting
	mov r13, [r12]
	mov [r11], r13

	mov r12, [item]			; Get List Item's item
	add r12, ListItem.item
	mov rax, [r12]

	noMatch:

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



getNextItemMatch:
namespace getNextItemMatch
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label list qword at rbp-24 
	label item qword at rbp-32
	label prevItem qword at rbp-40
	label prevItemIndex qword at rbp-48
	label itemMatch qword at rbp-56
	label listItemMatch qword at rbp-64

	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [list], rcx
	mov [itemMatch], rdx



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
	mov [prevItemIndex], rcx		; Begin as 0

	mov rbx, [list]
	add rbx, List.indexItem
	mov rdx, [rbx]
	mov [prevItem], rdx


	mov rbx, [list]
	mov rdx, rbx
	add rbx, List.index
	mov r8, [rbx]
	add rdx, List.indexedItemIndex
	mov r9, [rdx]
	cmp r8, r9
	je atIndexedItem

	mov rbx, [list]			; Get first item when indexed is not cached and retrievable.
	add rbx, List.firstItem
	mov rdx, [rbx]
	mov [prevItem], rdx

	mov rbx, [list]
	add rbx, List.index
	mov rcx, [rbx]
	cmp rcx, 0
	jne nextItem

	atIndexedItem:

	mov rbx, [prevItem]
	mov [item], rbx		

	jmp lastItemReached

	nextItem:
	mov rbx, [list]
	add rbx, List.index
	mov rcx, [rbx]
	mov rdx, [prevItemIndex]
	cmp rcx, rdx
	jne lastItemReached


	mov r9, [prevItem]
	add r9, ListItem.next
	mov r10, [r9]
	mov [item], r10

	mov r11, [prevItemIndex]
	add r11, 1b
	mov [prevItemIndex], r11		; Increase prior item index
	
	jmp nextItem

	lastItemReached:


	mov rbx, [list]			; Advance List index
	add rbx, List.index
	mov r11, [rbx]
	add r11, 1b
	mov [rbx], r11

	mov rbx, [list]			; Advance index item, index item index
	mov rdx, rbx
	add rbx, List.indexItem
	mov r13, [item]
	mov [rbx], r13
	add rdx, List.indexedItemIndex
	mov [rdx], r11

	mov r12, [item]			; Get List Item's item
	add r12, ListItem.item
	mov rax, [r12]
	mov r13, [itemMatch]
	cmp rax, r13
	jne nextItem

	mov r12, [item]	
	cmp r12, 0
	je noMatch

	mov rbx, [list]
	mov rdx, rbx
	add rdx, List.itemMatch			
	mov rcx, [rdx]
	mov [listItemMatch], rcx	
	mov r11, rcx
	add r11, ItemMatch.item
	mov r13, [itemMatch]
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
	mov r12, [item]	
	add r12, ListItem.nesting
	mov r13, [r12]
	mov [r11], r13



	noMatch:

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

;------------
;   Gets the next item match index in a list
;   Uses the List index value as a starting position
;   Leaves the List index advanced at the next item.
;   Takes List address, item as parameters.
;   Returns the item index or the item count when not found.
;------------
getNextItemMatchIndex:
namespace getNextItemMatchIndex
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*4);((8)+(8))

	;mov rcx, rcx 
	
	label listAddress qword at rbp-8 
	label item qword at rbp-16 
	label itemMatchIndex qword at rbp-24 
	label itemMatch qword at rbp-32 

	
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

	mov [listAddress], rcx
	mov [item], rdx


	
	mov rbx, [listAddress]
	add rbx, List.itemsCount
	mov rcx, [rbx]
	mov [itemMatchIndex], rcx				; Begin as item count


	nextItem:

	mov rbx, [listAddress]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov r8, [rbx]
	mov r9, [rdx]
	cmp r8, r9
	jnl completed
	
	sub rsp, 8*8
	mov rcx, [listAddress]
	call getNextItem
	add rsp, 8*8
	mov r10, [item]
	cmp rax, r10
	jne nextItem

	mov rcx, [listAddress]
	add rcx, List.index
	mov r12, [rcx]
	sub r12, 1b	

	mov [itemMatchIndex], r12				; Match found


	completed:

	mov rax, [itemMatchIndex]

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


; Components within next match. 
; Assumes match is an address and component value at loc is returned.
getNextItemMatchComp:
namespace getNextItemMatchComp

	push rbp 
	mov rbp, rsp 
	sub rsp, (8*9);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label list qword at rbp-24 
	label item qword at rbp-32
	label prevItem qword at rbp-40
	label prevItemIndex qword at rbp-48
	label itemMatch qword at rbp-56
	label listItemMatch qword at rbp-64
	label comp qword at rbp-72

	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [list], rcx
	mov [itemMatch], rdx
	mov [comp], r8



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
	mov [prevItemIndex], rcx		; Begin as 0

	mov rbx, [list]
	add rbx, List.indexItem
	mov rdx, [rbx]
	mov [prevItem], rdx


	mov rbx, [list]
	mov rdx, rbx
	add rbx, List.index
	mov r8, [rbx]
	add rdx, List.indexedItemIndex
	mov r9, [rdx]
	cmp r8, r9
	je atIndexedItem

	mov rbx, [list]			; Get first item when indexed is not cached and retrievable.
	add rbx, List.firstItem
	mov rdx, [rbx]
	mov [prevItem], rdx

	mov rbx, [list]
	add rbx, List.index
	mov rcx, [rbx]
	cmp rcx, 0
	jne nextItem

	atIndexedItem:

	mov rbx, [prevItem]
	mov [item], rbx		

	jmp lastItemReached

	nextItem:
	mov rbx, [list]
	add rbx, List.index
	mov rcx, [rbx]
	mov rdx, [prevItemIndex]
	cmp rcx, rdx
	jne lastItemReached


	mov r9, [prevItem]
	add r9, ListItem.next
	mov r10, [r9]
	mov [item], r10

	mov r11, [prevItemIndex]
	add r11, 1b
	mov [prevItemIndex], r11		; Increase prior item index
	
	jmp nextItem

	lastItemReached:


	mov rbx, [list]			; Advance List index
	add rbx, List.index
	mov r11, [rbx]
	add r11, 1b
	mov [rbx], r11

	mov rbx, [list]			; Advance index item, index item index
	mov rdx, rbx
	add rbx, List.indexItem
	mov r13, [item]
	mov [rbx], r13
	add rdx, List.indexedItemIndex
	mov [rdx], r11

	mov r12, [item]			; Get List Item's item
	add r12, ListItem.item
	mov rax, [r12]
	mov r13, [itemMatch]
	cmp rax, r13
	jne nextItem

	mov r12, [item]	
	cmp r12, 0
	je noMatch

	mov rbx, [list]
	mov rdx, rbx
	add rdx, List.itemMatch			
	mov rcx, [rdx]
	mov [listItemMatch], rcx	
	mov r11, rcx
	add r11, ItemMatch.item
	mov r13, [itemMatch]
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
	mov r12, [item]	
	add r12, ListItem.nesting
	mov r13, [r12]
	mov [r11], r13


	mov r8, rax
	add r8, [comp]
	mov rax, [r8]

	noMatch:

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

resetIndex:
namespace resetIndex
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*5);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label list qword at rbp-24 
	label item qword at rbp-32
	label prevItem qword at rbp-40
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [list], rcx



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





	mov rbx, [list]
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

extendList:
namespace extendList
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label list qword at rbp-24 
	label item qword at rbp-32
	label prevItem qword at rbp-40
	label extensionList qword at rbp-48

	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [list], rcx
	mov [extensionList], rdx


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
	mov rcx, [extensionList]
	call resetIndex
	add rsp, 8*8


	nextExtensionListItem:
	mov rbx, [extensionList]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov rcx, [rbx]
	mov r8, [rdx]
	cmp rcx, r8
	jnl endExtensionList


	sub rsp, 8*8
	mov rcx, [extensionList]
	call getNextItem
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, rax
	mov rcx, [list]
	call newLastItem
	add rsp, 8*8




	jmp nextExtensionListItem

	endExtensionList:	



	mov rax,[list]

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


;------------
;   Inserts a new numeric ascending item.
;   Takes List address, item address as parameters
;   Returns index item was inserted at.
;------------
newAscendingItem:
namespace newAscendingItem
	push rbp 
	mov rbp, rsp 
	sub rsp, ((8*9));+(8*6))

	mov rcx, rcx				; List
	mov rdx, rdx				; New Item
	label listAddress qword at rbp-8 
	label newItemAddress qword at rbp-16 
	label afterNewItemAddress qword at rbp-24
	label beforeNewItemAddress qword at rbp-32
	label beforeNewItemNesting qword at rbp-40 
	label hHeap qword at rbp-48 
	label hAllocatedMemory qword at rbp-56
	label newItemIndex qword at rbp-64
	label comparisonItem qword at rbp-72
	;virtual at rbp-112
	;	.newListItem ListItem
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

	mov [listAddress], rcx
	mov [newItemAddress], rdx


	mov rcx, 0
	mov [newItemIndex], rcx		; Begin as 0

	sub rsp, 8*8
	mov rcx, [listAddress]
	call resetIndex
	add rsp, 8*8


	nextItem:
	mov rbx, [listAddress]
	mov r9, rbx
	add r9, List.index
	add rbx, List.itemsCount
	mov rcx, [r9]
	mov rdx, [rbx]
	mov [newItemIndex], rcx		; Cache index
	cmp rcx, rdx
	jnl endList


	sub rsp, 8*8
	mov rcx, [listAddress]
	call getNextItem
	add rsp, 8*8
	mov [comparisonItem], rax


	mov rax, [comparisonItem]
	mov r10, [newItemAddress]	
	cmp r10, rax
	jg nextItem


	mov rbx, [listAddress]
	mov r9, rbx
	add r9, List.index
	mov r11, [newItemIndex]
	mov [r9], r11
	sub rsp, 8*8
	mov rdx, [newItemAddress]
	mov rcx, rbx
	call newNextItem
	add rsp, 8*8

	
	jmp completed
	endList:						; Must be end at this point

	sub rsp, 8*8
	mov rdx, [newItemAddress]
	mov rcx, [listAddress]
	call newLastItem
	add rsp, 8*8




	completed:

	mov rax, [newItemIndex]


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
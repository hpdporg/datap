


section '.data' data readable writeable align 16



	struc ListItem{
		.item dq 0
		.previous dq 0
		.next dq 0
		.nesting dq 0
		.itemSize dq 0
		.endListItemAddress dq 0
	}

	struc List{
		.firstItem dq 0
		.listSize dq 0
		.itemsCount dq 0
		.index dq 0
		.isBlankList dq 1
		.gradientNesting dq 0
		.gradientIndex dq 0			; Location of current Gradient
		.position dq 0				; Location within item of position (for Tensor Fields)
		.indexItem dq 0 			; Address of item at current index for faster item retrieval
		.indexedItemIndex dq 0			; Used to determine if index was set manually or actually equals indexed Item address
		.endListAddress dq 0
	}	

	; Used with address offsets
	virtual at 0
		ListItem ListItem
	end virtual

	; Used with address offsets
	virtual at 0
		List List
	end virtual

	; Struc initialization settings
	listInitialized dq 0
	listItemInitialized dq 0
	lastListItemInitialized dq 0

	; ---- newFirstItem variables
	listAddress dq 1
	itemAddress dq 1
	; ----
	
	; ---- newLastItem variables
	previousItemAddress dq 1
	; ----

	hHeap rq 1
	hAllocatedMemory rq 1 

	; ---- Structures
	list List
	listItem ListItem
	lastListItem ListItem
	newListItem ListItem

	
section '.text' code readable writeable executable align 16


newList:
	push rbp
	mov rbp, rsp 
	sub rsp, (8*2)+(8*11)
	;push ebp
	;mov ebp, esp
	;sub esp, (4*2)+(4*11)

	;mov ecx, [ebp+8] 
	;mov edx, [ebp+12] 
	label .hHeap qword at rbp-8	
	label .hAllocatedMemory qword at rbp-16 
	virtual at rbp-104
		.list List
	end virtual	

	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8


	sub rsp, 8*4
	call [GetProcessHeap]
	add rsp, 8*4
	mov [newList.hHeap], rax


	lea rax, [newList.list]
	lea rcx, [newList.list.endListAddress]


	;db 29h,11000001b		;sub ecx, eax
	;db 83h,00001000b,00001000b	;add ecx, 100b

	sub rcx, rax
	add rcx, 1000b

	mov [newList.list.listSize], rcx

	;lea r8, [newList.list.listSize]
	;mov rax, [newList.list.listSize]
	;push eax
	;push [newList.list.listSize]
	;db 6Ah, 00001000b	;push 000001000b
	;mov rcx, 1000b
	;push rcx
	;lea r9, [newList.hHeap]
	;push [newList.hHeap]
	sub rsp, 8*4
	mov rcx, [newList.hHeap]
	mov rdx, 1000b
	mov r8, [newList.list.listSize]
	call [HeapAlloc] 
	add rsp, 8*4
	mov [newList.hAllocatedMemory], rax



	
	mov [newList.list.firstItem], 0
	mov [newList.list.itemsCount], 0
	mov [newList.list.index], 0
	mov [newList.list.isBlankList], 1
	mov [newList.list.gradientNesting], 0
	mov [newList.list.gradientIndex], 0
	mov [newList.list.position], 0
	mov [newList.list.indexItem], 0
	mov [newList.list.indexedItemIndex], 0

	;jmp doneDBG
	
	
	cld

	mov rcx, [newList.list.listSize]

	lea rsi, [newList.list]
	mov rdi, [newList.hAllocatedMemory]

	rep movsb

	;mov rcx, [newList.hAllocatedMemory]
	;sub rsp, 8*8
	;call numAsLetters
	;add rsp, 8*8
	;mov rcx, rax
	;sub rsp, 8*8
	;call debugMsg2			
	;add rsp, 8*8

	;mov rcx, 1110b
	;sub rsp, 8*8
	;call numAsLetters
	;add rsp, 8*8
	;mov rcx, rax
	;sub rsp, 8*8
	;call debugMsg2			
	;add rsp, 8*8



	mov rax, [newList.hAllocatedMemory]

	;doneDBG:

	;mov rax, 0
	
	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0

;------------
;   Sets the first item for the list
;
;   Takes List address, item address as parameters
;------------
;align 16
newFirstItem:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*4)+(8*6)

	;mov ecx, [ebp+8]				;List address
	;mov edx, [ebp+12]				;Item address address
	mov rcx, rcx
	mov rdx, rdx
	label .listAddress qword at rbp-8 
	label .itemAddress qword at rbp-16
	label .hHeap qword at rbp-24
	label .hAllocatedMemory qword at rbp-32
	virtual at rbp-80
		.listItem ListItem
	end virtual	

	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	mov [newFirstItem.listAddress], rcx
	mov [newFirstItem.itemAddress], rdx

	;lea rax, [newFirstItem.listAddress]	
	;mov r8, rax
	;add rax, List.firstItem	
	;mov rbx, 0
	;mov rbx, 1
	;mov qword [rax], rbx



	sub rsp, 8*4
	call [GetProcessHeap]
	add rsp, 8*4
	mov [newFirstItem.hHeap], rax

	lea rax, [newFirstItem.listItem]
	lea rcx, [newFirstItem.listItem.endListItemAddress]

	sub rcx, rax
	add rcx, 1000b

	mov [newFirstItem.listItem.itemSize], rcx

	; Reserve new item struc space
	mov r8, [newFirstItem.listItem.itemSize]
	mov rdx, 000001000b
	mov rcx, [newFirstItem.hHeap]
	sub rsp, 8*4
	call [HeapAlloc] 
	add rsp, 8*4
	mov [newFirstItem.hAllocatedMemory], rax

	mov rax, [newFirstItem.itemAddress]

	; Set item struc item address
	mov [newFirstItem.listItem.item], rax
	mov [newFirstItem.listItem.next], 0
	mov [newFirstItem.listItem.nesting], 0
	mov [newFirstItem.listItem.previous], 0

	; Copy list item struc into reserved space
	mov rcx, [newFirstItem.listItem.itemSize]

	lea rsi, [newFirstItem.listItem]
	mov rdi, [newFirstItem.hAllocatedMemory]

	rep movsb

	; Set list's first item and current index item
	mov rbx, [newFirstItem.hAllocatedMemory]

	mov rax, [newFirstItem.listAddress]	


	mov r8, rax
	add r8, List.firstItem	
	;mov [rax+List.firstItem], rbx
	mov qword [r8], rbx
	mov r8, rax
	add r8, List.indexItem	
	mov qword [r8], rbx
	mov r8, rax
	add r8, List.indexedItemIndex	
	mov qword [r8], 0

	; Set item count
	mov rax, [newFirstItem.listAddress]	
	mov r8, rax
	add r8, List.itemsCount	
	mov qword [r8], 1b

	;mov rax, [newFirstItem.listAddress]
	;mov r8, rax
	;add r8, List.firstItem	
	
	;mov rbx, [newFirstItem.listAddress]
	;mov rcx, [r8]
	;add rcx, ListItem.item
	;mov rdx, [rcx]

	;mov rax, rdx
	mov rax, [newFirstItem.listAddress]


	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0

;------------
;   Sets last item for a list
;   Currently leaves List index unchanged
;   Takes List address, item address as parameters   
;------------
;align 16
newLastItem:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*5)+(8*6)

	mov rcx, rcx				;List address
	mov rdx, rdx				;Item address address
	label .listAddress qword at rbp-8 
	label .itemAddress qword at rbp-16
	label .previousItemAddress qword at rbp-24
	label .hHeap qword at rbp-32
	label .hAllocatedMemory qword at rbp-40
	virtual at rbp-88
		.lastListItem ListItem
	end virtual	

	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8


	mov [newLastItem.listAddress], rcx
	mov [newLastItem.itemAddress], rdx



	sub rsp, 8*4
	call [GetProcessHeap]
	add rsp, 8*4
	mov [newLastItem.hHeap], rax

	mov rax, [newLastItem.listAddress]

	; Get List items count
	mov r8, List.itemsCount
	add rax, r8
	mov rdx, [rax]

	; Check if originally blank
	cmp rdx, 0
	jne newLastItem.firstItemExists

	; Originally blank
	mov rdx, [newLastItem.itemAddress]
	mov rcx, [newLastItem.listAddress]
	sub rsp, 8*4
	call newFirstItem				
	add rsp, 8*4
	;add rsp, 16
	jmp newLastItem.originallyBlank

	.firstItemExists:
	mov rbx, [newLastItem.listAddress]
	mov r8, rbx
	add r8, List.firstItem
	mov rcx, [r8]

	; Get List Item's next Item address	
	.checkNextItem:
	mov [newLastItem.previousItemAddress], rcx
	mov r9, rcx
	add r9, ListItem.next
	mov rbx, [r9]


	mov rcx, 0
	cmp rbx, rcx
	je newLastItem.noNextItem

	.nextItemExists:

	mov [newLastItem.previousItemAddress], rbx
	mov rcx, rbx

	jmp newLastItem.checkNextItem
			
	.noNextItem:

	;call initLastListItemStruc

	lea rax, [newLastItem.lastListItem]
	lea rcx, [newLastItem.lastListItem.endListItemAddress]

	sub rcx, rax
	add rcx, 1000b

	mov rdx, [newLastItem.previousItemAddress]

	mov [newLastItem.lastListItem.itemSize], rcx
	mov [newLastItem.lastListItem.previous], rdx
	mov [newLastItem.lastListItem.next], 0
	mov rax, [newLastItem.listAddress]
	mov r9, rax
	add r9, List.gradientNesting
	mov rax, [r9]
	mov [newLastItem.lastListItem.nesting], rax
	mov rax, [newLastItem.itemAddress]
	mov [newLastItem.lastListItem.item], rax


	; Reserve new item struc space
	mov r8, [newLastItem.lastListItem.itemSize]
	mov rdx, 000001000b
	mov rcx, [newLastItem.hHeap]
	sub rsp, 8*4
	call [HeapAlloc] 
	add rsp, 8*4
	mov [newLastItem.hAllocatedMemory], rax

	cmp rax, 0
	jne newLastItem.allocated

	;mov rcx, rax
	;sub rsp, 8*4
	;call numAsLetters
	;add rsp, 8*4
	;add rsp, 8
	;mov rcx, rax
	;sub rsp, 8*4
	;call debugMsg2			
	;add rsp, 8*4
	;add rsp, 8
	mov rax, 0


	.allocated:


	; Copy item struc into reserved space
	mov rcx, [newLastItem.lastListItem.itemSize]

	lea rsi, [newLastItem.lastListItem]
	mov rdi, [newLastItem.hAllocatedMemory]

	rep movsb

	; Set last List Item address to previous item	
	mov rbx, [newLastItem.previousItemAddress]
	mov rdx, [newLastItem.hAllocatedMemory]

	mov r9, rbx
	add r9, ListItem.next
	mov qword [r9], rdx


	mov rbx, [newLastItem.listAddress]
	mov r10, rbx
	add r10, List.itemsCount
	mov rcx, [r10]

	add rcx, 1
	mov r10, rbx
	add r10, List.itemsCount
	mov qword [r10], rcx
	
	.originallyBlank:		



	;mov rcx, [newLastItem.listAddress]
	;sub rsp, 8*8
	;call numAsLetters
	;add rsp, 8*8
	;mov rcx, rax
	;sub rsp, 8*8
	;call debugMsg2			
	;add rsp, 8*8

	;mov rcx, 1101b
	;sub rsp, 8*8
	;call numAsLetters
	;add rsp, 8*8
	;mov rcx, rax
	;sub rsp, 8*8
	;call debugMsg2			
	;add rsp, 8*8

	;mov r10, [newLastItem.listAddress]
	;add r10, List.itemsCount
	;mov rcx, [r10]
	;sub rsp, 8*8
	;call numAsLetters
	;add rsp, 8*8
	;mov rcx, rax
	;sub rsp, 8*8
	;call debugMsg2			
	;add rsp, 8*8





	mov rax, [newLastItem.listAddress]

	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0

	

;------------
;   Gets the next item for a list
;   Uses the index value as a position
;   Takes List address as a parameter.
;------------
getNextItem:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8);((8)+(8))

	mov rcx, rcx 
	label .listAddress qword at rbp-8 

	
	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	mov [getNextItem.listAddress], rcx


	mov rbx, [getNextItem.listAddress]
	
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

	jmp itemReached

	retrieveFromFirstItem:

	mov rbx, [getNextItem.listAddress]
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
	mov rbx, [getNextItem.listAddress]
	mov r9, rbx
	add r9, List.index
	mov qword [r9], rax
	mov r10, rdx
	add r10, ListItem.item
	mov rax, [r10]


	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0



;------------
;   Resets the list position index to 0.
;    
;   Takes List address as a parameter
;------------
resetIndex:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8);((8)+(8))

	mov rcx, rcx 
	label .listAddress qword at rbp-8 

	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	mov [resetIndex.listAddress], rcx

	
	mov rbx, [resetIndex.listAddress]
	;mov rcx, List.index			;64-bit
	mov rdx, rbx
	add rdx, List.index
	mov qword [rdx], 0
	mov rdx, rbx
	add rdx, List.indexedItemIndex
	mov qword [rdx], 0
	mov rdx, rbx
	add rdx, List.firstItem
	mov r8, [rdx]
	mov rdx, rbx
	add rdx, List.indexItem
	mov qword [rdx], r8

	;mov rax, [listAddress]


	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0



verflachen:






;------------
;   Inserts item at the current position index.
;   If an item exists at the current index, the existing item will become the next item.
;   Updates list item count, item previous and next addresses, List index by 1, etc.
;   Updates should allow insertion to occur as a chain if used more than once.
;   Takes List address, item address as parameters
;------------
newNextItem:
	push rbp 
	mov rbp, rsp 
	sub rsp, ((8*8)+(8*6))

	mov rcx, rcx				; List
	mov rdx, rdx				; New Item
	label .listAddress qword at rbp-8 
	label .newItemAddress qword at rbp-16 
	label .afterNewItemAddress qword at rbp-24
	label .beforeNewItemAddress qword at rbp-32
	label .beforeNewItemNesting qword at rbp-40 
	label .hHeap qword at rbp-48 
	label .hAllocatedMemory qword at rbp-56
	label .newItemIndex qword at rbp-64
	virtual at rbp-112
		.newListItem ListItem
	end virtual



	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	mov [newNextItem.listAddress], rcx
	mov [newNextItem.newItemAddress], rdx




	mov rbx, [newNextItem.listAddress]
	mov r8, rbx
	add r8, List.itemsCount
	mov rcx, [r8]
	mov rax, 0


	cmp rcx, rax
	jne newNextItem.listNotBlank					; New First Item?

	mov rdx, [newNextItem.newItemAddress]
	mov rcx, [newNextItem.listAddress]
	sub rsp, 8*4
	call newFirstItem
	add rsp, 8*4
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
	sub rsp, 8*4
	call newLastItem
	add rsp, 8*4
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

	lea rax, [newNextItem.newListItem]
	lea rcx, [newNextItem.newListItem.endListItemAddress]

	sub rcx, rax
	add rcx, 1000b
	mov [newNextItem.newListItem.itemSize], rcx		; Calculate item size

	sub rsp, 8*4
	call [GetProcessHeap]
	add rsp, 8*4
	cmp rax, 0
	je newNextItem.newNextItemFailed
	mov [newNextItem.hHeap], rax				; Get Heap

	; Reserve new item struc space
	sub rsp, 8*4	
	mov r8, [newNextItem.newListItem.itemSize]
	mov rdx, 000001000b
	mov rcx, [newNextItem.hHeap]
	call [HeapAlloc] 
	add rsp, 8*4
	cmp rax, 0
	je newNextItem.newNextItemFailed
	mov [newNextItem.hAllocatedMemory], rax 		; New item allocated

	cmp rax, 0
	jne newNextItem.allocated

	mov rcx, rax
	sub rsp, 8*4
	call numAsLetters
	add rsp, 8*4
	;add rsp, 8
	mov rcx, rax
	sub rsp, 8*4
	call debugMsg2
	add rsp, 8*4
	;add rsp, 8
	mov rax, 0


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

	mov [newNextItem.newListItem.previous], rdx
	mov [newNextItem.newListItem.next], rbx
	mov rbx, [newNextItem.beforeNewItemNesting]
	mov [newNextItem.newListItem.nesting], rbx
	mov rax, [newNextItem.newItemAddress]
	mov [newNextItem.newListItem.item], rax

	; Copy item struc into reserved space
	mov rcx, [newNextItem.newListItem.itemSize]

	lea rsi, [newNextItem.newListItem]
	mov rdi, [newNextItem.hAllocatedMemory]

	rep movsb

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


	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0





;------------
;   Removes item from the current position index.
;   Updates list item count, item previous and next addresses, etc.
;   Takes List address as a parameter
;------------
removeNextItem:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);((8)+(8*4))

	mov rcx, rcx				;List address
	label .listAddress qword at rbp-8 
	label .itemAddress qword at rbp-16
	label .hHeap qword at rbp-24
	label .listIndex qword at rbp-32
	label .previousItem qword at rbp-40
	label .nextItem qword at rbp-48
	
	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	mov [removeNextItem.listAddress], rcx



	mov rbx, [removeNextItem.listAddress]
	
	mov r9, rbx
	add r9, List.index
	mov rcx, [r9]
	mov [removeNextItem.listIndex], rcx
	mov rax, 0

	mov r8, rbx
	add r8, List.firstItem
	mov rdx, [r8]

	cmp rcx, rax
	je removalItemReached

	removalItemNotReached:

	mov r8, rdx
	add r8, ListItem.next
	mov rbx, [r8]
	mov rdx, rbx
	add rax, 1
	
	cmp rax, rcx
	jne removalItemNotReached 


	removalItemReached:

	mov r8, rdx
	add r8, ListItem.item
	mov rax, [r8]
	mov [removeNextItem.itemAddress], rax

	mov r9, rdx
	add r9, ListItem.previous
	mov rax, [r9]
	mov [removeNextItem.previousItem], rax
	mov r9, rdx
	add r9, ListItem.next
	mov rbx, [r9]
	mov [removeNextItem.nextItem], rbx


	mov rcx, [removeNextItem.listIndex]
	cmp rcx, 0
	je removalItemWasFirstIndex

	;Need to update nesting if item after removed is higher nesting count, and subsequent
	;Reduce by 1 until same nesting level is reached
	mov rax, [removeNextItem.previousItem]
	mov rbx, [removeNextItem.nextItem]
	mov r8, rax
	add r8, ListItem.next
	mov qword [r8], rbx

	removalItemWasFirstIndex:
	
	mov rbx, [removeNextItem.nextItem]
	cmp rbx, 0
	je removalItemWasLastIndex

	mov rbx, [removeNextItem.nextItem]
	mov rax, [removeNextItem.previousItem]
	mov r9, rbx
	add r9, ListItem.previous
	mov qword [r9], rax
	;cmp rax, 0
	;jne removalItemWasLastIndex

	;mov rax, [removeNextItem.listAddress]
	;mov [rax+List.index], 63
	;Update first item if first List Item removed and next exists
	mov rdx, [removeNextItem.listAddress]
	mov r8, rdx
	add r8, List.firstItem
	mov qword [r8], rbx

	removalItemWasLastIndex:

	sub rsp, 8*4
	call [GetProcessHeap]
	add rsp, 8*4
	mov [removeNextItem.hHeap], rax

	mov r8, [removeNextItem.itemAddress]
	mov rdx, 0b
	mov rcx, [removeNextItem.hHeap]
	sub rsp, 8*4
	call [HeapFree]
	add rsp, 8*4

	mov rbx, [removeNextItem.listAddress]
	
	mov r9, rbx
	add r9, List.indexItem
	mov qword [r9], 0		;Until indexes updated
	mov r8, rbx
	add r8, List.itemsCount
	mov rcx, [r8]
	dec rcx
	mov r8, rbx
	add r8, List.itemsCount
	mov [r8], rcx

	;Maintain current List index

	mov rbx, [removeNextItem.listAddress]
	mov rax, [removeNextItem.listIndex]
	;db 8B,00000101b, [removeNextItem.listIndex]	;Address?
	mov r8, rbx
	add r8, List.index
	mov qword [r8], rax

	mov rax, [removeNextItem.listAddress]


	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0



;------------
;   Sets Gradient Index, Gradient Nesting from the current position index.
;   Takes List address as a parameter
;------------
resetGradient:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*2);((8)+(8*2))

	mov rcx, rcx 
	label .listAddress qword at rbp-8 
	label .gradientItemAddress qword at rbp-16 
	


	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	mov [resetGradient.listAddress], rcx

	mov rbx, [resetGradient.listAddress]
	
	mov r9, rbx
	add r9, List.index
	mov rcx, [r9]
	mov rax, 0

	mov r8, rbx
	add r8, List.firstItem
	mov rdx, [r8]
	
	cmp rcx, rax
	je gradientItemReached

	gradientItemNotReached:

	mov r8, rdx
	add r8, ListItem.next
	mov rdx, [r8]
	add rax, 1
	
	cmp rax, rcx
	jne gradientItemNotReached


	gradientItemReached:

	mov [resetGradient.gradientItemAddress], rdx
	mov rbx, [resetGradient.listAddress]
	mov r9, rbx
	add r9, List.index
	mov rcx, [r9]
	mov r8, rbx
	add r8, List.gradientIndex
	mov qword [r8], rcx
	mov r9, rdx
	add r9, ListItem.nesting
	mov rcx, [r9]
	mov r8, rbx
	add r8, List.gradientNesting
	mov qword [r8], rcx

	mov rax, 0

	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0


;------------
;   Sets Gradient Index, Gradient Nesting from the position index provided.
;   Takes List address, index as parameters
;------------
resetGradientWithIndex:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*3);((8)+(8*2))

	;mov rcx, rcx 
	label .listAddress qword at rbp-8 
	label .gradientItemAddress qword at rbp-16 
	label .index qword at rbp-24 
	


	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	mov [resetGradientWithIndex.listAddress], rcx
	mov [resetGradientWithIndex.index], rdx

	mov rbx, [resetGradientWithIndex.listAddress]
	mov r9, rbx
	add r9, List.index
	mov rcx, [resetGradientWithIndex.index]
	mov [r9], rcx


	sub rsp, 8*8
	mov rcx, [resetGradientWithIndex.listAddress]
	call resetGradient
	add rsp, 8*8


	mov rax, 0

	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0

;------------
;   Sets Gradient Index, Gradient Nesting from the next item match.
;   Takes List address, item as parameters
;------------
resetGradientAtNextMatch:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*3);((8)+(8*2))

	mov rcx, rcx 
	label .listAddress qword at rbp-8 
	label .item qword at rbp-16 
	label .index qword at rbp-16 
	


	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	mov [resetGradientAtNextMatch.listAddress], rcx
	mov [resetGradientAtNextMatch.item], rdx


	sub rsp, 8*8
	mov rdx, [resetGradientAtNextMatch.item]
	mov rcx, [resetGradientAtNextMatch.listAddress]
	call getNextItemMatchIndex
	add rsp, 8*8
	mov [resetGradientAtNextMatch.index], rax


	mov rbx, [resetGradientAtNextMatch.listAddress]
	mov r9, rbx
	add r9, List.index
	mov rcx, [resetGradientAtNextMatch.index]
	mov [r9], rcx


	sub rsp, 8*8
	mov rcx, [resetGradientAtNextMatch.listAddress]
	call resetGradient
	add rsp, 8*8


	mov rax, 0

	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0


;------------
;   Gets the next item within the current Gradient.
;   Uses the index value as a position.
;   Consider enforcing two calls when above Gradient nesting and at or below.
;   Returns last item within current Gradient if next item's Nesting is less than current Gradient Nesting.
;   Takes List address as a parameter.
;------------
converge:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*3);((8)+(8*3))

	mov rcx, rcx 
	label .listAddress qword at rbp-8 
	label .priorItemAddress qword at rbp-16
	label .convergeItemAddress qword at rbp-24 


	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	mov [converge.listAddress], rcx

	mov rbx, [converge.listAddress]
	
	mov r8, rbx
	add r8, List.index
	mov rcx, [r8]

	mov rax, 0

	mov r8, rbx
	add r8, List.firstItem
	mov rdx, [r8]
	

	;
	;mov rax, [rbx+List.index]
	;push rax
	;call numAsLetters
	;push rax
	;call debugMsg2
	;mov rax, 0
	;mov rbx, [converge.listAddress]
	;mov rcx, [rbx+List.index]
	;


	cmp rcx, rax
	je convergeItemReached


	convergeItemNotReached:

	mov r8, rdx
	add r8, ListItem.next
	mov rdx, [r8]
	add rax, 1
	
	cmp rax, rcx
	jne convergeItemNotReached


	convergeItemReached:


	add rax, 1

	;Compare Nesting with Gradient Nesting. Return List Item's previous Item if Nesting is less.
	mov [converge.convergeItemAddress], rdx
	mov rdx, [converge.convergeItemAddress]
	mov rbx, [converge.listAddress]
	mov r9, rbx
	add r9, List.gradientNesting
	mov rcx, [r9]
	mov r8, rdx
	add r8, ListItem.nesting
	mov rbx, [r8]
	cmp rbx, rcx
	jge convergeReached
	
	mov rdx, [converge.convergeItemAddress]
	mov r8, rdx
	add r8, ListItem.previous
	mov rdx, [r8]
	mov [converge.convergeItemAddress], rdx
	;mov rbx, [converge.listAddress]			;;dbg
	;mov rax, [rdx+List.gradientNesting]		;;dbg
	;push rax
	;call numAsLetters
	;push rax
	;call debugMsg2

	sub rax, 1

	convergeReached:

	mov rbx, [converge.listAddress]
	mov r9, rbx
	add r9, List.index
	mov qword [r9], rax
	mov rdx, [converge.convergeItemAddress]
	mov r9, rdx


	mov r8, rdx
	add r8, ListItem.item
	mov rax, [r8]


	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp


	retn 0


;------------
;   Gets the previous item for a list.
;   Uses the index value as a position
;   Consider enforcing two calls when below Gradient nesting and at or above.
;   Returns previous item outside current Gradient if previous item's Nesting is less than or equal to current Gradient Nesting only.
;   Takes List address as a parameter.
;------------
diverge:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*4);((8)+(8*3))

	mov rcx, rcx 
	label .listAddress qword at rbp-8 
	label .divergeItemAddress qword at rbp-16
	label .divergeNesting qword at rbp-24
	label .divergeItemIndex qword at rbp-32
	
	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	mov [diverge.listAddress], rcx

	mov rbx, [diverge.listAddress]

	mov r9, rbx
	add r9, List.index
	mov rcx, [r9]
	mov rax, 0
	mov [diverge.divergeItemIndex], rax
	mov r8, rbx
	add r8, List.gradientNesting
	mov rdx, [r8]
	mov [diverge.divergeNesting], rdx

	mov r8, rbx
	add r8, List.firstItem
	mov rbx, [r8]
	

	mov [diverge.divergeItemAddress], rbx

	cmp rcx, 0
	je divergeItemReached

	sub rcx, 1			
	
	cmp rcx, rax
	je divergeItemReached

	divergeItemNotReached:

	mov r8, rbx
	add r8, ListItem.next
	mov rbx, [r8]	;rbx to rbx?
	add rax, 1


	mov r9, rbx
	add r9, ListItem.nesting
	mov rdx, [r9]
	cmp rdx, [diverge.divergeNesting]
	jg checkEndDivergence

	mov [diverge.divergeItemAddress], rbx
	mov [diverge.divergeItemIndex], rax

	checkEndDivergence:

	cmp rax, rcx
	jne divergeItemNotReached 


	divergeItemReached:


	;add rax, 1
	mov rbx, [diverge.listAddress]
	mov rax, [diverge.divergeItemIndex]
	mov r8, rbx
	add r8, List.index
	mov qword [r8], rax
	mov rdx, [diverge.divergeItemAddress]
	mov r8, rdx
	add r8, ListItem.nesting
	mov rax, [r8]
	mov r9, rbx
	add r9, List.gradientNesting
	mov qword [r9], rax
	mov r8, rdx
	add r8, ListItem.item
	mov rax, [r8]


	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0


;------------
;   Gets the next item for a list at the Gradient nesting level.
;   Returns the current item if there is no next tangent.
;   Uses the index value as a position
;   Takes List address as a parameter.
;------------
nextTangent:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);((8)+(8*4))

	mov rcx, rcx 
	label .listAddress qword at rbp-8 
	label .tangentItemAddress qword at rbp-16
	label .tangentNesting qword at rbp-24
	label .itemsCount qword at rbp-32
	label .tangentIndex qword at rbp-40
	label .gradientIndex qword at rbp-48
	
	
	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	mov [nextTangent.listAddress], rcx

	mov rbx, [nextTangent.listAddress]

	mov r8, rbx
	add r8, List.index
	mov rcx, [r8]
	mov [nextTangent.gradientIndex], rcx
	mov r9, rbx
	add r9, List.gradientNesting
	mov rdx, [r9]
	mov [nextTangent.tangentNesting], rdx
	mov r8, rbx
	add r8, List.itemsCount
	mov rax, [r8]
	sub rax, 1
	mov [nextTangent.itemsCount], rax
	mov rax, 0

	mov r8, rbx
	add r8, List.firstItem
	mov rbx, [r8]
	

	mov [nextTangent.tangentItemAddress], rbx
	mov [nextTangent.tangentIndex], rax

	cmp [nextTangent.itemsCount], 0
	je nextTangentItemReached

	nextTangentItemNotReached:

	mov r8, rbx
	add r8, ListItem.next
	mov rbx, [r8]	
	add rax, 1

	cmp rax, [nextTangent.gradientIndex]
	jne checkNextTangent
	mov [nextTangent.tangentItemAddress], rbx	;This is current item, so store it
	mov [nextTangent.tangentIndex], rax

	jmp checkEndOfNextTangentList

	checkNextTangent:
	
	mov r8, rbx
	add r8, ListItem.nesting
	mov rdx, [r8]
	cmp rdx, [nextTangent.tangentNesting]
	jne checkEndOfNextTangentList

	cmp rax, [nextTangent.gradientIndex]
	jl checkEndOfNextTangentList			;Should be jump to not reached
	mov [nextTangent.tangentItemAddress], rbx
	mov [nextTangent.tangentIndex], rax
	jmp nextTangentItemReached

	checkEndOfNextTangentList:
	
	cmp rax, [nextTangent.itemsCount]
	jl nextTangentItemNotReached 


	nextTangentItemReached:

	mov rax, [nextTangent.tangentIndex]
	add rax, 1
	mov rbx, [nextTangent.listAddress]
	mov r9, rbx
	add r9, List.index
	mov qword [r9], rax
	mov rbx, [nextTangent.tangentItemAddress]
	mov r8, rbx
	add r8, ListItem.item
	mov rax, [r8]


	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0


;------------
;   Gets the previous item for a list at the current Gradient nesting.
;   Uses the index value as a position, List's gradientNesting as nesting
;   Consider replacing this with a getNextItem that decreases the List index and compares nesting
;   Returns current item if previous item's Nesting is not equal to current Gradient Nesting.
;   Takes List address as a parameter.
;------------
priorTangent:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*5);((8)+(8*4))

	mov rcx, rcx 
	label .listAddress qword at rbp-8 
	label .tangentItemAddress qword at rbp-16
	label .tangentNesting qword at rbp-24
	label .priorTangentExists qword at rbp-32
	label .priorTangentIndex qword at rbp-40	
	
	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	mov [priorTangent.listAddress], rcx

	mov rbx, [priorTangent.listAddress]
	mov [priorTangent.priorTangentExists], 0

	mov r8, rbx
	add r8, List.index
	mov rcx, [r8]
	mov rax, 0
	mov r9, rbx
	add r9, List.gradientNesting
	mov rdx, [r9]
	mov [priorTangent.tangentNesting], rdx

	mov r8, rbx
	add r8, List.firstItem
	mov rbx, [r8]


	cmp rcx, 1
	jne checkPriorTangentAndCurrentAreFirst
	
	mov r9, rbx
	add r9, ListItem.nesting
	mov rdx, [r9]
	cmp rdx, [priorTangent.tangentNesting]
	jne checkPriorTangentAndCurrentAreFirst
	
	mov [priorTangent.tangentItemAddress], rbx
	mov [priorTangent.priorTangentIndex], rax
	jmp priorTangentItemReached

	checkPriorTangentAndCurrentAreFirst:
	cmp rcx, 0
	jne priorTangentItemNotReached

	mov [priorTangent.tangentItemAddress], rbx
	mov [priorTangent.priorTangentIndex], rax
	jmp priorTangentItemReached
	
	priorTangentItemNotReached:

	mov r8, rbx
	add r8, ListItem.next
	mov rbx, [r8]
	add rax, 1

	sub rcx, 1
	cmp rax, rcx
	jne checkPriorNesting

	add rcx, 1
	cmp [priorTangent.priorTangentExists], 1
	je priorTangentItemReached

	mov [priorTangent.tangentItemAddress], rbx
	mov [priorTangent.priorTangentIndex], rax
	jmp priorTangentItemReached


	checkPriorNesting:
	add rcx, 1

	mov r8, rbx
	add r8, ListItem.nesting
	mov rdx, [r8]
	cmp rdx, [priorTangent.tangentNesting]
	jne priorTangentItemNotReached

	mov [priorTangent.tangentItemAddress], rbx
	mov [priorTangent.priorTangentIndex], rax
	mov [priorTangent.priorTangentExists], 1
	
	cmp rax, rcx
	jne priorTangentItemNotReached 


	priorTangentItemReached:


	mov rax, [priorTangent.priorTangentIndex]
	add rax, 1
	mov rbx, [priorTangent.listAddress]
	mov r9, rbx
	add r9, List.index
	mov qword [r9], rax
	mov rbx, [priorTangent.tangentItemAddress]
	mov r8, rbx
	add r8, ListItem.item
	mov rax, [r8]


	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0


;------------
;   Gets the next item match in a list
;   Uses the List index value as a starting position
;   Leaves the List index advanced at the next item.
;   Takes List address, item as parameters.
;   Returns the item when found, 0 otherwise.
;------------
getNextItemMatch:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*3);((8)+(8))

	;mov rcx, rcx 
	
	label .listAddress qword at rbp-8 
	label .item qword at rbp-16 
	label .itemMatch qword at rbp-24 

	
	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	mov [getNextItemMatch.listAddress], rcx
	mov [getNextItemMatch.item], rdx

	mov rcx, 0
	mov [getNextItemMatch.itemMatch], rcx				; Begin as 0


	.nextItem:

	mov rbx, [getNextItemMatch.listAddress]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov r8, [rbx]
	mov r9, [rdx]
	cmp r8, r9
	jnl getNextItemMatch.end
	
	sub rsp, 8*8
	mov rcx, [getNextItemMatch.listAddress]
	call getNextItem
	add rsp, 8*8
	mov r10, [getNextItemMatch.item]
	cmp rax, r10
	jne getNextItemMatch.nextItem

	mov [getNextItemMatch.itemMatch], rax				; Match found


	.end:

	mov rax, [getNextItemMatch.itemMatch]

	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0

;------------
;   Gets the next item match index in a list
;   Uses the List index value as a starting position
;   Leaves the List index advanced at the next item.
;   Takes List address, item as parameters.
;   Returns the item index or the item count when not found.
;------------
getNextItemMatchIndex:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*4);((8)+(8))

	;mov rcx, rcx 
	
	label .listAddress qword at rbp-8 
	label .item qword at rbp-16 
	label .itemMatchIndex qword at rbp-24 
	label .itemMatch qword at rbp-32 

	
	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	mov [getNextItemMatchIndex.listAddress], rcx
	mov [getNextItemMatchIndex.item], rdx


	
	mov rbx, [getNextItemMatchIndex.listAddress]
	add rbx, List.itemsCount
	mov rcx, [rbx]
	mov [getNextItemMatchIndex.itemMatchIndex], rcx				; Begin as item count


	.nextItem:

	mov rbx, [getNextItemMatchIndex.listAddress]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov r8, [rbx]
	mov r9, [rdx]
	cmp r8, r9
	jnl getNextItemMatchIndex.end
	
	sub rsp, 8*8
	mov rcx, [getNextItemMatchIndex.listAddress]
	call getNextItem
	add rsp, 8*8
	mov r10, [getNextItemMatchIndex.item]
	cmp rax, r10
	jne getNextItemMatchIndex.nextItem

	mov rcx, [getNextItemMatchIndex.listAddress]
	add rcx, List.index
	mov r12, [rcx]
	sub r12, 1b	

	mov [getNextItemMatchIndex.itemMatchIndex], r12				; Match found


	.end:

	mov rax, [getNextItemMatchIndex.itemMatchIndex]

	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0



; Increases nesting and new next item
newNextNested:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*3);((8)+(8))

	;mov rcx, rcx 
	
	label .listAddress qword at rbp-8 
	label .item qword at rbp-16 
	label .itemMatchIndex qword at rbp-24 

	
	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	mov [newNextNested.listAddress], rcx
	mov [newNextNested.item], rdx


	mov rbx, [newNextNested.listAddress]
	add rbx, List.gradientNesting
	mov rcx, [rbx]
	add rcx, 1b
	mov [rbx], rcx

	sub rsp, 8*8
	mov rdx, [newNextNested.item]
	mov rcx, [newNextNested.listAddress]
	call newNextItem
	add rsp, 8*8
	




	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0

; Increases nesting and new last item
newLastNested:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*3);((8)+(8))

	;mov rcx, rcx 
	
	label .listAddress qword at rbp-8 
	label .item qword at rbp-16 
	label .itemMatchIndex qword at rbp-24 

	
	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	mov [newLastNested.listAddress], rcx
	mov [newLastNested.item], rdx


	mov rbx, [newLastNested.listAddress]
	add rbx, List.gradientNesting
	mov rcx, [rbx]
	add rcx, 1b
	mov [rbx], rcx

	sub rsp, 8*8
	mov rdx, [newLastNested.item]
	mov rcx, [newLastNested.listAddress]
	call newLastItem
	add rsp, 8*8
	




	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0



; Get count of tangents at current gradient nesting
; Includes item at List's index in count
getFollowingTangentCount:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*5);((8)+(8))

	;mov rcx, rcx 
	
	label .listAddress qword at rbp-8 
	label .priorTangent qword at rbp-16 
	label .nextTangent qword at rbp-24 
	label .itemMatchIndex qword at rbp-32 
	label .count qword at rbp-40 

	
	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	mov [getFollowingTangentCount.listAddress], rcx
	;mov [getFollowingTangentCount.item], rdx


	mov rcx, 0
	mov [getFollowingTangentCount.count], rcx				; Begin as 0
	mov [getFollowingTangentCount.priorTangent], rcx			; Begin as 0
	mov [getFollowingTangentCount.nextTangent], rcx				; Begin as 0


	.nextItem:
	mov rbx, [getFollowingTangentCount.listAddress]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov rcx, [rbx]
	mov r8, [rdx]
	cmp rcx, r8
	jnl getFollowingTangentCount.end



	sub rsp, 8*8
	mov rcx, [getFollowingTangentCount.listAddress]
	call nextTangent
	add rsp, 8*8
	mov [getFollowingTangentCount.nextTangent], rax


	mov r11, [getFollowingTangentCount.nextTangent]
	mov r12, [getFollowingTangentCount.priorTangent]
	cmp r11, r12
	je getFollowingTangentCount.end

	mov r13, [getFollowingTangentCount.count]
	add r13, 1b
	mov [getFollowingTangentCount.count], r13

	mov [getFollowingTangentCount.priorTangent], r11			; Prior Tangent is next tangent


	jmp getFollowingTangentCount.nextItem


	.end:

	mov rax, [getFollowingTangentCount.count]

	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0


; Get count of tangents at current gradient nesting
; Includes item at List's index in count
getPriorTangentCount:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*5);((8)+(8))

	;mov rcx, rcx 
	
	label .listAddress qword at rbp-8 
	label .priorTangent qword at rbp-16 
	label .tangentMatch qword at rbp-24 
	label .itemMatchIndex qword at rbp-32 
	label .count qword at rbp-40 

	
	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	mov [getPriorTangentCount.listAddress], rcx
	;mov [getPriorTangentCount.item], rdx


	mov rcx, 0
	mov [getPriorTangentCount.count], rcx				; Begin as 0
	mov [getPriorTangentCount.priorTangent], rcx			; Begin as 0
	mov [getPriorTangentCount.tangentMatch], rcx			; Begin as 0


	.priorItem:
	mov rbx, [getPriorTangentCount.listAddress]
	add rbx, List.index
	mov rcx, [rbx]
	mov r8, 0
	cmp rcx, r8
	jnge getPriorTangentCount.end



	sub rsp, 8*8
	mov rcx, [getPriorTangentCount.listAddress]
	call priorTangent
	add rsp, 8*8
	mov [getPriorTangentCount.tangentMatch], rax


	mov r11, [getPriorTangentCount.tangentMatch]
	mov r12, [getPriorTangentCount.priorTangent]
	cmp r11, r12
	je getPriorTangentCount.end

	mov r13, [getPriorTangentCount.count]
	add r13, 1b
	mov [getPriorTangentCount.count], r13

	mov [getPriorTangentCount.priorTangent], r11			; Prior Tangent is next tangent


	jmp getPriorTangentCount.priorItem


	.end:

	mov rax, [getPriorTangentCount.count]

	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0


;------------
;   Gets the next item match nesting in a list
;   Leaves gradient unaffected
;   Returns List item count when no match exists.
;------------
getNestingAtNextMatch:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);((8)+(8))

	;mov rcx, rcx 
	
	label .listAddress qword at rbp-8 
	label .item qword at rbp-16 
	label .itemMatch qword at rbp-24 
	label .itemIndex qword at rbp-32 
	label .priorIndex qword at rbp-40 		; Index before matching
	label .priorNesting qword at rbp-48 		; Nesting before matching
	label .priorGradientIndex qword at rbp-56 	; Gradient Index before matching
	label .nestingMatch qword at rbp-64 	; 

	
	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	mov [getNestingAtNextMatch.listAddress], rcx
	mov [getNestingAtNextMatch.item], rdx




	mov rbx, [getNestingAtNextMatch.listAddress]
	mov rdx, rbx
	mov rax, rbx
	add rbx, List.index
	mov rcx, [rbx]
	mov [getNestingAtNextMatch.priorIndex], rcx					; Cache prior index, gradientNesting, gradientIndex. Restore at end.
	add rdx, List.gradientNesting
	mov rcx, [rdx]
	mov [getNestingAtNextMatch.priorNesting], rcx
	add rax, List.gradientIndex
	mov rcx, [rax]
	mov [getNestingAtNextMatch.priorGradientIndex], rcx


	
	sub rsp, 8*8
	mov rdx, [getNestingAtNextMatch.item]
	mov rcx, [getNestingAtNextMatch.listAddress]
	call getNextItemMatchIndex						; Use index as required by resetGradient
	add rsp, 8*8
	mov [getNestingAtNextMatch.itemIndex], rax





	mov rbx, [getNestingAtNextMatch.listAddress]
	add rbx, List.itemsCount
	mov rdx, [rbx]
	cmp rax, rdx
	jne getNestingAtNextMatch.matchExists					; No match found when index is item count

	mov [getNestingAtNextMatch.nestingMatch], rax

	jmp getNestingAtNextMatch.end						; No match when item index is item count

	.matchExists:

	mov rbx, [getNestingAtNextMatch.listAddress]
	add rbx, List.index
	mov rcx, [getNestingAtNextMatch.itemIndex]
	mov [rbx], rcx


	sub rsp, 8*8
	mov rcx, [getNestingAtNextMatch.listAddress]
	call resetGradient
	add rsp, 8*8	

	mov rbx, [getNestingAtNextMatch.listAddress]
	add rbx, List.gradientNesting
	mov rcx, [rbx]

	mov [getNestingAtNextMatch.nestingMatch], rcx



	.end:



	mov rbx, [getNestingAtNextMatch.listAddress]
	mov rdx, rbx
	mov rax, rbx
	add rbx, List.index
	mov rcx, [getNestingAtNextMatch.priorIndex]
	mov [rbx], rcx
	add rdx, List.gradientNesting
	mov rcx, [getNestingAtNextMatch.priorNesting]
	mov [rdx], rcx
	add rax, List.gradientIndex
	mov rcx, [getNestingAtNextMatch.priorGradientIndex]
	mov [rax], rcx							; Restore with prior index, gradient nesting, gradient index




	mov rax, [getNestingAtNextMatch.nestingMatch]

	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0


;------------
;   Gets the next item match with List's gradientNesting or 0 when none exist
;   Returns List item or 0 when no matches exist
;------------
getNextTangentMatch:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*13);((8)+(8))

	;mov rcx, rcx 
	
	label .listAddress qword at rbp-8 
	label .item qword at rbp-16 
	label .itemMatch qword at rbp-24 
	label .itemIndex qword at rbp-32 
	label .priorIndex qword at rbp-40 		; Index before matching
	label .priorNesting qword at rbp-48 		; Nesting before matching
	label .priorGradientIndex qword at rbp-56 	; Gradient Index before matching
	label .tangentMatch qword at rbp-64 
	label .nestingMatch qword at rbp-72 
	label .gradientIndex qword at rbp-80 
	label .tangentNesting qword at rbp-88 
	label .itemsCount qword at rbp-96 
	label .tangentItemAddress qword at rbp-104 

	
	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	mov [getNextTangentMatch.listAddress], rcx
	;mov [getNestingAtNextMatch.item], rdx



	mov rcx, 0
	mov [getNextTangentMatch.nestingMatch], rcx	; Begin as 0


	mov rbx, [getNextTangentMatch.listAddress]

	mov r8, rbx
	add r8, List.index
	mov rcx, [r8]
	mov [getNextTangentMatch.gradientIndex], rcx
	mov r9, rbx
	add r9, List.gradientNesting
	mov rdx, [r9]
	mov [getNextTangentMatch.tangentNesting], rdx
	mov r8, rbx
	add r8, List.itemsCount
	mov rax, [r8]
	sub rax, 1
	mov [getNextTangentMatch.itemsCount], rax
	mov rax, 0

	mov r8, rbx
	add r8, List.firstItem
	mov rdx, [r8]
	mov [getNextTangentMatch.tangentItemAddress], rdx
	

	mov rcx, 0
	cmp rcx, [getNextTangentMatch.gradientIndex]
	je getNextTangentMatch.nextTangent					; Start at first index	



	.nextItem:	
	mov rbx, [getNextTangentMatch.listAddress]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov r8, [rbx]
	mov r9, [rdx]
	cmp r8, r9
	jnl getNextTangentMatch.end



	mov r11, [getNextTangentMatch.tangentItemAddress]
	add r11, ListItem.next
	mov r12, [r11]
	mov [getNextTangentMatch.tangentItemAddress], r12			; Next

	mov rbx, [getNextTangentMatch.listAddress]
	add rbx, List.index
	mov rcx, [rbx]
	add rcx, 1b
	mov [rbx], rcx								; Increment index

	cmp rcx, [getNextTangentMatch.gradientIndex]
	je getNextTangentMatch.nextTangent	

	jmp getNextTangentMatch.nextItem


	.nextTangent:	
	mov rbx, [getNextTangentMatch.listAddress]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov r8, [rbx]
	mov r9, [rdx]
	cmp r8, r9
	jnl getNextTangentMatch.end


	mov r11, [getNextTangentMatch.tangentItemAddress]
	add r11, ListItem.nesting
	mov r12, [r11]
	cmp r12, [getNextTangentMatch.tangentNesting]
	je getNextTangentMatch.matchFound	

	mov r11, [getNextTangentMatch.tangentItemAddress]
	add r11, ListItem.next
	mov r12, [r11]
	mov [getNextTangentMatch.tangentItemAddress], r12			; Next


	mov rbx, [getNextTangentMatch.listAddress]
	add rbx, List.index
	mov rcx, [rbx]
	add rcx, 1b
	mov [rbx], rcx								; Increment index
	


	jmp getNextTangentMatch.nextTangent



	.matchFound:
	mov rbx, [getNextTangentMatch.tangentItemAddress]
	add rbx, ListItem.item
	mov r13, [rbx]
	mov [getNextTangentMatch.tangentMatch], r13

	jmp getNextTangentMatch.end



	.end:


	mov rax, [getNextTangentMatch.tangentMatch]

	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0



;------------
;   Gets the prior item match with List's gradientNesting or 0 when none exist
;   Returns List item or 0 when no matches exist
;------------
getPriorTangentMatch:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*12);((8)+(8))

	;mov rcx, rcx 
	
	label .listAddress qword at rbp-8 
	label .item qword at rbp-16 
	label .itemMatch qword at rbp-24 
	label .itemIndex qword at rbp-32 
	label .priorIndex qword at rbp-40 		; Index before matching
	label .priorNesting qword at rbp-48 		; Nesting before matching
	label .priorGradientIndex qword at rbp-56 	; Gradient Index before matching
	label .tangentMatch qword at rbp-64 
	label .gradientIndex qword at rbp-72 
	label .tangentNesting qword at rbp-80 
	label .itemsCount qword at rbp-88 
	label .tangentItemAddress qword at rbp-96 

	
	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	mov [getPriorTangentMatch.listAddress], rcx
	;mov [getNestingAtNextMatch.item], rdx



	mov rcx, 0
	mov [getPriorTangentMatch.tangentMatch], rcx	; Begin as 0


	mov rbx, [getPriorTangentMatch.listAddress]

	mov r8, rbx
	add r8, List.index
	mov rcx, [r8]
	mov [getPriorTangentMatch.gradientIndex], rcx
	mov r9, rbx
	add r9, List.gradientNesting
	mov rdx, [r9]
	mov [getPriorTangentMatch.tangentNesting], rdx
	mov r8, rbx
	add r8, List.itemsCount
	mov rax, [r8]
	sub rax, 1
	mov [getPriorTangentMatch.itemsCount], rax
	mov rax, 0

	mov r8, rbx
	add r8, List.firstItem
	mov rdx, [r8]
	mov [getPriorTangentMatch.tangentItemAddress], rdx
	

	mov rcx, 0
	cmp rcx, [getPriorTangentMatch.gradientIndex]
	je getPriorTangentMatch.priorTangent					; Start at first index	



	.nextItem:	
	mov rbx, [getPriorTangentMatch.listAddress]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov r8, [rbx]
	mov r9, [rdx]
	cmp r8, r9
	jnl getPriorTangentMatch.end



	mov r11, [getPriorTangentMatch.tangentItemAddress]
	add r11, ListItem.next
	mov r12, [r11]
	mov [getPriorTangentMatch.tangentItemAddress], r12			; Next

	mov rbx, [getPriorTangentMatch.listAddress]
	add rbx, List.index
	mov rcx, [rbx]
	add rcx, 1b
	mov [rbx], rcx								; Increment index

	cmp rcx, [getPriorTangentMatch.gradientIndex]
	je getPriorTangentMatch.priorTangent	

	jmp getPriorTangentMatch.nextItem


	.priorTangent:	
	mov rbx, [getPriorTangentMatch.listAddress]
	add rbx, List.index
	mov r8, [rbx]
	mov r9, 0
	cmp r8, r9
	jnge getPriorTangentMatch.end						; First List index or later, never before


	mov r11, [getPriorTangentMatch.tangentItemAddress]
	cmp r11, 0
	je getPriorTangentMatch.end						; No prior
	add r11, ListItem.nesting
	mov r12, [r11]
	cmp r12, [getPriorTangentMatch.tangentNesting]
	je getPriorTangentMatch.matchFound	

	mov r11, [getPriorTangentMatch.tangentItemAddress]
	add r11, ListItem.previous
	mov r12, [r11]
	mov [getPriorTangentMatch.tangentItemAddress], r12			; Previous


	mov rbx, [getPriorTangentMatch.listAddress]
	add rbx, List.index
	mov rcx, [rbx]
	sub rcx, 1b
	;cmp rcx, 0
	;jl getPriorTangentMatch.end
	mov [rbx], rcx								; Safely decrement index
	

	jmp getPriorTangentMatch.priorTangent



	.matchFound:
	mov rbx, [getPriorTangentMatch.tangentItemAddress]
	add rbx, ListItem.item
	mov r13, [rbx]
	mov [getPriorTangentMatch.tangentMatch], r13

	jmp getPriorTangentMatch.end



	.end:


	mov rax, [getPriorTangentMatch.tangentMatch]

	add rsp, 8	
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0




initListStruc:					;Initialization checks not needed, remove later
	mov rbx, [listInitialized]
	cmp rbx, 0
	jne listStrucInitialized
	
	mov [listInitialized], 1

	listStrucInitialized:
	mov [list.firstItem], 0
	mov [list.itemsCount], 0
	mov [list.isBlankList], 0


	retn 0

initListItemStruc:
	mov rbx, [listItemInitialized]
	cmp rbx, 0
	jne listItemStrucInitialized
	
	mov [listItemInitialized], 1

	listItemStrucInitialized:
	mov [listItem.previous], 0
	mov [listItem.next], 0
	mov [listItem.item], 0


	retn 0

initLastListItemStruc:
	mov rbx, [lastListItemInitialized]
	cmp rbx, 0
	jne lastListItemStrucInitialized
	
	mov [lastListItemInitialized], 1

	lastListItemStrucInitialized:
	mov [lastListItem.previous], 0
	mov [lastListItem.next], 0
	mov [lastListItem.item], 0


	retn 0                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
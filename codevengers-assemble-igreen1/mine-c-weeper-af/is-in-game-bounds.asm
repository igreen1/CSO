;	This function will check if a given x,y coordinates is within the game bounds
;	Params: *game, int x, int y
;	Return: 0 for false, 1 for true
;	To run nasm -felf64 is-in-game-bounds.asm &&gcc -no-pie string-plus.c io-utilities.c mine-c-weeper.c is-in-game-bounds.o mine-c-weeper-game.c && ./a.out
; 	:)

			global	is_in_game_bounds

			section	.text
			extern puts
			extern atoi
			extern sizeof

is_in_game_bounds:

			;Note for self, by convention (and the audience :) help you understand this code)
			; rdi holds pointer to game
			; rsi holds x
			; rdx holds y

			;first, reserve registers for internal use non-destructive
			push r12
			push r13
			push rdi
			push rsi
			push rdx

			;because I only use 32 bits, junk data could ruin this
			;so, just set them entirely to 0
			xor r12, r12
			xor r13, r13

			cmp rsi, 0				; check if x,y >= 0; if not, return false
			jl false				; could check against r12, r13 but this is more readable

			cmp rdx, 0	
			jl false

			;below, I check the bounds given by the *game structure 
			; move the bounds to r12, r13 and check against the x,y input
			; super simple

			mov r12d, [edi]			;use the last 32 bits since int is 32 bits
			mov r13d, [edi+4]

			cmp rsi, r12			; Since the leadings bits are 0s doesn't matter to use 64 bit comparison
			jge false				; and switching to the 32 bit registers breaks the program because of the way c passes in integer arguments into rsi

			cmp rdx, r13
			jge false

			jmp	true				;If no bounds are violated, return true


true:
			mov	rax, 1
			jmp finished

false:
			xor	rax, rax
			jmp finished

finished:
			pop rdx					; Get the values back and return
			pop rsi
			pop rdi
			pop r13
			pop r12
			ret 
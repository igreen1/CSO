;	This program will take a simple calculation (addition or subtraction) and perform it
;	input: [number] +/- [number]
;	output: Result of operation
; 	To run: nasm -felf64 addsub-func.asm && gcc -no-pie addsub-func.o && ./a.out [number] +/- [number]		
			global	add
			global subtract
			extern	atoi
			extern	strlen
			extern	strncmp
			extern	printf
			extern	puts

			section	.text
			
add:
			push    r12                     ; The necessity of these will depend on implementation;
			push    r13                     ; this is mainly a reminder to preserve any callee-save
			push    r14                     ; registers that you might use.
			push 	rdi
			push 	rsi
			;at this point we assume
			; rdi holds one variable
			; rsi holds another
			; and we are adding them


			xor r12, r12					; clear variables since sometimes c passes 32 bits
			xor r13, r13
			xor r14, r14

			mov r12, rdi					; store our variables since we will need to destroy them for printf
			mov r13, rsi

			mov r14, r12					; mov r12 to r14 then add r13 to it so
			add	r14, r13					; r14 = r12 - r13 :)

			mov rax, r14

			pop		rsi
			pop		rdi
			pop     r14
			pop     r13
			pop     r12
			ret

subtract:
			push    r12                     ; The necessity of these will depend on implementation;
			push    r13                     ; this is mainly a reminder to preserve any callee-save
			push    r14                     ; registers that you might use.
			push	rdi
			push 	rsi

			;at this point we assume
			; rdi holds one variable
			; rsi holds another
			; and we are adding them


			xor r12, r12					; clear variables since sometimes c passes 32 bits
			xor r13, r13
			xor r14, r14

			mov r12, rdi					; store our variables since we will need to destroy them for printf
			mov r13, rsi

			mov r14, r12					;mov r12 to r14 then add r13 to it so
			sub	r14, r13					;r14 = r12 - r13 :)

			mov rax, r14

			pop		rsi
			pop		rdi
			pop     r14
			pop     r13
			pop     r12
			ret


main:
			cmp     rdi, 4
			jne     incorrectArgumentCount

			push    r14                     ; registers that you might use.
			push	rdi
			push	rsi

			; Implement add/subtract here!
			; - operand conversion
			; - operator check
			; - ***** CALL THE RIGHT FUNCTION *****
			; - result display

			
			
			;first find length
			push rsi
			mov  rdi, [rsi+16] 
			call strlen
			mov  r14, rax
			pop rsi

			push rsi
			mov  rdi, [rsi+16]					;strncmp(inputOP, minusOP, length_of_inputOP)
			mov  rsi, minusOperator
			mov	rdx, r14
			call strncmp
			pop rsi

			cmp	rax, 0							; if above returned zero, inputOp = minusOP
			je asm_call_sub

			push rsi							;strncmp(inputOP, plusOP, length_of_inputOP)
			mov rdi, [rsi+16]
			mov rsi, plusOperator
			mov rdx, r14
			call strncmp
			pop rsi

			cmp rax, 							; if above returned zero, inputOp = plusOP
			je asm_call_add
			
			jmp incorrectOperator				; neither minus or plus, return an error


asm_call_sub:

				push rsi						;save these guys for later (don't destroy values)
				push r12
				push r13

				push rsi
				mov rdi, [rsi+8]				;convert to integers and store in r12, r13
				call atoi
				mov r12, rax
				pop rsi

				push rsi						;convert to integers and store in r12, r13
				mov rdi, [rsi+24]
				call atoi
				mov r13, rax
				pop rsi

				;put r12, r13 into rdi, rsi. I save rsi over this whole function so no worries
				mov rdi, r12
				mov rsi, r13
				call subtract
				
				;print (rax holds value)
				mov rdi, resultFormat			; printf(resultFormat, input1, minus, input2, result);
				mov rsi, r12
				mov rdx, minusOperator
				mov rcx, r13
				mov r8, rax
				xor rax, rax
				call printf
					
				;get my safe values back and return
				pop r13
				pop r12
				pop rsi
				jmp finished

asm_call_add:

				push rsi		;save rsi for later :)
				push r12
				push r13

				push rsi
				;convert to integers and store in r12, r13
				mov rdi, [rsi+8]
				call atoi
				mov r12, rax
				pop rsi

				push rsi
				mov rdi, [rsi+24]
				call atoi
				mov r13, rax
				pop rsi

				;put r12, r13 into rdi, rsi. I save rsi over this whole function so no worries
				mov rdi, r12
				mov rsi, r13
				call add
				
				;print (rax holds value)
				mov rdi, resultFormat			; printf(resultFormat, input1, minus, input2, result);
				mov rsi, r12
				mov rdx, plusOperator
				mov rcx, r13
				mov r8, rax
				xor rax, rax
				call printf
					
				;get my safe values back and return
				pop r13
				pop r12
				pop rsi
				jmp finished


finished:
			pop		rsi
			pop		rdi
			pop     r14
			ret

incorrectArgumentCount:
			mov	rdi, incorrectArgumentCountMessage
			call	puts
			ret

incorrectOperator:
			mov	rdi, incorrectOperatorMessage
			call	puts
			jmp	finished

			section	.data
plusOperator:		db	"+", 0
minusOperator:		db	"-", 0
resultFormat:		db	"%d %s %d = %d", 10, 0

testFormat: db "%d %d",0

incorrectArgumentCountMessage:
			db	"To use this program, either enter <number> + <number> or <number> - <number>.", 0

incorrectOperatorMessage:
			db	"This program only recognizes + or -.", 0

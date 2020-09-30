;	This program will take two integer inputs and output their difference
;	Input: [int] [int]
;	Output: the result of the operation in a nice format
;	nasm -felf64 sub.asm && gcc -no-pie sub.o && ./a.out [int] [int]	
		
			
			global	main
			extern	atoi
			extern	printf
			extern	puts

			section	.text
main:
			cmp	rdi, 3
			jne	incorrectArgumentCount

			push    r12                     ; The necessity of these will depend on implementation;
			push    r13                     ; this is mainly a reminder to preserve any callee-save
			push    r14                     ; registers that you might use.
			push 	rdi
			push	rsi

                        ; Implement subtraction here!

			;Convert rsi[1] and rsi[2] to integers in r12, r13 respectively
			push	rsi				;save rsi (argv) for later
			mov rdi, [rsi+8]		;move the first argv[1] into rdi
			call atoi				;to integer
			mov r12, rax			;save this result in r12 register
			pop 	rsi				;get our argv back

			push	rsi				;same as above but store in r13
			mov rdi, [rsi+16]
			call atoi
			mov r13, rax
			pop 	rsi

			mov r14, r12			;mov r12 to r14 then add r13 to it so
			sub	r14, r13			;r14 = r12 - r13 :)

			;now, print it all with printf and format given
			;very straigth forward, put eaceh argument in the right register
			mov rdi, format
			mov rsi, r12
			mov rdx, r13
			mov rcx, r14
			xor rax, rax
			call printf

			pop rsi
			pop rdi
			pop	r14
			pop	r13
			pop	r12
			ret

incorrectArgumentCount:
			mov	rdi, incorrectArgumentCountMessage
			call	puts
			ret

			section	.data
incorrectArgumentCountMessage:
			db	"Two arguments are needed in order to perform subtraction.", 0
format:			db	"%d - %d = %d", 10, 0

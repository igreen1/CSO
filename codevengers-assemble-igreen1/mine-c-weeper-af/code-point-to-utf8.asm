;	This function takes UTF codepoints and outputs the respective characters
;	Input: command line arguments (any amount) of UTF codepoints in U+[] format
; 	Output: The characters in unicode
; 	To run: nasm -felf64 code-point-to-utf8.asm && gcc -no-pie code-point-to-utf8.o && ./a.out [codepoints]	


			global	main
			extern	puts
			extern	sscanf
			extern	printf
			extern	emit_utf_8

			section	.text
main:

			push r12
			push r13
			push r14
			push rdi
			push rsi

			cmp rdi, 1
			je argumentsError			;If only 1 argument, error; else okay

			add rsi, 8					; we are skipping argv[0] for this program ;)
			dec rdi						; makes a recursive function easier

loop_over_argv:							;start of loop

			push rdi					;save our values for later
			push rsi 

			mov r12, [rsi]				; if there is an error, I will need to access rsi
										; this makes my life waaayyy easier

			mov rdi, [rsi]				; sscanf(agrv[i], format, &codePoint)
			mov rsi, codePointFormat
			mov rdx, codePoint
			call sscanf

			cmp rax, 1					; if sscanf != 1, output error
			jne formatError

emit:									; label purely for my sanity
										; if sscanf == 1, emit utf
			mov rdi, [codePoint]
			call emit_utf_8

			jmp continue

formatError:							; called when an argv[i] has incorrect value
			
			
			mov rdi, incorrectFormat	; printf(format, argv[i])
			mov rsi, r12
			call printf

			jmp continue 				; keep this loop going :)


continue:								; end of loop. checks conditions and either loops or exits

			pop rsi						; get our values and iterate on them
			pop rdi

			add rsi, 8					; go to argv[i+1]
			dec rdi						; if(--rdi == 0) we're done
			jnz loop_over_argv
			
			jmp finished
			; You can use the echo.asm sample program as a starting point
			; for this, but note that the solution differs in significant
			; ways so be ready to modify it as needed.
			;jmp loop_over_argv

finished:
			mov rdi, goodbyeMSG			; for now, just puts a newline for console output
			call puts					; did it this way to put something like "goodbye ! :)"

			pop rsi
			pop rdi
			pop	r14
			pop	r13
			pop	r12
			ret

argumentsError:		
			mov	rdi, argumentsRequiredMessage
			call	puts

			mov	rdi, argumentDescription
			call	puts

			xor	rax, rax
			inc	rax
			ret


			section	.data
			; The following definitions are here to get you started and to standardize
			; error messages but of course, feel free to define more as needed.
argumentsRequiredMessage:
			db	"This program requires one or more command line arguments,", 0
argumentDescription:	db	"one for each code point to encode as UTF-8.", 0
incorrectFormat:	db	"(%s incorrect format)", 0
codePointFormat:	db	"U+%6X", 0
goodbyeMSG: db "",0

			section	.bss
codePoint:		resb	8			; The code point from sscanf should go here.

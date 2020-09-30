; ----------------------------------------------------------------------------------------
; Creates folder 'Ian' then puts "is cool.txt" inside it 
;       and creates a link to 'is cool.txt" as "so cool"
;       then creates folder dondi and links 'so cool' to 'Ian/is cool' - because you're cool too :)
;           (sorry Alexis, I got tired after 5 commands)
;
;     nasm -felf64 combo.asm && gcc -no-pie combo.o && ./a.out
; ----------------------------------------------------------------------------------------

          global    main
          section   .text
main:                                               ;This is called by the C library startup code
            mov         rax, 83                     ;   mkdir
            mov         rdi, folder_name            ;   mkdir [folder_name]
            mov         rsi, 0777o                  ;   give me permission!
            syscall                                 ;   exceute

            mov         rax, 85                     ;   create file
            mov         rdi, file_name              ;   create file [file_name]
            mov         rsi, 0777o                  ;   permissions! (everyone allowed in :) )
            syscall

            mov         rax, 86                     ;   link (ln)
            mov         rdi, file_name              ;   link [old path]
            mov         rsi, link_name              ;   link [old path] [new path]
            syscall                                 ;   creates link from the file 'is cool.txt' to 'so cool' in folder Ian

            mov         rax, 83                     ;   mkdir 'dondi' with permission 777
            mov         rdi, second_folder
            mov         rsi, 0777o
            syscall

            mov         rax, 86                     ;   ln Ian/is cool.txt dondi/so_cool
            mov         rdi, file_name
            mov         rsi, second_link
            syscall

            ret                                     ;   return i think, its from Toal honestly, but it breaks if I remove it ...     

second_link:
            db        "dondi/so_cool",0             ;   again, you said not to change directories so I won't

second_folder:
            db        "dondi",0                     ;   i'm not beyond pandering

folder_name:
            db        "Ian",0                       ;   the name of directory to create

file_name:
            db        "Ian/is cool.txt",0           ;   The text file to make

link_name:
            db        "Ian/so cool",0               ;   I'm not messing with cd based on what you said
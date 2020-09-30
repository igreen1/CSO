; ----------------------------------------------------------------------------------------
; Creates folder 'A Name' then renames it to 'Another Name' :)
;   this isn't for a grade, just for testing ;)
;    
; ----------------------------------------------------------------------------------------

          global    main


          section   .text
main:                                       ; This is called by the C library startup code
          mov       rax, 83                 ;   mkdir
          mov       rdi, old_name           ;   mkdir [oldname]
          syscall                           ;   exceute
          mov       rax, 82                 ;   rename
          mov       rdi, old_name           ;   already there but juuust to be sure in case I mess with stuff in between
          mov       rsi, new_name           ;   rename from old name to new name
          syscall                           ;  
          ret                     
new_name:
          db        "Another name",0    ;the name of direcetory after the fact

old_name:
          db        "A Name",0       ; Note strings must be terminated with 0 in C
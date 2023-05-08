.486
.model flat, stdcall
.stack 4096

include winapi.inc 
include macros.inc 

.data
	txt1 db 'Wpisz 16 bitów: ',0
	txt2 db 'nacisnij ENTER',0
	txt3 db '[bin] = '
	txt4 db '[oct] = '
	txt5 db '[hex] = '
	txt6 db '[dec] = '
	wynik dw 0
	wynik_2 dw 0
.code
main proc
ustaw_kursor 2,2
	wyswietl txt1
	ustaw_kursor 3,2
	xor ax,ax
	
	mov ecx,16
ety1:
	push ecx

ety2:
	pob_znak

	cmp al,8		
	je ety3

	cmp al,'q'		
	je zamknij
	cmp al,'0'
	jb  ety2
	cmp al,'1'
	ja  ety2
	
	call zapisz
	pop ecx
	loop ety1

	ustaw_kursor 5,2
	wyswietl txt2

ety4:
	pob_znak
	cmp al,0Dh	;Enter
	jne ety4
	mov ecx, 16
	call pokaz_bin
	call pokaz_oct
	call pokaz_hex
	call pokaz_dec
	end_prog

ety3:
	pop ecx
	cmp ecx,16
	je  ety1
	
	inc ecx
	push ecx
	call usun
	wysw_znak 8
	wysw_znak ' '
	wysw_znak 8
	
	jmp ety2
main endp
zapisz proc
	push ax
	wysw_znak al
	pop ax
	xor ecx, ecx
	mov cx, [wynik]
	shl cx, 1
	sub ax, '0'
	add cx, ax
	mov [wynik], cx
	mov [wynik_2], cx
	
	ret
zapisz endp
zamknij proc
	end_prog
zamknij endp
usun proc
	mov cx, [wynik]
	shr cx, 1
	mov [wynik], cx
	ret
usun endp

pokaz_bin proc
	ustaw_kursor 7,2
	wyswietl txt3
	xor bx,bx
	mov bx,[wynik]
	mov ecx,16
ety1:
	push ecx
	rcl bx,1
	jc ety2
	mov dx,'0'
	jmp ety3
ety2:
	mov dx,'1'
ety3:
	wysw_znak dl
	pop ecx
	loop ety1

	ret

pokaz_bin endp
	
pokaz_oct proc
	ustaw_kursor 8,2
	
	wyswietl txt4

	mov ax,[wynik]  ;
	shr ax,15			   
	cmp al, 1
	je ety1
	jmp ety2
	ety1:
	mov ax, [wynik]
	neg ax
	mov [wynik], ax
	wysw_znak '-'
	ety2:

	mov ax,[wynik]  ; 0			
	shr ax,15
	add al,'0'			
	wysw_znak al

	mov ax,[wynik]  ; 1
	shl ax,1			
	shr ax,13
	add al,'0'			
	wysw_znak al

	mov ax,[wynik] ; 2
	shl ax, 4
	shr ax, 13
	add al, '0'
	wysw_znak al

	mov ax,[wynik] ; 3
	shl ax, 7
	shr ax, 13
	add al, '0'
	wysw_znak al

	mov ax,[wynik] ; 4
	shl ax, 10
	shr ax, 13
	add al, '0'
	wysw_znak al

	mov ax,[wynik] ; 5
	shl ax, 13
	shr ax, 13
	add al, '0'
	wysw_znak al

	mov ax, [wynik_2]
	mov [wynik], ax
 ret
pokaz_oct endp
pokaz_hex proc

	ustaw_kursor 9,2
	wyswietl txt5
	xor eax,eax

	mov ax,[wynik]  ;
	shr ax,15			   
	cmp al, 1
	je ety1
	jmp ety2
	ety1:
	mov ax, [wynik]
	neg ax
	mov [wynik], ax
	wysw_znak '-'
	ety2:

	mov ax,[wynik]
	shr ax, 12
	cmp al, 9
	ja ety3
	add al, '0'
	jmp ety3i
	ety3:
	add al, 55
	ety3i:
	wysw_znak al

	mov ax,[wynik]
	shl ax, 4
	shr ax, 12
	cmp al, 9
	ja ety4
	add al, '0'
	jmp ety4i
	ety4:
	add al, 55
	ety4i:
	wysw_znak al

	mov ax,[wynik]
	shl ax, 8
	shr ax, 12
	cmp al, 9
	ja ety5
	add al, '0'
	jmp ety5i
	ety5:
	add al, 55
	ety5i:
	wysw_znak al

	mov ax,[wynik]
	shl ax, 12
	shr ax, 12
	cmp al, 9
	ja ety6
	add al, '0'
	jmp ety6i
	ety6:
	add al, 55
	ety6i:
	wysw_znak al

	mov ax, [wynik_2]
	mov [wynik], ax
	ret
pokaz_hex endp
pokaz_dec proc
	ustaw_kursor 10,2
	wyswietl txt6
	xor eax,eax

	mov ax,[wynik]  ;
	shr ax,15			   
	cmp al, 1
	je ety1
	jmp ety2
	ety1:
	mov ax, [wynik]
	neg ax
	mov [wynik], ax
	wysw_znak '-'
	ety2:

	mov ax, [wynik]
	mov bx,10
	div bx
	add dx, '0'
	push dx


	mov bx,10
	cmp ax, 0
	je ety3
	xor edx, edx
	div bx
	add dx, '0'
	push dx

	
	mov bx,10
	cmp ax, 0
	je ety4
	xor edx, edx
	div bx
	add dx, '0'
	push dx

	mov bx,10
	cmp ax, 0
	je ety5
	xor edx, edx
	div bx
	add dx, '0'
	push dx
	
	add al, '0'
	wysw_znak al
	pop ax
	wysw_znak al
	ety5:
	pop ax
	wysw_znak al
	ety4:
	pop ax
	wysw_znak al
	ety3:
	pop ax
	wysw_znak al
	ret
pokaz_dec endp

	public main
END main
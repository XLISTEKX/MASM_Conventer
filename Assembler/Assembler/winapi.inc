; --------------------[ PROTOTYPY I STA£E WYWO£AÑ WINAPI ] ------------------------
; ---------------------------------------------------------------------------------
; Win32 Console handles
STD_INPUT_HANDLE EQU -10
STD_OUTPUT_HANDLE EQU -11		; predefined Win API constant
STD_ERROR_HANDLE EQU -12

; sta³e b³êdów
INVALID_HANDLE_VALUE EQU -1


KEY_EVENT       =  1
MOUSE_EVENT     =  2
WINDOW_BUFFER_SIZE_EVENT = 4          ; window change event record
MENU_EVENT      = 8                   ; menu event record
FOCUS_EVENT     = 16                  ; focus change

; ControlKeyState constants (used by ReadKey)
KBDOWN_FLAG = 00000001h		; Bit set for press, clear for release



; Nadpisanie aliansu z WINAPI - domyœlnie jest ustawione na przyjmowanie ASCII (WriteConsoleA)

GetCommandLine	EQU <GetCommandLineA>
MessageBox      	EQU <MessageBoxA>
PeekConsoleInput	EQU <PeekConsoleInputA>
ReadConsole 	EQU <ReadConsoleA>
ReadConsoleInput	EQU <ReadConsoleInputA>
WriteConsole 	EQU <WriteConsoleA>
WriteConsoleOutputCharacter 	EQU <WriteConsoleOutputCharacterA>
wsprintf 		EQU <wsprintfA>


HANDLE TEXTEQU <DWORD>		; used in Win32 API documentation

COORD STRUCT
	X WORD ?
	Y WORD ?
COORD ENDS

KEY_EVENT_RECORD STRUCT
	bKeyDown          DWORD ?
	wRepeatCount      WORD  ?
	wVirtualKeyCode   WORD  ?
	wVirtualScanCode  WORD  ?
	UNION uChar
	  UnicodeChar     WORD  ?
	  AsciiChar       BYTE  ?
	ENDS
	dwControlKeyState DWORD ?
KEY_EVENT_RECORD ENDS

MOUSE_EVENT_RECORD STRUCT
	dwMousePosition         COORD <>
	dwButtonState           DWORD ?
	dwMouseControlKeyState  DWORD ?  
	dwEventFlags            DWORD ?
MOUSE_EVENT_RECORD ENDS

WINDOW_BUFFER_SIZE_RECORD STRUCT
	dwSize COORD <>
WINDOW_BUFFER_SIZE_RECORD ENDS

MENU_EVENT_RECORD STRUCT
	dwCommandId DWORD ?		; reserved
MENU_EVENT_RECORD ENDS

FOCUS_EVENT_RECORD STRUCT
  bSetFocus DWORD ?
FOCUS_EVENT_RECORD ENDS

INPUT_RECORD STRUCT
	EventType WORD ?
	ALIGN DWORD	; align next field on doubleword boundary
	UNION Event
		KEY_EVENT_RECORD <>
		MOUSE_EVENT_RECORD <>
		WINDOW_BUFFER_SIZE_RECORD <>
		MENU_EVENT_RECORD <>
		FOCUS_EVENT_RECORD <>
	ENDS
INPUT_RECORD ENDS



; Buttons:
MB_OK         = 0
MB_OKCANCEL   = 1
MB_ABORTRETRYIGNORE = 2
MB_YESNOCANCEL = 3
MB_YESNO       = 4
MB_RETRYCANCEL = 5
MB_CANCELTRYCONTINUE = 6
MB_HELP        =  4000h          ; does not close the window

; ---------------------------------------------------------------------------------
AllocConsole PROTO 		; nowa konsola

CloseHandle PROTO,		; close file handle
	hObject:DWORD

ExitProcess PROTO,                  	; exit program
	dwExitCode:DWORD		; return code


FlushConsoleInputBuffer PROTO,		; flush the input buffer
	hConsoleInput:HANDLE		; standard input handle

FreeConsole PROTO 			; uwolnij konsolê

GetCommandLine PROTO		; returns pointer to command-line string

GetConsoleCP PROTO		; returns code page ID in eax

GetLastError PROTO		; get most recent error return value

GetStdHandle PROTO,               	; get standard handle
	nStdHandle:HANDLE  		; type of console handle

MessageBoxA PROTO,		; displays a pop-up message box
	hWnd:DWORD,		; handle to window (can be null)
	lpText:PTR BYTE,		; string for inside of dialog box
	lpCaption:PTR BYTE,		; string for dialog box title
	uType:DWORD		; contents and behavior of the dialog

PeekConsoleInput PROTO,
	hConsoleInput:HANDLE,		; input handle
	lpBuffer:PTR BYTE,		; pointer to buffer
	nLength:DWORD,    		; number of chars to read
	lpNumberOfEventsRead:PTR DWORD  	; ptr to number of events read
	
ReadConsole PROTO,
	hConsoleInput:HANDLE,              ; input handle
	lpBuffer:PTR BYTE,                	; pointer to buffer
	nNumberOfBytesToRead:DWORD,    	; number of chars to read
	lpNumberOfCharsRead:PTR DWORD,  	; ptr to number of bytes read
	lpReserved:DWORD               	; (not used)

ReadConsoleInput PROTO,
	hConsoleInput:HANDLE,		; input handle
	lpBuffer:PTR INPUT_RECORD,		; ptr to input record
	nLength:DWORD,		; request number of recs
	lpNumberOfEventsRead:PTR DWORD	; ptr to number of bytes read

	
SetConsoleMode PROTO,
	hConsoleHandle:HANDLE,		; output handle
	dwMode:DWORD		; console mode flags

SetConsoleCursorPosition PROTO,
	hConsoleOutput:HANDLE,		; output handle
	dwCursorPosition:COORD		; screen X,Y coordinates

Sleep PROTO,	   	; sleeep for n milliseconds
	dwMilliseconds:DWORD

WriteConsole PROTO,		; write a buffer to the console
	hConsoleOutput:HANDLE,		; output handle
	lpBuffer:PTR BYTE,		; pointer to buffer
	nNumberOfCharsToWrite:DWORD,		; size of buffer
	lpNumberOfCharsWritten:PTR DWORD,		; ptr to number of bytes written
	lpReserved:DWORD		; (not used)

WriteConsoleOutputCharacter PROTO,
	hConsoleOutput:HANDLE,		; console output handle
	lpCharacter:PTR BYTE,		; pointer to buffer
	nLength:DWORD,		; size of buffer
	dwWriteCoord:COORD,		; first cell coordinates
	lpNumberOfCharsWritten:PTR DWORD	; output count

wsprintf PROTO NEAR C,
	lpOut:PTR BYTE,		; output buffer
	lpFmt:PTR BYTE,		; format-control string
	vars :VARARG		; optional arguments

;-------------------------------------------------------------------------
printf PROTO C,		; Std C library function
	format:PTR BYTE, args:VARARG		; (in libc.lib)

scanf PROTO C,		; Std C library function
	format:PTR BYTE, args:VARARG		; (in libc.lib)
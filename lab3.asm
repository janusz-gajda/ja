; �������������������������������������������������������������������������

      .486                      ; create 32 bit code
      .model flat, stdcall      ; 32 bit memory model
      option casemap :none      ; case sensitive

      include \masm32\include\dialogs.inc
      include simple.inc

      dlgproc PROTO :DWORD,:DWORD,:DWORD,:DWORD
      app_path PROTO :DWORD
      app_name PROTO :DWORD

    .code

; �������������������������������������������������������������������������

start:

      mov hInstance, FUNC(GetModuleHandle,NULL)

      call main

      invoke ExitProcess,eax

; �������������������������������������������������������������������������

main proc

    Dialog "Paluch & Gajda Productiuon INC","MS Sans Serif",10, \            ; caption,font,pointsize
            WS_OVERLAPPED or WS_SYSMENU or DS_CENTER, \     ; style
            2, \                                            ; control count
            50,50,150,80, \                                 ; x y co-ordinates
            1024                                            ; memory buffer size

    DlgButton "&Barka",WS_TABSTOP,8,40,60,15,IDCANCEL
    ;                         x,y,width,height
    DlgButton "&Watykanczyk",WS_TABSTOP,78,40,60,15,IDOK
    DlgStatic "Simple Dialog Written In MASM32",SS_CENTER,2,20,140,9,100

    CallModalDialog hInstance,0,dlgproc,NULL

    ret

main endp

; �������������������������������������������������������������������������

dlgproc proc hWin:DWORD,uMsg:DWORD,wParam:DWORD,lParam:DWORD
    LOCAL hMem$ :DWORD

    .if uMsg == WM_INITDIALOG
      invoke SendMessage,hWin,WM_SETICON,1,FUNC(LoadIcon,NULL,IDI_ASTERISK)

    .elseif uMsg == WM_COMMAND
      .if wParam == IDCANCEL
        call sciezka
      .elseif wParam == IDOK
        call watykanczyk
      .endif
    .elseif uMsg == WM_CLOSE
      quit_dialog:
        invoke EndDialog,hWin,0

    .endif

    xor eax, eax
    ret

dlgproc endp

sciezka proc
  LOCAL buffer[260]:BYTE
  LOCAL pbuf  :DWORD

    mov pbuf, ptr$(buffer)

    invoke app_path,pbuf
    fn MessageBox,0,pbuf,"app_path",MB_OK

    invoke app_name,pbuf
    fn MessageBox,0,pbuf,"app_path",MB_OK

    ret

sciezka endp

app_path proc buffer:DWORD

  ; ---------------------------------------------------------
  ; call this procedure with the address of a 260 byte buffer
  ; return the path with a trailing "\" at address "buffer"
  ; ---------------------------------------------------------
    invoke GetModuleFileName,NULL,buffer,260

    mov ecx, buffer
    add ecx, eax            ; add length
    add ecx, 1

  @@:                       ; scan backwards to find last "\"
    sub ecx, 1
    cmp BYTE PTR [ecx], "\"
    je @F
    cmp ecx, buffer
    jge @B

  @@:
    mov BYTE PTR [ecx+1], 0 ; truncate string after last "\"

    ret

app_path endp

; ��������������������������������������������������������������������������������������������������

app_name proc buffer:DWORD

  ; ---------------------------------------------------------
  ; call this procedure with the address of a 260 byte buffer
  ; returns the file name at address "buffer"
  ; ---------------------------------------------------------
    push ebx

    invoke GetModuleFileName,NULL,buffer,260

    mov ecx, buffer
    add ecx, eax                    ; add length
    add ecx, 1

  @@:                               ; scan backwords to find last "\"
    sub ecx, 1
    cmp BYTE PTR [ecx], "\"
    je @F
    cmp ecx, buffer
    jge @B

  @@:
    add ecx, 1
    mov eax, buffer
    or ebx, -1

  @@:                               ; overwrite buffer with file name
    add ebx, 1
    movzx edx, BYTE PTR [ecx+ebx]
    mov [eax+ebx], dl
    test dl, dl
    jnz @B

    pop ebx

    ret

app_name endp

watykanczyk proc
  LOCAL swid  :DWORD
    LOCAL shgt  :DWORD
    LOCAL dwid  :DWORD
    LOCAL hDC   :DWORD
    LOCAL cDC   :DWORD
    LOCAL hScr  :DWORD
    LOCAL hBmp  :DWORD
    LOCAL hOld  :DWORD

    mov hScr, 0                                         ; screen handle is zero
    mov hDC,  rv(GetDC,hScr)                            ; get its DC
    mov swid, rv(GetSystemMetrics,SM_CXSCREEN)          ; get screen width
    add eax,  eax                                       ; double it
    mov dwid, eax                                       ; store it in a variable
    mov shgt, rv(GetSystemMetrics,SM_CYSCREEN)          ; get the screen height
    mov hBmp, rv(CreateCompatibleBitmap,hDC,dwid,shgt)  ; make double width bitmap
    mov cDC,  rv(CreateCompatibleDC,hDC)                ; create a DC for it
    mov hOld, rv(SelectObject,cDC,hBmp)                 ; select compatible bitmap into compatible DC

  ; ----------------------------------------
  ; blit 2 copies of the current screen side
  ; by side onto the compatible bitmap.
  ; ----------------------------------------
    invoke BitBlt,cDC,0,0,swid,shgt,hDC,0,0,SRCCOPY
    invoke BitBlt,cDC,swid,0,swid,shgt,hDC,0,0,SRCCOPY

  ; --------------------------------------------------------
  ; repeatedly blit the shifting image to the current screen
  ; --------------------------------------------------------
    push esi
    mov esi, swid
  @@:
    invoke BitBlt,hDC,0,0,swid,shgt,cDC,esi,0,SRCCOPY
    invoke Sleep, 20                                    ; slow it up a bit
    sub esi, 8
    jns @B

    pop esi

    invoke SendMessage,0,WM_PAINT,hDC,0                 ; clean up the mess after

    invoke DeleteObject,hBmp                            ; delete the compatible bitmap
    invoke SelectObject,cDC,hOld                        ; reselect the old one
    invoke DeleteDC,cDC                                 ; delete the compatible DC
    invoke ReleaseDC,hScr,hDC                           ; release the screen DC

    ret
watykanczyk endp
; �������������������������������������������������������������������������

end start
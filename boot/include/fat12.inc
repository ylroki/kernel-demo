; FAT12 boot sector format
BS_OEMName db 'ylroki  '; 8 bytes
BPB_BytsPerSec dw 512
BPB_SecPerClus db 1
BPB_RsvdSecCnt dw 1
BPB_NumFATs db 2
BPB_RootEntCnt dw 224
BPB_TotSec16 dw 2880; 1.44MB/512B
BPB_Media db 0xf0
BPB_FATSz16 dw 9
BPB_SecPerTrk dw 18
BPB_NumHeads dw 2
BPB_HiddSec dd 0
BPB_TotSec32 dd 0
BS_DrvNum db 0
BS_Reserved1 db 0
BS_BootSig db 29h
BS_VolID dd 0
BS_VolLab db 'ylroki     '; 11 bytes
BS_FileSystype db 'FAT12   '; 8 bytes
; end of FAT12  boot sector format

FAT1SectorNo equ 1
RootDirNo	equ 19
RootDirSectors equ 14
DeltaSectorNo equ 17



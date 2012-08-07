<map version="0.9.0">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node CREATED="1337871856572" ID="ID_772912536" MODIFIED="1344340265228" TEXT="Boot">
<node CREATED="1337871909178" ID="ID_1889343576" MODIFIED="1337871961351" POSITION="right" TEXT="According FAT12 format, some definition should added before code"/>
<node CREATED="1337872039109" ID="ID_748993542" MODIFIED="1337872042373" POSITION="right" TEXT="code">
<node CREATED="1337872054032" ID="ID_1681108400" MODIFIED="1337872068785" TEXT="Initialize segment register"/>
<node CREATED="1337872079685" ID="ID_275154318" MODIFIED="1337872095476" TEXT="Clear screen"/>
<node CREATED="1337872103549" ID="ID_861787043" MODIFIED="1337872118855" TEXT="Loop, for each sector">
<node CREATED="1337872137790" ID="ID_1687983110" MODIFIED="1337872183031" TEXT="Read root directory sector"/>
<node CREATED="1337872146058" ID="ID_1833852016" MODIFIED="1337872302910" TEXT="Loop, for each item in sector">
<node CREATED="1337872203249" ID="ID_745273635" MODIFIED="1337872231502" TEXT="Judge whether it is loader.bin">
<node CREATED="1337872398686" ID="ID_1566960598" MODIFIED="1344341596434" TEXT="Yes, load it into a block of memory space, and JMP to there">
<icon BUILTIN="idea"/>
<node CREATED="1344341170005" ID="ID_1578103983" MODIFIED="1344341604910" TEXT="Call int15 to get information of memory"/>
<node CREATED="1344341489029" ID="ID_1872769187" MODIFIED="1344341608707" TEXT="Find kernel.bin and load it"/>
<node CREATED="1344341549495" ID="ID_1093790420" MODIFIED="1344341617979" TEXT="Jmp to protected mode"/>
<node CREATED="1344341565264" ID="ID_697782209" MODIFIED="1344341673518" TEXT="Print infomation of memory"/>
<node CREATED="1344341674325" ID="ID_8850561" MODIFIED="1344341896982" TEXT="Set paging">
<icon BUILTIN="idea"/>
</node>
<node CREATED="1344341898585" ID="ID_1105676398" MODIFIED="1344342042321" TEXT="According to the ELF file format, copy program to memory">
<icon BUILTIN="idea"/>
</node>
</node>
<node CREATED="1337872424779" ID="ID_1182334784" MODIFIED="1344341591287" TEXT="No, continue"/>
</node>
</node>
<node CREATED="1337872263183" ID="ID_77171703" MODIFIED="1344341580305" TEXT="If this sector doesn&apos;t contain loader.bin, continue"/>
</node>
<node CREATED="1337872336374" ID="ID_493941065" MODIFIED="1337872357206" TEXT="Can&apos;t find loader.bin"/>
</node>
<node CREATED="1337871963144" ID="ID_645861885" MODIFIED="1337872036336" POSITION="right" TEXT="Fill file with 0x0 and end with 0xaa55, so that contans 512 bytes"/>
</node>
</map>

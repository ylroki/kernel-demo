<map version="0.9.0">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node CREATED="1337871856572" ID="ID_772912536" MODIFIED="1337871877930" TEXT="Boot">
<node CREATED="1337871909178" ID="ID_1889343576" MODIFIED="1337871961351" POSITION="right" TEXT="According FAT12 format, some definition should added before code"/>
<node CREATED="1337872039109" ID="ID_748993542" MODIFIED="1337872042373" POSITION="right" TEXT="code">
<node CREATED="1337872054032" ID="ID_1681108400" MODIFIED="1337872068785" TEXT="Initialize segment register"/>
<node CREATED="1337872079685" ID="ID_275154318" MODIFIED="1337872095476" TEXT="Clear screen"/>
<node CREATED="1337872103549" ID="ID_861787043" MODIFIED="1337872118855" TEXT="Loop, for each sector">
<node CREATED="1337872137790" ID="ID_1687983110" MODIFIED="1337872183031" TEXT="Read root directory sector"/>
<node CREATED="1337872146058" ID="ID_1833852016" MODIFIED="1337872302910" TEXT="Loop, for each item in sector">
<node CREATED="1337872203249" ID="ID_745273635" MODIFIED="1337872231502" TEXT="Judge whether it is loader.bin">
<node CREATED="1337872398686" ID="ID_1566960598" MODIFIED="1337872456479" TEXT="yes, load it"/>
<node CREATED="1337872424779" ID="ID_1182334784" MODIFIED="1337872436869" TEXT="no, continue"/>
</node>
</node>
<node CREATED="1337872263183" ID="ID_77171703" MODIFIED="1337872325691" TEXT="if this sector doesn&apos;t contain loader.bin, continue"/>
</node>
<node CREATED="1337872336374" ID="ID_493941065" MODIFIED="1337872357206" TEXT="Can&apos;t find loader.bin"/>
</node>
<node CREATED="1337871963144" ID="ID_645861885" MODIFIED="1337872036336" POSITION="right" TEXT="Fill file with 0x0 and end with 0xaa55, so that contans 512 bytes"/>
</node>
</map>

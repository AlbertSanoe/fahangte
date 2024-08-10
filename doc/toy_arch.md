# Design for the toy architecture *tiny-arch*

## introduction to instructions

### non-operand instructions

| Instruction Number | Assembly Instruction |     Usage     |
| :----------------: | :------------------: | :------------: |
|         0         |         NOP         |  displacement  |
|         1         |         HALT         | stop execution |

### one-operand instructions

| Instruction Number | Assembly Instruction |                        Parameter Type                        |                                     Usage                                     |
| :----------------: | :------------------: | :----------------------------------------------------------: | :---------------------------------------------------------------------------: |
|         0         |        STDIN        |            ***reg*** or ***mem***            | read a number from the standard input,<br />strore it in a register or memory |
|         1         |        STDOUT        | ***imme*** or ***reg*** or ***mem*** |                              the standard output                              |
|         2         |         JMP         | ***imme*** or ***reg*** or ***mem*** |               jump to the address pointed by the<br />parameter               |
|         3         |          JE          | ***imme*** or ***reg*** or ***mem*** |                               jump if %ex == 0                               |
|         4         |         JNE         | ***imme*** or ***reg*** or ***mem*** |                                jump if %ex !=0                                |
|         5         |         JLT         | ***imme*** or ***reg*** or ***mem*** |                                jump if %ex <0                                |
|         6         |         JLE         | ***imme*** or ***reg*** or ***mem*** |                                jump if %ex <=0                                |
|         7         |         JGT         | ***imme*** or ***reg*** or ***mem*** |                                jump if %ex >0                                |
|         8         |         JGE         | ***imme*** or ***reg*** or ***mem*** |                                jump if %ex >=0                                |

### two-operand instructions

| Instruction Number | Assembly Instruction | Destination Type |    Source Type    |            Usage            |
| :----------------: | :------------------: | :---------------: | :----------------: | :-------------------------: |
|         0         |         MOV         | ***reg*** | ***reg*** | move data from src to dest |
|         1         |         MOV         | ***reg*** | ***mem*** | move data from src to dest |
|         2         |         MOV         | ***reg*** | ***imme*** | move data from src to dest |
|         3         |         MOV         | ***mem*** | ***reg*** | move data from src to dest |
|         4         |         MOV         | ***mem*** | ***imme*** | move data from src to dest |
|         5         |         ADD         | ***reg*** | ***reg*** |      dest = dest + src      |
|         6         |         ADD         | ***reg*** | ***mem*** |      dest = dest + src      |
|         7         |         ADD         | ***reg*** | ***imme*** |      dest = dest + src      |
|         8         |         ADD         | ***mem*** | ***reg*** |      dest = dest + src      |
|         9         |         ADD         | ***mem*** | ***imme*** |      dest = dest + src      |
|         10         |         SUB         | ***reg*** | ***reg*** |      dest = dest - src      |
|         11         |         SUB         | ***reg*** | ***mem*** |      dest = dest - src      |
|         12         |         SUB         | ***reg*** | ***imme*** |      dest = dest - src      |
|         13         |         SUB         | ***mem*** | ***reg*** |      dest = dest - src      |
|         14         |         SUB         | ***mem*** | ***imme*** |      dest = dest - src      |
|         15         |         MUL         | ***reg*** | ***reg*** |                            |
|         16         |         MUL         | ***reg*** | ***mem*** |                            |
|         17         |         MUL         | ***reg*** | ***imme*** |                            |
|         18         |         MUL         | ***mem*** | ***reg*** |                            |
|         19         |         MUL         | ***mem*** | ***imme*** |                            |
|         20         |         DIV         | ***reg*** | ***reg*** |                            |
|         21         |         DIV         | ***reg*** | ***mem*** |                            |
|         22         |         DIV         | ***reg*** | ***imme*** |                            |
|         23         |         DIV         | ***mem*** | ***reg*** |                            |
|         24         |         DIV         | ***mem*** | ***imme*** |                            |

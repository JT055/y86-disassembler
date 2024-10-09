#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This is an array of register mnemonics in y86
const char *register_names[] =
    {
        "%eax",
        "%ecx",
        "%edx",
        "%ebx",
        "%esp",
        "%ebp",
        "%esi",
        "%edi",
        "UNKNOWN_REGSITER"};

int convertStrToByteCode(const char *str, unsigned char inst[], int size);

int main(int argc, char **argv)
{
  FILE *pFile = NULL;

  char buffer[15];

  if (argc < 2)
  {
    pFile = fopen("./test2.txt", "r");
  }
  else
  {
    pFile = fopen(argv[1], "r");
  }

  if (pFile == NULL)
  {
    printf("Error open test file, please make sure they exist.\n");

    return 0;
  }

  while (fgets(buffer, 15, pFile) && strlen(buffer) > 1)
  {
    //This unsigned char array stores an instruction read from the file
    //As the largest y86 instruction is 6 bytes, there are 6 unsigned char in the array where
    //each represents a byte.
    unsigned char instruction[6] = {0, 0, 0, 0, 0, 0};
    convertStrToByteCode(buffer, instruction, 6);

    //this code here is used to split second bytes into two so that that code is able to get right registor for each opcode.
    unsigned char operandA = (instruction[1] >> 4) & 0x7;
    unsigned char operandB = instruction[1] & 0x7;

    //TODO: From here, your task is to complete the implementation so that all y86 opcode and operands can be disassembled.
    //Any undisassembled opcode should display as "TODO: undisassembled opcode and operands"

//the first three if statements are simple becuase "halt", "nop" and "ret" are the only three instructions that do not have a registor or value so if the code see it in the bytes then it will just print them
if (instruction[0] == 0x00)
{
  printf("halt\n");
}  
  
else if (instruction[0] == 0x10)
{
  printf("nop\n");
}
  
else if (instruction[0] == 0x90)
{
  printf("ret\n");
}
//the if statment from here display both registor so it uses the code that split the byte into two so that these opcodes are able to be display the right registors. 
else if (instruction[0] == 0x20)
{
  printf("rrmovl %s, %s\n", register_names[operandA], register_names[operandB]);
}
  
else if (instruction[0] == 0x21)
{
  printf("cmolve %s, %s\n", register_names[operandA], register_names[operandB]);
}  
  
else if (instruction[0] == 0x22)
{
  printf("cmovl %s, %s\n", register_names[operandA], register_names[operandB]);
}
  
else if (instruction[0] == 0x23)
{
  printf("cmove %s, %s\n", register_names[operandA], register_names[operandB]);
}
  
else if (instruction[0] == 0x24)
{
  printf("cmovne %s, %s\n", register_names[operandA], register_names[operandB]);
}
  
else if (instruction[0] == 0x25)
{
  printf("cmovge %s, %s\n", register_names[operandA], register_names[operandB]);
}
  
else if (instruction[0] == 0x26)
{
  printf("cmovg %s, %s\n", register_names[operandA], register_names[operandB]);
}
  
else if (instruction[0] == 0x60)
{
printf( "addl %s, %s\n", register_names[operandA], register_names[operandB]);
}
  
else if (instruction[0] == 0x61)
{
  printf("subl %s, %s\n", register_names[operandA], register_names[operandB]);
}
  
else if (instruction[0] == 0x62)
{
  printf("andl %s, %s\n", register_names[operandA], register_names[operandB]);
}
  
else if (instruction[0] == 0x63)
{
  printf("xorl %s, %s\n", register_names[operandA], register_names[operandB]);
}

//pushl is unique opcode becuase it only display registorA which mean i had only had to uses the operandA for this opcode. 
else if (instruction[0] == 0xA0)
{
  printf("pushl %s\n", register_names[operandA]);
}

 //popl is like pushl in that it display registorA. 
else if (instruction[0] == 0xB0)
{
  printf("popl %s\n", register_names[operandA]);
} 
//the next three opcodes are only one that display a value and registor so that means had use the operand code for the registor each operand displayed and as well *(int*)&instruction[2] which workout the value for the opcode.
else if (instruction[0] == 0x30)
{
printf( "irmovl $%d, %s\n",*(int*)&instruction[2], register_names[operandB]);
}
  
else if (instruction[0] == 0x40) 
{
  printf( "rmmovl %s, %d(%s)\n", register_names[operandA], *(int*)&instruction[2], register_names[operandB]);
}
  
else if (instruction[0] == 0x50)
{
  printf( "mrmovl %d(%s), %s\n", *(int*)&instruction[2], register_names[operandB], register_names[operandA]);
}
//the last few opcode don't display any registor and only they name and value so i only have to put they name in the printf as well as %d.
else if (instruction[0] == 0x70)
{
  printf("jmp %u\n", *(int*)&instruction[1]);
}

else if (instruction[0] == 0x71)
{
  printf("jle %u\n", *(int*)&instruction[1]);
}

else if (instruction[0] == 0x72)
{
  printf("jl %u\n", *(int*)&instruction[1]);
}

else if (instruction[0] == 0x73)
{
  printf("je %u\n", *(int*)&instruction[1]);
}

else if (instruction[0] == 0x74) 
{
  printf("jne %u\n", *(int*)&instruction[1]);
}

else if (instruction[0] == 0x75)
{
  printf("jge %u\n", *(int*)&instruction[1]);
}

else if (instruction[0] == 0x76)
{
  printf("jg %u\n", *(int*)&instruction[1]);
}

else if (instruction[0] == 0x80)
{
  printf("call %u\n", *(int*)&instruction[1]);
}

//the else statment is here to print an error message if there an opcode that is not covered from my code.
else
printf("TODO: undisassembled opcode and operands. The first byte of the instruction is 0x%X\n", instruction[0]);
  }

  fclose(pFile);

  return 0;
}

/****************************************************************************
N.B. You do not need to modify or work in this function.
Description:
This function converts a line of machine code read from the text file
into machine byte code.
The machine code is stored in an unsigned char array.
******************************************************************************/
int convertStrToByteCode(const char *str, unsigned char inst[], int size)
{
  int numHexDigits = 0;
  char *endstr;
  //Each instruction should consist of at most 12 hex digits
  numHexDigits = strlen(str) - 1;
  //Convert the string to integer, N.B. this integer is in decimal
  long long value = strtol(str, &endstr, 16);

  int numBytes = numHexDigits >> 1;
  int byteCount = numHexDigits >> 1;

  while (byteCount > 0)
  {
    unsigned long long mask = 0xFF;
    unsigned long shift = (numBytes - byteCount) << 3;

    inst[byteCount - 1] = (value & (mask << shift)) >> shift;
    byteCount--;
  }

  //Return the size of the instruction in bytes
  return numHexDigits >> 1;
}
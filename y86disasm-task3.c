#include <stdio.h>
#include <stdlib.h>

//This is the help function that reads y86 binary code from a file
unsigned int loadBinFromFile(const char *filename, unsigned char memory[], unsigned int memsize);

//This code is used to get opcode names from the opcodes values. it works by replacing the value with the right tag, when the value appear in code. (the code is here becuase it produces a error in the compiler if it is not here) 
const char* GetOpcodeName(int opcode) {
      switch(opcode) {
          case 0x00:
              return "halt";
          case 0x10:
              return "nop";
          case 0x90:
              return "ret";
          case 0x20:
              return "rrmovl";
          case 0x21:
              return "cmovle";
          case 0x22:
              return "cmovl";
          case 0x23:
              return "cmove";
          case 0x24:
              return "cmovne";
          case 0x25:
              return "cmovge";
          case 0x26:
              return "cmovg";
          case 0x60:
              return "addl";
          case 0x61:
              return "subl";
          case 0x62:
              return "andl";
          case 0x63:
              return "xorl";
          case 0xA0:
              return "pushl";
          case 0xB0:
              return "popl";
          case 0x30:
              return "irmovle";
          case 0x40:
              return "rmmovl";
          case 0x50:
              return "mrmovl";
          case 0x70:
              return "jmp";
          case 0x71:
              return "jle";
          case 0x72:
              return "jl";
          case 0x73:
              return "je";
          case 0x74:
              return "jne";
          case 0x75:
              return "jge";
          case 0x76:
              return "jg";
          case 0x80:
              return "call";
          default:
              return "UNKNOWN_OPCODE";
      }
}
//this code is used to get the value for the opcodes, its is here becuase it will prodeces an error if in the area that we are advised to uses.
int GetOffSet(char* memory, int PC) {
    int offset = *(int*)&memory[PC + 2];
    return offset;
}
//this an array that is used to store the registers that will be used in the function that will give the right register to the opcode.
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
    "UNKNOWN_REGISTER"
};

unsigned char GetRegisterValue(const unsigned char *memory, int PC, unsigned char operandA, unsigned char operandB) {
    return (memory[PC + 1] >> 4) & 0x7;
}

int main(int argc, char **argv)
{
  unsigned int MAX_MEMSIZE = 4096;
  unsigned char memory[MAX_MEMSIZE]; //This array represents the 4KB memory space
  unsigned int PC = 0;               //This is the initial program counter address

  if (argc < 2)
  {
    printf("Usage: please specify a y86 binary program file in the argument.\n");
    return -1;
  }

  unsigned int program_size = loadBinFromFile(argv[1], memory, MAX_MEMSIZE);

  if (program_size == 0)
    return 0;

  //TODO: Implement your disassembler from here
  //At the moment, it simply display each byte from the memory.
while (PC < program_size)
{
//the if statment and else if statment are uses to checkt to see if the memory has certain opcode and if does then it will uses the GetOpcodeName function to replace the opcode value with the Opcode naem so for e.g. if there 0x00 in the memory then the function would replace it with halt.
if (memory[PC] == 0x00) 
{
        printf("%s\n", GetOpcodeName(memory[PC]));
        PC += 6;
}
  
else if (memory[PC] == 0x10)
{
        printf("%s\n", GetOpcodeName(memory[PC]));
        PC += 2;
}
  
else if (memory[PC] == 0x90)
{
        printf("%s\n", GetOpcodeName(memory[PC]));
        PC += 2;
}
  
//from here the else if statment will look for register which will go through the array of register names and will replace the register value with the right register name.
else if (memory[PC] == 0x20)
{
  printf("%s %s, %s\n", GetOpcodeName(memory[PC]), register_names[GetRegisterValue(memory, PC, 0, 0)], register_names[GetRegisterValue(memory, PC, 1, 0)]);
      PC += 2;
}
  
else if (memory[PC] == 0x21)
{
  printf("%s %s, %s\n", GetOpcodeName(memory[PC]), register_names[GetRegisterValue(memory, PC, 0, 0)], register_names[GetRegisterValue(memory, PC, 1, 0)]);
          PC += 2;
}
  
else if (memory[PC] == 0x22)
{
  printf("%s %s, %s\n", GetOpcodeName(memory[PC]), register_names[GetRegisterValue(memory, PC, 0, 0)], register_names[GetRegisterValue(memory, PC, 1, 0)]);
  PC += 2;
}
  
else if (memory[PC] == 0x23)
{
  printf("%s %s, %s\n", GetOpcodeName(memory[PC]), register_names[GetRegisterValue(memory, PC, 0, 0)], register_names[GetRegisterValue(memory, PC, 1, 0)]);
  PC += 2;
}
  
else if (memory[PC] == 0x24)
{
  printf("%s %s, %s\n", GetOpcodeName(memory[PC]), register_names[GetRegisterValue(memory, PC, 0, 0)], register_names[GetRegisterValue(memory, PC, 1, 0)]);
  PC += 2;
}
  
else if (memory[PC] == 0x25)
{
  printf("%s %s, %s\n", GetOpcodeName(memory[PC]), register_names[GetRegisterValue(memory, PC, 0, 0)], register_names[GetRegisterValue(memory, PC, 1, 0)]);
  PC +=2;
}
  
else if (memory[PC] == 0x26)
{
  printf("%s %s, %s\n", GetOpcodeName(memory[PC]), register_names[GetRegisterValue(memory, PC, 0, 0)], register_names[GetRegisterValue(memory, PC, 1, 0)]);
  PC += 2;
} 
  
else if (memory[PC] == 0x60)
{
  printf("%s %s, %s\n", GetOpcodeName(memory[PC]), register_names[GetRegisterValue(memory, PC, 0, 0)], register_names[GetRegisterValue(memory, PC, 1, 0)]);
  PC += 2; 
}

else if (memory[PC] == 0x61)
{
  printf("%s %s, %s\n", GetOpcodeName(memory[PC]), register_names[GetRegisterValue(memory, PC, 0, 0)], register_names[GetRegisterValue(memory, PC, 1, 0)]);
  PC += 2;
}

else if (memory[PC] == 0x62)
{
  printf("%s %s, %s\n", GetOpcodeName(memory[PC]), register_names[GetRegisterValue(memory, PC, 0, 0)], register_names[GetRegisterValue(memory, PC, 1, 0)]);
  PC += 2;
}

else if (memory[PC] == 0x63)
{
  printf("%s %s, %s\n", GetOpcodeName(memory[PC]), register_names[GetRegisterValue(memory, PC, 0, 0)], register_names[GetRegisterValue(memory, PC, 1, 0)]);
  PC += 2;
}
//for 0xA0 is only uses the registerA so it will only print the registerA due to the function GetRegisterValue slipting the values that is retived from the memory.
else if (memory[PC] == 0xA0)
{
  printf("%s %s\n", GetOpcodeName(memory[PC]), register_names[GetRegisterValue(memory, PC, 0, 0)]);
  PC += 2;
}
//like the 0xA0 opcode the 0xB0 opcode will only print one register but only the registerB.
else if (memory[PC] == 0xB0)
{
  printf("%s %s\n", GetOpcodeName(memory[PC]), register_names[GetRegisterValue(memory, PC, 1, 0)]);
  PC += 2;
}
//0x30 and upcoming opcodes are different from the prevous opcode becuase these opcode have value instead for register, except for 0x30, 0x40, 0x50 becuase they still display certain resgister. the way that we get the value for the opcode would be from the function GetOffSet.
  
//0x30 will display is opcode name, then $vlaue anf registerB
else if (memory[PC] == 0x30)
{
 printf("%s, $%d, %s\n", GetOpcodeName(memory[PC]), GetOffSet((char *)memory, PC), register_names[GetRegisterValue(memory, PC, 1, 0)]);
        PC += 2;
}
  
//0x40 will display is opcode name, then registerA and $value(regisgerB) which means we must change how do the printf statment by haivng it going in this order "%s(opcode), %s(registerA), $%d(%s(registerB))". 
else if (memory[PC] == 0x40)
{
  printf("%s, %s, %d(%s)\n", GetOpcodeName(memory[PC]), register_names[GetRegisterValue(memory, PC, 0, 0)], GetOffSet((char *)memory, PC), register_names[GetRegisterValue(memory, PC, 1, 0)]);
  PC += 2;
}
  
else if (memory[PC] == 0x50)
{
  printf("%s, %d(%s), %s\n",GetOpcodeName(memory[PC]) ,GetOffSet((char*)memory, PC), register_names[GetRegisterValue(memory, PC, 0, 0)],  register_names[GetRegisterValue(memory, PC, 0, 0)]);
  PC += 2;
}
//the opcode from here don't display register, only opcode names and the values so the printf statment will be "%s, $%d".
else if (memory[PC] == 0x70)
{
  printf("%s, %d\n", GetOpcodeName(memory[PC]), GetOffSet((char *)memory, PC));
  PC += 2;
}

else if (memory[PC] == 0x71)
{
  printf("%s, %d\n", GetOpcodeName(memory[PC]), GetOffSet((char *)memory, PC));
  PC += 2;
}

else if (memory[PC] == 0x72)
{
  printf("%s, %d\n", GetOpcodeName(memory[PC]), GetOffSet((char *)memory, PC));
  PC += 2;
}

else if (memory[PC] == 0x73)
{
  printf("%s, %d\n", GetOpcodeName(memory[PC]), GetOffSet((char *)memory, PC));
  PC += 2;
}

else if (memory[PC] == 0x74)
{
  printf("%s, %d\n", GetOpcodeName(memory[PC]), GetOffSet((char *)memory, PC));
  PC += 2;
}

else if (memory[PC] == 0x75)
{
  printf("%s, %d\n", GetOpcodeName(memory[PC]), GetOffSet((char *)memory, PC));
  PC += 2;
}
  
else if (memory[PC] == 0x76)
{
  printf("%s, %d\n", GetOpcodeName(memory[PC]), GetOffSet((char *)memory, PC));
  PC += 2;
}  

else if (memory[PC] == 0x80)
{
  printf("%s, %d\n", GetOpcodeName(memory[PC]), GetOffSet((char *)memory, PC));
  PC += 2;

}
//this else statment is here so that if some that is not covered in the if statment above, appears in the memory, then it will print out the error message.
else
   {   
        printf("%02X\n", memory[PC]);
        PC++;
      }
    }
   return 0;
  }


/****************************************************************************
N.B. You do not need to modify or work in this function.
Description:
This function reads in a y86 machine bytecode from file and
store them in an unsigned char array.
******************************************************************************/
unsigned int loadBinFromFile(const char *filename, unsigned char memory[], unsigned int memsize)
{
  unsigned int bytes_read = 0;

  unsigned int file_size = 0;

  FILE *pfile = fopen(filename, "rb");

  if (!pfile)
  {
    printf("Unable to load file %s, please check if the path and name are correct.\n", filename);
    return 0;
  }

  fseek(pfile, 0, SEEK_END);
  file_size = ftell(pfile);
  rewind(pfile);

  if (file_size > memsize)
  {
    printf("Program size exceeds memory size of %d.\n", memsize);
    return 0;
  }

  bytes_read = fread(memory, 1, file_size, pfile);

  if (bytes_read != file_size)
  {
    printf("Bytes read does not match the file size.\n");
    return 0;
  }

  fclose(pfile);

  return bytes_read;
}



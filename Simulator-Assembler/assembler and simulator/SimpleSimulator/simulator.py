import sys

file_input = sys.argv[1]
file_ouput = sys.argv[2]

binaryfile = open(file_input,"r+")
outputfile = open(file_ouput,"w+")
# binaryfile = open("binaryfile.text","r+")
# outputfile = open("outputfile.text","w+")
registers={
        "pc_Counter" :  "0b00000000000000000000000000000000",
        "00000" : "0b00000000000000000000000000000000",
        "00001" : "0b00000000000000000000000000000000",
        "00010" : "0b00000000000000000000000100000000",
        "00011" : "0b00000000000000000000000000000000",
        "00100" : "0b00000000000000000000000000000000",
        "00101" : "0b00000000000000000000000000000000",
        "00110" : "0b00000000000000000000000000000000",
        "00111" : "0b00000000000000000000000000000000",
        "01000" : "0b00000000000000000000000000000000",
        "01001" : "0b00000000000000000000000000000000",
        "01010" : "0b00000000000000000000000000000000",
        "01011" : "0b00000000000000000000000000000000",
        "01100" : "0b00000000000000000000000000000000",
        "01101" : "0b00000000000000000000000000000000",
        "01110" : "0b00000000000000000000000000000000",
        "01111" : "0b00000000000000000000000000000000",
        "10000" : "0b00000000000000000000000000000000",
        "10001" : "0b00000000000000000000000000000000",
        "10010" : "0b00000000000000000000000000000000",
        "10011" : "0b00000000000000000000000000000000",
        "10100" : "0b00000000000000000000000000000000",
        "10101" : "0b00000000000000000000000000000000",
        "10110" : "0b00000000000000000000000000000000",
        "10111" : "0b00000000000000000000000000000000",
        "11000" : "0b00000000000000000000000000000000",
        "11001" : "0b00000000000000000000000000000000",
        "11010" : "0b00000000000000000000000000000000",
        "11011" : "0b00000000000000000000000000000000",
        "11100" : "0b00000000000000000000000000000000",
        "11101" : "0b00000000000000000000000000000000",
        "11110" : "0b00000000000000000000000000000000",
        "11111" : "0b00000000000000000000000000000000",
    } 
                   
d={65536:["0x00010000","0b00000000000000000000000000000000"],
   65540:["0x00010004","0b00000000000000000000000000000000"],
   65544:["0x00010008","0b00000000000000000000000000000000"],
65548:["0x0001000c","0b00000000000000000000000000000000"],
65552:["0x00010010","0b00000000000000000000000000000000"],
65556:["0x00010014","0b00000000000000000000000000000000"],
65560:["0x00010018","0b00000000000000000000000000000000"],
65564:["0x0001001c","0b00000000000000000000000000000000"],
65568:["0x00010020","0b00000000000000000000000000000000"],
65572:["0x00010024","0b00000000000000000000000000000000"],
65576:["0x00010028","0b00000000000000000000000000000000"],
65580:["0x0001002c","0b00000000000000000000000000000000"],
65584:["0x00010030","0b00000000000000000000000000000000"],
65588:["0x00010034","0b00000000000000000000000000000000"],
65592:["0x00010038","0b00000000000000000000000000000000"],
65596:["0x0001003c","0b00000000000000000000000000000000"],
65600:["0x00010040","0b00000000000000000000000000000000"],
65604:["0x00010044","0b00000000000000000000000000000000"],
65608:["0x00010048","0b00000000000000000000000000000000"],
65612:["0x0001004c","0b00000000000000000000000000000000"],
65616:["0x00010050","0b00000000000000000000000000000000"],
65620:["0x00010054","0b00000000000000000000000000000000"],
65624:["0x00010058","0b00000000000000000000000000000000"],
65628:["0x0001005c","0b00000000000000000000000000000000"],
65632:["0x00010060","0b00000000000000000000000000000000"],
65636:["0x00010064","0b00000000000000000000000000000000"],
65640:["0x00010068","0b00000000000000000000000000000000"],
65644:["0x0001006c","0b00000000000000000000000000000000"],
65648:["0x00010070","0b00000000000000000000000000000000"],
65652:["0x00010074","0b00000000000000000000000000000000"],
65656:["0x00010078","0b00000000000000000000000000000000"],
65660:["0x0001007c","0b00000000000000000000000000000000"]}

count = 0
pc_Counter = 0
pccount=-4
def Utype(temp_list,pc_Counter,registers,opcode):
    register_list=temp_list[20:25]
    immediate_list = temp_list[:20]
    output = 0 
    if opcode == "0010111":
        final_immediate_list = immediate_list + "0"*12; 
        # print(immediate_list)
        # print(final_immediate_list , "final")
        output = int(final_immediate_list,2)
        # for i in range(len(final_immediate_list),0 , -1):
        #     output=output+int(final_immediate_list[i])*(2**i)
        final = output + pc_Counter
        # print(final , "hellow")
        binaryoutput = str(bin(final))
        # print(binaryoutput)
        if(binaryoutput[0] == "-"):
            value = binaryoutput[3:]
            increaseby = 32 - len(value)
            registers[register_list] = "0b" +  "1"*increaseby + value
        else :
            value = binaryoutput[2:]
            increaseby = 32 - len(value)
            registers[register_list] = "0b" +  "0"*increaseby + value
            # reverse = int(immediate_list[::-1])
            # final_immediate = str(reverse + final_counter)
            # lenght_Of_immediate = len(final_immediate)
            
            # increaseby = 32 - lenght_Of_immediate
            # final_immediate = final_immediate[::-1] + "0"*increaseby
            # print(final_immediate)
            # registers[register_list] = "0b" + final_immediate
        # print(registers[register_list])
    if opcode == "0110111":
        registers[register_list] = "0b" + immediate_list +"000000000000"
        
# binary to integer uses string as input and returns integer

def binary_to_integer_converter_I_TYPE(input):
    input=input[len(input)-1::-1]
    output=0
    # output = int(output,2)
    for i in range(len(input)):
        output=output+int(input[i])*(2**i)
    return output

def twos_complement_addition(input1,input2):
    output=''
    carry=0
    for i in range(len(input1)-1,-1,-1):
        if (carry==0):
            if (input1[i]==input2[i] and input1[i]=='0'):
                output=output+'0'
                carry=0
            elif (input1[i]==input2[i] and input1[i]=='1'):
                output=output+'0'
                carry=1
            elif (input1[i]!=input2[i]):
                output=output+'1'
                carry=0
        elif (carry==1):
            if (input1[i]==input2[i] and input1[i]=='0'):
                output=output+'1'
                carry=0
            elif (input1[i]==input2[i] and input1[i]=='1'):
                output=output+'1'
                carry=1
            elif (input1[i]!=input2[i]):
                output=output+'0'
                carry=1
    return output[::-1]

def integer_to_binary_I_TYPE(input):
    if (input>=0):
        return bin(input)[2:].zfill(32)
    elif (input<0):
        temp=input*-1
        temp_output=bin(temp)[2:].zfill(32)
        for i in range(0,32):
            if (temp_output[i]=='0'):
                temp_output=temp_output[0:i]+'1'+temp_output[i+1:]
            else:
                temp_output=temp_output[0:i]+'0'+temp_output[i+1:]
        return twos_complement_addition(temp_output,"00000000000000000000000000000001")

def addi(input):
    imm=input[0:12]
    if(imm[0]=='0'):
        imm="00000000000000000000"+imm
    else:
        imm="11111111111111111111"+imm
    rs1=input[12:17]
    funct3=input[17:20]
    rd=input[20:25]
    opcode=input[25:31]
    registers[rd]="0b"+twos_complement_addition((registers[rs1])[2:],imm)
    
def sltiu(input):
    imm=input[0:12]
    rs1=input[12:17]
    funct3=input[17:20]
    rd=input[20:25]
    opcode=input[25:31]
    if binary_to_integer_converter_I_TYPE(registers[rs1])<binary_to_integer_converter_I_TYPE(imm):
        registers[rd]="0b00000000000000000000000000000001"
        
        
def jalr(input):
    imm=input[0:11]
    global pc_Counter
    if(imm[0]=='0'):
        imm="000000000000000000000"+imm
    else:
        imm="111111111111111111111"+imm
    rs1=input[11:16]
    funct3=input[16:19]
    rd=input[19:24]
    opcode=input[24:31]
    # print(twos_complement_addition(registers[rs1][2:],imm))
    registers[rd]="0b"+twos_complement_addition(integer_to_binary_I_TYPE((pc_Counter)),"00000000000000000000000000000100")
    pc_Counter=binary_to_integer_converter_I_TYPE(twos_complement_addition(registers[rs1][2:],imm))
    
def lw(input):
    imm=input[0:12]
    if(imm[0]=='0'):
        imm="00000000000000000000"+imm
    else:
        imm="11111111111111111111"+imm
    rs1=input[12:17]
    funct3=input[17:20]
    rd=input[20:25]
    opcode=input[25:31]
    # print("register and imm",registers[rd][2:],imm, registers[rs1])
    mem_address=twos_complement_addition(registers[rs1][2:],imm)
    # print("mem adress", mem_address)
    # print("l type",binary_to_integer_converter_I_TYPE(mem_address) )
    registers[rd]=d[binary_to_integer_converter_I_TYPE(mem_address)][1]

def jal(input):
    piece20=input[0]
    piece10to1=input[1:11]
    piece11=input[11]
    piece19to12=input[12:20]
    rd=input[20:25]
    # print(rd)
    opcode=input[25:]
    # print(opcode)
    imm=piece10to1[::-1]+piece11+piece19to12[::-1]+piece20
    imm=imm[::-1]
    global pc_Counter
    # print(imm)
    registers[rd]=twos_complement_addition(integer_to_binary_I_TYPE(pc_Counter),"00000000000000000000000000000100")
    pc_Counter=pc_Counter+binary_to_integer_converter_I_TYPE(imm)
    
def twos_complement(immediate):
    for i in range(len(immediate)):
        if immediate[i]=='0':
            immediate=immediate[0:i]+'1'+immediate[i+1:]
        else:
            immediate=immediate[0:i]+'0'+immediate[i+1:]
    carry='1'
    for i in range(len(immediate) - 1, -1, -1):
            if carry == '1':
                if immediate[i] == '0':
                    immediate = immediate[0:i]+'1'+immediate[i+1:]
                    carry = '0'
                else:
                   immediate=immediate[0:i]+'0'+immediate[i+1:]

            # Stop when carry becomes '0'
            if carry == '0':
                break
    return immediate


def SS(out, r, memory):
    # print("start")
    # print(out,"out")
    register2 = out[7:12]
    register1 = out[12:17]
    immediate = out[0:7] + out[20:25]
    # print(register1)
    # print(immediate)
    if immediate[0] == "0":
        decimal = int(immediate, 2)
    else:
        # Calculate the two's complement if the immediate value is negative
        inverted_bits = ''.join('1' if bit == '0' else '0' for bit in immediate)
        two_complement = bin(int(inverted_bits, 2) + 1)[2:]
        decimal = int(two_complement, 2) * -1
    mem_offset = r[register1]
    if mem_offset[0] == "0":
            m_offset= int(mem_offset, 2)
    else:
        # Calculate the two's complement if the mem_offset value is negative
        inverted_bits = ''.join('1' if bit == '0' else '0' for bit in mem_offset)
        two_complement = bin(int(inverted_bits, 2) + 1)[2:]
        m_offset = int(two_complement, 2) * -1
    # print(r)
    # print("mem ofset " + mem_offset)
    # Perform the memory access
    # print(m_offset,decimal)
    memory_address = m_offset + decimal
    # print(memory_address,"retard")
    # Check if the memory address is within bounds
        # Store the value of register2 at the calculated memory address
    if memory_address >= 65536 :
        memory[memory_address][1] = r[register2]
    elif memory_address >= 32768 and memory_address <= 32830:
        memory_address = memory_address*2
        memory[memory_address][1] = r[register2]
    else :
        print("memory outof range")

# Example usage:
# out = "00000010000100010010000000100011"
# pc = 0  # Program counter
# registers = {'00000': 0, '00001':5, '00010': "01010"}  # Example register values
# memory = [0] * 100  # Example memory

# SS(out, registers, memory)
# print("Registers after execution:", registers)
# print("Memory after execution:", memory)

def twos_complement_to_decimal(binary_str):
    # Check if the number is negative (if the leftmost bit is 1)
    if binary_str[0] == '1':
        # Convert the binary string to its equivalent positive decimal representation
        positive_decimal = int(binary_str, 2)
        # Calculate the two's complement by subtracting 2^len(binary_str)
        return positive_decimal - 2**len(binary_str)
    else:
        # If the number is positive, simply convert the binary string to decimal
        return int(binary_str, 2)
def BS(out,pc):
    immediate=out[0]+out[24]+out[1:7]+out[20:24]+"0"
    # print(immediate)
    decimal_number=twos_complement_to_decimal(immediate)
    # print("current pc", pc)
    # print(decimal_number)
    pc=pc+decimal_number
    
    # print("pc is " ,pc)
    return(pc)

#conditioning now


def BSIMULATOR(out,pc, registers):
    register1=out[7:12]
    register2=out[12:17]
    func=out[17:20]
    opcode=out[25:32]
    #beq
    if (opcode=="1100011" and func=="000"):
        if (registers[register1]==registers[register2]):
            BS(out,pc)
    #bne
    elif (opcode=="1100011" and func=="001"):
        if(registers[register1]!=registers[register2]):
            BS(out,pc)
    #bge 
    elif (opcode=="1100011" and func=="101"):
        if(twos_complement_to_decimal(registers[register1])>=twos_complement_to_decimal(registers[register2])):
            BS(out,pc)
    #bgeu(check)
    elif (opcode=="1100011" and func=="111"):
        if(int(registers[register1],2)>=int(registers[register2],2)):
            BS(out,pc)
    #blt
    elif (opcode=="1100011" and func=="100"):
        if(twos_complement_to_decimal(registers[register1])<twos_complement_to_decimal(registers[register2])):
            BS(out,pc)
    #bltu
    elif (opcode=="1100011" and func=="110"):
        if(int(registers[register1],2)<int(registers[register2],2)):
            BS(out,pc)


def extendSign(binarydata):
    sign=binarydata[0]
    signExtended=sign*(32-len(binarydata))+binarydata
    finalsign = signExtended[2:]
    return finalsign

# def Rtype(binarydata,registers):
    opcode = binarydata[25:]  
    temp_opcode = opcode.strip() 
    rd = binarydata[20:25]
    funct3 = binarydata[17:20]
    temp_funct3 =   funct3.strip()
    rs1 = binarydata[12:17]
    rs2 = binarydata[7:12]
    funct7 =binarydata[0:7]
    temp_fnct7 = funct7.strip()

    if opcode=="0110011":
        if funct3 == "000" and funct7 == "0000000":
            if  temp_funct3 == "000" and temp_fnct7 == "0000000":
                carry=0
                val1=extendSign(registers[rs1])
                val2=extendSign(registers[rs2])
                print(val1)
                print(val2)
                value1 = int(val1,2)
                value2 = int(val2,2)
                added=value1+value2
                addition = str(value1+value2)
                print(addition)
                binary_num=bin(added)[2:]
                absolute=abs(added)
                if added<0:
                    registers[rd]="0b"+"1"*(32-len(binary_num))+binary_num
                else:
                    registers[rd]="0b"+"0"*(32-len(binary_num))+binary_num
                print(registers[rd])

        
        if funct3 == "000" and funct7 == "0100000":
            val1=extendSign(registers[rs1])
            val2=extendSign(registers[rs2])
            if rs1=="00000":
                registers[rd]="0b"+twos_complement(val2)
            else:
                print(val1)
                val3=twos_complement(val2)

                value1=int(val1,2)
                value2=int(val3,2)
                subtraction=str(value1+value2)
                print(subtraction)
            absolute=abs(value1+value2)
            binary_num=bin(absolute)[2:]
            if (value1+value2)<0:
                registers[rd]="0b"+"1"*(32-len(binary_num))+binary_num
            else:
                registers[rd]="0b"+"0"*(32-len(binary_num))+binary_num
            print(registers[rd])
        
        if funct3 == "001" and funct7 == "0000000":
            val1=extendSign(registers[rs1])
            val2=extendSign(registers[rs2])
            lower5bits=val1[-5:]
            val3=int(lower5bits,2)
            value1=int(val1,2)
            lsl=str(value1*(2**val3))
            binary_num=bin(int(lsl))[2:]
            registers[rd]="0b"+"0"*(32-len(binary_num))+binary_num
            print(lsl)
            print(registers[rd])    

        if funct3 == "010" and funct7 == "0000000":
            val1=extendSign(registers[rs1])
            val2=extendSign(registers[rs2])
            for i in range(32):
                bit1=int(val1[i])
                bit2=int(val2[i])
                if bit1<bit2:
                    registers[rd]="0b"+"0"*31+"1"
                else:
                    registers[rd]="0b"+"0"*32
            print(registers[rd])

        if funct3 == "011" and funct7 == "0000000":
            val1=extendSign(registers[rs1])
            val2=extendSign(registers[rs2])
            for i in range(1,32):
                bit1=int(val1[i])
                bit2=int(val2[i])
                if bit1<bit2:
                    registers[rd]="0b"+"0"*31+"1"
                else:
                    registers[rd]="0b"+"0"*32
            print(registers[rd])
        if funct3 == "100" and funct7 == "0000000":
            val1=extendSign(registers[rs1])
            val2=extendSign(registers[rs2])
            value1=int(val1,2)
            value2=int(val2,2)
            value=value1^value2
            res=bin(value)[2:]
            res="0"*(32-len(res))+res
            registers[rd]="0b"+res
            print(registers[rd])

        if funct3 == "101" and funct7 == "0000000":
            val1=extendSign(registers[rs1])
            val2=extendSign(registers[rs2])
            lower5bits=registers[rs2][-5:]
            val3=int(lower5bits,2)
            registers[rd]="0b"+"0"*val3+val1[:-val3]
            print(registers[rd])

        if funct3 == "110" and funct7 == "0000000":
            val1=extendSign(registers[rs1])
            val2=extendSign(registers[rs2])
            value1=int(val1,2)
            value2=int(val2,2)
            value=value1|value2
            res=bin(value)[2:]
            res="0"*(32-len(res))+res
            registers[rd]="0b"+res
            print(registers[rd])
            
        if funct3 == "111" and funct7 == "0000000":
            val1=extendSign(registers[rs1])
            val2=extendSign(registers[rs2])
            value1=int(val1,2)
            value2=int(val2,2)
            value=value1&value2
            res=bin(value)[2:]
            res="0"*(32-len(res))+res
            registers[rd]="0b"+res
            print(registers[rd])
            
            
def Rtype(n,reg):
    dest_reg = n[20:25]
    f3 = n[17:20]
    rs1 = n[12:17]
    rs2 = n[7:12]
    f7 = n[0:7]

    if f3 == "000" and f7 == "0000000":
        
        value = int(reg[rs1],2) + int(reg[rs2],2)
        binary = bin(value)
        sliced = binary[2:]
        reg[dest_reg] = "0b" + "0"*(32-len(sliced)) + sliced
        # print(reg[dest_reg])
    elif f3 == "000" and f7 == "0100000":
        
        value = int(reg[rs1],2) - int(reg[rs2],2)
        binary = bin(value)
        sliced = binary[2:]
        reg[dest_reg] = "0b" + "0"*(32-len(sliced)) + sliced
        # print(reg[dest_reg])
        
    # sll
    elif f3 == "001":
        bin_rs1 = (reg[rs1])
        bin_rs2 = (reg[rs2])
        
        bin_rs1 = bin_rs1[2:]
        bin_rs2 = bin_rs2[2:]
        # print(bin_rs1, bin_rs2)

        if len(bin_rs2) >= 5 :
            left_shift = bin_rs2[len(bin_rs2)-5:len(bin_rs2)]
            reg[rs1] = reg[rs1] + "0"* int(left_shift,2)
            reg[rs1] = reg[rs1][int(left_shift,2)+2 : ]
            reg[rs1] = "0b" + reg[rs1]
            # print(int(reg[rs1],2))

        else:
            extend_0 = 5 - len(bin_rs2)
            for i in range(extend_0):
                bin_rs2= "0" + bin_rs2
            left_shift = bin_rs2
            ans = bin_rs1 + bin_rs2
            # print("OTHER case: ", ans)
        
        int_of_left_shift = 0
        len_left_shift = len(left_shift)
        for i in range(0,len_left_shift):       #  immediate to integer 
            int_of_left_shift = int_of_left_shift + int(left_shift[len_left_shift-i-1]) * (2**i)
        
        # print("->", int_of_left_shift)
        
        ans = bin_rs1
        for i in range(int_of_left_shift):
            ans = ans + "0"
        
        # // print("::",ans)
        if ( len(ans) > 32 ):
            ans = ans[len(ans) - 32 : ]

            
        int_of_ans = 0
        len_ans = len(ans)
        for i in range(0,len_ans):       #  immediate to integer 
            int_of_ans = int_of_ans + int(ans[len_ans-i-1]) * (2**i)
            # // print("->", int_of_ans)
        
        # int_of_ans = binary_to_integer(sign_extend(ans))
        # print( ans, len(ans), int_of_ans)
        
        reg[dest_reg] = str(bin(int_of_ans))
        reg[dest_reg] = reg[dest_reg][2:]
        reg[dest_reg] = "0b" + "0"*(32-len(reg[dest_reg]))+reg[dest_reg]

    elif f3 == "010":   # slt
        if reg[rs1] < reg[rs2]:     # sign extended rs1 and rs2
            reg[dest_reg] = "0b00000000000000000000000000000001"
    elif f3 == "011":   # sltu
        if reg[rs1] < reg[rs2]:     # unsigned rs1 and rs2
            reg[dest_reg] = "0b00000000000000000000000000000001"
    elif f3 == "100":   # xor
        reg[dest_reg] = bin(reg[rs1][2:]) ^ bin(reg[rs2][2:])

    # elif f3 == "010":   # slt
    #     if reg[rs1] < reg[rs2]:     # sign extended rs1 and rs2
    #         reg[dest_reg] = 1
    # elif f3 == "011":   # sltu
    #     if reg[rs1] < reg[rs2]:     # unsigned rs1 and rs2
    #         reg[dest_reg] = 1
    # elif f3 == "100":   # xor
    #     reg[dest_reg] = reg[rs1] ^ reg[rs2]
    




    # srl
    elif f3 == "101":
        # print("srl")
        bin_rs1 = (reg[rs1])
        bin_rs2 = (reg[rs2])
        
        bin_rs1 = bin_rs1[2:]
        bin_rs2 = bin_rs2[2:]
        # print(bin_rs1, bin_rs2)

        if len(bin_rs2) >= 5 :
            right_shift = bin_rs2[len(bin_rs2)-5:len(bin_rs2)]
            # // ans = bin_rs1 + right_shift
            # // print("NORMAL case: ", ans)

        else:
            extend_0 = 5 - len(bin_rs2)
            for i in range(extend_0):
                bin_rs2= "0" + bin_rs2
            right_shift = bin_rs2
            # // ans = bin_rs1 + bin_rs2
            # // print("OTHER case: ", ans)
        
        # print(right_shift)


        int_of_right_shift = 0
        len_right_shift = len(right_shift)
        for i in range(0,len_right_shift):       #  immediate to integer 
            int_of_right_shift = int_of_right_shift + int(right_shift[len_right_shift-i-1]) * (2**i)
            # // print("->", int_of_right_shift)
        
        # print("int right_shift: ",int_of_right_shift)



        extend_0 = 32 - len(bin_rs1)
        for j in range(extend_0):
            bin_rs1 = "0" + bin_rs1
        # bin_rs1 = "0b" + bin_rs1

        
        # print("-->",bin_rs1, len(bin_rs1))

        ans = ""
        for i in range(int_of_right_shift):
            ans = "0" + ans
        # print("semi-ans: ", ans, len(ans))
        ans = ans + bin_rs1[0:32-int_of_right_shift]
        # print("final ans: (bin)", ans, len(ans))

        int_of_ans = 0
        len_ans = len(ans)
        for i in range(0,len_ans):       #  immediate to integer 
            int_of_ans = int_of_ans + int(ans[len_ans-i-1]) * (2**i)
            # // print("->", int_of_ans)
        
        binary_ans = bin(int_of_ans)
        # print( ans, len(ans), int_of_ans)
        reg[dest_reg] = "0b" + "0"*(32- len(binary_ans[2:])) +binary_ans[2:]

    elif f3 == "110":   # or
        reg[dest_reg] = reg[rs1] or reg[rs2]

    elif f3 == "111":   # and
        # print("And starts from",reg[rs1],reg[rs2])
        reg[dest_reg] = reg[rs1] and reg[rs2]
        # print(reg[dest_reg])

output_registers = []
for temp_list in binaryfile:
    
    striped_temp= temp_list.strip()
    count += 1
    opcode = temp_list[25:]
    fnct3=temp_list[17:20]
    pc_Counter += 4
    pccount +=4
    striped_output = opcode.strip()
    check_halt = 0
    if (striped_temp == "00000000000000000000000001100011"):
                # print(pc_Counter,"code ended")
                pc_Counter = pc_Counter -4
                check_halt = 1
    if striped_output == "0010111" or striped_output == "0110111" :
        output = Utype(temp_list , pccount ,registers,striped_output)
        
    if striped_output == "0010011" :
        if fnct3 == "000" :
            addi(temp_list)
        elif fnct3 == "011" :
            sltiu(temp_list) 
            
    if striped_output == "1100111":
        jalr(temp_list)
        
    if striped_output == "0000011" :
        lw(temp_list)
        
    if striped_output == "0110011":
        Rtype(temp_list,registers)
        
    if striped_output == "0100011" :
        SS(temp_list , registers , d)
        
    if striped_output == "1100011":
        BSIMULATOR(temp_list , pc_Counter , registers )
        
    
    
    # print(pc_Counter)    
    pc_register = bin(pc_Counter)[2:]
    length_of_pcounter = len(pc_register)
    if(length_of_pcounter) < 32 :
        difference = 32 - length_of_pcounter
        pc_register = "0b" + "0"*difference + str(pc_register)
        registers["pc_Counter"] = pc_register
    
    for value in registers.values():
        outputfile.write(value)
        outputfile.write(" ")
    outputfile.write("\n")
    if check_halt == 1 :
        break
for answer in d.values():
    outputfile.write(answer[0] + ":" + answer[1])
    outputfile.write("\n")
outputfile.close()
binaryfile.close()
        
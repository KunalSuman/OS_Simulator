import sys
file_input = sys.argv[1]
file_output = sys.argv[2]


file = open(file_input,"r+")
file1 = open(file_output, "w")

#R TYPE
# def Rtype(register):
#     for i in range(len(register)-1):
#         if register[i] not in 

def ADD(register):
    binarycode=["0000000"]
    binarycode.append(register[2])
    binarycode.append(register[1])
    binarycode.append("000")
    binarycode.append(register[0])
    binarycode.append("0110011")
    return binarycode
    
def SUB(register):
    binarycode=["0100000"]
    binarycode.append(register[2])
    binarycode.append(register[1])
    binarycode.append("000")
    binarycode.append(register[0])
    binarycode.append("0110011")
    return binarycode


def SLL(register):
    binarycode=["0000000"]
    binarycode.append(register[2])
    binarycode.append(register[1])
    binarycode.append("001")
    binarycode.append(register[0])
    binarycode.append("0110011")
    return binarycode


def SLT(register):
    binarycode=["0000000"]
    binarycode.append(register[2])
    binarycode.append(register[1])
    binarycode.append("010")
    binarycode.append(register[0])
    binarycode.append("0110011")
    return binarycode

def SLTU(register):
    binarycode=["0000000"]
    binarycode.append(register[2])
    binarycode.append(register[1])
    binarycode.append("011")
    binarycode.append(register[0])
    binarycode.append("0110011")
    return binarycode

def XOR(register):
    binarycode=["0000000"]
    binarycode.append(register[2])
    binarycode.append(register[1])
    binarycode.append("100")
    binarycode.append(register[0])
    binarycode.append("0110011")
    return binarycode

def SRL(register):
    binarycode=["0000000"]
    binarycode.append(register[2])
    binarycode.append(register[1])
    binarycode.append("101")
    binarycode.append(register[0])
    binarycode.append("0110011")
    return binarycode

def OR(register):
    binarycode=["0000000"]
    binarycode.append(register[2])
    binarycode.append(register[1])
    binarycode.append("110")
    binarycode.append(register[0])
    binarycode.append("0110011")
    return binarycode

def AND(register):
    binarycode=["0000000"]
    binarycode.append(register[2])
    binarycode.append(register[1])
    binarycode.append("111")
    binarycode.append(register[0])
    binarycode.append("0110011")
    return binarycode

# BTYPE
# func (r1,r2,pc,labeladdr dictionary,list,list1,file )
def btype(rs4,rs5,pc,d,lis1,list1):
    opcode ="1100011"
    
    
    last_element = list1[-1]

    try:
    
        # Try converting the last element to an integer
        labeladdr = int(last_element)
        if labeladdr<-2048 or labeladdr>2047:
            return str("ERROR: immediate out of bounds")
        pc_offset = labeladdr
    except ValueError:
        # Conversion failed, so it's not an integer
        labeladdr=d[list1[-1]]

        pc_offset = (pc-labeladdr)
    
    

    
    if lis1[0] =="beq":
        funct3="000"
    elif lis1[0] =="bne":
        funct3="001"
    elif lis1[0] =="blt":
        funct3="100"
    elif lis1[0] =="bge":
        funct3="101"
    elif lis1[0] =="bltu":
        funct3="110"
    elif lis1[0] =="bgeu":
        funct3="111"
    
    if(pc_offset>=0):
        a = bin(pc_offset)
        n=16
        b = a[2:]
        
        c=n-len(b)
        immediate=""

        for i in range(0,c):
            immediate=immediate+"0"
        immediate=immediate+b
    else:
       # Make the offset positive for processing
        pc_offset = abs(pc_offset)

        # Convert the positive offset to binary
        a = bin(pc_offset)
        n=16
        b = a[2:]
        
        c=n-len(b)
        immediate=""

        for i in range(0,c):
            immediate=immediate+"0"
        immediate=immediate+b

        # Invert the bits
        inverted_str = ''.join('1' if bit == '0' else '0' for bit in immediate)

        # Add 1 to the inverted binary
        carry = 1
        immediate = ""
        for bit in inverted_str[::-1]:
            new_bit = str((int(bit) + carry) % 2)
            carry = int(bit) and carry
            immediate = new_bit + immediate


        immediate = ''.join(immediate)
        
    out=immediate[-13]+immediate[-11 : -5:1]+rs5+ rs4+ funct3+immediate[-5 : -1:1]+immediate[-12]+opcode

    return out

#i type

register_encoding={'ra':'10000','a2':'00110','a3':'10110','a4':'01110','a5':'11110','a6':'00001','a7':'10001','s1':'10010','sp':'01000','zero':'00000','gp':'11000','tp':'00100','t0':'10100','t1':'01100','t2':'11100','s0':'00010','fp':'00010','a0':'01010','a1':'11010','s2':'01001','s3':'11001','s4':'00101','s5':'10101','s6':'01101','s7':'11101','s8':'00011','s9':'10011','s10':'01011','s11':'11011','t3':'00111','t4':'10111','t5':'01111','t6':'11111'}
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



def reverse_string(input_string):
    return input_string[::-1]
def addi(input_list):
    if len(input_list)!=3:
        return str("ERROR: Format of the input is incorrect for registers and immediate!")
    if input_list[0] not in register_encoding:
        return str("ERROR: Incorrect register addresses given!")
    if input_list[1] not in register_encoding:
        return str("ERROR: Incorrect register addresses given!")
    input_list[0]=register_encoding[input_list[0]]
    input_list[1]=register_encoding[input_list[1]]
    if int(input_list[2])<(-2048) or int(input_list[2])>2048:
        return "ERROR: IMMEDIATE VALUE OUT OF BOUNDS!!"
    else:
        imm=input_list[2]
        if int(input_list[2])<0:
            imm=str((-1)*int(input_list[2]))
            imm=str(bin(int(imm)).replace("0b",""))   
            imm='0'*(12-len(imm))+imm
            imm=twos_complement(imm)
            input_list[2]=reverse_string(imm)
        else:
            imm=str(bin(int(input_list[2])).replace("0b",""))
            input_list[2]=reverse_string(str('0'*(12-len(imm))+imm))
    return reverse_string(str('1100100'+input_list[0]+'000'+input_list[1]+input_list[2]))
def sltiu(input_list):
    if len(input_list)!=3:
        return str("ERROR: Format of the input is incorrect for registers and immediate!")
    if input_list[0] not in register_encoding:
        return str("ERROR: Incorrect register addresses given!")
    if input_list[1] not in register_encoding:
        return str("ERROR: Incorrect register addresses given!")
    input_list[0]=register_encoding[input_list[0]]
    input_list[1]=register_encoding[input_list[1]]
    if int(input_list[2])<(-2048) or int(input_list[2])>2048:
        return "ERROR: IMMEDIATE VALUE OUT OF BOUNDS!!"
    else:
        imm=input_list[2]
        if int(input_list[2])<0:
            imm=str((-1)*int(input_list[2]))
            imm=str(bin(int(imm)).replace("0b",""))   
            imm='0'*(12-len(imm))+imm
            imm=twos_complement(imm)
            input_list[2]=reverse_string(imm)
        else:
            imm=str(bin(int(input_list[2])).replace("0b",""))
            input_list[2]=reverse_string(str('0'*(12-len(imm))+imm))
    return reverse_string(str('1100100'+input_list[0]+'110'+input_list[1]+input_list[2]))
def jalr(input_list):
    if len(input_list)!=3:
        return str("ERROR: Format of the input is incorrect for registers and immediate!")
    if input_list[0] not in register_encoding:
        return str("ERROR: Incorrect register addresses given!")
    if input_list[1] not in register_encoding:
        return str("ERROR: Incorrect register addresses given!")
    input_list[0]=register_encoding[input_list[0]]
    input_list[1]=register_encoding[input_list[1]]
    if int(input_list[2])<(-2048) or int(input_list[2])>2048:
        return "ERROR: IMMEDIATE VALUE OUT OF BOUNDS!!"
    else:
        imm=input_list[2]
        if int(input_list[2])<0:
            imm=str((-1)*int(input_list[2]))
            imm=str(bin(int(imm)).replace("0b",""))   
            imm='0'*(12-len(imm))+imm
            imm=twos_complement(imm)
            input_list[2]=reverse_string(imm)
        else:
            imm=str(bin(int(input_list[2])).replace("0b",""))
            input_list[2]=reverse_string(str('0'*(12-len(imm))+imm))
    return reverse_string(str('1110011'+input_list[0]+'000'+input_list[1]+input_list[2]))
def lw(input_list):
    if len(input_list)!=2:
        return str("ERROR: Format of the input is incorrect for registers and immediate!")
    input_list[0]=register_encoding[input_list[0]]
    breaker=0
    end=0
    for i in range(len(input_list[1])):
        if input_list[1][i]=='(':
            breaker=i
        elif input_list[1][i]==')':
            end=i
    if breaker==0 or end==0:
        return str("ERROR: Incorrect format!!")
    imm=input_list[1][:breaker]
    input_list[1]=register_encoding[input_list[1][breaker+1:end]]  
    if int(imm)<(-2048) or int(imm)>2048:
        return "ERROR: IMMEDIATE VALUE OUT OF BOUNDS!!"
    else:
        if int(imm)<0:
            imm=str((-1)*int(imm))
            imm=str(bin(int(imm)).replace("0b",""))   
            imm='0'*(12-len(imm))+imm
            imm=twos_complement(imm)
            input_list[2]=reverse_string(imm)
        else:
            imm=str(bin(int(imm)).replace("0b",""))
            input_list.append('lol')
            input_list[2]='0'*(12-len(imm))+imm
            input_list[2]=input_list[2][::-1]
    return reverse_string(str('1100000'+input_list[0]+'010'+input_list[1]+input_list[2]))

#j type
#jal ra,label
def jtype(r1,lis,list1,d,pc):
    opcode ="1101111"
    
   
    last_element = list1[-1]

    try:
        # Try converting the last element to an integer
        labeladdr = int(last_element)
        if labeladdr<-524288 or labeladdr> 524287:
            return str("ERROR: immediate out of bounds")
        pc_offset = labeladdr
    except ValueError:
        # Conversion failed, so it's not an integer
        labeladdr=d[list1[-1]]

        pc_offset = (pc-labeladdr)

    if(pc_offset>=0):
        a = bin(pc_offset)
        n=21
        b = a[2:]
        
        c=n-len(b)
        immediate=""

        for i in range(0,c):
            immediate=immediate+"0"
        immediate=immediate+b
    else:
       # Make the offset positive for processing
        pc_offset = abs(pc_offset)

        # Convert the positive offset to binary
        a = bin(pc_offset)
        n=21
        b = a[2:]
        
        c=n-len(b)
        immediate=""

        for i in range(0,c):
            immediate=immediate+"0"
        immediate=immediate+b

        # Invert the bits
        inverted_str = ''.join('1' if bit == '0' else '0' for bit in immediate)

        # Add 1 to the inverted binary
        carry = 1
        immediate = ""
        for bit in inverted_str[::-1]:
            new_bit = str((int(bit) + carry) % 2)
            carry = int(bit) and carry
            immediate = new_bit + immediate


        immediate = ''.join(immediate)
        
    out=immediate[0]+immediate[10:20]+immediate[9]+immediate[1:9]+r1+opcode
    
    return out
    
# register encoding 
def registerencode(list1):
    list1 =list1
    encoding=[]
    for i in range(len(list1)) :
        if list1[i] == "zero":
            encoding.append("00000")
        elif list1[i] == "ra" :
            encoding.append("00001")
        elif list1[i] == "sp" :
            encoding.append("00010")
        elif list1[i] == "gp" :
            encoding.append("00011")
        elif list1[i] == "tp" :
            encoding.append("00100")
        elif list1[i] == "t0" :
            encoding.append("00101")
        elif list1[i] == "t1" :
            encoding.append("00110")
        elif list1[i] == "t2" :
            encoding.append("00111")
        elif list1[i] in ["s0", "fp"] :
            encoding.append("01000")
        elif list1[i] == "s1" :
            encoding.append("01001")
        elif list1[i] == "a0" :
            encoding.append("01010")
        elif list1[i] == "a1" :
            encoding.append("01011")
        elif list1[i] == "a2" :
            encoding.append("01100")
        elif list1[i] == "a3" :
            encoding.append("01101")
        elif list1[i] == "a4" :
            encoding.append("01110")
        elif list1[i] == "a5" :
            encoding.append("01111")
        elif list1[i] == "a6" :
            encoding.append("10000")
        elif list1[i] == "a7" :
            encoding.append("10001")
        elif list1[i] == "s2" :
            encoding.append("10010")
        elif list1[i] == "s3" :
            encoding.append("10011")
        elif list1[i] == "s4" :
            encoding.append("10100")
        elif list1[i] == "s5" :
            encoding.append("10101")
        elif list1[i] == "s6" :
            encoding.append("10110")
        elif list1[i] == "s7" :
            encoding.append("10111")
        elif list1[i] == "s8" :
            encoding.append("11000")
        elif list1[i] == "s9" :
            encoding.append("11001")
        elif list1[i] == "s10" :
            encoding.append("11010")
        elif list1[i] == "s11" :
            encoding.append("11011")
        elif list1[i] == "t3" :
            encoding.append("11100")
        elif list1[i] == "t4" :
            encoding.append("11101")
        elif list1[i] == "t5" :
            encoding.append("11110")
        elif list1[i] == "t6" :
            encoding.append("11111")
        
        else:
            return -1
    return encoding    
#s type

I_TYPE_FUNCTION_LIST=['lw','addi','sltiu','jalr']
S_TYPE_FUNCTION_LIST=['sw']
register_encoding={'ra':'10000','a2':'00110','a3':'10110','a4':'01110','a5':'11110','a6':'00001','a7':'10001','s1':'10010','sp':'01000','zero':'00000','gp':'11000','tp':'00100','t0':'10100','t1':'01100','t2':'11100','s0':'00010','fp':'00010','a0':'01010','a1':'11010','s2':'01001','s3':'11001','s4':'00101','s5':'10101','s6':'01101','s7':'11101','s8':'00011','s9':'10011','s10':'01011','s11':'11011','t3':'00111','t4':'10111','t5':'01111','t6':'11111'}
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



def reverse_string(input_string):
    return input_string[::-1]

def sw(input_list):
    if len(input_list)!=2:
        return str("ERROR: Format of the input is incorrect for registers and immediate!")
    rs1=register_encoding[input_list[0]]
    breaker=0
    end=0
    for i in range(len(input_list[1])):
        if input_list[1][i]=='(':
            breaker=i
        elif input_list[1][i]==')':
            end=i
    if breaker==0 or end==0:
        return str("ERROR: Incorrect format!!")
    imm=input_list[1][:breaker]
    if int(imm)<(-2048) or int(imm)>2048:
        return str("ERROR: immediate out of bounds")
    else:
        if int(imm)<0:
            imm=str((-1)*int(imm))
            imm=str(bin(int(imm)).replace("0b",""))   
            imm='0'*(12-len(imm))+imm
            imm=reverse_string(twos_complement(imm))
        else:
            imm=str(bin(int(imm)).replace("0b",""))
            input_list.append('lol')
            imm='0'*(12-len(imm))+imm
            imm=imm[::-1]
    rs2=register_encoding[input_list[1][breaker+1:end]]
    input_list[0]=imm[0:5]
    input_list[1]=rs1
    input_list.append('lol')
    input_list.append('lol1')
    input_list[2]=rs2
    input_list[3]=((imm[5:]))
    return reverse_string(str('1100010'+input_list[0]+'010'+input_list[2]+''+input_list[1]+''+input_list[3]))

#u type


def auipc(input_list):
    if len(input_list)!=2:
        return str("ERROR: Format of the input is incorrect for registers and immediate!")
    if input_list[0] not in register_encoding:
        return str("ERROR: Incorrect register is given!!")
    input_list[0]=register_encoding[input_list[0]]
    if int(input_list[1])<(-2048) or int(input_list[1])>2048:
        return str("ERROR: immediate out of bounds")
    else:
        imm=input_list[1]
        if int(input_list[1])<0:
            imm=str((-1)*int(input_list[1]))
            imm=str(bin(int(imm)).replace("0b",""))   
            imm='0'*(32-len(imm))+imm
            imm=twos_complement(imm)
            input_list[1]=imm[0:20]
        else:
            imm=str(bin(int(input_list[1])).replace("0b",""))
            imm='0'*(32-len(imm))+imm
            input_list[1]=imm[0:20]
    return reverse_string(str('1110100'+input_list[0]+input_list[1]))
def lui(input_list):
    if len(input_list)!=2:
        return str("ERROR: Format of the input is incorrect for registers and immediate!")
    if input_list[0] not in register_encoding:
        return str("ERROR: Incorrect register is given!!")
    input_list[0]=register_encoding[input_list[0]]
    if input_list[1].isnumeric()==False and int(input_list[1])>0:
        return str("ERROR: Format of the input is incorrect for registers and immediate!")
    if int(input_list[1])<(-2048) or int(input_list[1])>2048:
        return str("ERROR: immediate out of bounds")
    else:
        imm=input_list[1]
        if int(input_list[1])<0:
            imm=str((-1)*int(input_list[1]))
            imm=str(bin(int(imm)).replace("0b",""))   
            imm='0'*(32-len(imm))+imm
            imm=twos_complement(imm)
            input_list[1]=reverse_string(imm[0:20])
        else:
            imm=str(bin(int(input_list[1])).replace("0b",""))
            imm='0'*(32-len(imm))+imm
            input_list[1]=reverse_string(imm[0:20])
    return reverse_string(str('1110110'+''+input_list[0]+''+input_list[1]))
# RUNNER CODE
count = 0
pc=-4
setx =1
d = {}
labelpc = -4
inst_cnt=0
j=0
for i in file:

    if i.strip() == "":
        continue
    inst_cnt=inst_cnt+1
    labelpc += 4
    line = i.strip()  # Remove leading/trailing whitespaces
    list=i.strip().split(" ")
    
    command = list[0][-1]
    if line.endswith(":"):
        label = line[:-1]  # Remove the colon
        d[label] = labelpc
    elif command==":": #if the label is with assembly code 
        label = list[0][:-1]
        d[label] = labelpc




file.seek(0)

for i in file:
    if i.strip() == "":
        continue
    val= i.strip()
    if(val[-1]==":"):
        count += 1
        pc=pc+4
        j=j+1
    
    else:
        j=j+1 #counting assembly code lines
        count += 1
        pc=pc+4
        list=i.strip().split(" ")
        command = list[0][-1]
        list1=list[1].strip().split(",")
        
        
        if command==(":"):
            list.remove(list[0])
            list1=list[1].strip().split(",")
            
        if list[0] == "add" :
            register=registerencode(list1)
            if len(list1)!=3:
                file1.write("ERROR:SYNTAX ERROR (NOT ENOUGH REGISTERS)")
                break
            elif register==-1:
                file1.write("ERROR:REGISTER NOT FOUND")
                break
            
            else:
                binarycode = ADD(register)
            
            
        elif list[0] == "sub" :
            register=registerencode(list1)
            if len(list1)!=3:
                file1.write("ERROR:SYNTAX ERROR (NOT ENOUGH REGISTERS)")
                break
            elif register==-1:
                file1.write("ERROR:REGISTER NOT FOUND")
                break
            else:
                binarycode = SUB(register)
            
            
        elif list[0] == "sll" :
            register=registerencode(list1)
            if len(list1)!=3:
                file1.write("ERROR:SYNTAX ERROR (NOT ENOUGH REGISTERS)")
                break
            elif register==-1:
                file1.write("ERROR:REGISTER NOT FOUND")
                break
            else:
                binarycode = SLL(register)
           
            
        elif list[0] == "slt" :
            register=registerencode(list1)
            if len(list1)!=3:
                file1.write("ERROR:SYNTAX ERROR (NOT ENOUGH REGISTERS)")
                break
            elif register==-1:
                file1.write("ERROR:REGISTER NOT FOUND")
                break
            else:
                binarycode = SLT(register)
           
            
        elif list[0] == "sltu" :
            register=registerencode(list1)
            if len(list1)!=3:
                file1.write("ERROR:SYNTAX ERROR (NOT ENOUGH REGISTERS)")
                break
            elif register==-1:
                file1.write("ERROR:REGISTER NOT FOUND")
                break
            else:
                binarycode = SLTU(register)
            
            
        elif list[0] == "xor" :
            register=registerencode(list1)
            if len(list1)!=3:
                file1.write("ERROR:SYNTAX ERROR (NOT ENOUGH REGISTERS)")
                break
            elif register==-1:
                file1.write("ERROR:REGISTER NOT FOUND")
                break
            else:
                binarycode = XOR(register)
            
            
        elif list[0] == "srl" :
            register=registerencode(list1)
            if len(list1)!=3:
                file1.write("ERROR:SYNTAX ERROR (NOT ENOUGH REGISTERS)")
                break
            elif register==-1:
                file1.write("ERROR:REGISTER NOT FOUND")
                break
            else:
                binarycode = SRL(register)
            
            
        elif list[0] == "or" :
            register=registerencode(list1)
            if len(list1)!=3:
                file1.write("ERROR:SYNTAX ERROR (NOT ENOUGH REGISTERS)")
                break
            elif register==-1:
                file1.write("ERROR:REGISTER NOT FOUND")
                break
            else:
                binarycode = OR(register)
            
            
        elif list[0] == "and" :
            register=registerencode(list1)
            if len(list1)!=3:
                file1.write("ERROR:SYNTAX ERROR (NOT ENOUGH REGISTERS)")
                break
            elif register==-1:
                file1.write("ERROR:REGISTER NOT FOUND")
                break
            else:
                binarycode = AND(register)
           
            

        elif list[0] =="beq" or list[0] =="bne" or list[0]=="blt" or list[0]=="bge" or list[0]=="bltu" or list[0]=="bgeu":
            register=registerencode(list1[:-1])
            if len(list1)!=3:
                file1.write("ERROR:SYNTAX ERROR (NOT ENOUGH REGISTERS)")
                break
            elif register==-1:
                file1.write("ERROR:REGISTER NOT FOUND")
                break
            else:
                binarycode= btype(register[0], register[1], pc, d, list, list1)
                if binarycode =="ERROR: immediate out of bounds":
                    for i in binarycode :
                        file1.write(i)
                    file1.write("\n")
                    break
                elif binarycode=="00000000000000000000000001100011":
                    
                    for i in binarycode :
                        file1.write(i)
                    file1.write("\n")
                    
                    
                    break
                
                
#jagan

        elif list[0] == "addi":
            register=registerencode(list1[:-1])
            if len(list1)!=3:
                file1.write("ERROR:SYNTAX ERROR (NOT ENOUGH REGISTERS)")
                break
            elif register==-1:
                file1.write("ERROR:REGISTER NOT FOUND")
                break
            else:
                binarycode=addi(list1)
                if binarycode =="ERROR: immediate out of bounds":
                    for i in binarycode :
                        file1.write(i)
                    file1.write("\n")
                    break


        elif list[0] == "sltiu":
            register=registerencode(list1[:-1])
            if len(list1)!=3:
                file1.write("ERROR:SYNTAX ERROR (NOT ENOUGH REGISTERS)")
                break
            elif register==-1:
                file1.write("ERROR:REGISTER NOT FOUND")
                break
            else:
                binarycode=sltiu(list1)
                if binarycode =="ERROR: immediate out of bounds":
                    for i in binarycode :
                        file1.write(i)
                    file1.write("\n")
                    break


        elif list[0] == "jalr":
            register=registerencode(list1[:-1])
            if len(list1)!=3:
                file1.write("ERROR:SYNTAX ERROR (NOT ENOUGH REGISTERS)")
                break
            elif register==-1:
                file1.write("ERROR:REGISTER NOT FOUND")
                break
            else:
                binarycode=jalr(list1)
                if binarycode =="ERROR: immediate out of bounds":
                    for i in binarycode :
                        file1.write(i)
                    file1.write("\n")
                    break


        elif list[0] == "lw":
            aj=""
            aj=list1[-1][-3:-1]
            listj=[]
            listj.append(list1[0])
            listj.append(aj)
            
            
            register=registerencode(listj)
            if len(list1)!=2:
                file1.write("ERROR:SYNTAX ERROR (NOT ENOUGH REGISTERS)")
                break
            elif register==-1:
                file1.write("ERROR:REGISTER NOT FOUND")
                break
            else:
                binarycode=lw(list1)
                if binarycode =="ERROR: immediate out of bounds":
                    for i in binarycode :
                        file1.write(i)
                    file1.write("\n")
                    break

            
        elif list[0] =="jal":
            register=registerencode(list1[:-1])
            if len(list1)!=2:
                file1.write("ERROR:SYNTAX ERROR (NOT ENOUGH REGISTERS)")
                break
            elif register==-1:
                file1.write("ERROR:REGISTER NOT FOUND")
                break
            else:
                binarycode=jtype(register[0],list,list1,d,pc)
                if binarycode =="ERROR: immediate out of bounds":
                    for i in binarycode :
                        file1.write(i)
                    file1.write("\n")
                    break
            

        elif list[0]=="sw":
            aj=""
            aj=list1[-1][-3:-1]
            listj=[]
            listj.append(list1[0])
            listj.append(aj)
            
            register=registerencode(listj)
            if len(list1)!=2:
                file1.write("ERROR:SYNTAX ERROR (NOT ENOUGH REGISTERS)")
                break
            elif register==-1:
                file1.write("ERROR:REGISTER NOT FOUND")
                break
            else:
                binarycode=sw(list1)
                if binarycode =="ERROR: immediate out of bounds":
                    for i in binarycode :
                        file1.write(i)
                    file1.write("\n")
                    break
            
        elif list[0]=="auipc":
            register=registerencode(list1[:-1])
            if len(list1)!=2:
                file1.write("ERROR:SYNTAX ERROR (NOT ENOUGH REGISTERS)")
                break
            elif register==-1:
                file1.write("ERROR:REGISTER NOT FOUND")
                break
            else:
                binarycode=auipc(list1)
                if binarycode =="ERROR: immediate out of bounds":
                    for i in binarycode :
                        file1.write(i)
                    file1.write("\n")
                    break

        elif list[0]=="lui":
            register=registerencode(list1[:-1])
            if len(list1)!=2:
                file1.write("ERROR:SYNTAX ERROR (NOT ENOUGH REGISTERS)")
                break
            elif register==-1:
                file1.write("ERROR:REGISTER NOT FOUND")
                break
            else:
                binarycode=lui(list1)
                if binarycode =="ERROR: immediate out of bounds":
                    for i in binarycode :
                        file1.write(i)
                    file1.write("\n")
                    break

        
        if j==inst_cnt and binarycode!="00000000000000000000000001100011":
                for i in binarycode :
                    file1.write(i)
                file1.write("\n")
                file1.write("VIRTUAL HALT MISSING")
                
                break
            
        for i in binarycode :
            file1.write(i)
        
        file1.write("\n")
file1.close()

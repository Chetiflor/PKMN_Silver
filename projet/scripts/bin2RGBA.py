def transcribe_extension(filename,extension):
    f = open("projet/"+filename+extension)
    text_file = open("projet/"+filename+"_RGBA"+extension, "w")
    for x in f:
        if(len(x)!=2 and (x[0]=="0" or x[0]=="1" or x[0]=="R")):
            for i in range(len(x)):
                if(x[i]=="1"):
                    text_file.write("{0,0,0,255}")
                if(x[i]=="0"):
                    text_file.write("{252,252,252,255}")
                if(x[i]=="R"):
                    text_file.write("{252,0,0,255}")
            text_file.write("\n")
        else:
            text_file.write(x)
    text_file.close()

def split_extension(filename):
    name =""
    extension=""
    passed = False
    for i in range(len(filename)):
        if(filename[i]=="."):
            passed = True
        if(passed):
            extension+=filename[i]
        else:
            name+=filename[i]
    return(name,extension)

def transcribe(filename):
    name,extension = split_extension(filename)
    transcribe_extension(name,extension)

#transcribe("ascii_pkm.txt")
transcribe("style_1.txt")
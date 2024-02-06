import glob
key = "bhUlIshutrea98liOp"
file_paths = glob.glob("forela-criticaldata/*.24bes")
for file in file_paths:
    with open(file, "rb") as f:
        data = f.read()
    new_data = bytearray()
    for i in range(0, len(data)):
        tmp = data[i] ^ ord(key[i % len(key)])
        tmp_hex = hex(tmp)
        new_data.append(tmp)
    with open(file[:-6], "wb") as nf:
        nf.write(new_data)

        
    

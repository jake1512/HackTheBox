key = 'b7894532snsmajuys6'

with open('3090', "rb") as f:
    data = f.read()
    new_data = bytearray()
    for i in range(0, len(data)):
        tmp = data[i] ^ ord(key[i % len(key)])
        tmp_hex = hex(tmp)
        new_data.append(tmp)

print(new_data)
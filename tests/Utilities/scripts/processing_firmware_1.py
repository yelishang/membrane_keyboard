# -*- coding: utf8 -*-

'''
  本脚本用于处理固件
'''

import sys
import binascii
import os
import shutil
from intelhex import IntelHex

print('====== Processing Firmware Start ======')

if len(sys.argv) != 2:
  print('script.py inout.hex')
  sys.exit(1)

print('Input hex file: {}'.format(sys.argv[1]))

ih = IntelHex()
ih.loadfile(sys.argv[1], format='hex')

print('This image address range is [0x{:08X},0x{:08X}]'.format(ih.minaddr(), ih.maxaddr()))

#ih.dump()

fwbin = bytearray()
fwdict = ih.todict()
for addr in range(ih.minaddr(), ih.maxaddr()+1):
  data = fwdict.get(addr)
  if data == None:
    fwbin.append(0x00)
  else:
    fwbin.append(data)
# 如果固件SIZE不是4的倍数，则补齐
remainder = len(fwbin) % 4
if remainder != 0:
  for i in range(4-remainder):
    fwbin.append(0x00)
fwbin_size = len(fwbin)
print('fwbin size = {}'.format(fwbin_size))


# 将固件SIZE和CRC32存放到指定位置
fwbin[0x1C:0x20] = int.to_bytes(0, 4, byteorder='little', signed=False)
fwbin[0x20:0x24] = int.to_bytes(0, 4, byteorder='little', signed=False)
fwbin_crc32 = binascii.crc32(fwbin)
print("fwbin_size = {}, fwbin_crc32 = 0x{:08X}".format(fwbin_size, fwbin_crc32))
fwbin[0x1C:0x20] = int.to_bytes(fwbin_size, 4, byteorder='little', signed=False)
fwbin[0x20:0x24] = int.to_bytes(fwbin_crc32, 4, byteorder='little', signed=False)

# 重命名原始HEX文件
original_file_path = os.path.splitext(sys.argv[1])[0] + '_original.hex'
if os.path.exists(original_file_path):
  os.remove(original_file_path)
os.rename(sys.argv[1], original_file_path)
print('The original hex file was renamed to {}'.format(original_file_path))

# 将处理过的固件代码输出为指定Hex文件
pih = IntelHex()
pih.frombytes(fwbin, offset=ih.minaddr())
pih.start_addr = ih.start_addr
print('Output hex file: {}'.format(sys.argv[1]))
pih.write_hex_file(sys.argv[1])


print('====== Processing Firmware End ======')

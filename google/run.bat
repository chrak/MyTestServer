set DST_DIR=.\..\Packet
set SRC_DIR=.\..\Packet\proto
protoc -I=%SRC_DIR% --cpp_out=%DST_DIR% %SRC_DIR%/C2L_Packet.proto
protoc -I=%SRC_DIR% --cpp_out=%DST_DIR% %SRC_DIR%/L2C_Packet.proto
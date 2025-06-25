CC = gcc                             # The compiler to use
CFLAGS = -Iinclude                   # Include directory for header files

#Source files
CLIENT_SRC = src/client.c
SERVER_SRC = src/server.c
SYSINFO_SRC = src/system_info.c

#Object files
SERVER_OBJ = build/server.o
SYSINFO_OBJ = build/system_info.o

#Executable names
CLIENT_EXEC = build/client
SERVER_EXEC = build/server

client:
	$(CC) $(CFLAGS) $(CLIENT_SRC) -o $(CLIENT_EXEC)
	# Compiles client.c into the 'client' executable

build/system_info.o:
	$(CC) $(CFLAGS) -c $(SYSINFO_SRC) -o $(SYSINFO_OBJ)
	# Compiles system_info.c into system_info.o

build/server.o:
	$(CC) $(CFLAGS) -c $(SERVER_SRC) -o $(SERVER_OBJ)
	# Compiles server.c into server.o

server: build/server.o build/system_info.o
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(SYSINFO_OBJ) -o $(SERVER_EXEC)
	# Links server.o and system_info.o into the 'server' executable

clean:
	rm -f $(SERVER_OBJ) $(SYSINFO_OBJ) $(SERVER_EXEC) $(CLIENT_EXEC)
	# Deletes object files and executables to start fresh

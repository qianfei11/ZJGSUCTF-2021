BINARY=encryptor
all: $(BINARY)
encryptor: encryptor.cpp
	g++ encryptor.cpp -o encryptor -z now -fPIE -pie
	strip encryptor
clean:
		rm -f $(BINARY)

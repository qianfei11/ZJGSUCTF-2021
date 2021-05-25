BINARY=anti-f5
all: $(BINARY)
anti-f5: anti-f5.c
	gcc anti-f5.c -o anti-f5 -m32 -masm=intel -z now -fPIE -pie
	strip anti-f5
clean:
	rm -f $(BINARY)

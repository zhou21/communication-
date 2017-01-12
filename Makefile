CC=gcc
obj=main.c cJSON.c
LIBS:= -lm 

main: $(target)
	$(CC) $(obj) -o main $(LIBS) 

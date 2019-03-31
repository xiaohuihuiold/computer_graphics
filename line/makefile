CC = gcc
OUT_DIR = ./out
CFLAGS = -lGLEW -lglfw -lGL \
		 -lpthread \
		 -lX11 -lXrandr -lXi -lXxf86vm -lXinerama -lXcursor \
		 -lrt -lm -ldl

all: dda

# DDA画线算法
dda: $(OUT_DIR) dda.c draw.o
	$(CC) $(CFLAGS) dda.c $(OUT_DIR)/draw.o -o $(OUT_DIR)/dda

# 绘图函数库
draw.o: draw.c
	$(CC) $(CFLAGS) -c draw.c -o $(OUT_DIR)/draw.o

$(OUT_DIR):
	mkdir $(OUT_DIR)

clean:
	rm -rf $(OUT_DIR)

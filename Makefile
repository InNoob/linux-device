Target=mousecom
Objs= ./bin/$(path)/*.class

all:$(Target)

$(Target): 
	gcc src/*.c -o bin/mousecom -fPIC -lX11 -lpthread -lXtst

clean:
	-rm -rf ./bin/*

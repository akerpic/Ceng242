LDFLAGS=-std=c++11

all: ; g++ $(LDFLAGS) main.cpp GameParser.cpp GameEngine.cpp Player.cpp Board.cpp Berserk.cpp Tracer.cpp Ambusher.cpp Pacifist.cpp Dummy.cpp TestablePlayer.cpp TestableBoard.cpp TestableGameEngine.cpp TestableGameParser.cpp TestableAllStream.cpp -o CengNite
run: ; ./CengNite input.txt
clean: ; rm -rf CengNite;
valgrind: ; valgrind --leak-check=full --error-exitcode=1 ./CengNite input.txt

zipper: ; cat filesToUpload.txt | zip -@ hw4.zip
zipDeleter: ; rm -f hw4.zip

testValgrind: ; make all && make valgrind && echo $?

player: ; g++ $(LDFLAGS) main.cpp TestableGameParser.cpp GameParser.cpp Player.cpp Berserk.cpp Tracer.cpp Ambusher.cpp Pacifist.cpp Dummy.cpp TestablePlayer.cpp -o player

board: ; g++ $(LDFLAGS) main.cpp TestableGameParser.cpp GameParser.cpp Player.cpp Board.cpp TestableBoard.cpp  Berserk.cpp Tracer.cpp Ambusher.cpp Pacifist.cpp Dummy.cpp TestablePlayer.cpp -o board

engine: ; g++ $(LDFLAGS) main.cpp TestableGameEngine.cpp GameEngine.cpp TestableGameParser.cpp GameParser.cpp Player.cpp Board.cpp TestableBoard.cpp  Berserk.cpp Tracer.cpp Ambusher.cpp Pacifist.cpp Dummy.cpp TestablePlayer.cpp -o engine

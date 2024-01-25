mac: mac-link mac-run

mac-link:
	g++ -std=c++17 main.cpp Piece.cpp Pieces.cpp Color.cpp Game.cpp Board.cpp Position.cpp -o omac -I "./include" -L "./lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
mac-run:
	./omac

windows: windows-link windows-run

windows-link: 
	g++ -std=c++17 main.cpp Piece.cpp Pieces.cpp Color.cpp Game.cpp Board.cpp Position.cpp -o owin -I "./includewindows" -L "./libwindows" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

windows-run:

	./owin

linux: linux-link linux-run

linux-link:
	g++ -std=c++17 main.cpp Piece.cpp Pieces.cpp Color.cpp Game.cpp Board.cpp Position.cpp -o olin -I "./includelinux" -L "./liblinux" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
linux-run:
	./olin


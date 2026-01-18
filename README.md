# Monkemon_OOP
Projekt iz OOP, Nikola Mačukatić i Ivan Josipović

Za Linux:

Potrebna instalacija rayliba:

git clone https://github.com/raysan5/raylib.git
cd raylib
mkdir build && cd build
cmake ..
make
sudo make install

Kompajliranje:
//NAPOMENA: potreban je g++
g++ src/*.cpp -o Monkemon $(pkg-config --cflags --libs raylib)
//NAPOMENA: umijesto src, staviti put do foldera u kojem se nalazi projekt
./Monkemon


Za Windows:

Pokreče se preko Monkemon.exe file

Monkemon:

Sve kontrole su objašnjene korisniku unutar igre



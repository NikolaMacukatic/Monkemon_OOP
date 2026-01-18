# Monkemon OOP
Projekt iz OOP  
Autori: Nikola Mačkatić i Ivan Josipović

## Za Linux

### Potrebna instalacija rayliba
```bash
git clone https://github.com/raysan5/raylib.git
cd raylib
mkdir build && cd build
cmake ..
make
sudo make install
```

### Kompajliranje
> Napomena: potreban je `g++`

```bash
g++ src/*.cpp -o Monkemon $(pkg-config --cflags --libs raylib)
```

### Pokretanje
```bash
./Monkemon
```

---

## Za Windows
Program se pokreće preko `Monkemon.exe` datoteke.

---

## Monkemon
Sve kontrole su objašnjene korisniku unutar igre.

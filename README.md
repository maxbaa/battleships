# battleships
C++-Project for lecture

# Instructions
Voraussetzungen:
- Boost-Library

Programm starten:
1. Boost-Library Pfad in CMakeLists.txt in lokalen Speicherort der Boost-Library ändern
2. Build Ordner unter root-Pfad anlegen 
3. Build Ordner im Terminal öffnen
4. Unter diesem Pfad (".\build") "cmake.." ausführen
5. Und anschließend unter dem selben Pfad "cmake --build ." ausführen
6. Zum Ausführen in Debug-Ordner (".\build\Debug") navigieren und Battleships.exe ausführen

ToDo:
- [X] Networking
  - [X] Connecten
    - [X] Wie finde ich meinen Gegner?
      - [X] IP-Adresse zum Verbinden mit Server
  - [X] In Game Loop
  - [X] Protokoll festlegen
- [X] Hit Detection (Shoot Methode)
- [X] In Game logic -> game board
- [X] Game Loop
  - [X] State Machine: Hauptmenu, Ingame
  - [X] State: Am Zug, Gegner am Zug, Auswertung
- [X] KI
  - [X] Random Init Ships
  - [X] Random Target selection   

 

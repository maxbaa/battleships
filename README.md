# battleships
C++-Project for lecture

# Instructions
To run execute following command to first compile the game:
````g++ AI.cpp Game.cpp GameBoard.cpp GameConfig.cpp Human.cpp main.cpp NetworkConnection.cpp Ship.cpp -o battleship.exe && battleship.exe ````

Then run
```` .\battleship.exe ```` 
to start the game

ToDo:
- [ ] Networking
  - [ ] Connecten
    - [ ] Wie finde ich meinen Gegner?
      - [ ] Erstmal mit IP
        - [ ] Darstellen der IP ingame?! 
      - [ ] Danach Lobby Codes 
  - [ ] In Game Loop
  - [ ] Protokoll festlegen
- [X] Hit Detection (Shoot Methode)
- [X] In Game logic -> game board
- [ ] Game Loop
  - [ ] State Machine: Hauptmenu, Ingame, Pausiert
  - [X] State: Am Zug, Gegner am Zug, Auswertung
- [ ] KI
  - [X] Random Init Ships
  - [X] Random Target selection
  - [ ] Further improvements
     

 

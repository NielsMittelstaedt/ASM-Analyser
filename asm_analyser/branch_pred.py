# bei conditional b, bx, bl, (pop, load mit pc)
# muss die branch prediction eingebaut werden.

# Wir brauchen zwei globale variablen für die Anzahl conditional branches
# und die Anzahl Misspredictions

# Bei einem conditional branch wird je nach if auswertung dann
# die branch pred bits erhöht oder verringert und die misprediction gezählt


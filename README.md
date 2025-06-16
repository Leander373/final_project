# Abschlussprojekt - Zelluläre Automaten (25 Punkte)

Für das Abschlussprojekt im Kurs `Programmieren für Physikstudierende` sollen Sie ein vollständiges Programm zu einer physikalischen Anwendung von Grund auf selbst erstellen. Dabei sollen Sie das, bisher in diesem Kurs erlangte, Wissen anwenden. Sie benötigen dazu unter anderem Kenntnisse über `structs`, Lesen und Schreiben von Dateien, sowie die Handhabung von Bibliotheken (also jene Kapitel aus der letzten Praktikumsphase). Zusätzlich sollen Sie anstatt der bis jetzt verwendeten, direkten Kompiliermethode ein Makefile erstellen, das die Kompilierung automatisch übernimmt. Literatur zur Wiederholung dieser Themen ist ganz unten angeführt.

## Motivation

In der Physik werden häufig Simulationen verwendet, um komplexe Prozesse zu charakterisieren oder theoretische Modelle zu testen. Oft sind das sehr aufwändige Simulationen, die nur auf Hochleistungsrechnern durchgeführt werden können. Oft ist es aber auch interessant, das Verhalten eines System zu untersuchen, das nur auf ganz simplen Regeln beruht. In diesem Projekt sollen Sie mit so genannten zellulären Automaten arbeiten. Es handelt sich dabei um diskrete dynamische Systeme, die seit vielen Jahren bekannt sind und studiert werden. Einige Wissenschaftler glauben, dass unser gesamtes Universum als ein solches System beschrieben werden könnte.

## Aufgabenstellung

### (a) Eindimensionale zelluläre Automaten

Eindimensionale zelluläre Automaten sind im Prinzip eine Zeile aus Nullen und Einsen, die in jedem Zeitschritt aktualisiert wird. Zum Beispiel könnte ein Zustand durch `0 0 0 1 0 0 0` beschrieben werden. Dann werden bestimmte Regeln verwendet, um diese Zeile zu verändern. Dabei beziehen sich die Regeln immer auf eine Zelle und ihre direkten Nachbarn in beide Richtungen. Für die Randzellen werden dabei jeweils die gegenüberliegenden Randzellen mit in Betracht gezogen. Die Regeln sehen zum Beispiel folgendermaßen aus:

- 1 1 1 -> 0
- 1 1 0 -> 1
- 1 0 1 -> 1
- 1 0 0 -> 0
- 0 1 1 -> 1
- 0 1 0 -> 1
- 0 0 1 -> 1
- 0 0 0 -> 0

Für unsere Beispiel (0 0 0 1 0 0 0) sind für den ersten Zeitschritt also folgende Regeln wichtig:

- 0 0 0 -> 0 für die 1., 2., 6., und 7\. Stelle
- 0 0 1 -> 1 für die 3\. Stelle
- 0 1 0 -> 1 für die 4\. Stelle und
- 1 0 0 -> 0 für die 5\. Stelle.

Nach einem Schritt sieht unsere Zeile nun also so aus: `0 0 1 1 0 0 0`.

Diese, von uns angewandte, Regel wird auch `Regel 110` genannt, weil ihre Binärdarstellung $`01101110_2 = 110_{10}`$ unsere Änderungen für die Sets aus drei Zahlen bestimmt. Es gibt also 256 verschiedene Regeln für die Entwicklung eines solchen zellulären Automaten.

Implementieren Sie ein Programm, das für zelluläre Automaten mit den Regeln 22, 106, 187, 214 der Größe `N` die Entwicklung für `M` Zeitschritte berechnet, wobei `N` und `M` beim Ausführen übergeben werden sollen. Dies soll jeweils für den Startwert 0 0 ... 0 1 0 .... 0 0 (also 1 in der Mitte, 0 sonst) und einer zufälligen Verteilung von 0 und 1 geschehen. Schreiben Sie dabei die Zeile nach jedem Zeitschritt in eine Datei im Ordner `1d_states/`. Der Dateiname muss von der Form `1d_rule_<regel>.txt` sein, also beispielsweise `1d_rule_187.txt`. Das Format soll so aussehen, dass der Inhalt der Datei nach zwei Zeitschritten folgendermaßen aussieht:

```
0 0 0 1 0 0 0
0 0 1 1 0 0 0
```

Dieses Ergebnis kann dann, mit Hilfe der Plotting-Tools visualisiert werden. Dazu benötigt man den Befehl: `./plot_1d <regel>` wobei sie `<regel>` mit z.B. 187 ersetzen müssen. Damit wird ein Bild `1d_rule_<regel>.png` im Ordner `1d_plots` erzeugt.

### (b) Zweidimensionale zelluläre Automaten

Das Prinzip von zweidimensionalen zellulären Automaten ist recht ähnlich. Hierbei handelt es sich um eine zweidimensionale Struktur aus Nullen und Einsen, etwa:

```
1 0 1 1 0 0 1
1 1 0 1 1 0 1
1 0 1 0 1 0 1
1 0 0 1 1 1 1
1 1 0 1 1 0 1
```

Für einen neuen Zeitschritt werden die Werte, abhängig von allen acht Nachbarzellen einer Zelle berechnet. Man spricht von einer Zelle als lebendig, wenn sie den Wert 1 hat und als tot, wenn sie den Wert 0 hat. Implementieren Sie so einen zweidimensionalen zellulären Automaten, der nach den folgenden Regeln aktualisiert wird:

- Eine tote Zelle wird zum Leben erweckt, wenn sie genau drei lebendige Nachbarn hat.
- Eine lebendige Zelle mit weniger als zwei lebendigen Nachbarn stirbt an Einsamkeit.
- Eine lebendige Zelle mit zwei oder drei lebendigen Nachbarn bleibt am Leben.
- Eine lebendige Zelle mit mehr als drei lebendigen Nachbarn stirbt an Überbevölkerung.

Auch hier soll die Implementierung wieder ein `N` und `M` übernehmen, so, dass ein Gitter der Größe $`N \times N`$ angelegt wird. Füllen Sie dieses zu Beginn mit zufälligen Werten (0 und 1) und lassen es dann für `M` Zeitschritte entwickeln. Jeder Zeitschritt soll dann in eine Datei (startend von `2d_state_0001.txt` bis maximal `2d_state_9999.txt`) geschrieben werden, wobei Sie diese Dateien im Ordner `2d_states/` abspeichern müssen. Diese sollen dann nämlich, mit Hilfe der zur Verfügung gestellten Plotting-Tools zu einer Animation verarbeitet werden. Das funktioniert mittels `./plot_2d <n_steps>`, wobei `<n_steps>` die Anzahl an zu plottenden Zeitschritten ist. Damit wird `animation_<n_steps>_steps.gif` im Ordner `2d_plots/` erzeugt.

### (c) Besondere Strukturen im zweidimensionalen zellulären Automaten

Entwickelt man ein Gitter nach den Regeln aus b), kann es zu bestimmen Strukturen kommen, die dann, zum Beispiel als Raumschiff, durch das Gitter wandern. Schreiben Sie ein Programm, das ein Gitter der Größe 200 x 200 entwickelt, das zunächst nur mit Nullen und folgender Struktur gefüllt ist

```
0 1 0 0 1
1 0 0 0 0
1 0 0 0 1
1 1 1 1 1
```

und entwickeln Sie es für 200 Zeitschritte. Es sollte sich in eine Richtung fortbewegen und dabei seine Darstellung regelmäßig ändern. Erzeugen Sie auch hier wieder ein Video mit den zur Verfügung gestellten Plotting-Tools.

### (d) Automatisieren Sie das Kompilieren Ihres Codes mit Hilfe von `make`

Erstellen Sie ein `Makefile`, das Ihr Programm automatisch mit dem Befehl `make` kompiliert. Ihre Funktionen sollen auf mehrere `.c` Dateien und mehrere Header Dateien (`.h`) aufgeteilt werden. Zum Beispiel eine Datei für das Schreiben von Ausgabedateien, eine Datei für die Zeitevolution und eine Header-Datei in der etwaige `structs` definiert sind. Die Datei, die die `main` Funktion enthält, soll keine weiteren Funktionsdefinitionen enthalten. Definieren Sie alle anderen Funktionen in geeignet zusammengefassten, weiteren `.c` Dateien und lagern Sie Konstanten und Prototypen in Header aus.

### (e) Schreiben Sie (wie für die vorherigen Aufgaben) eine ausführliche Dokumentation zu Ihrem Programm

Vergessen Sie dabei nicht zu beschreiben, wie Sie das `Makefile` strukturiert haben und welche Befehle damit unterstützt werden. Machen Sie bitte erkenntlich, wer für welchen Teil Ihrer Abgabe verantwortlich war. Falls es die Dateigröße erlaubt, können Sie gerne auch die erstellten Animationen hinzufügen.

## Literatur:

**Strukturen:**

<https://de.wikibooks.org/wiki/C-Programmierung:_Komplexe_Datentypen#Strukturen>

<http://openbook.rheinwerk-verlag.de/c_von_a_bis_z/015_c_strukturen_001.htm>

**File handling:**

<https://de.wikibooks.org/wiki/C-Programmierung:_Dateien>

<http://openbook.rheinwerk-verlag.de/c_von_a_bis_z/016_c_ein_ausgabe_funktionen_005.htm#mj47f082541eb4df9dbdcefdbc2775feae>

<http://openbook.rheinwerk-verlag.de/c_von_a_bis_z/016_c_ein_ausgabe_funktionen_009.htm#mje5a9730700783816c72f0f4556b59d10>

<https://www.tutorialspoint.com/c_standard_library/c_function_fscanf.htm>

**Header & Include:**

<https://de.wikibooks.org/wiki/C-Programmierung:_Eigene_Header>

<http://openbook.rheinwerk-verlag.de/c_von_a_bis_z/010_c_praeprozessor_001.htm#mjf374f026d04c7badd6109bab24ff1114>

**Getrenntes Kompilieren:**

<http://openbook.rheinwerk-verlag.de/c_von_a_bis_z/009_c_funktionen_019.htm#mj58913b45fd4f8e5cbad7632da152ca54>

**Makefiles:**

<https://www.c-howto.de/tutorial/makefiles/>

<https://makefiletutorial.com/>

<https://web.stanford.edu/class/archive/cs/cs107/cs107.1174/guide_make.html>

# Procvičování funkcí v jazyce C

Následující dokument popisuje sadu úloh pro procvičování psaní základních funkcí v jazyce C.
Každá úloha má číslo v hranatých závorkák (např. [0.1]), které odpovídá úrovni (složitosti)
a pořadí úlohy. Tento údaj slouží k identifikaci jednotlivých úkolu.

Kromně napsani funkce samotné musíte také oveřit jeji funkčnost ([MVP](https://pixelfield.cz/blog/mvp-co-to-znamena-a-proc-je-to-dulezity-pro-vas-byzny/))
(ve funkci main nebo jiným způsobem demostrujícím použití funkce).

## Odevzdání úkolu

Úkol se odevzdává pomocí `MS Teams`.

Při odevzávání úkolu, můžete zvolit:

- **jeden velký soubor**, který bude mít přiložen seznam vyřešených úloh:
  - `inf_2c_{příjmení+iniciál}_master.c`
  - `inf_2c_{příjmení+iniciál}_list.txt`
    - (příklad: `inf_2c_michalekt_master.c`, `inf_2c_michalekt_list.txt`)
- **samostatně řešené úlohy** (nebo úrovně), kde formát je následující:
  - `inf_2c_{příjmení+iniciál}_task_{level}_{číslo}.c`
    - (příklad: _inf\_2c\_michalekt\_task\_0\_1.c_ <- řešení úlohy mph na kph)

## Povinné úlohy

### [level 0] -- ✈️ Rychlosti

Někdy potřebujeme znát jak rychle se na nás něco řítí nebo jaká je maximální povolená rychlost.
Ale ne všude ve světě se používají stejné jednotky (hint: USA - 😒). Pojďme si proto převést
základní jednoty rychlosti.

> I feed the need... The need for speed!
>
> -- Maveric ([Top Gun](https://www.youtube.com/watch?v=4PzpztFJZ))

#### [0.0] 📗 Napište funkci pro převod kilometrů za hodinu na míle za hodinu

- Tato funkce bude příjímat jakékoliv rychlost (bez kontroly).
- Samotný převod si musíte najít nebo odvodit.

#### [0.1] 📗 Napište funkci pro převod mil za hodinu (mph) na kilometry za hodinu (kph)

- Tato funkce bude příjímat jakoukoliv hodnotu rychlosti v rozmezí
od `0` do [`MACH2`](https://jalopnik.com/be-the-coolest-pilot-in-the-sky-in-this-supersonic-figh-1847868163) (2,385.36 kph).
- V případě, že je hodnota mimo toto rozmezí, vypíše se hláška a funkce vrátí zápornou hodnotu (-1).

### [level 1] -- 🤖 Číslicovka

> „Matematický stroj nesmí být sensačním překvapením pro mladého člověka.
> Musí se s ním seznámit jako s obvyklým zařízením, které je jedním z běžných
> prostředků k dobývání obživy.“
>
> -- Antonín Svoboda (I. celostátní konference v oboru výpočetní a organizační techniky), Praha 1958

Následující úlohy mají návaznost na předmět `číslicová technika` a možná i `základy elektrotechniky`.

#### [1.0] 📗 Napište funkce pro výpočty veličin ohmova zákona

- funkce pro napětí
- funkce pro proud
- funkce pro odpor

#### [1.1] 📗 Realizujte funkci, která po zadání čísla integrovaného obvodu, vypíše jeho funkci

Pro realizaci této úlohy budete muset najít některé obvody, které se objěvují v řadě obvodů `TTL 74xx`, kterou využívame na CITku.
Najďete si proto následující obvody (stačí jejich čísla):

- RAM 16 × 1 bit
- 4 × 2vstupový multiplexer
- dělič 1 : 50
- 2 × 4vstupové hradlo NAND
- 4 × 2vstupové hradlo NOR

- Pokud uživatel funkce zadá neexistující (pro vás neznámy obvod) - zahlásíte mu to zprávou: `"Neznamy obvod"`

## Nepovinné úlohy (které vám však můžou pomoci se připravit na písemku)

### [level 2] -- 🌡️ Teplota

![Image](hotcold.jpeg)

#### [2.0] 📘 Napište funci pro převod `Fahrenhait -> Celsius`

#### [2.1] 📘 Napište funci pro převod `Celsius -> Fahrenhait`

#### [2.2] 📘 Napište funkci pro převod `Celsius -> Kelvin`

#### [2.3] 📙 Pomoci předchozích funkcí realizujte převod `Fahrenhait -> Kelvin`

### [level 3] -- ⏱️ Čas

Následující úlohy pracují s časem. Přesto, že se každá funkce dá řešit zvlášť, vaším úkolem je je napsat postupně
za sebou a k řešení další úlohy vždy použít tu předchozí. Sekunda je pro nás nedělitelnou jednotkou.

> Za všechno může čas ...
> ... a v něm vteřina je delší než rok ...
> -- Lenka Filipová ([Za všechno může čas](https://www.youtube.com/watch?v=mcS2hq15BgE&t=40s))

#### [3.0] 📘 Napište funkci, která převede sekundy na minuty

#### [3.1] 📘 Pomocí předchozí funkce [3.0] realizujte funkci, která převede minuty na hodiny

#### [3.2] 📘 Pomocí předchozí funkce [3.1] realizujte funkci, která převede hodiny na dny

#### [3.3] 📘 Napište funkci, která spočítá kolik času jste strávili ve škole (jeden den) a výsledek vypíše jako [HH:mm]

- jako vstup funkce bude:
  - čas příchodu (hodin, minuta)
  - čas odchodu (hodina, minuta)
- hint:
  - převedeme příchod a odchod na společnou jednotku a odečteme je od sebe.
  - Výsledek musíme znovu pak převést zpět.

## Bonusové úlohy (které vám rozšíří obzory, ale vyžajují více přemýšlet)

### [level 4] -- 🤖 Číslicovka

#### [4.0] 📙 Napiště funkci, která po zadání čísla (0-15) vypíše jeho binární podobu

- Tuto funkci lze řešit několika spůsoby. Zvolit můžete jak univerzální postup, který tuto
úlohu vyřeší pro jakékoliv číslo, nebo specializovanou funkci, která bude řešit jen
tyto čísla (0-15).

### [level 5] -- 🧮 Matematika

#### [5.0] 📙 Napište funkce, která po zadání intervalů vypočíta jejich průsek

- internaly se zadají jako:
  - start intervalu 1.
  - konec intervalu 1.
  - start intervalu 2.
  - konec intervalu 2.
- funkce vypíše text:
  - `"Intervaly <1_start;1_stop> a <2_start;2_stop> se neprotínají."`
  - `"Intervaly <1_start;1_stop> a <2_start;2_stop> mají průsek <start;stop>"`
- funkce vrátí hodnotu:
  - `1` protínají se
  - `0` neprotínají se

#### [5.1] 📙 Napište funkci, která bude vypisovat čísla od 1 do n s tím, že když je číslo dělitelné 3 jak se místo čísla napíše `SP` a když je dělitelné `5` tak `SE`

- Pokud je číslo dělitelné jak `3` tak `5` vypíšeme místo čísla "SPSE"
- Příkladový výstup:
  - `1 2 SP 4 SE SP 7 8 SP SE 11 SP 13 14 SPSE 16` (pro n = 16)

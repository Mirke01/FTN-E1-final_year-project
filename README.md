-Zasto ovaj projekat?

*Projekat je sastavni(najveci) deo cetvrte godine na E1 smeru na podsmeru embeded sistemi i algoritmi. Glavna Ideja projekta je da se prodju 4 glavne pozicije za koje se embeded inzenjer 
skoluje na ovom smeru i da se stekne dublji uvid i iskustvo o tome sta cemo raditi po zavrsetku fakulteta. Takodje svaki deo projekta predstavlja i jedan od delova sa 4 glavna ispita koja
se polazu u zavrsnoj godinii. To znaci da iz svakog dela student mora da odradi barem 50% posla.

*Zamisljeno je da svaki deo nosi izazove sa kojima se srecu inzenjeri na sledecim pozicijama: Arhitekta embedded sistema, Dizajner hardvera, Verifikator hardvera i embedded softver inzenjer. Kroz rad na projektima, student stice skoro pa juniorsko znanje iz navedenih oblasti i projekat predstavlja dobar dodak cv-u.

-Tema projekta:

*Tema projekta je na pocetku bila specifikacija sistema koji razlikuje logoe automobila u nekom visokom jeziku, a zatim se prosirila na hardversko ubrzavanje dvodimenzionalne konvolucije.

-Prvi deo projekta: "Projektovanje sistema na sistemskom nivou".

*Zapoceli smo sa pravljenjem specifikacije naseg sistema u pajtonu. Napisali smo neuronsku mrezu druge generacije(konvolucionalnu neuronsku mrezu) i sistem nahranili sa datasetom od preko pedeset hiljada slika 40 vrsta automobilskih logoa. Sistemu smo na kraju davali slike logoa koje se nisu nalazile u datasetu, a on je sa 98% tacnosti znao da prepozna tacan logo.

*Odradili smo prebacivanje glavnih funkcija neuronske mreze(2Dkonvolucija, Dense, Maxpooling, Relu...), plus neke funkcije iz openCV biblioteke u C jezik, a zatim odradili profajliranje koda sa visual studio ugradjenim profajlerom. Rezultat profajliranja je pokazao da je funkcija kojoj treba najvise vremena da se odradi(i koja je pogodna za hardversko ubrzavanje) 2Dkonvolucija.

*Prvi korak u hardverskom ubrzavanju nekog algoritma obavlja obicno najiskusniji inzenjer u timu. On se naziva "Arhitekta embedded sistema". Sada nam je zadatak bio da napisemo specifikaciju embedded sistema koji ce biti u stanju da hardverski ubrza 2Dkonvoluciju. Za programski jezik u kome ce biti napisana specifikacija sistema smo izabrali C++(kako zbog njegove objektno orijentisane strane, tako i zbog najveceg poznavanja ovog jezika). Glavna biblioteka koju smo koristili tokom pravljenja virtuelne platforme(C++ kod koji simulira kako bi ceo sistem trebao da se ponasa i kako softverski i hardverski delovi sistema komuniciraju) je systemC. SysytemC uvodi iluziju paralelizma u C++, pa samim tim predstavlja odlicnu opciju za simuliranje konkuretnog hardvera. Napisali smo klase koje modeluju komponente sistema: Softverski CPU i hardverki BRAM, interkonekt i nas IP blok unutar koga se nalazi 2Dkonvolucija. Sistem krece sa radom tako sto CPU putem TLM interfejsa, a preko interkonekta salje ulaznu sliku i kernel u BRAM, zatim salje flag IP-u koji govori da on moze da pocne sa obradom slike, a zatim CPU ulazi u prekidnu rutinu. IP cita BRAM sa adresa gde su slika i kernel, smesta ih u svoje interne registre, a zatim zapocinje Konvoluciju. Rezultat konvolucije je konvoluirana slika(slika na kojoj su detektovani neki objekti ili neko drugo procesiranje(u zavisnosti od kerenela)). IP konvoluiranu sliku upisuje u BRAM, a zatim putem asihronog signala obavestava CPU da izadje iz prekida i da moze da krene sa slanjem novih ulaznih parametara u BRAM.

*Kada smo zavrsili sa pisanjem virtuelne platforme, sledeci zadatak je bio procenjivanje THROUGHPUT-A(u nasem slucaju koliko slika IP uspesno konvoluira za jednu sekundu) i procena 
frekvencije sitema. U vitis alat smo ubacili C++ kod 2Dkonvolucije i on nam je dao procenu frekvecnija priblizno 144MHZ. Za racunanje throughput-a smo samo pokrenuli vp na 1 
sekundu(systemC takodje uvodi pojam vremena u C++) i dobili da nas sistem za 1 sekundu moze da obradi 499 slika.

*Zadnji korak ovog dela je pisanje izlazne dokumentacije u nekom alatu za pisanje teksta.

-Drugi deo projekta: "Hardverski dizajn 2Dkonvoluera i pakovanje njega u IP uz koriscenje AXI-LITE interfejsa"

*

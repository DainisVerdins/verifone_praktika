# Verifone praktika uzdevuma nostadne
Nosūtu uzdevumu, kurš jāveic lietojot C valodu, konsoles režīmā, bez vizuāliem papildelementiem, kā formas vai text box. Lietot var jebkuru kompilatoru, tikai lai programmas rezultātu varētu palaist uz Windows darba stacijas.

Lai pārbaudītu rezultātus, nepieciešams izpildāmais fails un programmas kods. Attiecīgajiem failiem jābūt saarhivētiem .zip vai .rar formātā.

 

Uzdevuma risināšanā lūdzu neizmantot "string" un "long long" tipus; goto; malloc.

 

Uzdevums ir vienkāršs bez īpašiem slēptiem “zemūdens akmeņiem” un domāts C pamat zināšanu un koda veidošanas struktūras iemaņu pārbaudei.

 

Uzdevums.

 

Pievienotajā .txt failā atrodas karšu numuru tabula, kurā atrodas sekojoši lauki: 1. Range Start; 2. Range End; 3 Name.

[Range Start] un [Range End] lauki var būt no 1 līdz 16 simbolu (ciparu) gari.

Programmas uzdevums būtu sekojošs:

1. Pieprasīt ievadīt 16 ciparus garu kartes numuru.

    Kartes numura ievadei, pārbaudei un apstrādei jāizmanto char[n] tips (simbolu masīvs), lai pārbaudītu zināšanas par masīviem un norādēm (pointer).

    Ja kartes numurs ievadīts nekorekti, uz ekrāna izvadīt atbilstošu paziņojumu un atgriezties pie kartes numura ievades.

2. Pārbaudīt, vai ieraksts, kas atbilst ievadītajam kartes numuram, atrodams teksta failā (pārbaudīt pēc ievadītā numura pirmajiem n cipariem, kur n=ciparu skaits attiecīgajā kolonā failā file.txt). Piemēram, faila pirmā rinda satur sekojošu informāciju:"400000000000;499999999999;VISA;" Tas nozīmē, ka ievadītais kartes numurs atbilst šai rindai, ja skaitlis, kas atbilst tā pirmajiem 12 cipariem >=400000000000 un <=499999999999. Ja ievadītais numurs neatbilst nevienai rindai failā, 2 sekundes uz ekrāna parādīt brīvi izvēlētu kļūdas paziņojumu un atgriezties uz punktu 1.

3. Pieprasīt ievadīt summu formātā "nnnn.mm", kur nnnn- 1 līdz 4 ciparu gara summa eiro, bet mm - 2 ciparu summa centos.

    Ja summa ievadīta nekorekti, uz ekrāna izvadīt atbilstošu paziņojumu un atgriezties pie summas ievades.

4. Saglabāt failā "trans.txt" ievadīto kartes numuru, numuram atbilstošo "Name" lauku no task.txt un ievadīto summu.

5. Atgriezties uz punktu 1.

 

Ja ir kādas neskaidrības par uzdevuma nostādni, dodiet ziņu un centīšos izskaidrot nesaprotamās lietas.

 

Laika limita uzdevuma izpildei nav, galvenais ir kvalitāte!  

<img src="https://imgur.com/VbgdZ7h" alt="Lamp">  


- [x] is inputed card number valid
- [x] read file.txt
- [x] parse inputed string from file.txt
- [x] found if inputed card number match, if so return name of card string
- [ ] promt user input DEPOSIT
- [ ] check if DEPOSIT input is valid
- [ ] write cards name and DEPOSIT to file
- [ ] while loop for promt and user interface
- [ ] error msg's 

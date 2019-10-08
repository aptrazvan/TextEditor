Student: Apetroaie Razvan-Mihai
Grupa: 313CB

	Anterior functiei "main" se regasesc subprogramele ce realizeaza asupra textului actiunile introduse si subprogramele auxiliare,
in scopul usurarii modului de lucru si organizarii spatiului de lucru.

	Functiile "longestLine", "countLines", "cpyText", "resetText", "moveUp" sunt subprograme ce realizeaza sarcini simple necesare in 
mod repetat in realizarea actiunilor introduse: aflarea lungimii celei mai lungi linii din text, numararea liniilor, copierea continului 
unui text, stergerea acestuia si respectiv mutarea acestuia cu o pozitie mai sus.
	Functia "clearSpace" elimina "trailing whitespace" din text. Acesta numara spatiile pana la intalnirea primului caracter ce nu este 
spatiu/tab si plaseaza capatul liniei pe pozitia determinata.
	Functia "invalidOperation" realizeaza comenzile necesare in cazul introducerii unor actiuni invalide, si anume afisarea textului din 
enunt si inlocuirea textului cu versiunea sa initiala.
	Functia "sort" este utilizata in cazul listelor ordonate si are ca scop ordonare alfabetica/analfabetica a textului in functie de 
argumentul "order" introdus.
	Functia "checkInvalidInput" verifica introducerea unor limite valide in cazul lucrului pe fragmente de text.
	Functia "wrap" realizeaza actiunea corespunzatoare pe un paragraf dictat de functia "wrapCompound". Se numara spatiile primei linii 
in scopul adaugarii acestora la "charCount" si se aliniaza restul textului la stanga folosind "allignLeft" pentru eliminarea spatiilor 
nedorite la inceputul liniilor in cazul in care linia depaseste dimensiunea dorita, se parcurg folosind functia "strtok" cuvintele pana 
la atingerea dimensiunii iar restul cuvintelor sunt adaugate liniei urmatoare prin intermediul sirului "addLine". In linia curenta se 
pastreaza numai cuvintele numarate pana la depasirea limitei. In cazul in care linia are lungimea mai mica decat dimensiunea dorita, se 
adauga acesteia continutul urmatoarei linii.
	Functia "wrapCopmpound" realizeaza actiunea de "wrap" pe mai multe paragrafe. Se utilizeaza functia "wrap" pe fiecare paragraf 
delimitat de variabila "delim" si aparitia unei linii nepopulate iar rezultatul este adaugat intr-o matrice de caractere auxiliara.
	Functia "center" realizeaza actiunea de centrare a textului. Principiul subprogramului este adaosul de spatii la inceputul si 
sfarsitul lniei pana la atingerea dimensiunii dorite.
	Functia "allignLeft" aliniaza textul la stanga prin copierea continutului liniei excluzand spatiile aflate pana la intalnirea 
primului caracter distinct. In mod similar lucreaza si "allignRight", numai ca se copiaza continutul liniei pe pozitii favorabile 
atingerii dimensiunii necesare.
	Functia "allignPar" paragrafeaza textul prin adaos de spatii la nivelul primei linii si al liniilor precedate de "end line".
	Functia "justify" realizeaza actiunea respectiva prin adaugarea unui spatiu in locurile unde exista initial unul prin concatenarea 
sirului "addLine" pana la atingerea dimensiunii liniei maxime .
	Functia "list" are ca rol listarea liniilor indicate in modul introdus. In cazul listei numerice, se salveaza cifrele contorului in 
sirul "addList", cifrele de "0" urmand a fi eliminate. In cazul listei alfabetice, se incrementeaza si se adauga carecterul introdus.

	La inceputul si sfarsitul funtiei "main" se gaseste scheletul oferit la inceputul cerintei. Am eliminat caracterele "\n" pentru 
usurarea modului de lucru, urmand a fi reimplementate la crearea fisierului final. Din motive similare, actiunile si argumentele 
acestora sunt parcurse folosind functia "strtok" si salvate in matricea "cmds".
	In cazul unei operatii invalide, se salveaza textul initial prin intermediul functiei "cpyText". Se apeleaza funtiile 
corespunzatoare fiecarei actiuni tinandu-se cont de argumentele specifice si tratarea cazurilor de existenta a limitatorilor "minLine" 
si maxLine. In cazul introducerii unor argumente invalide, se schimba variabila valid in scopul conditionarii functiei 
"invalidOperation". Operatiile sunt numarate folosindu-se variabila "operationCount". La depasirea valorii "10" se va afisa textul din 
enunt si se va opri realizarea actiunilor ramase.
	In cazul listelor ordonate, se preia tipul de ordonare dupa care functia "sort" va fi apelata, iar parametrul va fi eliminat din 
lista de comanda pentru ca actiunea sa se poata desfasura asemenea unei listari de tip "I", dar cu elemente sortate.
	Pentru a se respecta aspectul necesar fisierului final, se elimina "trailing whitespace" din text si se adauga caracterul "\n" la 
sfarsitul fiecarei linii.
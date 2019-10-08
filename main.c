/*
Student: Apetroaie Razvan-Mihai
Grupa: 313CB
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void allignLeft(char text[1000][1000], int minLine, int maxLine);
void allignPar(char text[1000][1000], int numSpaces, int minLine, int maxLine);

//functie ce returneaza lungimea celei mai lungi linii din text
int longestLine(char text[1000][1000], int maxLines)
{
	int i, max = 0;
	for(i = 0; i < maxLines; i++)
	{
		if(strlen(text[i]) > max)
		{
			max = strlen(text[i]);
		}
	}

	return max;
}


//functie ce returneaza numarul liniilor din text
int countLines(char text[1000][1000])
{
	int count = 0;
	while((strlen(text[count + 1]) >1) || (strlen(text[count + 2]) > 1))
	{
		count++;
	}

	if(text[count][0] == '\0')
	{
		count--;
	}
	return count + 1;
}

//functie ce elimina "trailing whitespace" din text
void clearSpace(char text[1000][1000])
{
	int i, space, maxLines = countLines(text);

	for(i=0; i < maxLines; i++)
	{
		space = strlen(text[i]) - 1;

		//se numara spatiile pana la intalnirea primului caracter ce nu este spatiu/tab
		while(((text[i][space] == ' ') || (text[i][space] == '\t')) && 
			((text[i][space - 1] == ' ') || (text[i][space - 1] == '\t')))
		{
			space--;
		}
		/*in cazul in care a existat un spatiu/tab, se plaseaza capatul
		liniei pe pozitia determinata*/
		if(text[i][space] == ' ' || text[i][space] == '\t')
		{
			text[i][space] = '\0';
		}
	}
}


//functie ce copiaza continutul unei matrici text in alta
void cpyText(char text[1000][1000], char copy[1000][1000])
{
	int i, maxLine = countLines(text);
	for(i = 0; i <= maxLine; i++)
	{
		strcpy(copy[i], text[i]);
	}
}

/*functie utilizata la revenirea in starea initiala a textului
in cazul unei opratii invalide*/
void invalidOperation(char text[1000][1000], char copy[1000][1000])
{
	int i, maxLine = countLines(text);
	
	printf("Invalid operation!\n");
	for(i = 0; i <= maxLine; i++)
	{
		strcpy(text[i], copy[i]);
	}
}

/*functie utilizata la sortarea alfabetica/analfabetica a liniilor
listei, dupa argumentul introdus*/
void sort(char text[1000][1000], int minLine, int maxLine, char order)
{
	int i, j;
	char cpyText[1000];

	if(order == 'a')
	{
		for(i = minLine; i <= maxLine; i++)
		{
			for(j = minLine; j <= maxLine; j++)
			{
				if(strcmp(text[i], text[j]) < 0)
				{
					strcpy(cpyText, text[i]);
					strcpy(text[i], text[j]);
					strcpy(text[j], cpyText);
				}
			}
		}
	}
	else if(order == 'z')
	{
		for(i = minLine; i <= maxLine; i++)
		{
			for(j = minLine; j <= maxLine; j++)
			{
				if(strcmp(text[i], text[j]) > 0)
				{
					strcpy(cpyText, text[i]);
					strcpy(text[i], text[j]);
					strcpy(text[j], cpyText);
				}
			}
		}
	}
}

/*functie ce verifica introducerea valida a valorilor ce determina
intervalul de desfasurare a unei actiuni*/
int checkValidInput(int minLine, int maxLine, int valid)
{
	if(minLine > maxLine || minLine < 0)
	{
		return 0;
	}
	else
	{
		return valid;
	}
}

//functie ce sterge textul prin plasarea capatului pe prima pozitie
void resetText(char text[1000][1000])
{
	int i, maxLine = countLines(text);

	for(i = 0; i < maxLine; i++)
	{
		text[i][0] = '\0';
	}
}

//functie utilizata la deplasarea unui fragment de text cu o pozitie mai sus
void moveUpText(char text[1000][1000], int currentLine)
{
	int i, maxLines = countLines(text);

	for(i = currentLine; i < maxLines - 1; i++)
	{
		strcpy(text[i], text[i + 1]);
	}

	text[maxLines - 1][0] = '\0';
}

/*functie ce realizeaza actiunea de "wrap" pe un paragraf
dictat de functia "wrapCompound"*/
void wrap(char text[1000][1000], int maxLineLength)
{
	int charCount = 0, spaceCount = 0, line = 0, br = 0;
	char *p;
	char addLine[1000], textLine[1000];

	//se numara spatiile primei linii in scopul adaugarii acestora la "charCount"
	while(text[line][spaceCount] == ' ')
	{
		spaceCount++;
	}

	/*se aliniaza restul textului la stanga pentru eliminarea spatiilor nedorite
	la inceputul liniilor*/
	allignLeft(text, 1, countLines(text));
	clearSpace(text);

	while(line >= 0)
	{
		strcpy(textLine, text[line]);	

		if(strlen(text[line]) > maxLineLength)
		{
			p = strtok(text[line], " ");
			charCount = strlen(p);
			if(line == 0)
			charCount += spaceCount;

			/*in cazul in care linia depaseste dimensiunea dorita, se parcurg folosind
			functia "strtok" cuvintele pana la atingerea dimensiunii*/
			while(charCount <= maxLineLength)
			{
				br = charCount;
				p = strtok(NULL, " ");
				charCount += strlen(p) + 1; 
			}

			/*restul cuvintelor sunt adaugate liniei urmatoare
			prin intermediul sirului "addLine"*/
			strcpy(addLine, p);
			strcat(addLine, " ");
			while(p)
			{
				p = strtok(NULL, " ");
				if(p!=NULL)
				{
					strcat(addLine, p);
					strcat(addLine, " ");
				}

			}

			/*se pastreaza in linia curenta numai cuvintele numarate
			pana la depasirea limitei*/
			strncpy(text[line], textLine, br);
			if(text[line + 1][0] != '\0')
			{
				strcat(addLine, text[line + 1]);
			}

			strcpy(text[line + 1], addLine);

		}
		else if(strlen(text[line]) < maxLineLength)
		{
			/*in cazul in care linia are lungimea mai mica decat dimensiunea
			dorita, se adauga acesteia continutul urmatoarei linii*/
			strcat(text[line], " ");
			strcat(text[line], text[line + 1]);
			strcpy(text[line + 1], text[line]);
			moveUpText(text, line);
			line--;
		}
		//actiunea se sfarseste la sfarsitul paragrafului
		else if((strlen(text[line + 2]) < 2) && (strlen(text[line + 3]) < 2))
		{
				line = -2;
		}

		line++;
	}

}

//functie utilizata la realizarea actiunii de "wrap" pe mai multe paragrafe
void wrapCompound(char text[1000][1000], int maxLineLength)
{
	char wrapCpy[1000][1000], wrapText[1000][1000];
	int i, j, l = 0, delim = 0, maxLine = countLines(text);

	for(i = 0; i <= maxLine + 1; i++)
	{
		/*se utilizeaza functia "wrap" pe fiecare paragraf delimitat de
		variabila "delim" si aparitia unei linii nepopulate*/
		if(text[i][0] == '\0')
		{
			resetText(wrapCpy);
			for(j = delim; j < i; j++)
			{
				strcpy(wrapCpy[j - delim], text[j]);
			}
			wrap(wrapCpy, maxLineLength);

			//rezultatul este adaugat intr-o matrice de caractere auxiliara
			for(j = 0; j <= countLines(wrapCpy); j++)
			{
				strcpy(wrapText[l], wrapCpy[j]);
				l++;
			}

			delim = i + 1;

		}
	}

	resetText(text);

	for(i = 0; i < countLines(wrapText); i++)
	{
		strcpy(text[i], wrapText[i]);
	}
}

//functie utilizata la centrarea textului
void center(char text[1000][1000], int minLine, int maxLine)
{
	int maxLineLength = 0, i;
	char spacedLine[1000];
	maxLineLength = longestLine(text, countLines(text));
	for(i = minLine; i <= maxLine; i++)
	{
		/*pana la atingere dimensiunii dorite se adauga
		spatii la inceputul si sfarsitul liniei*/
		while(strlen(text[i]) + 1 <= maxLineLength)
		{
			strcpy(spacedLine, " ");
			strcat(spacedLine, text[i]);
			strcat(spacedLine, " ");
			strcpy(text[i], spacedLine);
		}
	}
}

//functie ce aliniaza textul la stanga
void allignLeft(char text[1000][1000], int minLine, int maxLine)
{
	char allignText[1000];
	int i, j, spaceCount;

	for(i = minLine; i <= maxLine; i++)
	{
		spaceCount = 0;
		for(j = 0; j < strlen(text[i]); j++)
		{
			allignText[j] = ' ';
		}

		allignText[strlen(text[i])] = '\0';
		
		while(text[i][spaceCount] == ' ' || text[i][spaceCount] == '\t')
		{
			spaceCount++;
		}

		/*se copiaza continutul liniei excluzand spatiile aflate pana
		la intalnirea primului caracter distinct*/
		for(j = spaceCount; j < strlen(text[i]); j++)
		{
			allignText[j - spaceCount] = text[i][j];
		}

		strcpy(text[i], allignText);
	}
}

//functie ce aliniaza la dreapta textul introdus
void allignRigth(char text[1000][1000], int minLine, 
	int maxLine, int maxLineLength)
{
	char allignText[1000];
	int i, j, spaceCount;

	for(i = minLine; i <= maxLine; i++)
	{
		spaceCount = maxLineLength - strlen(text[i]);

		for(j = 0; j < spaceCount; j++)
		{
			allignText[j] = ' ';
		}


		/*se copiaza continutul liniei pe pozitiile corespunzatoare
		liniei celei mai lungi*/
		for(j = strlen(text[i]) - 1; j >= 0; j--)
		{
			allignText[j + spaceCount] = text[i][j];
		}


		strcpy(text[i], allignText);
	}
}

//functie ce paragrafeaza textul dupa numarul de spatii introdus
void allignPar(char text[1000][1000], int numSpaces, int minLine, int maxLine)
{
	int i;
	char addSpace[1000], cpySpace[1000];

	if(numSpaces)
	{
		strcpy(addSpace, " ");
		numSpaces--;
	}

	while(numSpaces)
	{
		strcat(addSpace, " ");
		numSpaces--;
	}

	strcpy(cpySpace, addSpace);

	/*in cazul primei linii, instructiunea "for" ce urmeaza ar
	accesa o pozitie invalida*/
	if(minLine == 0)
	{
		strcat(addSpace, text[0]);
		strcpy(text[0], addSpace);
		strcpy(addSpace, cpySpace);
		minLine++;
	}

	for(i = minLine; i <= maxLine; i++)
	{
		//se adauga numarul de spatii dorit primei linii din paragraf
		if(text[i - 1][0] == '\0')
		{
			strcat(addSpace, text[i]);
			strcpy(text[i], addSpace);
			strcpy(addSpace, cpySpace);
		}
	}
}

/*functie ce realizeaza actiunea de "justify" prin
adaugare de spatii in interiorul liniei*/
void justify(char text[1000][1000], int minLine, int maxLine)
{
	int i, j, k, maxLineLength = longestLine(text, countLines(text));
	char addSpace[1000];

	for(i = minLine; i <= maxLine; i++)
	{
		if(text[i][0] != '\0' && text[i + 1][0] != 0)
		{
			while(strlen(text[i]) < maxLineLength)
			{
				for(j = 0; j < strlen(text[i]); j++)
				{
					/*pana la atingerea dimensiunii liniei maxime se adauga un spatiu in locurile
					unde exista initial unul prin concatenarea sirului "addLine"*/
					if(text[i][j] == ' ' && strlen(text[i]) < maxLineLength)
					{
						strncpy(addSpace, text[i], j + 1);
						strcat(addSpace, " ");

						for(k = j; k <= strlen(text[i]); k++)
						{
							addSpace[k + 1] = text[i][k];

						}

						strcpy(text[i], addSpace);
						j += 2;

					}
				}
			}
		}
	}
}

//functie ce listeaza linii dintr-un text in modul introdus
void list(char text[1000][1000], char listType[], 
	char specialChar[], int minLine, int maxLine)
{
	int i, listCount;
	char addList[1000], cpyList[1000];
	listType[1] = '\0';
	specialChar[1] = '\0';

	/*in cazul in care limita introdusa depaseste dimensiunea textului, se
	va realiza operatia pana la sfarsitul textului*/
	if(maxLine > countLines(text) - 1)
	{
		maxLine = countLines(text) - 1;
	}

	//in cazul unei liste "bullet", se adauga caracterul urmat de spatiu folosind sirul "addList"
	if(listType[0] == 'b')
	{
		strcpy(addList, specialChar);
		strcat(addList, " ");
		strcpy(cpyList, addList);
		for(i = minLine; i <= maxLine; i++)
		{
			strcpy(addList, cpyList);
			strcat(addList, text[i]);
			strcpy(text[i], addList);
		}
	}
	else
	{
		if(listType[0] == 'n')
		{
			listCount = 0;

			for(i = minLine; i <= maxLine; i++)
			{
				/*in cazul listei numerice, se salveaza cifrele
				contorului in sirul "addList"*/
				listCount++;
				addList[3] = '\0';
				addList[0] = listCount / 100 + '0';
				addList[1] = listCount / 10 % 10 + '0';
				addList[2] = listCount % 10 + '0';

				if(addList[0] == '0')
				{
					addList[0] = ' ';
				}

				if(addList[1] == '0')
				{
					addList[1] = ' ';
				}

				/*cifrele "0" sunt inlocuite de spatii, urmand a fi eliminate
				folosind functie "allignLeft"*/
				strcpy(addList, addList);
				strcat(addList, specialChar);
				strcat(addList, " ");
				strcat(addList, text[i]);
				strcpy(text[i], addList);
			}

			allignLeft(text, minLine, maxLine);
		}
		else if(listType[0] == 'a' || listType[0] == 'A')
		{
			/*in cazul listei alfabetice, caracterul, urmat de spatiu, este
			incrementat si adaugat folsind sirul "addList"*/
			for(i = minLine; i <= maxLine; i++)
			{
				strcpy(addList, listType);
				strcat(addList, specialChar);
				strcat(addList, " ");
				strcat(addList, text[i]);
				strcpy(text[i], addList);
				listType[0]++;
			}
		}
	}
}

int main(int argc, char *argv[]) {
  char buf[1000],               // buffer used for reading from the file
      original[1000][1000],     // original text, line by line
      result[1000][1000];       // text obtained after applying operations
  int original_line_count = 0,  // number of lines in the input file
      result_line_count = 0,    // number of lines in the output file
      i;

  if (argc != 4) {  // invalid number of arguments
    fprintf(stderr,
            "Usage: %s operations_string input_file output_file\n",
            argv[0]);
    return -1;
  }

  // Open input file for reading
  FILE *input_file = fopen(argv[2], "r");

  if (input_file == NULL) {
    fprintf(stderr, "File \"%s\" not found\n", argv[2]);
    return -2;
  }

  // Read data in file line by line
  while (fgets(buf, 1000, input_file)) {
    strcpy(original[original_line_count], buf);
    original_line_count++;
  }

  fclose(input_file);

  /*
   * TODO apply operations in operation_string (argv[1]) one by one and save
   * the result in the 'result' matrix.
   *
   * Replace this comment and the next piece of code with your solution.
   */

	char *p, maxLineLength[4], minLine[4], maxLine[4], numSpaces[4],
	 cpyOriginal[1000][1000], cmds[50][50];
	char order, listType[4], specialChar[4];
	int l = 0, k = 0, lineLength, addEndLine = 0, valid = 1, operationCount = 0;
	p = strtok(argv[1], " ");

	/*pe parcursul realizarii actiunilor caracterele "\n" sunt
	eliminate pentru usurarea modului de lucru, urmand
	a fi reimplementate la crearea fisierului final*/

	if(original[original_line_count - 1][0] == '\n')
	{
		/*in cazul in care ultima linie cuprinde numai caracterul "\n", acesta
		ar fi eliminat la apelul functiei "countLines", fiind astfel
		necesara reimplementarea acestuia la fisierul final*/
		addEndLine = 1;
	}

	for(i = 0; i < original_line_count; i++)
	{
		original[i][strlen(original[i]) - 1] = '\0';
	}

	original_line_count = countLines(original);

	/*actiunile si argumentele acestora sunt parcurse folosind
	functia "strtok" si salvate in matricea "cmds" pentru usurarea
	modului de lucru si o mai mare libertate asupra operatiilor*/
	while(p)
	{
		strcpy(cmds[l], p);
		l++;
		p = strtok(NULL, " ");
	}

	//in cazul unei operatii invalide, se salveaza textul initial
	cpyText(original, cpyOriginal);

	/*pentru a respecta sintaxa instruciunii "while" urmatoare, se adauga
	caracterul "," la sfarsitul ultimei operatii*/
	strcat(cmds[l - 1], ",");
	while(k < l)
	{

		/*
		Se apeleaza funtiile corespunzatoare fiecarei actiuni
		tinandu-se cont de argumentele specifice si tratarea cazurilor
		de existenta a limitatorilor "minLine" si maxLine.
		In cazul introducerii unor argumente invalide, se schimba variabila
		valid in scopul conditionarii functiei "invalidOperation".
		*/
		if(cmds[k][0] == 'w' || cmds[k][0] == 'W')
		{
			operationCount++;
			k++;

			clearSpace(original);

			if(cmds[k][strlen(cmds[k]) - 1] == ',')
			{
				strncpy(maxLineLength, cmds[k], strlen(cmds[k]) - 1);
				wrapCompound(original, atoi(maxLineLength));
			}
			else
			{
				valid = 0;
			} 
			original_line_count = countLines(original);

		}


		else if(cmds[k][0] == 'c' || cmds[k][0] == 'C')
		{
			operationCount++;
			clearSpace(original);
			if(cmds[k][strlen(cmds[k]) - 1] == ',')
			{
				center(original, 0, original_line_count);
			}
			else
			{
				k++;
				if(cmds[k][strlen(cmds[k]) - 1] == ',')
				{
					strncpy(minLine, cmds[k], strlen(cmds[k]) - 1);
					center(original, atoi(minLine), original_line_count);
					valid = checkValidInput(atoi(minLine), original_line_count, valid);
				}
				else if(cmds[k + 1][strlen(cmds[k + 1]) - 1] == ',')
				{
					strcpy(minLine, cmds[k]);
					k++;
					strncpy(maxLine, cmds[k], strlen(cmds[k]) - 1);
					center(original, atoi(minLine), atoi(maxLine));
					valid = checkValidInput(atoi(minLine), atoi(maxLine), valid);
				}
				else
				{
					valid = 0;
				}
			}
		}

		else if(cmds[k][0] == 'l' || cmds[k][0] == 'L')
		{
			operationCount++;
			if(cmds[k][strlen(cmds[k]) - 1] == ',')
			{
				allignLeft(original, 0, original_line_count);
			}
			else
			{
				k++;
				if(cmds[k][strlen(cmds[k]) - 1] == ',')
				{
					strncpy(minLine, cmds[k], strlen(cmds[k]) - 1);
					allignLeft(original, atoi(minLine), original_line_count);
					valid = checkValidInput(atoi(minLine), original_line_count, valid);
				}
				else if(cmds[k + 1][strlen(cmds[k + 1]) - 1] == ',')
				{
					strcpy(minLine, cmds[k]);
					k++;
					strncpy(maxLine, cmds[k], strlen(cmds[k]) - 1);
					allignLeft(original, atoi(minLine), atoi(maxLine));
					valid = checkValidInput(atoi(minLine), atoi(maxLine), valid);
				}
				else
				{
					valid = 0;
				}
			}

		}

		else if(cmds[k][0] == 'r' || cmds[k][0] == 'R')
		{
			operationCount++;
			clearSpace(original);
			lineLength = longestLine(original, countLines(original));
			if(cmds[k][strlen(cmds[k]) - 1] == ',')
			{
				allignLeft(original, 0, original_line_count - 1);
				clearSpace(original);
				allignRigth(original, 0, original_line_count - 1, lineLength);
			}
			else
			{
				k++;
				if(cmds[k][strlen(cmds[k]) - 1] == ',')
				{
					strncpy(minLine, cmds[k], strlen(cmds[k]) - 1);

					allignLeft(original, atoi(minLine), original_line_count - 1);
					clearSpace(original);
					allignRigth(original, atoi(minLine), original_line_count - 1, lineLength);

					valid = checkValidInput(atoi(minLine), original_line_count - 1, valid);
				}
				else if(cmds[k + 1][strlen(cmds[k + 1]) - 1] == ',')
				{
					strcpy(minLine, cmds[k]);
					k++;
					strncpy(maxLine, cmds[k], strlen(cmds[k]) - 1);

					allignLeft(original, atoi(minLine), atoi(maxLine));
					clearSpace(original);
					allignRigth(original, atoi(minLine), atoi(maxLine), lineLength);

					valid = checkValidInput(atoi(minLine), atoi(maxLine), valid);
				}
				else
				{
					valid = 0;
				}
			}
		}

		else if(cmds[k][0] == 'p' || cmds[k][0] == 'P')
		{
			operationCount++;
			k++;
			if(cmds[k][strlen(cmds[k]) - 1] == ',')
			{
				strncpy(numSpaces,cmds[k],strlen(cmds[k]) - 1);
				allignPar(original, atoi(numSpaces), 0, original_line_count);
			}
			else
			{
				strcpy(numSpaces,cmds[k]);
				k++;
				if(cmds[k][strlen(cmds[k]) - 1] == ',')
				{
					strncpy(minLine, cmds[k], strlen(cmds[k]) - 1);
					allignPar(original, atoi(numSpaces), atoi(minLine), original_line_count);

					valid = checkValidInput(atoi(minLine), original_line_count, valid);
				}
				else if(cmds[k + 1][strlen(cmds[k + 1]) - 1] == ',')
				{
					strcpy(minLine, cmds[k]);
					k++;
					strncpy(maxLine, cmds[k], strlen(cmds[k]) - 1);
					allignPar(original, atoi(numSpaces), atoi(minLine), atoi(maxLine));

					valid = checkValidInput(atoi(minLine), atoi(maxLine), valid);
				}
				else
				{
					valid = 0;
				}
			}

		}

		else if(cmds[k][0] == 'j' || cmds[k][0] == 'J')
		{
			operationCount++;
			if(cmds[k][strlen(cmds[k]) - 1] == ',')
			{
				allignLeft(original, 0, original_line_count);
				clearSpace(original);
				justify(original, 0, original_line_count);
			}
			else
			{
				k++;
				if(cmds[k][strlen(cmds[k]) - 1] == ',')
				{
					strncpy(minLine, cmds[k], strlen(cmds[k]) - 1);
					allignLeft(original, atoi(minLine), original_line_count);
					clearSpace(original);
					justify(original, atoi(minLine), original_line_count);

					valid = checkValidInput(atoi(minLine), original_line_count, valid);
				}
				else if(cmds[k + 1][strlen(cmds[k + 1]) - 1] == ',')
				{
					strcpy(minLine, cmds[k]);
					k++;
					strncpy(maxLine, cmds[k], strlen(cmds[k]) - 1);
					allignLeft(original, atoi(minLine), atoi(maxLine));
					clearSpace(original);
					justify(original, atoi(minLine), atoi(maxLine));

					valid = checkValidInput(atoi(minLine), atoi(maxLine), valid);
				}
				else
				{
					valid = 0;
				}
			}

		}

		else if(cmds[k][0] == 'i' || cmds[k][0] == 'I' || 
			cmds[k][0] == 'o' || cmds[k][0] == 'O')
		{
			operationCount++;
			original_line_count = countLines(original);

			if(cmds[k][0] == 'o'|| cmds[k][0] == 'O')
			{
				order = cmds[k + 3][0];

				/*in cazul listelor ordonate, se preia tipul de ordonare
				dupa care functia "sort" va fi apelata*/
				if(cmds[k + 3][1] == ',') 
				{
					strcat(cmds[k + 2], ",");
				}

				l--;

				/*parametrul va fi eliminat din lista de comanda pentru ca actiunea
				sa se poata desfasura asemenea unei listari de
				tip "I", dar cu elemente sortate*/
				for(i = k + 3; i < l; i++)
				{
					strcpy(cmds[i], cmds[i + 1]);
				}

				cmds[l][0] = '\0';
			}


			k++;
			strcpy(listType, cmds[k]);
			if(listType[0] != 'b' && listType[0] != 'n' && 
				listType[0] != 'a' && listType[0] != 'A')
			{
				valid = 0;
			}
			if(listType[1] == ',')
			{
				valid = 0;
			}
			k++;
			if(cmds[k][strlen(cmds[k]) - 1] == ',')
			{
				strncpy(specialChar, cmds[k], strlen(cmds[k]) - 1);

				if(cmds[k - 2][0] == 'o'|| cmds[k - 2][0] == 'O')
				{
					sort(original, 0, original_line_count - 1, order);
				}

				allignLeft(original, 0, original_line_count - 1);
				clearSpace(original);
				list(original, listType, specialChar, 0, original_line_count - 1);
			}
			else
			{
				strcpy(specialChar, cmds[k]);
				k++;
				if(cmds[k][strlen(cmds[k]) - 1] == ',')
				{
					strncpy(minLine, cmds[k], strlen(cmds[k]) - 1);

					if(cmds[k - 3][0] == 'o'|| cmds[k - 3][0] == 'O')
					{
						sort(original, atoi(minLine), original_line_count - 1, order);
					}

					allignLeft(original, atoi(minLine), original_line_count - 1);
					clearSpace(original);
					list(original, listType, specialChar, atoi(minLine), 
						original_line_count - 1);

					valid = checkValidInput(atoi(minLine), original_line_count - 1, valid);
				}
				else if(cmds[k + 1][strlen(cmds[k + 1]) - 1] == ',')
				{
					strcpy(minLine, cmds[k]);
					k++;
					strncpy(maxLine, cmds[k], strlen(cmds[k]) - 1);

					if(cmds[k - 4][0] == 'o'|| cmds[k - 4][0] == 'O')
					{
						sort(original, atoi(minLine), atoi(maxLine), order);
					}

					allignLeft(original, atoi(minLine), atoi(maxLine));
					clearSpace(original);
					list(original, listType, specialChar, atoi(minLine), atoi(maxLine));

					valid = checkValidInput(atoi(minLine), atoi(maxLine), valid);
				}
				else
				{
					valid = 0;
				}
			}
		}
		else
		{
			/*in cazul in care actiunea nu respecta niciuna din
			formele anterioare, aceasta este invalida*/
			valid = 0;
			operationCount++;
		}		
		if(valid == 0)
		{
			k = l;
		}
		k++;


		if(operationCount == 10 && k < l)
		{
			printf("Too many operations! Only the first 10 will be applied.\n");
			/*in cazul depasirii limitei de actiuni, instructiunea
			"while" curenta se opreste prin nerespectarea conditiei*/
			k = l;
		}
	}

	//se elimina "trailing whiteSpace" din rezultatul final
	clearSpace(original);

	if(valid == 0)
	{
		invalidOperation(original, cpyOriginal);
	}
	original_line_count = countLines(original);

	if(addEndLine == 1)
	{
		//se readuce caracterul "\n" pierdut in urma apelarii functiei "counLines"
		strcat(original[original_line_count - 1], "\n");
	}

  for (i = 0; i < original_line_count; i++) {
    strcpy(result[i], original[i]);
  }
  result_line_count = original_line_count;

  // Open output file for writing
  FILE *output_file = fopen(argv[3], "w");

  if (output_file == NULL) {
    fprintf(stderr, "Could not open or create file \"%s\"\n", argv[3]);
    return -2;
  }

  // Write result in output file

  for (i = 0; i < (result_line_count); i++) {
  	strcat(result[i], "\n");
    fputs(result[i], output_file);
  }

  //fputs(result[result_line_count - 1], output_file);
  fclose(output_file);
  return 0;
}

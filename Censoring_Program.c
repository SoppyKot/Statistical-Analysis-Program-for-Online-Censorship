#include<stdio.h>
#include<stdlib.h>
void main(int argc, char *argv[])
{
	FILE *f1;
	f1 = fopen(argv[1], "r");
	if(f1 == NULL)
	{
		printf("Content file error.\n");
		exit(0);
	}
	
	char delim; // for holding delimiter
	char temp; // for holding temporary character from fgetc
	int i; // loop variable
	char title[100]; // stores the title
	char viewsstr[100]; // stores number of views as string
	float views; // stores number of views as long integer after parsing from likesstr
	char reportsstr[100]; // stores number of reports as string
	float reports; // stores number of reports as long integer after parsing from reportsstr
	
	while((delim = fgetc(f1)) != EOF) // Title
	{
		if(delim == '"')
		{
			for(i = 0; (temp = fgetc(f1)) != '"'; i++)
			{
				title[i] = temp;
			}
			title[i + 1] = '\0';
			break;
		}
	}
	
	while((delim = fgetc(f1)) != EOF) // Views
	{
		if(delim == '-')
		{
			for(i = 0; (temp = fgetc(f1)) != ';'; i++)
			{
				viewsstr[i] = temp;
			}
			viewsstr[i + 1] = '\0';
			break;
		}
	}
	views = (float) atoi(viewsstr);
	
	while((delim = fgetc(f1)) != EOF) // Reports
	{
		if(delim == '-')
		{
			for(i = 0; (temp = fgetc(f1)) != ';'; i++)
			{
				reportsstr[i] = temp;
			}
			reportsstr[i + 1] = '\0';
			break;
		}
	}
	reports = (float) atoi(reportsstr);
	
	// By this point, all details of the content have been stored.
	
	fclose(f1);
	FILE *f2;
	f2 = fopen(argv[2], "r");
	if(f2 == NULL)
	{
		printf("Reporters file error.");
		exit(0);
	}
	long int c1 = 0, c2 = 0, c3 = 0; // H, S, Z Religions
	long int r1 = 0, r2 = 0, r3 = 0; // Nallakunta, Kompally, Bachupally
	long int a1 = 0, a2 = 0, a3 = 0; // Teenage, Adulthood, Seniority
	char temp2[100];
	
	int lines = 0;
	for(i = 0;(temp =  fgetc(f2)) != EOF; i++)
	{
		if(temp == '\n')
			lines++;
	}
	lines = lines + 1;
	fseek(f2, 0, SEEK_SET);
	
	int j;
	for(j = 1; j <= lines; j++)
	{
		while((delim = fgetc(f2)))
		{
			if(delim == '-')
			{
				for(i = 0; (temp = fgetc(f2)) != ';'; i++)
					temp2[i] = temp;
				temp2[i + 1] = '\0';
				if(temp2[0] == 'H')
					c1++;
				else if(temp2[0] == 'S')
					c2++;
				else if(temp2[0] == 'Z')
					c3++;
				break;
			}
			//puts(temp2);
		}
		for(i = 0; i < 100; i++)
			temp2[i] = '\0';
		while((delim = fgetc(f2)))
		{
			if(delim == '-')
			{
				for(i = 0; (temp = fgetc(f2)) != ';'; i++)
					temp2[i] = temp;
				temp2[i + 1] = '\0';
				if(atoi(temp2) <= 19)
					a1++;
				else if((atoi(temp2) >= 20) && (atoi(temp2) < 58))
					a2++;
				else if(atoi(temp2) >= 58)
					a3++;
				break;
			}
		}
		for(i = 0; i < 100; i++)
			temp2[i] = '\0';
		while((delim = fgetc(f2)))
		{
			if(delim == '-')
			{
				for(i = 0; (temp = fgetc(f2)) != ';'; i++)
					temp2[i] = temp;
				temp2[i + 1] = '\0';
				if(temp2[0] == 'N')
					r1++;
				else if(temp2[0] == 'K')
					r2++;
				else if(temp2[0] == 'B')
					r3++;
				break;
			}
		}
		for(i = 0; i < 100; i++)
			temp2[i] = '\0';
	}
	printf("Debug info: c1=%ld c2=%ld c3=%ld a1=%ld a2=%ld a3=%ld r1=%ld r2=%ld r3=%ld views=%f reports=%f\n", c1, c2, c3, a1, a2, a3, r1, r2, r3, views, reports);
//////////////////////////////////////////////////////////////////////////////////
// this part of the program deals with the censoring after collecting the inputs//
//////////////////////////////////////////////////////////////////////////////////
	float count;
	if((reports/views) >= 0.25)
	{
		printf("Content to be sent for futher analysis.\n");
        if(c1 >= c2)
			count = c1;
        else
			count = c2;
        if(c3 >= count)
			count = c3;
        else
			count = c2;
        if((count/reports) >= 0.5)
		{
			if(count == c1)
				printf("This content is offensive to Hindus and is therefore confirmed to be SPAM.\n");
			else if(count == c2)
				printf("This content is offensive to Sikhs and is therefore confirmed to be SPAM.\n");
			else if(count == c3)
				printf("This content is offensive to Zoroastrians and is therefore confirmed to be SPAM.\n");
		}
        else
			printf("The content is not related to any kind of religious discrimination.\n");
	  
        if(r1 >= r2)
			count = r1;
        else
			count = r2;
        if(r3 >= count)
			count = r3;
        else
			count = r2;
        if((count/reports) >= 0.5)
		{
			if(count == r1)
				printf("This content is offensive to residents of Nallakunta and is therefore confirmed to be SPAM.\n");
			else if(count == r2)
				printf("This content is offensive to residents of Kompally and is therefore confirmed to be SPAM.\n");
			else if(count == r3)
				printf("This content is offensive to residents of Bachupally and is therefore confirmed to be SPAM.\n");
		}
        else
			printf("The content is not related to any kind of regional discrimination.\n");

        if(a1 >= a2)
			count = a1;
        else
			count = a2;
        if(a3 >= count)
			count = a3;
        else
			count = a2;
        if((count/reports) >= 0.5)
		{
			if(count == a1)
				printf("This content is offensive to teens and is therefore confirmed to be SPAM.\n");
			else if(count == a2)
				printf("This content is offensive to adults between the ages of 20 and 58 and is therefore confirmed to be SPAM.\n");
			else if(count == a3)
				printf("This content is offensive to senior citizens and is therefore confirmed to be SPAM.\n");
		}
        else
			printf("The content is not related to any kind of age-group discrimination.\n");
	}
	else
		printf("\nContent is not inappropriate.\n");
	printf("Thank you for using this program.\n");
}
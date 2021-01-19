#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int id;
    char name[10];
    int price;
    int qty;
} Product;

typedef struct
{
    int pid;
    char pname[10];
    int pprice;
} Bill;



int getID(); 
int billFileNo();

void manageProduct();
void purchaseProduct();
void generateBill();
void addProduct();
void displayPro();
Product findProduct(int id);
void updateProduct(int id,int qty);

char fproduct[]={"product.dat"};
char fbill[]={"bill.dat"};
int total=0;

int main()
{
    FILE *fp;
    int ch;



    while(1)
    {

        system("cls");

        printf("____________________________________________________\n\n");

        printf("\t\t Weclome To Your Shop Management Program \n\n");

        printf("____________________________________________________\n\n");

        printf("1. Manage Products.\n\n");
        printf("2. Buy Product\n\n");

        printf("3. Create bill\n\n");

        printf("0. Exit.\n\n");

        printf("___________________________________________________\n\n");

        printf("Please enter your choice:");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1: manageProduct();
                    break;

            case 2: purchaseProduct();
                    break;

            case 3: generateBill();
                    break;

            case 0: exit(0);
        }
        getch();

    }

    return (0);
}

int getID() 
{
    FILE *fp;
    int value=0;
    fp=fopen("prodid.txt","r");

    if (fp==NULL)
    {
        fp=fopen("prodid.txt","w");
        fprintf(fp,"%d",0);
        fclose(fp);
        fp=fopen("prodid.txt","r");
    }

    fscanf(fp,"%d", &value);

    fclose(fp);

    fp=fopen("prodid.txt","w");

    fprintf(fp,"%d", value+1);

    fclose(fp);

    return value+1;
}

void manageProduct()
{
    int ch;
    int back=0;
    while(1)
    {

        system("cls");

        printf("______________________________________\n\n");

        printf("\t\t Add or Display Product Here.\n\n");

        printf("______________________________________\n\n");

        printf("1. Add New Product.\n\n");
        printf("2. Display All Products.\n\n");

        printf("0. Exit.\n\n");

        printf("______________________________________\n\n");

        printf("Please Enter Your Choice Here:");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1: addProduct();
                    break;

            case 2: displayPro();
                    break;

            case 0: back=1;
                    break;
        }

        if(back==1)
        {
            break;
        }
        else
        {
            getch();
        }
    }
}

void addProduct()
{
    FILE *fp;
    Product t1;

    fp=fopen(fproduct,"ab");

    t1.id=getID();

    printf("\nEnter Product Name:");
    scanf("%s",t1.name);
    printf("\nEnter Product Price:");
    scanf("%d",&t1.price);
    printf("\nEnter Quantity:");
    scanf("%d",&t1.qty);

    fwrite(&t1,sizeof(t1),1,fp);

    fclose(fp);
}

void displayPro()
{
    FILE *fp;
    Product t;
    int id,found=0;

    system("cls");

    fp=fopen(fproduct,"rb");

    printf("______________________________________\n\n");
    printf("\t\t Product Details \n\n");
    printf("______________________________________\n\n");

    printf("ID\tName\tQuantity\tPrice\n\n");


    while(1)
    {
    	fread (&t,sizeof(t),1,fp);

    	if (feof(fp))
    	{
    		break;
		}

		printf("%d\t",t.id);
		printf("%s\t",t.name);
		printf("%d\t",t.qty);
		printf("%d\t\t\n",t.price);
	}
	printf("______________________________________\n\n");
	fclose(fp);
}
void purchaseProduct() 
{
	char ch1,ch2;
	int id;
	system("cls");
	printf("______________________________________\n\n");

	printf("\t\t Welcome Product Management Tab.\n\n");

	printf("______________________________________\n\n");

	while(1)
	{
		displayPro();
		fflush(stdin);

		printf("\n\n\nDo you want to purchase[Y/N]:");
		scanf("%c",&ch1);

		if(ch1=='Y')
		{
			FILE *fp;
			Bill t1;
			Product t2;

			fp=fopen(fbill,"ab");

			printf("\n\nEnter The Product ID To Purchase:");
			scanf("%d",&id);

			t2=findProduct(id);

			t1.pid=t2.id;
			strcpy(t1.pname,t2.name);
			t1.pprice=t2.price;

			fwrite(&t1,sizeof(t1),1,fp);

			fclose(fp);
		}
		fflush(stdin);
		printf("\n\n\nDo you want to continue [Y/N]:");
		scanf("%c",&ch2);


		if(ch2=='N')
		{
			break;
		}
		getch();
	}
}

 Product findProduct(int id)
{
	FILE *fp;
    Product t;

	fp=fopen(fproduct,"rb");

	while(1)
	{
		fread(&t,sizeof(t),1,fp);

		if(feof(fp))
		{
			break;
		}

		if(t.id==id)
		{
			updateProduct(id,t.qty-1);
			break;
		}
	}
	fclose(fp);
	return t;
}

void updateProduct(int id,int qty)
{
	FILE *fp,*fp1;
	Product t,t1;
	int found=0;

	fp=fopen(fproduct,"rb");
	fp1=fopen("temp.dat","wb");

	while(1)
	{
		fread(&t,sizeof(t),1,fp);

		if(feof(fp))
		{
			break;
		}
		if(t.id==id)
		{
			found=1;
			t.qty=qty;
			fwrite(&t,sizeof(t),1,fp1);
		}
		else
		{
			fwrite(&t,sizeof(t),1,fp1);
		}
	}
	fclose(fp);
	fclose(fp1);

	if(found==0)
	{
		printf("Sorry No Product Matches!");
	}
	else
	{
		fp=fopen(fproduct,"wb");
		fp1=fopen("temp.dat","rb");

		while(1)
		{
			fread(&t,sizeof(t),1,fp1);

			if(feof(fp1))
			{
				break;
			}
			fwrite(&t,sizeof(t),1,fp);
		}

	}
	fclose(fp);
	fclose(fp1);
}

void generateBill()
{
	FILE *fp,*fp1;
	Bill t;
	int id,found=0;
	char ch1;
	int brel=0;
	char billname[30];

	system("cls");

	fp=fopen(fbill,"rb");

	printf("______________________________________\n\n");
	printf("Bill Details \n\n");
	printf("______________________________________\n\n");

	printf("Pro-ID\tPro-Name\tPro-Price\n\n");

	while(1)
	{
		fread(&t,sizeof(t),1,fp);

		if(feof(fp))
		{
			break;
		}

		printf("%d\t",t.pid);
		printf("%s\t",t.pname);
		printf("\t\t%d\n",t.pprice);
		total=total+t.pprice;
	}

	printf("\n\n=======>>>Total Bill [Tk.: %d]\n\n",total);

	fclose(fp);

	if(total!=0)
	{
		fflush(stdin);
		printf("\n\n\n Do you want to see the final bill now [Y/N]:");
		scanf("%c",&ch1);

		if(ch1=='Y'||ch1=='y')
		{
			brel=billFileNo();
			sprintf(billname,"%s%d","",brel);
			strcat(billname,".dat");

			fp=fopen(fbill,"rb");
			fp1=fopen(billname,"wb");

			while(1)
			{
				fread(&t,sizeof(1),1,fp);

				if(feof(fp))
				{
					break;
				}
				fwrite(&t,sizeof(t),1,fp1);
			}
			fclose(fp);
			fclose(fp1);

			fp=fopen(fbill,"wb");
			fclose(fp);
			total=0;
		}
	}
	else
	{
		printf("\n\n Sorry no item selected\n\n");
	}
}

int billFileNo()
{
	FILE *fp;
	int value=0;
	fp=fopen("billno.txt","r");

	if(fp==NULL)
	{
		fp=fopen("billno.txt","w");
		fprintf(fp,"%d",0);
		fclose(fp);
		fp=fopen("billno.txt","r");
	}

	fscanf(fp,"%d",&value);

	fclose(fp);

	fp=fopen("billno.txt","w");
	fprintf(fp,"%d",value+1);
	fclose(fp);

	return value+1;

}


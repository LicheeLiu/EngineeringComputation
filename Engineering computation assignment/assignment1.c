#include <stdio.h>
#include<math.h>

int 	print_distance(float long2, float la2);
int 	stage1(int day[7]);
int 	print_one_line(char *c, int day[7]);
int		print_dash(int dist1);
int		stage2(int day[7]);
int		first_part_stage2(char *c, int day[7]);
int   	count_day(char *c, int day[7]);
int 	find_biggest(int day[7]);
int		stage3(int day[7]);

int 	main()
{	
	int 	day[7] = {0};
	stage1(day);
	return (1);
}

//carry out the stage1 task
int		stage1(int day[7])
{
	char 	c[100];
    int 	i = 0;
    float	flag;
    float 	lat2 = 0,long2 = 0;
    do
    {
    	c[i]=getchar();
        i++;
    }while (c[i] != '\n'); //read in the first line of inputs
    
    printf("Stage 1\n");
    printf("==========\n");
    printf("Accident: #");
   
    for(i = 0; i < 7; i++)
    {
    	printf("%c", c[i]);
    }
    printf("\n");
    printf("Location: <");
    
    //turn longitute into float number
    flag = 100;
    for(i = 8; i < 11; i++ )
    {
    	printf("%c", c[i]);
    	long2 += flag * (c[i] - '0');
    	flag = flag / 10;
    }
    printf(".");
    for(i = 12; i < 18; i++)
    {
    	    printf("%c", c[i]);
    	    long2 += flag * (c[i] - '0');
    	    flag = flag / 10;
    }
    printf(", -");

    //turn altitude into float number
    flag = 10;
    for(i = 20; i < 22; i++)
    {
    	    printf("%c", c[i]);
    	    lat2 += flag * (c[i] - '0');
    	    flag = flag / 10;
    }
    printf(".");
    
    for(i = 23; i < 29; i++)
    {
    	    printf("%c", c[i]);
    	    lat2 += flag *(c[i] - '0');
    	    flag = flag / 10;
    }
    lat2 = (-1) * lat2;
    printf(">\n");
    
    i++;
    printf("Date: ");
    while( c[i] - ' ' != 0)
    {
    	printf("%c", c[i]);
    	i++;
    }
    printf("\n");
    i++;
   
    printf("Time: ");
    while(c[i]-' ' != 0)
    {
    	printf("%c", c[i]);
    	i++;
    }
    i++;
    printf("\n");
   
    printf("Distance to reference: ");
    print_distance(long2, lat2);
    printf("\n");
    first_part_stage2(c,day);
    return (1);
}

//handle the first line of stage 2, since it has already been read in, unlike lines afterward
int		first_part_stage2(char *c, int day[7])
{
 	printf("\nStage 2\n==========\n");
	print_one_line(c, day);
	stage2(day);
	return (1);
}

int		stage2(int day[7])
{
	char	c[1000];
	int		i = 0;
	
	do
	{
		do
		{
			c[i] = getchar();
			i++;
		}while(c[i] != '\n');
		print_one_line(c, day);
	}while(c[i] != EOF);
		
	stage3(day);
	return (1);
}

//print out each line for stage2
int 	print_one_line(char *c, int day[7])
{
	int		i = 0, dist1;
	float 	long2 =0, lat2 = 0; //the location of the accident 
	float	flag = 100;
	
	printf("Accident: #");
	while(i < 7)
	{
		printf("%c", c[i]);
		i++;
	}
	
	printf(", distance to reference: ");
	
	//turn longtitude into float number
	for(i = 8; i < 11; i++)
	{
		long2 += (c[i] - '0') * flag;
		flag = flag / 10;
	}
	for(i = 12; i < 18; i++)
	{
		long2 +=  (c[i] - '0') * flag;
		flag = flag / 10;
	}
	//turn latitude into float number
	flag = 10;
	for(i = 20; i < 22; i++)
	{
		lat2 += (c[i] - '0') * flag;
		flag = flag / 10;
	}
	for(i = 23; i < 29; i++)
	{
		lat2 += (c[i] - '0') * flag;
		flag = flag / 10;
	}
	lat2 = -1 * lat2;
	count_day(c, day);
	dist1 = print_distance(long2, lat2);
	print_dash(dist1);
	return (1);
 }
 
 int	stage3(int day[7])
 {
 	 int 	big_day = 0;
 	 int	count_acc = 0;
 	 int	i = 0;
 
 	 big_day = find_biggest(day);
 	 
 	 for(i = 0; i< 7; i++)
 	 {
 	 	 count_acc += day[i];
 	 }
 	 printf("\nStage 3\n==========\nNumber of accidents: %d", count_acc);
 	 printf("\nDay of week with the most accidents: ");
	 if(big_day == 0)
	 	 printf("Monday");
	 else if(big_day == 1)
	 	 printf("Tuesday");
	 else if(big_day == 2)
	 	 printf("Wednesday");
	 else if(big_day == 3)
	 	 printf("Thursday");
	 else if(big_day == 4)
	 	 printf("Friday");
	 else if(big_day == 5)
	 	 printf("Saturday");
	 else 
	 	 printf("Sunday");
	 printf(" (%d accident(s))\n", day[big_day]);
	 return(1);
}

//store the number of times of accident in each weekday into an array
int   	count_day(char *c, int day[7])
{
	int		i = 0;
	
	while(c[i]<'A' || c[i]>'Z')
	{
		i++;
	}
	if(c[i] == 'M')
		day[0]++;	   	   
   	else if(c[i] == 'T' && c[i + 1] == 'u')
   	  	day[1]++;
   	else if(c[i] == 'W')
   		day[2]++;
   	else if(c[i] == 'T' && c[i + 1] == 'h')
   		day[3]++;
   	else if(c[i] == 'F')
   		day[4]++;
  	else if(c[i] == 'S' && c[i + 1] == 'a')
  		day[5]++;
  	else if(c[i] == 'S' && c[i + 1] == 'u')
  		day[6]++;
  	return (1);
 }

 //compare the array that stored the number of times and find the biggest
 int find_biggest(int	day[7])
 {
	int	i = 0, big_num= 0, big_day = 0;
	
	for(i = 0; i < 7; i++)
	{
		if(day[i] > big_day)
		{
			big_day = day[i];
			big_num = i;
		}
	}
	return big_num;
 }

 //print out the distance to the reference point
int	print_distance(float long2, float lat2)
{
	float 	lat1 = -37.810592,long1 =144.963123;
	float 	chord_length = 0, angle_distance = 0, dist = 0;	
	int		temp, dist1;
	float 	temp1, temp2, temp3;
	
	//calculate the distance
	temp1 = ((lat2 - lat1)/2)*(3.14159/180);
	temp2 = ((long2 - long1)/2)*(3.14159/180);
	chord_length= (sin(temp1))*(sin(temp1)) + cos(lat1*3.14159/180)*cos(lat2*3.14159/180)*(sin(temp2))*(sin(temp2));
	angle_distance = 2 * atan2(sqrt(chord_length), sqrt(1-chord_length));
	dist = 6371 * angle_distance;
	dist1 = dist / 1;
    
	//print out the distance in the requested format
	if(dist < 10)
	{
		printf("0");
		temp = dist/1;
		printf("%d", temp);
		printf(".");
		temp3 = dist*10;
		temp = temp3 / 1;
		printf("%d", temp % 10);
		temp3 = dist*100;
		temp = temp3 / 1;
		printf("%d", temp % 10);
	}
	else
	{
		temp = dist / 1;
		printf("%d", temp);
		printf(".");
		temp3 = dist*10;
		temp = temp3 / 1;
		printf("%d", temp % 10);
		temp3 = dist * 100;
		temp = temp3 / 1;
		printf("%d", temp%10);
	}																																												
 	return dist1;
}

//print out the dash line in stage2 that visualize the distance
int		print_dash(int dist1)
{
	int i = 0;
	int dec = 0, uni= 0;
	printf(" |");
	dist1++;
	if(dist1 <= 9)
	{
		for(i = 0; i < dist1; i++)
		{
			printf("-");	
		}
	}
	else
	{	
		dec = dist1 / 10;
		uni = dist1 % 10; 
		for(i = 0; i< dec; i++)		
			printf("---------+");
		for(i = 0 ; i<uni; i++)
			printf("-");
	}
	printf("\n");
	return (1);
 }
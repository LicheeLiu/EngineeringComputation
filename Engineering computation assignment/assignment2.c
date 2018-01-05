#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
		double x;
		double y;
		double sound_level;
}sound;

typedef struct{
		double x;
		double y;
}position;

double	L_sum_observe_point(int count, position point, sound loudspeaker[]);
double	stage1(sound loudspeaker[], int i);
int		stage3(int count, position point, sound loudspeaker[]);
double	L_origin(double origin_x, double origin_y, double speaker_x , double speaker_y, double level);
int		print_character(double a);
int		stage4(int count, position point, sound loudspeaker[]);

int		main()
{
	sound loudspeaker[99];
	position point;
	
	char	c;
	double	L_sum = 0;
	int 	count = 0;
	int 	i = 0;
	
	while(scanf("%c %lf %lf %lf\n", &c, &loudspeaker[i].x, &loudspeaker[i].y, &loudspeaker[i].sound_level)==4 && c == 'S') 
	{
		L_sum += stage1(loudspeaker, i);
		i++;
	}
	L_sum = 10 * log10(L_sum);
	count = i;
	
	printf("Stage 1\n==========\nNumber of loudspeakers: ");
	printf("%02d\n", count);
	printf("Sound level at (000.0, 000.0): %1.2lf dB\n\n", L_sum);
	
	//carry out stage 2 task
	printf("Stage 2\n==========\n");
	point.x = loudspeaker[i].x;
	point.y = loudspeaker[i].y;
	i = 0;
	L_sum_observe_point(count, point, loudspeaker);
	printf("Sound level at (%05.1lf, %05.1lf): %1.2lf dB\n",point.x, point.y, L_sum_observe_point(count, point, loudspeaker));
	while(scanf("%c %lf %lf\n", &c, &point.x, &point.y) == 3 && c == 'P')
	{
		printf("Sound level at (%05.1lf, %05.1lf): %1.2lf dB\n",point.x, point.y, L_sum_observe_point(count, point, loudspeaker));
	}
	stage3(count, point, loudspeaker);
	stage4(count, point, loudspeaker);
	return (0);
}

double	stage1(sound loudspeaker[], int i)
{
	double 	Level_origin = 0;
	double 	L_sum = 0;
	
	Level_origin = L_origin(0, 0, loudspeaker[i].x, loudspeaker[i].y, loudspeaker[i].sound_level);
	if(Level_origin > 0)
	{
		L_sum += pow(10, Level_origin / 10);
	}
	return L_sum;
}

//calculate the sum of sound level at the observe point
double	L_sum_observe_point(int count, position point, sound loudspeaker[])
{
	double	L_observe_point = 0;
	double 	L_sum_observe_point = 0;
	int 	i = 0;
	
	//sum up the sound of all loudspeakers 
	while(i < count)
		{
			L_observe_point = L_origin(point.x, point.y, loudspeaker[i].x, loudspeaker[i].y, loudspeaker[i].sound_level);
			i++;
			if(L_observe_point > 0)
			{
				L_sum_observe_point += pow(10, L_observe_point / 10);			
			}
		}
	L_sum_observe_point = 10 * log10(L_sum_observe_point);
	return (L_sum_observe_point);
}

//carry out stage 3 task
int		stage3(int count, position point, sound loudspeaker[])
{
	int		x = 0;
	int 	y = 0;
	int		count_below = 0;
	double 	L_sum_every_point;
	double 	percentage = 0;
	double temp = 0;

	//calculate sound level at each obervation point
	for(x = 4; x <= 308; x += 4)
		for(y = 4; y <= 308; y += 4)
		{
			point.x = x;
			point.y = y;
			L_sum_every_point = L_sum_observe_point(count, point, loudspeaker);
			if(L_sum_every_point <= 55)
			{
				count_below += 1;			
			}
		}
	temp = count_below;
	percentage = temp * 100 / 5929;
	printf("\nStage 3\n==========\n");
	printf("5929 points sampled\n");
	printf("%04d points (%05.2lf%%) have sound level <= 55 dB\n", count_below, percentage);
	return (1);
}

//carry out stage 4 task
int		stage4(int count, position point, sound loudspeaker[])
{
	int		x = 0;
	int 	y = 0;
	double 	L_sum_every_point;
	
	printf("\nStage 4\n==========\n");

	//print out symbol character at each sampling point
	for(y = 308; y >= 4; y -= 8)
	{	
		for(x = 2;x <= 310; x += 4)
		{
			point.x = x;
			point.y = y;
			L_sum_every_point = L_sum_observe_point(count, point, loudspeaker);
			print_character(L_sum_every_point);
		}
		printf("\n");
	}
	return (1);
}

//find out the corresponding symbol character
int		print_character(double a)
{
	if(a <= 55)
		printf("-");
	else if(a < 60)
		printf(" ");
	else if(a < 70)
		printf("6");
	else if(a < 80)
		printf(" ");
	else if(a < 90)
		printf("8");
	else if(a < 100)
		printf(" ");
	else if(a >= 100)
		printf("+");
	return (1);
}

//calculate the sound level for a single loudspeaker at the given origin
double	L_origin(double origin_x, double origin_y, double speaker_x , double speaker_y, double level)
{
	double distance = 0;
	double	L_origin = 0;
	double distance_x = 0;
	double distance_y = 0;
	
	distance_x = origin_x - speaker_x;
	distance_y = origin_y - speaker_y;
	distance = sqrt(distance_x * distance_x + distance_y * distance_y);
	L_origin = level + 20 * log10(1 / distance);
	return L_origin;
}
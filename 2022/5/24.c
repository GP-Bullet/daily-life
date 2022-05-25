#include<stdio.h>
#include<math.h>
struct point
{
	float x,y;
};
struct line
{
	struct point p1,p2,p3;
	float length;
};
int main()
{
	struct line a,b,c;
	printf("Please input x,y for the point #1:");
	scanf("%f %f",&a.p1.x,&a.p1.y);
	printf("Please input x,y for the point #2:");
	scanf("%f %f",&b.p2.x,&b.p2.y);
	printf("Please input x,y for the point #3:");
	scanf("%f %f",&c.p3.x,&c.p3.y);
	a.length=(float)sqrt((a.p1.x-a.p2.x)*(a.p1.x-a.p2.x)+(a.p1.y-a.p2.y)*(a.p1.y-a.p2.y));
	b.length=(float)sqrt((b.p1.x-b.p3.x)*(b.p1.x-b.p3.x)+(b.p1.y-b.p3.y)*(b.p1.y-b.p3.y));
	c.length=(float)sqrt((c.p2.x-c.p3.x)*(c.p2.x-c.p3.x)+(c.p2.y-c.p3.y)*(c.p2.y-c.p3.y));
	float l;
	l=a.length+b.length+c.length;
	printf("l=%.2f\n",l);
	return 0;
}
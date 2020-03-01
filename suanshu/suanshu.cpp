#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;

struct Grades
{
	double Average;
	double Median;
	int Mode;
	double Sd;
};

double getAverage(int* grades, int size);
double getMedian(int* grades, int size);
int getMode(int* grades, int size);
double getVariance(int* grades, int size);
double getSd(int* grades, int size);

int main()
{
	int data;
	cout << "How many grades do you wish :\t";
	cin >> data;							//Input the number.
	cout << "Enter the grades:\n";
	int* grades = new int[data];			//Dynamically allocate an array to hold grades.
	for (int i = 0; i < data; i++)
	{
		cin >> grades[i];					//Input the grades.
	}
	sort(grades, grades + data);			//Ascending.
	
	cout << "The sequence is: " << endl;
	for (int i = 0; i < data; i++)
	{
		cout << grades[i] << " ";			//Output the sort results.
	}
	cout << endl;

	double ave = getAverage(grades, data);
	cout << "Average: " << ave << endl;		//Output the average.
	double midian = getMedian(grades, data);
	cout << "Median: " << midian << endl;	//Output the median.
	int mode = getMode(grades, data);
	cout << "Mode: " << mode << endl;		//Output the mode number.
	double var = getVariance(grades, data);
	cout <<"Variance: " << var << endl;		//Output the variance.	
	double biaozhunc = getSd(grades, data);
	cout << "Sd: " << biaozhunc << endl;	//Output the standerd deviation.
	delete[]grades;							//Free dynamically allocated memory.
	grades = nullptr;						//Make grades a null pointer.

	return 0;
}

double getAverage(int* grades, int size)
{
	double total = 0, ave = 0.0;
	for (int i = 0; i < size; i++)
	{
		total+=grades[i];					//Calculate summation.
	}
	ave = total / size;						//Calculate average.
	return ave;
	
}

double getMedian(int* grades, int size)
{
	int mid = (size - 1) / 2;
	double median;
	if (size % 2 == 1)					    //Determines whether the array is odd.
	{
		median = *(grades + mid);		    //If so, take the middle value.
	}
	else
		median = (double)(*(grades + mid) + *(grades + (mid + 1))) / 2;		//Otherwise, take the average of the two middle values.

	return median;
}

int getMode(int* grades, int size)
{
	int mode = grades[0], mode_num = 1, n = 1;//n is occurrences.
	for (int i = 0; i < size; i++)
	{
		if ((i+1<size) && (grades[i] == grades[i+1]))//Judge equal.
		{
			n++;                            //Number of occurrences of the same number plus 1.
		}
		else
		{			
			if (n > mode_num)				
			{
				mode_num = n;				//Record the most times .
				
				mode = grades[i];			
			}
			n = 1;							//Initialize.
		}
	}
	return mode;
}

double getVariance(int*grades,int size)
{
	double variance, num,he = 0;			//Call Average.
	double ave = getAverage(grades,size);
	for (int i = 0;i < size; i++)
	{
		num = (grades[i] - ave) * (grades[i] - ave);//Square of computation.
		he += num;							//Summation.
		
	}
	variance = he / size;
	return variance;
}

double getSd(int* grades, int size)
{
	double fangcha = getVariance(grades, size);//Call Variance.
	double Standard;
	Standard = sqrt(fangcha);			       //Calculate standard deviation.
	return Standard;
}
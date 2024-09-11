#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo>
#include <map>

using namespace std;

template <typename T>
T GetInput(string inputMessage);
int GetChoice(string inputMessage, string* options, int optionsSize);
void Measurement();
void Gender();
float Weight();
float Height();
void BMI(float weight, float height);
float MHR(int age);
void THR(float mhr);
void BMR(float weight, float height, int age);
void HelpMenu();

bool isMet = true;
bool isMale = true;

int main()
{
	Measurement();
	Gender();
	float weight = Weight();
	float height = Height();
	BMI(weight, height);
	int age = GetInput<int>("What is your age?");
	float mhr = MHR(age);
	THR(mhr);
	BMR(weight, height, age);
	HelpMenu();
}
template <typename T>
T GetInput(string inputMessage)
{
	T userInput;
	while (true)
	{
		cout << inputMessage << endl;
		string rawInput;
		getline(cin, rawInput);
		try
		{
			istringstream ss(rawInput);
			ss >> userInput;
			if (ss.fail() || ss.peek() != EOF) {
				throw new exception;
			}
			break;
		}
		catch (...)
		{
			cout << "this input is invalid. please try the right data type" << endl;
		}
	}
	return userInput;
}
int GetChoice(string inputMessage, string* options, int optionsSize)
{
	int userInput = 0;
	while (true)
	{
		for (int x = 0; x < optionsSize; x++)
		{
			cout << endl << x + 1 << " ---> " << options[x] << endl;
		}
		cout << endl << inputMessage << endl;
		string rawInput;
		getline(cin, rawInput);
		try
		{
			istringstream ss(rawInput);
			ss >> userInput;
			if (ss.fail() || ss.peek() != EOF)
			{
					throw new exception;
			}
			else if (userInput < 1 || userInput > optionsSize)
			{
				throw new exception;
			}
			else
			{
				break;
			}
		}
		catch (...)
		{
			cout << "this input is invalid. please try the right data type" << endl;
		}
	}
	return userInput;
}
void Measurement()
{
	string* metricOptions = new string[2]{ "Metric", "Imperial" };
	int isMetric = GetChoice("what is your preferred unit of measurement", metricOptions, 2);
	if (isMetric == 2)
	{
		isMet = false;
	}
	delete[] metricOptions;
}
void Gender()
{
	string* genderOptions = new string[2]{ "Male", "Female" };
	int isGender = GetChoice("what is your gender?", genderOptions, 2);
	if (isGender == 2)
	{
		isMale = false;
	}
	delete[] genderOptions;
}
float Height()
{
	float height = 0.0;
	if (isMet == false)
	{
		height = GetInput<float>("what is your height in inches?");
		height = height * 2.54;
	}
	else
	{
		height = GetInput<float>("what is your height in centimeters?");
	}
	return height;
}
float Weight()
{
	float weight = 0.0;
	if (isMet == false)
	{
		weight = GetInput<float>("what is your weight in pounds?");
		weight = weight * 0.453592;
	}
	else
	{
		weight = GetInput<float>("what is your weight in kilograms?");
	}
	return weight;
}
void BMI(float weight, float height)
{
	map<string, float> bmiRange = { {"underwight", 18.4}, {"normal", 24.9}, {"overweight", 29.9}, {"obese", 100} };
	string bmiCategory = "";
	height = (float)height / 100;
	float bmi = weight / (height * height);
	for (auto const& range : bmiRange)
	{
		bmiCategory = range.first;
		if (bmi < range.second)
		{
			break;
		}
		 
	}
	cout << endl << "you have a BMI of: " << bmi << ", meaning, you are " << bmiCategory << endl;
}
float MHR(int age)
{
	float mhr = 0.0;
	if (age >= 40)
	{
		mhr = 208 - (0.75 * age);
	}
	else
	{
		mhr = 220 - age;
	}
	cout << endl << "your MHR is: " << mhr << endl;
	return mhr;
}
void THR(float mhr)
{
	float lhr = mhr * 0.5;
	float uhr = mhr * 0.85;
	float thr = (float)((lhr + uhr) / 2);
	cout << endl << "your THR is: " << thr << endl;
}
void BMR(float weight, float height, int age)
{
	float bmr = 0.0;
	if (isMale == true)
	{
		bmr = (10 * weight + 6.25 * height - 5 * age) + 5;
	}
	else
	{
		bmr = (10 * weight + 6.25 * height - 5 * age) - 161;
	}
	cout << endl << "your BMR is: " << bmr << endl;
}
void HelpMenu()
{
	string* helpOptions = new string[2]{ "yes", "no" };
	int helpChoice = GetChoice("Would you like any further information?", helpOptions, 2);
	map<string, string> equations{ {"Inches to Centimeters", "Inches x 2.54 "}, {"Pounds to Kilograms", "Pounds * 0.453592"}, {"BMI", "Weight in Kilograms / Height in Meters^2"}, {"MHR (Over 40)","208 - (0.75 * age)"}, {"MHR (Under 40)","220 - age"}, {"THR","((MHR x 0.5) + (MHR x 0.85)) / 2"}, {"BMR (Male)","(10 x weight in Kilograms + 6.25 x height in centimetres - 5 x age) + 5 "}, {"BMR (Female)","(10 x weight in Kilograms + 6.25 x height in centimetres - 5 x age) - 161 "} };
	if (helpChoice == 1)
	{
		for (pair<string, string> equation : equations)
		{
			cout << endl << equation.first << " --> " << equation.second << endl;
		}
	}
}



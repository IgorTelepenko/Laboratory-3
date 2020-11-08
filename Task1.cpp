#include <iostream>
#include<cmath>

using namespace std;

void number_into_fraction(float the_numb, int& numer, int& denum); // знайти чисельник і знаменник цього дійсного числа
void chain_fraction(int numer, int denum); //написати ланцюговий дріб


int main()
{

	float number;
	cout << " enter the real number: ";
	cin >> number;

	int n_numerator, n_denomerator; //чисельник і знаменник даного числа
	number_into_fraction(number, n_numerator, n_denomerator); //через посилання записує в змінні n_numerator і n_denomerator чисельник і знаменник введеного дійсного числа
	//cout << n_numerator << "/" << n_denomerator<<endl;

	chain_fraction(n_numerator, n_denomerator); //знайти і вивести ланцюговий дріб

	//cout << "1578/685: ";
	//chain_fraction(1578, 685);

	return 0;
}

void number_into_fraction(float the_numb, int& numer, int& denum)
{
	float const around_zero = 1E-5; //наближене знач. до 0, враховуючи що float змінні не є точними  
	int len_after_point = 0; //для рахування кількості знаків після коми в даному числі
	float int_part = 0, frac_part = 0, rubbish_int_parts;
	frac_part = modf(the_numb, &int_part); //розділяємо на цілу і дробову частину
	float auxiliary_frac = frac_part;
	while (fabs(auxiliary_frac / (pow(10, len_after_point))) >= around_zero) //поки не закінчаться знаки після коми (не рахуючи автоматичні значення в 10^(-5) і далі, що можуть автоматично записуватись в float змінних)
	{
		len_after_point++; //рахуємо к-сть знаків після коми
		auxiliary_frac *= 10; //так як ми відкинули цілу частину, беремо почергово кожну наступну цифру з дробової частини числа, отримуємо її як цілу частину після домноження на 10
		auxiliary_frac = modf(auxiliary_frac, &rubbish_int_parts); //відкидаємо перевірену цифру

	}

	denum = pow(10, len_after_point); //повертаємо значення знаменника 
	numer = int_part * denum + frac_part * denum; //повертаємо значення чисельника

}


void chain_fraction(int numer, int denum) //вивести ланцюговий дріб
{
	int int_part = 0;
	int count_brackets = 0; //кількість відкритих дужок в виведеному записі, які потрібно буде закрити в кінці ланцюгового дробу - для візуального вигляду

	int_part = numer / denum; //ціла частина дробу
	cout << int_part; //виводимо перший доданок
	while (int_part * denum != numer) //якщо отримується ціле число без дробової частини, ланцюговий дріб завершився
	{
		cout << " + 1/("; //продовжуємо ланцюговий дріб
		numer -= int_part * denum;


		swap(numer, denum);
		int_part = numer / denum; //нова ціла частина оберненого попереднього результату, яка записується як число в знаменнику ланц. дробу
		cout << int_part;
		count_brackets++;
	}

	for (int i = 0;i < count_brackets;i++)
	{
		cout << ")";	//закриваємо всі відкриті дужки в візуальному результаті
	}
}